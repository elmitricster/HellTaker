#include "yaSuccessEffect.h"
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
	SuccessEffect::SuccessEffect()
	{
	}

	SuccessEffect::SuccessEffect(Vector2 position)
	{
		mGameObjType = eGameObjectType::Effect;
		SetName(L"SuccessEffect");
		SetPos(position);
		SetScale({ 0.8333f, 0.8333f });

		mAnimator = new Animator();
		mAnimator->CreateAnimations(L"..\\Resources\\Animations\\Effect\\Success", L"SuccessEffect");

		mAnimator->Play(L"SuccessEffect", false);

		AddComponent(mAnimator);
	}

	SuccessEffect::~SuccessEffect()
	{
	}

	void SuccessEffect::Tick()
	{
		GameObject::Tick();
	}

	void SuccessEffect::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void SuccessEffect::EffectComplete()
	{
		Death();
	}

}