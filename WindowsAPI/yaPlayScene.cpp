#include "yaPlayScene.h"
#include "yaPlayer.h"
#include "yaInput.h"
#include "yaSceneManager.h"
#include "yaBgImageObject.h"
#include "yaRock.h"
#include "yaObject.h"
#include "yaCollisionManager.h"
#include "yaTileMap.h"

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
		//bg->mPlayer = mPlayer;

		mons[0] = ya::object::Instantiate<Monster>(Vector2{ 880, 400 }, eColliderLayer::Monster);
		mons[1] = ya::object::Instantiate<Monster>(Vector2{ 800, 320 }, eColliderLayer::Monster);
		mons[2] = ya::object::Instantiate<Monster>(Vector2{ 720, 400 }, eColliderLayer::Monster);

		rocks[0] = ya::object::Instantiate<Rock>(Vector2{ 880, 560 }, eColliderLayer::Rock);
		rocks[1] = ya::object::Instantiate<Rock>(Vector2{ 640, 560 }, eColliderLayer::Rock);
		rocks[1]->SetImage(L"rock02", L"Rock02.bmp");
		rocks[2] = ya::object::Instantiate<Rock>(Vector2{ 640, 640 }, eColliderLayer::Rock);
		rocks[2]->SetImage(L"rock03", L"Rock03.bmp");
		rocks[3] = ya::object::Instantiate<Rock>(Vector2{ 800, 640 }, eColliderLayer::Rock);
		rocks[3]->SetImage(L"rock04", L"Rock04.bmp");

		mNPC = ya::object::Instantiate<NPC>(eColliderLayer::NPC);

		flameBases[0] = ya::object::Instantiate<FlameBase>(Vector2{ 556, 260 }, eColliderLayer::FlameBase);
		flameBases[1] = ya::object::Instantiate<FlameBase>(Vector2{ 1056, 465 }, eColliderLayer::FlameBase);

		TileMap* tile = new TileMap();
		tile->SetTileMap(mPlayer, 1, 7);
		tile->SetTileMap(dynamic_cast<GameObject*>(mons[0]), 2, 4);
		tile->SetTileMap(dynamic_cast<GameObject*>(mons[1]), 3, 3);
		tile->SetTileMap(dynamic_cast<GameObject*>(mons[2]), 3, 5);
		tile->SetTileMap(dynamic_cast<GameObject*>(rocks[0]), 5, 2);
		tile->SetTileMap(dynamic_cast<GameObject*>(rocks[1]), 5, 5);
		tile->SetTileMap(dynamic_cast<GameObject*>(rocks[2]), 6, 2);
		tile->SetTileMap(dynamic_cast<GameObject*>(rocks[3]), 6, 4);
		tile->SetTileMap(dynamic_cast<GameObject*>(mNPC), 6, 7);

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
		CollisionManager::SetLayer(eColliderLayer::Monster, eColliderLayer::Player, true);
	}

	void PlayScene::Exit()
	{

	}
}
