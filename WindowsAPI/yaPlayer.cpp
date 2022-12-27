#include "yaPlayer.h"
#include "yaTime.h"
#include "yaSceneManager.h"
#include "yaInput.h"
#include "yaMissile.h"
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
#include "yaObject.h"

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
		//mAnimator->CreateAnimations(L"..\\Resources\\Animations\\Player\\Idle", L"HeroIdle");

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
			, Vector2(0.0f, 440.0f), Vector2(100.0f, 130.0f)
			, Vector2(10.0f, -20.0f), 25, 0.12f);


		mAnimator->Play(L"Idle", true);

		//mAnimator->FindEvents(L"Move")->mCompleteEvent = std::bind(&Player::AttackComplete, this);
		//mAnimator->GetCompleteEvent(L"Move") = std::bind(&Player::AttackComplete, this);

		mAnimator->FindEvents(L"Attack")->mCompleteEvent = std::bind(&Player::AttackComplete, this);
		mAnimator->GetCompleteEvent(L"Attack") = std::bind(&Player::AttackComplete, this);

		//mAnimator->FindEvents(L"Win")->mCompleteEvent = std::bind(&Player::AttackComplete, this);
		//mAnimator->GetCompleteEvent(L"Win") = std::bind(&Player::AttackComplete, this);

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
		case ya::Player::State::IDLE:
			Idle();
			break;
		case ya::Player::State::MOVE:
			Move(mDir);
			break;
		case ya::Player::State::ATTACK:
			Attack();
			break;
		case ya::Player::State::VICTORY:
			Victory();
			break;
		case ya::Player::State::DEAD:
			Dead();
			break;
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
		mState = State::IDLE;
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
					mState = State::ATTACK;
				}
				else if (nextObj->GetObjType() == eGameObjectType::Rock)
				{
					Rock* rock = dynamic_cast<Rock*>(nextObj);
					rock->Damaged(Direction::UP);
					mAnimator->Play(L"Attack", false);
					AttackEffect* atk = ya::object::Instantiate<AttackEffect>(nextObj->GetPos(), eColliderLayer::Effect);
					mState = State::ATTACK;
				}
			}
			else
			{
				mAnimator->Play(L"Move", true);
				mDir = Direction::UP;
				mDest = GetPos();
				mDest.y -= 80.0f;
				mState = State::MOVE;
				mIndex.y--;
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
					mState = State::ATTACK;
				} 
				else if (nextObj->GetObjType() == eGameObjectType::Rock)
				{
					Rock* rock = dynamic_cast<Rock*>(nextObj);
					rock->Damaged(Direction::DOWN);
					mAnimator->Play(L"Attack", false);
					AttackEffect* atk = ya::object::Instantiate<AttackEffect>(nextObj->GetPos(), eColliderLayer::Effect);
					mState = State::ATTACK;
				}
			}
			else
			{
				mAnimator->Play(L"Move", true);
				mDir = Direction::DOWN;
				mDest = GetPos();
				mDest.y += 80.0f;
				mState = State::MOVE;
				mIndex.y++;
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
					mState = State::ATTACK;
				}
				else if (nextObj->GetObjType() == eGameObjectType::Rock)
				{
					Rock* rock = dynamic_cast<Rock*>(nextObj);
					rock->Damaged(Direction::LEFT);
					mAnimator->Play(L"Attack", false);
					AttackEffect* atk = ya::object::Instantiate<AttackEffect>(nextObj->GetPos(), eColliderLayer::Effect);
					mState = State::ATTACK;
				}
			}
			else
			{
				mAnimator->Play(L"Move", true);
				mDir = Direction::LEFT;
				mDest = GetPos();
				mDest.x -= 80.0f;
				mState = State::MOVE;
				mIndex.x--;
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
					mState = State::ATTACK;
				}
				else if (nextObj->GetObjType() == eGameObjectType::Rock)
				{
					Rock* rock = dynamic_cast<Rock*>(nextObj);
					rock->Damaged(Direction::RIGHT);
					mAnimator->Play(L"Attack", false);
					AttackEffect* atk = ya::object::Instantiate<AttackEffect>(nextObj->GetPos(), eColliderLayer::Effect);
					mState = State::ATTACK;
				}
			}
			else {
				mAnimator->Play(L"Move", true);
				mDir = Direction::RIGHT;
				mDest = GetPos();
				mDest.x += 80.0f;
				mState = State::MOVE;
				mIndex.x++;
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
				mState = State::IDLE;
				mAnimator->Play(L"Idle", true);
			}
		}
			break;
		case Direction::RIGHT:
		{
			if (abs(pos.x - mDest.x) < 3.0f)
			{
				SetPos(mDest);
				mState = State::IDLE;
				mAnimator->Play(L"Idle", true);
			}
		}
			break;
		case Direction::UP:
		{
			if (abs(pos.y - mDest.y) < 3.0f)
			{
				SetPos(mDest);
				mState = State::IDLE;
				mAnimator->Play(L"Idle", true);
			}
		}
			break;
		case Direction::DOWN:
		{
			if (abs(pos.y - mDest.y) < 3.0f)
			{
				SetPos(mDest);
				mState = State::IDLE;
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

	void Player::Dead()
	{
	}
}
