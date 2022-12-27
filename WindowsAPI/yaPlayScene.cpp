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
		TileMap::Initiailize();

		BgImageObject* bg = new BgImageObject();
		bg->SetImage(L"chapterBG01", L"chapterBG0001.bmp");
		bg->Initialize();

		AddGameObject(bg, eColliderLayer::BackGround);

		mPlayer = ya::object::Instantiate<Player>(eColliderLayer::Player);
		TileMap::PushGameObject(Index(6, 1), mPlayer);

		mons[0] = ya::object::Instantiate<Monster>(Vector2{ 800, 320 }, eColliderLayer::Monster);
		mons[1] = ya::object::Instantiate<Monster>(Vector2{ 720, 400 }, eColliderLayer::Monster);
		mons[2] = ya::object::Instantiate<Monster>(Vector2{ 880, 400 }, eColliderLayer::Monster);
		TileMap::PushGameObject(Index(4, 2), (GameObject*)mons[0]);
		TileMap::PushGameObject(Index(3, 3), (GameObject*)mons[1]);
		TileMap::PushGameObject(Index(5, 3), (GameObject*)mons[2]);


		rocks[0] = ya::object::Instantiate<Rock>(Vector2{ 880, 560 }, eColliderLayer::Rock);
		rocks[1] = ya::object::Instantiate<Rock>(Vector2{ 640, 560 }, eColliderLayer::Rock);
		rocks[1]->SetImage(L"rock02", L"Rock02.bmp");
		rocks[2] = ya::object::Instantiate<Rock>(Vector2{ 640, 640 }, eColliderLayer::Rock);
		rocks[2]->SetImage(L"rock03", L"Rock03.bmp");
		rocks[3] = ya::object::Instantiate<Rock>(Vector2{ 800, 640 }, eColliderLayer::Rock);
		rocks[3]->SetImage(L"rock04", L"Rock04.bmp");

		TileMap::PushGameObject(Index(2, 5), rocks[1]);
		TileMap::PushGameObject(Index(5, 5), rocks[0]);
		TileMap::PushGameObject(Index(2, 6), rocks[2]);
		TileMap::PushGameObject(Index(4, 6), rocks[3]);

		mNPC = ya::object::Instantiate<NPC>(eColliderLayer::NPC);
		TileMap::PushGameObject(Index(6, 6), (GameObject*)mNPC);

		flameBases[0] = ya::object::Instantiate<FlameBase>(Vector2{ 556, 260 }, eColliderLayer::FlameBase);
		flameBases[1] = ya::object::Instantiate<FlameBase>(Vector2{ 1056, 465 }, eColliderLayer::FlameBase);

		
		

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
