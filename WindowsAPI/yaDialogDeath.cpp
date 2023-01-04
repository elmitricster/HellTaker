#include "yaDialogDeath.h"
#include "yaTime.h"
#include "yaSceneManager.h"
#include "yaInput.h"
#include "yaScene.h"
#include "yaImage.h"
#include "yaResources.h"
#include "yaAnimator.h"
#include "yaCamera.h"

namespace ya
{
	DialogDeath::DialogDeath()
	{
	}

	DialogDeath::DialogDeath(Vector2 position)
	{
		mGameObjType = eGameObjectType::Effect;
		SetName(L"DialogDeath");
		SetPos(position);
		SetScale({ 0.8333f, 0.8333f });

		mAnimator = new Animator();
		mAnimator->CreateAnimations(L"..\\Resources\\Animations\\Effect\\Death", L"DialogDeath");

		mAnimator->Play(L"DialogDeath", false);

		AddComponent(mAnimator);
	}

	DialogDeath::~DialogDeath()
	{
	}

	void DialogDeath::Tick()
	{
		GameObject::Tick();
	}

	void DialogDeath::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void DialogDeath::AnimeComplete()
	{
		Death();
	}
}