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

		mons[0] = ya::object::Instantiate<Monster>(Vector2{ 870, 380 }, eColliderLayer::Monster);
		mons[1] = ya::object::Instantiate<Monster>(Vector2{ 790, 300 }, eColliderLayer::Monster);
		mons[2] = ya::object::Instantiate<Monster>(Vector2{ 710, 380 }, eColliderLayer::Monster);

		rocks[0] = ya::object::Instantiate<Rock>(Vector2{ 870, 550 }, eColliderLayer::Rock);
		rocks[1] = ya::object::Instantiate<Rock>(Vector2{ 630, 550 }, eColliderLayer::Rock);
		rocks[2] = ya::object::Instantiate<Rock>(Vector2{ 630, 640 }, eColliderLayer::Rock);
		rocks[3] = ya::object::Instantiate<Rock>(Vector2{ 790, 640 }, eColliderLayer::Rock);
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

		std::wstring pos = L"x : " + std::to_wstring(mPlayerPos.x)
			+ L" y : " + std::to_wstring(mPlayerPos.y);

		TextOut(hdc, 10, 60, pos.c_str(), pos.length());

	}

	void PlayScene::Enter()
	{

	}

	void PlayScene::Exit()
	{

	}
}
