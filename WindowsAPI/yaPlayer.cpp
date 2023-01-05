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
#include "yaSound.h"

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

		mMoveSound = Resources::Load<Sound>(L"character_move", L"..\\Resources\\Sound\\character_move_01.wav");
		mMonsterAttackSound = Resources::Load<Sound>(L"enemy_kick", L"..\\Resources\\Sound\\enemy_kick_01.wav");
		mStoneAttackSound = Resources::Load<Sound>(L"stone_kick", L"..\\Resources\\Sound\\stone_kick_01.wav");
		mDeathSound = Resources::Load<Sound>(L"player_death", L"..\\Resources\\Sound\\player_death_01.wav");
		mSuccessSound = Resources::Load<Sound>(L"succub_capture", L"..\\Resources\\Sound\\succub_capture_01.wav");
		mTransSound = Resources::Load<Sound>(L"screen_changer", L"..\\Resources\\Sound\\screen_changer_part1.wav");
		
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
			, Vector2(10.0f, -20.0f), 19, 0.3f);

		mAnimator->CreateAnimations(L"..\\Resources\\Animations\\Player\\Death", L"Death", Vector2(270, -100));

		mAnimator->CreateAnimations(L"..\\Resources\\Animations\\Player\\Move", L"rMove", Vector2(0.0f, -5.0f));
		
		mAnimator->CreateAnimations(L"..\\Resources\\Animations\\Player\\Idle", L"rIdle", Vector2(5.0f, -5.0f));

		mAnimator->CreateAnimations(L"..\\Resources\\Animations\\Player\\Attack", L"rAttack", Vector2(5.0f, -5.0f));

		mAnimator->Play(L"Idle", true);

		//mAnimator->FindEvents(L"Move")->mCompleteEvent = std::bind(&Player::AttackComplete, this);
		//mAnimator->GetCompleteEvent(L"Move") = std::bind(&Player::AttackComplete, this);

		mAnimator->FindEvents(L"Attack")->mCompleteEvent = std::bind(&Player::AttackComplete, this);
		mAnimator->GetCompleteEvent(L"Attack") = std::bind(&Player::AttackComplete, this);

		mAnimator->FindEvents(L"rAttack")->mCompleteEvent = std::bind(&Player::AttackComplete, this);
		mAnimator->GetCompleteEvent(L"rAttack") = std::bind(&Player::AttackComplete, this);

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
				mDeathSound->Play(false);
				mAnimator->Play(L"Death", false);
				mState = PlayerState::DEADSTART;
			}
			else if (KEY_DOWN(eKeyCode::A))
			{
				mDeathSound->Play(false);
				mAnimator->Play(L"Death", false);
				mState = PlayerState::DEADSTART;
			}
			else if (KEY_DOWN(eKeyCode::S))
			{
				mDeathSound->Play(false);
				mAnimator->Play(L"Death", false);
				mState = PlayerState::DEADSTART;
			}
			if (KEY_DOWN(eKeyCode::D))
			{
				mDeathSound->Play(false);
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
		//if (mFlip == true) // D키
		//{
		//	mAnimator->Play(L"Idle", true);
		//	
		//}
		//else if (mFlip == false) // A키
		//{
		//	mAnimator->Play(L"Idle", true);
		//}

		mAnimator->Play(L"Idle", true);
		mState = PlayerState::IDLE;
		mClearCheck = true; // 클리어 체크 초기화 시점 ( 어차피 공격없이 깨지는 스테이지가 없음 )
	}

	void Player::StageComplete()
	{
		mSumTime += Time::DeltaTime();
		
		if (mSumTime > 1.5f && mClearCheck)
		{
			SceneManager::ChangeScene(eSceneType::Dialog_pand);
			mSumTime = 0;
			mClearCheck = false;
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
					mMonsterAttackSound->Play(false);
					mAnimator->Play(L"Attack", false);
					AttackEffect* atk = ya::object::Instantiate<AttackEffect>(nextObj->GetPos(), eColliderLayer::Effect);
					mState = PlayerState::ATTACK;
					CountDown();
				}
				else if (nextObj->GetObjType() == eGameObjectType::Rock)
				{
					Rock* rock = dynamic_cast<Rock*>(nextObj);
					rock->Damaged(Direction::UP);
					mStoneAttackSound->Play(false);
					mAnimator->Play(L"Attack", false);
					AttackEffect* atk = ya::object::Instantiate<AttackEffect>(nextObj->GetPos(), eColliderLayer::Effect);
					mState = PlayerState::ATTACK;
					CountDown();
				}
			}
			else
			{
				mMoveSound->Play(false);
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
					mMonsterAttackSound->Play(false);
					mAnimator->Play(L"Attack", false);
					AttackEffect* atk = ya::object::Instantiate<AttackEffect>(nextObj->GetPos(), eColliderLayer::Effect);
					mState = PlayerState::ATTACK;
					CountDown();
				} 
				else if (nextObj->GetObjType() == eGameObjectType::Rock)
				{
					Rock* rock = dynamic_cast<Rock*>(nextObj);
					rock->Damaged(Direction::DOWN);
					mStoneAttackSound->Play(false);
					mAnimator->Play(L"Attack", false);
					AttackEffect* atk = ya::object::Instantiate<AttackEffect>(nextObj->GetPos(), eColliderLayer::Effect);
					mState = PlayerState::ATTACK;
					CountDown();
				}
			}
			else
			{
				mMoveSound->Play(false);
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
					mMonsterAttackSound->Play(false);
					mAnimator->Play(L"rAttack", false);
					AttackEffect* atk = ya::object::Instantiate<AttackEffect>(nextObj->GetPos(), eColliderLayer::Effect);
					mState = PlayerState::ATTACK;
					CountDown();
					mFlip = false;
				}
				else if (nextObj->GetObjType() == eGameObjectType::Rock)
				{
					Rock* rock = dynamic_cast<Rock*>(nextObj);
					rock->Damaged(Direction::LEFT);
					mStoneAttackSound->Play(false);
					mAnimator->Play(L"rAttack", false);
					AttackEffect* atk = ya::object::Instantiate<AttackEffect>(nextObj->GetPos(), eColliderLayer::Effect);
					mState = PlayerState::ATTACK;
					CountDown();
					mFlip = false;
				}
			}
			else
			{
				mMoveSound->Play(false);
				mAnimator->Play(L"rMove", true);
				mDir = Direction::LEFT;
				mDest = GetPos();
				mDest.x -= 80.0f;
				MoveEffect* mv = ya::object::Instantiate<MoveEffect>(GetPos(), eColliderLayer::Effect);
				mState = PlayerState::MOVE;
				mIndex.x--;
				CountDown();
				mFlip = false;
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
					mMonsterAttackSound->Play(false);
					mAnimator->Play(L"Attack", false);
					AttackEffect* atk = ya::object::Instantiate<AttackEffect>(nextObj->GetPos(), eColliderLayer::Effect);
					mState = PlayerState::ATTACK;
					CountDown();
				}
				else if (nextObj->GetObjType() == eGameObjectType::Rock)
				{
					Rock* rock = dynamic_cast<Rock*>(nextObj);
					rock->Damaged(Direction::RIGHT);
					mStoneAttackSound->Play(false);
					mAnimator->Play(L"Attack", false);
					AttackEffect* atk = ya::object::Instantiate<AttackEffect>(nextObj->GetPos(), eColliderLayer::Effect);
					mState = PlayerState::ATTACK;
					CountDown();
				}
				else if (nextObj->GetObjType() == eGameObjectType::NPC)
				{
					mSuccessSound->Play(false);
					mAnimator->Play(L"Success", false);
				}
			}
			else
			{
				mMoveSound->Play(false);
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
			mTransSound->Play(false);
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
