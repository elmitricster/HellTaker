#include "yaRock.h"
#include "yaTime.h"
#include "yaSceneManager.h"
#include "yaInput.h"
#include "yaScene.h"
#include "yaImage.h"
#include "yaResources.h"
#include "yaAnimator.h"
#include "yaCollider.h"
#include "yaCamera.h"
#include "yaTileMap.h"
#include "yaSound.h"

namespace ya
{
	Rock::Rock()
	{
		
	}

	Rock::Rock(Vector2 position)
	{
		mGameObjType = eGameObjectType::Rock;
		SetName(L"Rock");
		SetPos(position);
		SetScale({ 0.8333f, 0.8333f });
		mDir = Direction::NONE;

		if (mImage == nullptr)
		{
			mImage = Resources::Load<Image>(L"Rock", L"..\\Resources\\Image\\Rock01.bmp");
		}

		mMoveSound = Resources::Load<Sound>(L"stone_move", L"..\\Resources\\Sound\\stone_move_01.wav");

		//AddComponent(new Collider());
	}

	Rock::~Rock()
	{

	}

	void Rock::Tick()
	{
		GameObject::Tick();

		switch (mState)
		{
		case ya::Rock::State::IDLE:
			Idle();
			break;
		case ya::Rock::State::MOVE:
			Move(mDir);
			break;
		case ya::Rock::State::DAMAGED:
			Damaged(mDir);
			break;
		case ya::Rock::State::DEAD:
			Dead();
			break;
		}
	}

	void Rock::Render(HDC hdc)
	{
		Vector2 pos = GetPos();
		Vector2 scale = GetScale();

		Vector2 finalPos;
		finalPos.x = (pos.x - mImage->GetWidth() * (scale.x / 2.0f));
		finalPos.y = (pos.y - mImage->GetHeight() * (scale.y / 2.0f));

		Vector2 rect;
		rect.x = mImage->GetWidth() * scale.x;
		rect.y = mImage->GetHeight() * scale.y;

		finalPos = Camera::CalculatePos(finalPos);

		TransparentBlt(hdc, finalPos.x, finalPos.y, rect.x, rect.y
			, mImage->GetDC(), 0, 0, mImage->GetWidth(), mImage->GetHeight()
			, RGB(255, 0, 255));
		
		GameObject::Render(hdc);
	}

	void Rock::Idle()
	{
		
	}

	void Rock::Move(Direction mDir)
	{
		Vector2 pos = GetPos();
		pos = math::lerp(pos, mDest, 0.05f);
		SetPos(pos);

		switch (mDir)
		{
		case Direction::LEFT:
		{
			if (abs(mDest.x - pos.x) < 5.0f)
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

	void Rock::Damaged(Direction dir)
	{
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
			if (other->GetObjType() == eGameObjectType::Wall)
			{

			}
			else if (other->GetObjType() == eGameObjectType::Rock)
			{

			}
		}
		else
		{
			mMoveSound->Play(false);
			TileMap::PushGameObject(mIndex, nullptr);
			mState = State::MOVE;
		}
		
	}

	void Rock::Dead()
	{

	}

	void Rock::SetImage(const std::wstring& key, const std::wstring& fileName)
	{
		std::wstring path = L"..\\Resources\\Image\\";
		path += fileName;

		mImage = Resources::Load<Image>(key, path);
	}

}