#include "yaPlayScene.h"
#include "yaPlayer.h"
#include "yaInput.h"
#include "yaSceneManager.h"
#include "yaBgImageObject.h"
#include "yaRock.h"
#include "yaObject.h"
#include "yaCollisionManager.h"
#include "yaTileMap.h"
#include "yaWall.h"

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
		TileMap::Initiailize();

		BgImageObject* bg = new BgImageObject();
		bg->SetImage(L"chapterBG01", L"chapterBG0001.bmp");
		bg->Initialize();

		AddGameObject(bg, eColliderLayer::BackGround);

		mPlayer = ya::object::Instantiate<Player>(eColliderLayer::Player);
		TileMap::PushGameObject(Index(7, 2), mPlayer);

		mons[0] = ya::object::Instantiate<Monster>(Vector2{ 800, 320 }, eColliderLayer::Monster);
		mons[1] = ya::object::Instantiate<Monster>(Vector2{ 720, 400 }, eColliderLayer::Monster);
		mons[2] = ya::object::Instantiate<Monster>(Vector2{ 880, 400 }, eColliderLayer::Monster);
		TileMap::PushGameObject(Index(5, 3), (GameObject*)mons[0]);
		TileMap::PushGameObject(Index(4, 4), (GameObject*)mons[1]);
		TileMap::PushGameObject(Index(6, 4), (GameObject*)mons[2]);

		rocks[0] = ya::object::Instantiate<Rock>(Vector2{ 880, 560 }, eColliderLayer::Rock);
		rocks[1] = ya::object::Instantiate<Rock>(Vector2{ 640, 560 }, eColliderLayer::Rock);
		rocks[1]->SetImage(L"rock02", L"Rock02.bmp");
		rocks[2] = ya::object::Instantiate<Rock>(Vector2{ 640, 640 }, eColliderLayer::Rock);
		rocks[2]->SetImage(L"rock03", L"Rock03.bmp");
		rocks[3] = ya::object::Instantiate<Rock>(Vector2{ 800, 640 }, eColliderLayer::Rock);
		rocks[3]->SetImage(L"rock04", L"Rock04.bmp");

		TileMap::PushGameObject(Index(3, 6), rocks[1]);
		TileMap::PushGameObject(Index(6, 6), rocks[0]);
		TileMap::PushGameObject(Index(3, 7), rocks[2]);
		TileMap::PushGameObject(Index(5, 7), rocks[3]);

		mNPC = ya::object::Instantiate<NPC>(eColliderLayer::NPC);
		//TileMap::PushGameObject(Index(7, 7), (GameObject*)mNPC);

		flameBases[0] = ya::object::Instantiate<FlameBase>(Vector2{ 556, 260 }, eColliderLayer::FlameBase);
		flameBases[1] = ya::object::Instantiate<FlameBase>(Vector2{ 1056, 465 }, eColliderLayer::FlameBase);
		flameBases[2] = ya::object::Instantiate<FlameBase>(Vector2{ 467, 504 }, eColliderLayer::FlameBase);
		flameBases[3] = ya::object::Instantiate<FlameBase>(Vector2{ 799, 170 }, eColliderLayer::FlameBase);
		//flameBases[2]->SetImage();

		// Wall
		// 가로벽
		Wall* wall = ya::object::Instantiate<Wall>(eColliderLayer::Wall);
		for (size_t i = 0; i < 11; i++)
		{
			TileMap::PushGameObject(Index(0 + i, 0), wall);
		}
		for (size_t i = 0; i < 11; i++)
		{
			TileMap::PushGameObject(Index(0 + i, 1), wall);
		}
		for (size_t i = 0; i < 11; i++)
		{
			TileMap::PushGameObject(Index(0 + i, 8), wall);
		}
		for (size_t i = 4; i < 8; i++)
		{
			TileMap::PushGameObject(Index(0 + i, 5), wall);
		}
		for (size_t i = 2; i < 6; i++)
		{
			TileMap::PushGameObject(Index(0 + i, 2), wall);
		}

		// 세로벽
		for (size_t i = 0; i < 9; i++)
		{
			TileMap::PushGameObject(Index(0, 0 + i), wall);
		}
		for (size_t i = 0; i < 9; i++)
		{
			TileMap::PushGameObject(Index(1, 0 + i), wall);
		}
		for (size_t i = 0; i < 9; i++)
		{
			TileMap::PushGameObject(Index(9, 0 + i), wall);
		}
		for (size_t i = 0; i < 9; i++)
		{
			TileMap::PushGameObject(Index(10, 0 + i), wall);
		}
		for (size_t i = 2; i < 7; i++)
		{
			TileMap::PushGameObject(Index(8, 0 + i), wall);
		}

		// 단일벽
		TileMap::PushGameObject(Index(7, 4), wall);
		TileMap::PushGameObject(Index(2, 3), wall);
		TileMap::PushGameObject(Index(2, 4), wall);

	}

	void PlayScene::Tick()
	{
		Scene::Tick();

		mPlayerPos = mPlayer->GetPos();

		if (KEY_DOWN(eKeyCode::N))
		{
			SceneManager::ChangeScene(eSceneType::End);
		}

		TileMap::CheckSuccess(mPlayer);

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
		//CollisionManager::SetLayer(eColliderLayer::Monster, eColliderLayer::Player, true);
	}

	void PlayScene::Exit()
	{

	}
}
