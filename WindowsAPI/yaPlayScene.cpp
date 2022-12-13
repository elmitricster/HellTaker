#include "yaPlayScene.h"
#include "yaPlayer.h"
#include "yaInput.h"
#include "yaSceneManager.h"
#include "yaBgImageObject.h"
#include "yaObject.h"

namespace ya
{
	PlayScene::PlayScene()
	{
	}

	PlayScene::~PlayScene()
	{
	}

	void PlayScene::Initialize()
	{
		//AddGameObject(new Player(), eColliderLayer::Player);

		BgImageObject* bg = new BgImageObject();
		bg->SetImage(L"chapterBG01", L"chapterBG0001.bmp");
		bg->Initialize();

		AddGameObject(bg, eColliderLayer::BackGround);

		mPlayer = ya::object::Instantiate<Player>(eColliderLayer::Player);
		bg->mPlayer = mPlayer;
	}

	void PlayScene::Tick()
	{
		Scene::Tick();

		mPlayerPos = mPlayer->GetPos();

		if (KEY_DOWN(eKeyCode::N))
		{
			SceneManager::ChangeScene(eSceneType::End);
		}

	}

	void PlayScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
		wchar_t szFloat[50] = {};
		swprintf_s(szFloat, 50, L"Play Scene");
		int strLen = wcsnlen_s(szFloat, 50);
		TextOut(hdc, 10, 30, szFloat, strLen);

		wchar_t szFloat2[50] = {};
		swprintf_s(szFloat2, 50, L"ÇöÀç ÁÂÇ¥ : ", mPlayerPos.x);
		int strLen2 = wcsnlen_s(szFloat2, 50);
		TextOut(hdc, 10, 60, szFloat2, strLen2);

	}

	void PlayScene::Enter()
	{

	}

	void PlayScene::Exit()
	{

	}
}
