#include "yaAttackEffect.h"
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
	AttackEffect::AttackEffect()
	{

	}

	AttackEffect::AttackEffect(Vector2 position)
	{
		mGameObjType = eGameObjectType::Effect;
		SetName(L"AttackEffect");
		SetPos(position);
		SetScale({ 0.8333f, 0.8333f });

		mAnimator = new Animator();
		mAnimator->CreateAnimations(L"..\\Resources\\Animations\\Effect\\Attack", L"AttackEffect");
		
		mAnimator->Play(L"AttackEffect", false);

		AddComponent(mAnimator);

		mAnimator->FindEvents(L"AttackEffect")->mCompleteEvent = std::bind(&AttackEffect::EffectComplete, this);
		mAnimator->GetCompleteEvent(L"AttackEffect") = std::bind(&AttackEffect::EffectComplete, this);
	}

	AttackEffect::~AttackEffect()
	{
	}

	void AttackEffect::Tick()
	{
		GameObject::Tick();
	}

	void AttackEffect::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void AttackEffect::EffectComplete()
	{
		Death();
	}
}