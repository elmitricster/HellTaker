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

namespace ya
{
	Monster::Monster()
	{
		SetName(L"Monster");
		SetPos({ 870, 380 });
		SetScale({ 1.0f, 1.0f });

		if (mImage == nullptr)
		{
			mImage = Resources::Load<Image>(L"Monster", L"..\\Resources\\Image\\Monster.bmp");
		}

		mAnimator = new Animator();

		mAnimator->CreateAnimation(L"Idle", mImage
			, Vector2(0.0f, 0.0f), Vector2(100.0f, 120.0f)
			, Vector2(5.0f, -20.0f), 12, 0.12f);

		mAnimator->CreateAnimation(L"Damaged", mImage
			, Vector2(0.0f, 220.0f), Vector2(100.0f, 120.0f)
			, Vector2(5.0f, -20.0f), 13, 0.12f);

		mAnimator->Play(L"Idle", true);

		mAnimator->FindEvents(L"Damaged")->mCompleteEvent = std::bind(&Monster::WalkComplete, this);
		mAnimator->GetCompleteEvent(L"Damaged") = std::bind(&Monster::WalkComplete, this);

		//AddComponent(new Animator());
		AddComponent(new Collider());
		AddComponent(mAnimator);
	}

	Monster::Monster(Vector2 position)
	{
		SetName(L"Monster");
		SetPos(position);
		SetScale({ 1.0f, 1.0f });

		if (mImage == nullptr)
		{
			mImage = Resources::Load<Image>(L"Monster", L"..\\Resources\\Image\\Monster.bmp");
		}

		mAnimator = new Animator();

		mAnimator->CreateAnimation(L"Idle", mImage
			, Vector2(0.0f, 0.0f), Vector2(100.0f, 130.0f)
			, Vector2(5.0f, -20.0f), 12, 0.12f);

		mAnimator->CreateAnimation(L"Damaged", mImage
			, Vector2(0.0f, 220.0f), Vector2(100.0f, 130.0f)
			, Vector2(5.0f, -20.0f), 6, 0.12f);

		mAnimator->Play(L"Idle", true);

		mAnimator->FindEvents(L"Damaged")->mCompleteEvent = std::bind(&Monster::WalkComplete, this);
		mAnimator->GetCompleteEvent(L"Damaged") = std::bind(&Monster::WalkComplete, this);

		//AddComponent(new Animator());
		//AddComponent(new Collider());
		AddComponent(mAnimator);
	}

	Monster::~Monster()
	{

	}

	void Monster::Tick()
	{
		GameObject::Tick();

		Vector2 pos = GetPos();

		SetPos(pos);

		if (KEY_DOWN(eKeyCode::LSHIFT))
		{
			mAnimator->Play(L"Damaged", true);
		}

		//mTime += Time::DeltaTime();

		//if (mTime > 5.0f)
		//{
		//	pos.x -= 30;
		//	SetPos(pos);
		//	mTime = 0.0f;
		//}
	}

	void Monster::Render(HDC hdc)
	{
		/*Vector2 pos = GetPos();
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
			, RGB(255, 0, 255));*/

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
}
