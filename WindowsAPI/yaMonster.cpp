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
#include "yaTileMap.h"

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
		mGameObjType = eGameObjectType::Monster;
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
			Damaged(mDir);
			break;
		case ya::Monster::State::DEAD:
			Dead();
			break;
		}
	}

	void Monster::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Monster::OnCollisionEnter(Collider* other)
	{
		
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

	void Monster::Move(Direction mDir)
	{	
		Vector2 pos = GetPos();
		pos = math::lerp(pos, mDest, 0.05f);
		SetPos(pos);

		switch (mDir)
		{
		case Direction::LEFT:
		{	
			if (abs(mDest.x- pos.x) < 5.0f)
			{
				SetPos(mDest);
				mIndex.x--;
				TileMap::MoveGameObject(mIndex, this);
				mState = State::IDLE;
			}
		}
		break;
		case Direction::RIGHT:
		{	
			if (abs(pos.x - mDest.x) < 5.0f)
			{
				SetPos(mDest);
				mIndex.x++;
				TileMap::MoveGameObject(mIndex, this);
				mState = State::IDLE;
			}
		}
		break;
		case Direction::UP:
		{	
			if (abs(pos.y - mDest.y) < 5.0f)
			{
				SetPos(mDest);
				mIndex.y--;
				TileMap::MoveGameObject(mIndex, this);
				mState = State::IDLE;
			}
		}
		break;
		case Direction::DOWN:
		{	
			if (abs(pos.y - mDest.y) < 5.0f)
			{
				SetPos(mDest);
				mIndex.y++;
				TileMap::MoveGameObject(mIndex, this);
				mState = State::IDLE;
			}
		}
		break;
		}
	}

	void Monster::Damaged(Direction dir)
	{
		mAnimator->Play(L"Damaged", true);
		mDest = GetPos();

		Index index = mIndex;

		if (dir == Direction::LEFT)
		{
			mDir = Direction::LEFT;
			mDest.x -= 80.0f;
			index.x--;
		}
		else if (dir == Direction::RIGHT)
		{
			mDir = Direction::RIGHT;
			mDest.x += 80.0f;
			index.x++;
		}
		else if (dir == Direction::UP)
		{
			mDir = Direction::UP;
			mDest.y -= 80.0f;
			index.y--;
		}
		else if (dir == Direction::DOWN)
		{
			mDir = Direction::DOWN;
			mDest.y += 80.0f;
			index.y++;
		}

		GameObject* other = TileMap::GetGameObject(index);
		if (other != nullptr)
		{
			this->Death();
			TileMap::PushGameObject(mIndex, nullptr);
		}

		mState = State::MOVE;
	}

	void Monster::Dead()
	{
	}
}
