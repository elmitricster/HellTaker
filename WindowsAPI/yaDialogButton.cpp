#include "yaDialogButton.h"
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
	DialogButton::DialogButton()
	{
	}

	DialogButton::DialogButton(Vector2 position)
	{
		mGameObjType = eGameObjectType::Dialogue_BUTTON;
		SetName(L"Booper");
		SetPos(position);
		SetScale({ 0.8333f, 0.8333f });

		/*if (mImage == nullptr)
		{
			mImage = Resources::Load<Image>(L"Booper", L"..\\Resources\\Image\\Booper01.bmp");
		}*/

		mAnimator = new Animator();
		mAnimator->CreateAnimations(L"..\\Resources\\Animations\\Button", L"Booper");
		
		mAnimator->Play(L"Booper", true);

		AddComponent(mAnimator);
	}

	DialogButton::~DialogButton()
	{
	}

	void DialogButton::Tick()
	{
		GameObject::Tick();
	}

	void DialogButton::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}