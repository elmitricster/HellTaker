#include "yaTransition.h"
#include "yaTime.h"
#include "yaSceneManager.h"
#include "yaInput.h"
#include "yaScene.h"
#include "yaImage.h"
#include "yaResources.h"
#include "yaAnimator.h"
#include "yaCamera.h"
#include "yaUIManager.h"

namespace ya
{
	Transition::Transition()
	{
		mGameObjType = eGameObjectType::Transition;
		SetPos({ 960.0f, 540.0f });
		SetName(L"Transition");
		SetScale({ 0.833f, 0.833f });

		mAnimator = new Animator(Animator::Mode::UIGameObject);
		mAnimator->CreateAnimations(L"..\\Resources\\Animations\\Transition", L"Transition");

		mAnimator->Play(L"Transition", false);

		AddComponent(mAnimator);

		mAnimator->FindEvents(L"Transition")->mCompleteEvent = std::bind(&Transition::TransitionComplete, this);
		mAnimator->GetCompleteEvent(L"Transition") = std::bind(&Transition::TransitionComplete, this);
	}

	Transition::~Transition()
	{
	}

	void Transition::Tick()
	{
		GameObject::Tick();
	}

	void Transition::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Transition::TransitionComplete()
	{
		UIManager::Pop(eUIType::TPANEL);
	}
}