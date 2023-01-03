#include "yaMoveEffect.h"
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
	MoveEffect::MoveEffect()
	{
	}

	MoveEffect::MoveEffect(Vector2 position)
	{
		mGameObjType = eGameObjectType::Effect;
		SetName(L"MoveEffect");
		SetPos(position);
		SetScale({ 0.8333f, 0.8333f });

		mAnimator = new Animator();
		mAnimator->CreateAnimations(L"..\\Resources\\Animations\\Effect\\Move", L"MoveEffect");

		mAnimator->Play(L"MoveEffect", false);

		AddComponent(mAnimator);

		mAnimator->FindEvents(L"MoveEffect")->mCompleteEvent = std::bind(&MoveEffect::EffectComplete, this);
		mAnimator->GetCompleteEvent(L"MoveEffect") = std::bind(&MoveEffect::EffectComplete, this);
	}

	MoveEffect::~MoveEffect()
	{
	}

	void MoveEffect::Tick()
	{
		GameObject::Tick();
	}

	void MoveEffect::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void MoveEffect::EffectComplete()
	{
		Death();
	}
}