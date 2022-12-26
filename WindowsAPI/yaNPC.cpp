#include "yaNPC.h"
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
	NPC::NPC()
	{
		SetName(L"NPC");
		SetPos({ 1050, 660 });
		SetScale({ 0.8333f, 0.8333f });

		if (mImage == nullptr)
		{
			mImage = Resources::Load<Image>(L"NPC", L"..\\Resources\\Image\\NPC.bmp");
		}

		mAnimator = new Animator();

		mAnimator->CreateAnimation(L"Idle", mImage
			, Vector2(0.0f, 0.0f), Vector2(100.0f, 100.0f)
			, Vector2(5.0f, -20.0f), 12, 0.12f);

		mAnimator->Play(L"Idle", true);

		//AddComponent(new Animator());
		//AddComponent(new Collider());
		AddComponent(mAnimator);
	}

	NPC::NPC(Vector2 position)
	{
		SetName(L"NPC");
		SetPos(position);
		SetScale({ 1.0f, 1.0f });

		if (mImage == nullptr)
		{
			mImage = Resources::Load<Image>(L"NPC", L"..\\Resources\\Image\\NPC.bmp");
		}

		mAnimator = new Animator();

		mAnimator->CreateAnimation(L"Idle", mImage
			, Vector2(0.0f, 0.0f), Vector2(100.0f, 130.0f)
			, Vector2(0.0f, 0.0f), 12, 0.12f);

		mAnimator->Play(L"Idle", true);

		//AddComponent(new Animator());
		//AddComponent(new Collider());
		AddComponent(mAnimator);
	}

	NPC::~NPC()
	{

	}

	void NPC::Tick()
	{
		GameObject::Tick();

		Vector2 pos = GetPos();

		SetPos(pos);
	}

	void NPC::Render(HDC hdc)
	{

		GameObject::Render(hdc);
	}

}
