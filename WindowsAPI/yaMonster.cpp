#include "yaMonster.h"
#include "yaTime.h"
#include "yaSceneManager.h"
#include "yaInput.h"
#include "yaScene.h"
#include "yaImage.h"
#include "yaResources.h"
#include "yaAnimator.h"
#include "yaCollider.h"
#include "yaCamera.h"
#include "yaPlayer.h"

namespace ya
{
	//Monster::Monster()
	//{
	//	SetName(L"Monster");
	//	SetPos({ 870, 380 });
	//	SetScale({ 0.8333f, 0.8333f });

	//	if (mImage == nullptr)
	//	{
	//		mImage = Resources::Load<Image>(L"Monster", L"..\\Resources\\Image\\Monster.bmp");
	//	}

	//	mAnimator = new Animator();

	//	mAnimator->CreateAnimation(L"Idle", mImage
	//		, Vector2(0.0f, 0.0f), Vector2(100.0f, 120.0f)
	//		, Vector2(5.0f, -20.0f), 12, 0.12f);

	//	mAnimator->CreateAnimation(L"Damaged", mImage
	//		, Vector2(0.0f, 220.0f), Vector2(100.0f, 120.0f)
	//		, Vector2(5.0f, -20.0f), 13, 0.12f);

	//	mAnimator->Play(L"Idle", true);

	//	mAnimator->FindEvents(L"Damaged")->mCompleteEvent = std::bind(&Monster::WalkComplete, this);
	//	mAnimator->GetCompleteEvent(L"Damaged") = std::bind(&Monster::WalkComplete, this);

	//	//AddComponent(new Animator());
	//	//AddComponent(new Collider());
	//	AddComponent(mAnimator);
	//}

	Monster::Monster(Vector2 position)
	{
		SetName(L"Monster");
		SetPos(position);
		SetScale({ 0.8333f, 0.8333f });
		mDir = Direction::NONE;

		if (mImage == nullptr)
		{
			mImage = Resources::Load<Image>(L"Monster", L"..\\Resources\\Image\\Monster.bmp");
		}

		mAnimator = new Animator();
		AddComponent(mAnimator);

		mAnimator->CreateAnimation(L"Idle", mImage
			, Vector2(0.0f, 0.0f), Vector2(100.0f, 130.0f)
			, Vector2(10.0f, -20.0f), 12, 0.12f);

		mAnimator->CreateAnimation(L"Damaged", mImage
			, Vector2(0.0f, 220.0f), Vector2(100.0f, 130.0f)
			, Vector2(10.0f, -20.0f), 6, 0.12f);

		mAnimator->Play(L"Idle", true);

		mAnimator->FindEvents(L"Damaged")->mCompleteEvent = std::bind(&Monster::WalkComplete, this);
		mAnimator->GetCompleteEvent(L"Damaged") = std::bind(&Monster::WalkComplete, this);

		//mCollider = new Collider();
		//AddComponent(mCollider);
		//mCollider->SetScale(Vector2(50.0f, 50.0f));

	}

	Monster::~Monster()
	{

	}

	void Monster::Tick()
	{
		GameObject::Tick();

		switch (mState)
		{
		case ya::Monster::State::IDLE:
			Idle();
			break;
		case ya::Monster::State::MOVE:
			Move(mDir);
			break;
		case ya::Monster::State::DAMAGED:
			Damaged();
			break;
		case ya::Monster::State::DEAD:
			Dead();
			break;
		}

		/*Vector2 pos = GetPos();

		SetPos(pos);*/
	}

	void Monster::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Monster::OnCollisionEnter(Collider* other)
	{
		mAnimator->Play(L"Damaged", true);
		
		//mDir = other->GetOwner().

		Player* player = dynamic_cast<Player*>(other->GetOwner());
		mDir = player->GetDir();

		mDest = GetPos();
		
		if (mDir == Direction::LEFT)
		{
			mDest.x -= 80.0f;
		}
		else if (mDir == Direction::RIGHT)
		{
			mDest.x += 80.0f;
		}
		else if (mDir == Direction::UP)
		{
			mDest.y -= 80.0f;
		}
		else if (mDir == Direction::DOWN)
		{
			mDest.y += 80.0f;
		}
		
		mState = State::MOVE;
		
	}

	void Monster::OnCollisionStay(Collider* other)
	{
		
	}

	void Monster::OnCollisionExit(Collider* other)
	{
		
	}

	void Monster::WalkComplete()
	{
		mAnimator->Play(L"Idle", true);
	}

	void Monster::Idle()
	{
		
	}

	void Monster::Move(Direction dir)
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
		}
	}

	void Monster::Damaged()
	{
		
	}

	void Monster::Dead()
	{
	}
}
