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

namespace ya
{
	Player::Player()
		: mSpeed(1.0f)
	{
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

		mAnimator->CreateAnimation(L"Win", mImage
			, Vector2(0.0f, 440.0f), Vector2(100.0f, 130.0f)
			, Vector2(10.0f, -20.0f), 25, 0.12f);


		mAnimator->Play(L"Idle", true);

		mAnimator->FindEvents(L"Move")->mCompleteEvent = std::bind(&Player::WalkComplete, this);
		mAnimator->GetCompleteEvent(L"Move") = std::bind(&Player::WalkComplete, this);

		mAnimator->FindEvents(L"Attack")->mCompleteEvent = std::bind(&Player::WalkComplete, this);
		mAnimator->GetCompleteEvent(L"Attack") = std::bind(&Player::WalkComplete, this);

		mAnimator->FindEvents(L"Win")->mCompleteEvent = std::bind(&Player::WalkComplete, this);
		mAnimator->GetCompleteEvent(L"Win") = std::bind(&Player::WalkComplete, this);

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

		//Vector2 pos = GetPos();

		//if (KEY_PREESE(eKeyCode::W))
		//{
		//	pos.y -= 120.0f * Time::DeltaTime();
		//}
		//if (KEY_PREESE(eKeyCode::S))
		//{
		//	pos.y += 120.0f * Time::DeltaTime();
		//}
		//if (KEY_PREESE(eKeyCode::A))
		//{
		//	pos.x -= 120.0f * Time::DeltaTime();

		//	//Vector2 pos = GetPos();
		//	//pos = math::lerp(pos, dest, 0.003f);
		//	//SetPos(pos);
		//}
		//if (KEY_PREESE(eKeyCode::D))
		//{
		//	pos.x += 120.0f * Time::DeltaTime();
		//}
		//SetPos(pos);

	}

	void Player::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Player::OnCollisionEnter(Collider* other)
	{	
		mAnimator->Play(L"Attack", true);
		mState = State::IDLE;
	}

	void Player::OnCollisionStay(Collider* other)
	{
		
	}

	void Player::OnCollisionExit(Collider* other)
	{
		//mCollider->SetOffset(Vector2(0.0f, 0.0f));
		//mState = State::IDLE;
	}

	void Player::WalkComplete()
	{
		mAnimator->Play(L"Idle", true);
	}

	void Player::Idle()
	{
		if (KEY_DOWN(eKeyCode::W))
		{	
			//mCollider->SetOffset(Vector2(0.0f, -30.0f));
			mAnimator->Play(L"Move", true);
			mDir = Direction::UP;
			mDest = GetPos();
			mDest.y -= 80.0f;
			mState = State::MOVE;

			/*TileMap* tile = new TileMap();
			tile->ChangeTileMap(this, -1, 0);*/
			
		}
		if (KEY_DOWN(eKeyCode::S))
		{
			//mCollider->SetOffset(Vector2(0.0f, 30.0f));

			mAnimator->Play(L"Move", true);
			mDir = Direction::DOWN;
			mDest = GetPos();
			mDest.y += 80.0f;
			mState = State::MOVE;
		}
		if (KEY_DOWN(eKeyCode::A))
		{	
			//mCollider->SetOffset(Vector2(-30.0f, 0.0f));

			mAnimator->Play(L"Move", true);
			mDir = Direction::LEFT;
			mDest = GetPos();
			mDest.x -= 80.0f;
			mState = State::MOVE;
		}
		if (KEY_DOWN(eKeyCode::D))
		{
			//mCollider->SetOffset(Vector2(30.0f, 0.0f));

			mAnimator->Play(L"Move", true);
			mDir = Direction::RIGHT;
			mDest = GetPos();
			mDest.x += 80.0f;
			mState = State::MOVE;
		}
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
				//mCollider->SetOffset(Vector2(0.0f, 0.0f));
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
				//mCollider->SetOffset(Vector2(0.0f, 0.0f));
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
				//mCollider->SetOffset(Vector2(0.0f, 0.0f));
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
				//mCollider->SetOffset(Vector2(0.0f, 0.0f));
			}
		}
			break;
		case Direction::NONE:
			break;
		}
	}

	void Player::Attack()
	{	
		mAnimator->Play(L"Attack", true);
		//mState = State::IDLE;
	}

	void Player::Victory()
	{
	}

	void Player::Dead()
	{
	}
}
