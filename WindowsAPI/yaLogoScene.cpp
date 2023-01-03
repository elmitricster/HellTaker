#include "yaLogoScene.h"
#include "yaPlayer.h"
#include "yaMonster.h"
#include "yaInput.h"
#include "yaSceneManager.h"
#include "yaBgImageObject.h"
#include "yaCollisionManager.h"
#include "yaObject.h"
#include "yaApplication.h"
#include "yaToolScene.h"
#include "yaUIManager.h"
#include "yaHUD.h"
#include "yaButton.h"
#include "yaTime.h"

namespace ya
{
	LogoScene::LogoScene()
	{
	}

	LogoScene::~LogoScene()
	{
	}

	void LogoScene::Initialize()
	{
		mBgImage = new BgImageObject();
		mBgImage->SetImage(L"LogoBG", L"LogoBG.bmp");
		mBgImage->SetPos(Vector2{-10.0f, -10.0f});
		mBgImage->Initialize();

		AddGameObject(mBgImage, eColliderLayer::BackGround);

	}

	void LogoScene::Tick()
	{
		// 오브젝트 tick 을 호출한다.
		Scene::Tick();

		mBgImage->SetScale(mBgImage->GetScale() + Vector2(0.003f * Time::DeltaTime(), 0.003f * Time::DeltaTime()));

		mSumTime += Time::DeltaTime();

		if (mSumTime > 10.0f)
		{
			SceneManager::ChangeScene(eSceneType::Title);
		}

		if (KEY_DOWN(eKeyCode::N))
		{
			SceneManager::ChangeScene(eSceneType::Title);
		}
		
	}

	void LogoScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
		
		/*wchar_t szFloat[50] = {};
		swprintf_s(szFloat, 50, L"Logo Scene.bmp");
		int strLen = wcsnlen_s(szFloat, 50);
		TextOut(hdc, 10, 30, szFloat, strLen);*/
	}

	void LogoScene::Enter()
	{
	}

	void LogoScene::Exit()
	{
	}
}