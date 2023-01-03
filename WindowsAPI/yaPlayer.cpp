#include "yaPlayer.h"
#include "yaTime.h"
#include "Common.h"
#include "yaSceneManager.h"
#include "yaInput.h"
#include "yaScene.h"
#include "yaImage.h"
#include "yaResources.h"
#include "yaAnimator.h"
#include "yaCollider.h"
#include "yaCamera.h"
#include "yaBackPack.h"
#include "yaRigidbody.h"
#include "yaUIManager.h"
#include "yaTileMap.h"
#include "yaMonster.h"
#include "yaRock.h"
#include "yaAttackEffect.h"
#include "yaMoveEffect.h"
#include "yaObject.h"
#include "yaTransition.h"
#include "yaPlayScene.h"
#include "def.h"

namespace ya
{
	Player::Player()
		: mSpeed(1.0f)
	{
		mGameObjType = eGameObjectType::Player;
		SetName(L"Player");
		SetPos({ 960.0f, 240.0f });
		SetScale({ 0.8333f, 0.8333f });
		
		if (mImage == nullptr)
		{
			mImage = Resources::Load<Image>(L"Player", L"..\\Resources\\Image\\Hero.bmp");
		}
		
		mAnimator = new Animator();

		mAnimator->CreateAnimation(L"Idle", mImage
			, Vector2(0.0f, 0.0f), Vector2(100.0f, 130.0f)
			, Vector2(10.0f, -20.0f), 12, 0.12f);

		mAnimator->CreateAnimation(L"Move", mImage
			, Vector2(0.0f, 440.0f), Vector2(100.0f, 130.0f)
			, Vector2(10.0f, -20.0f), 6, 0.12f);

		mAnimator->CreateAnimation(L"Attack", mImage
			, Vector2(0.0f, 220.0f), Vector2(100.0f, 130.0f)
			, Vector2(10.0f, -20.0f), 13, 0.12f);

		mAnimator->CreateAnimation(L"Success", mImage
			, Vector2(600.0f, 440.0f), Vector2(100.0f, 130.0f)
			, Vector2(10.0f, -20.0f), 19, 0.15f);

		mAnimator->CreateAnimations(L"..\\Resources\\Animations\\Player\\Death", L"Death", Vector2(270, -100));

		mAnimator->Play(L"Idle", true);

		//mAnimator->FindEvents(L"Move")->mCompleteEvent = std::bind(&Player::AttackComplete, this);
		//mAnimator->GetCompleteEvent(L"Move") = std::bind(&Player::AttackComplete, this);

		mAnimator->FindEvents(L"Attack")->mCompleteEvent = std::bind(&Player::AttackComplete, this);
		mAnimator->GetCompleteEvent(L"Attack") = std::bind(&Player::AttackComplete, this);

		//mAnimator->FindEvents(L"Death")->mEndEvent = std::bind(&Player::DeathComplete, this);
		//mAnimator->GetEndEvent(L"Death") = std::bind(&Player::DeathComplete, this);

		mAnimator->FindEvents(L"Success")->mCompleteEvent = std::bind(&Player::StageComplete, this);
		mAnimator->GetCompleteEvent(L"Success") = std::bind(&Player::StageComplete, this);

		AddComponent(mAnimator);

		//mCollider = new Collider();
		//AddComponent(mCollider);
		//mCollider->SetScale(Vector2(50.0f, 50.0f));

	}

	Player::~Player()
	{

	}

	void Player::Tick()
	{
		GameObject::Tick();

		switch (mState)
		{
		case PlayerState::IDLE:
			Idle();
			break;
		case PlayerState::MOVE:
			Move(mDir);
			break;
		case PlayerState::ATTACK:
			Attack();
			break;
		case PlayerState::VICTORY:
			Victory();
			break;
		case PlayerState::DEADSTART:
			DeadStart();
			break;
		case PlayerState::DEAD:
			Dead();
			break;
		}

		if (mpScene!=nullptr && mpScene->GetCurMoveCnt() < 0)
		{
			if (KEY_DOWN(eKeyCode::W))
			{
				mAnimator->Play(L"Death", false);
				mState = PlayerState::DEADSTART;
			}
			else if (KEY_DOWN(eKeyCode::A))
			{
				mAnimator->Play(L"Death", false);
				mState = PlayerState::DEADSTART;
			}
			else if (KEY_DOWN(eKeyCode::S))
			{
				mAnimator->Play(L"Death", false);
				mState = PlayerState::DEADSTART;
			}
			if (KEY_DOWN(eKeyCode::D))
			{
				mAnimator->Play(L"Death", false);
				mState = PlayerState::DEADSTART;
			}
		}

		


	}

	void Player::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Player::OnCollisionEnter(Collider* other)
	{	

	}

	void Player::OnCollisionStay(Collider* other)
	{
		
	}

	void Player::OnCollisionExit(Collider* other)
	{

	}

	void Player::AttackComplete()
	{
		mAnimator->Play(L"Idle", true);
		mState = PlayerState::IDLE;
	}

	void Player::StageComplete()
	{
		mSumTime += Time::DeltaTime();
		
		if (mSumTime > 0.7f)
		{
			SceneManager::ChangeScene(eSceneType::Dialog_pand);
		}
	}

	void Player::Idle()
	{
		if (KEY_DOWN(eKeyCode::W))
		{
			Index nextIndex = mIndex;
			nextIndex.y--;

			GameObject* nextObj = TileMap::GetGameObject(nextIndex);

			if (nextObj)
			{	
				if (nextObj->GetObjType() == eGameObjectType::Monster)
				{
					Monster* monster = dynamic_cast<Monster*>(nextObj);
					monster->Damaged(Direction::UP);
					mAnimator->Play(L"Attack", false);
					AttackEffect* atk = ya::object::Instantiate<AttackEffect>(nextObj->GetPos(), eColliderLayer::Effect);
					mState = PlayerState::ATTACK;
					CountDown();
				}
				else if (nextObj->GetObjType() == eGameObjectType::Rock)
				{
					Rock* rock = dynamic_cast<Rock*>(nextObj);
					rock->Damaged(Direction::UP);
					mAnimator->Play(L"Attack", false);
					AttackEffect* atk = ya::object::Instantiate<AttackEffect>(nextObj->GetPos(), eColliderLayer::Effect);
					mState = PlayerState::ATTACK;
					CountDown();
				}
			}
			else
			{
				mAnimator->Play(L"Move", true);
				mDir = Direction::UP;
				mDest = GetPos();
				mDest.y -= 80.0f;
				MoveEffect* mv = ya::object::Instantiate<MoveEffect>(GetPos(), eColliderLayer::Effect);
				mState = PlayerState::MOVE;
				mIndex.y--;
				CountDown();
			}
		}
		if (KEY_DOWN(eKeyCode::S))
		{
			Index nextIndex = mIndex;
			nextIndex.y++;

			GameObject* nextObj = TileMap::GetGameObject(nextIndex);

			if (nextObj)
			{
				if (nextObj->GetObjType() == eGameObjectType::Monster)
				{
					Monster* monster = dynamic_cast<Monster*>(nextObj);
					monster->Damaged(Direction::DOWN);
					mAnimator->Play(L"Attack", false);
					AttackEffect* atk = ya::object::Instantiate<AttackEffect>(nextObj->GetPos(), eColliderLayer::Effect);
					mState = PlayerState::ATTACK;
					CountDown();
				} 
				else if (nextObj->GetObjType() == eGameObjectType::Rock)
				{
					Rock* rock = dynamic_cast<Rock*>(nextObj);
					rock->Damaged(Direction::DOWN);
					mAnimator->Play(L"Attack", false);
					AttackEffect* atk = ya::object::Instantiate<AttackEffect>(nextObj->GetPos(), eColliderLayer::Effect);
					mState = PlayerState::ATTACK;
					CountDown();
				}
			}
			else
			{
				mAnimator->Play(L"Move", true);
				mDir = Direction::DOWN;
				mDest = GetPos();
				mDest.y += 80.0f;
				MoveEffect* mv = ya::object::Instantiate<MoveEffect>(GetPos(), eColliderLayer::Effect);
				mState = PlayerState::MOVE;
				mIndex.y++;
				CountDown();
			}
		}
		if (KEY_DOWN(eKeyCode::A))
		{
			Index nextIndex = mIndex;
			nextIndex.x--;

			GameObject* nextObj = TileMap::GetGameObject(nextIndex);

			if (nextObj)
			{
				if (nextObj->GetObjType() == eGameObjectType::Monster)
				{
					Monster* monster = dynamic_cast<Monster*>(nextObj);
					monster->Damaged(Direction::LEFT);
					mAnimator->Play(L"Attack", false);
					AttackEffect* atk = ya::object::Instantiate<AttackEffect>(nextObj->GetPos(), eColliderLayer::Effect);
					mState = PlayerState::ATTACK;
					CountDown();
				}
				else if (nextObj->GetObjType() == eGameObjectType::Rock)
				{
					Rock* rock = dynamic_cast<Rock*>(nextObj);
					rock->Damaged(Direction::LEFT);
					mAnimator->Play(L"Attack", false);
					AttackEffect* atk = ya::object::Instantiate<AttackEffect>(nextObj->GetPos(), eColliderLayer::Effect);
					mState = PlayerState::ATTACK;
					CountDown();
				}
			}
			else
			{
				mAnimator->Play(L"Move", true);
				mDir = Direction::LEFT;
				mDest = GetPos();
				mDest.x -= 80.0f;
				MoveEffect* mv = ya::object::Instantiate<MoveEffect>(GetPos(), eColliderLayer::Effect);
				mState = PlayerState::MOVE;
				mIndex.x--;
				CountDown();
			}
		}
		if (KEY_DOWN(eKeyCode::D))
		{
			Index nextIndex = mIndex;
			nextIndex.x++;

			GameObject* nextObj = TileMap::GetGameObject(nextIndex);

			if (nextObj)
			{
				if (nextObj->GetObjType() == eGameObjectType::Monster)
				{
					Monster* monster = dynamic_cast<Monster*>(nextObj);
					monster->Damaged(Direction::RIGHT);
					mAnimator->Play(L"Attack", false);
					AttackEffect* atk = ya::object::Instantiate<AttackEffect>(nextObj->GetPos(), eColliderLayer::Effect);
					mState = PlayerState::ATTACK;
					CountDown();
				}
				else if (nextObj->GetObjType() == eGameObjectType::Rock)
				{
					Rock* rock = dynamic_cast<Rock*>(nextObj);
					rock->Damaged(Direction::RIGHT);
					mAnimator->Play(L"Attack", false);
					AttackEffect* atk = ya::object::Instantiate<AttackEffect>(nextObj->GetPos(), eColliderLayer::Effect);
					mState = PlayerState::ATTACK;
					CountDown();
				}
				else if (nextObj->GetObjType() == eGameObjectType::NPC)
				{
					mAnimator->Play(L"Success", false);
				}
			}
			else {
				mAnimator->Play(L"Move", true);
				mDir = Direction::RIGHT;
				mDest = GetPos();
				mDest.x += 80.0f;
				MoveEffect* mv = ya::object::Instantiate<MoveEffect>(GetPos(), eColliderLayer::Effect);
				mState = PlayerState::MOVE;
				mIndex.x++;
				CountDown();
			}
		}

		TileMap::MoveGameObject(mIndex, this);
	}

	void Player::Move(Direction dir)
	{
		Vector2 pos = GetPos();
		pos = math::lerp(pos, mDest, 0.05f);
		SetPos(pos);

		switch (mDir)
		{
		case Direction::LEFT:
		{
			if (abs(pos.x - mDest.x) < 3.0f)
			{
				SetPos(mDest);
				mState = PlayerState::IDLE;
				mAnimator->Play(L"Idle", true);
			}
		}
			break;
		case Direction::RIGHT:
		{
			if (abs(pos.x - mDest.x) < 3.0f)
			{
				SetPos(mDest);
				mState = PlayerState::IDLE;
				mAnimator->Play(L"Idle", true);
			}
		}
			break;
		case Direction::UP:
		{
			if (abs(pos.y - mDest.y) < 3.0f)
			{
				SetPos(mDest);
				mState = PlayerState::IDLE;
				mAnimator->Play(L"Idle", true);
			}
		}
			break;
		case Direction::DOWN:
		{
			if (abs(pos.y - mDest.y) < 3.0f)
			{
				SetPos(mDest);
				mState = PlayerState::IDLE;
				mAnimator->Play(L"Idle", true);
			}
		}
			break;
		case Direction::NONE:
			break;
		}
	}

	void Player::Attack()
	{	
		//mAnimator->Play(L"Attack", true);
		//mState = State::IDLE;
	}

	void Player::Victory()
	{
		mAnimator->Play(L"Success", false);
	}

	void Player::DeadStart()
	{
		mSumTime += Time::DeltaTime();

		if (mSumTime > 1.5f)
		{
			UIManager::Push(eUIType::TPANEL);
			mState = PlayerState::DEAD;

			mSumTime = 0;
		}
	}

	void Player::Dead()
	{
		mSumTime += Time::DeltaTime();

		TileMap::MoveGameObject(Index(7, 2), this);
		
		//SetPos({ -100.0f, -100.0f });
	
		if (mSumTime > 1.5f)
		{
			SetPos({ 960.0f, 240.0f });
			mAnimator->Play(L"Idle", true);
			SetState(PlayerState::IDLE);
			mpScene->SetCurMoveCnt(mpScene->GetInitMoveCnt());
			mpScene->Restart();

			mSumTime = 0;
		}
	}

	void Player::CountDown(int mNum)
	{
		mpScene->SetCurMoveCnt(mpScene->GetCurMoveCnt() - mNum);
	}

	void Player::GetDamaged(int damage)
	{
		CountDown(damage);

		// 데미지 이펙트 넣기

	}

}
