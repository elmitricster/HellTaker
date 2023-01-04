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
#include "yaAttackEffect.h"
#include "yaFlameBase.h"
#include "yaNPC.h"
#include "yaMonster.h"
#include "yaUIManager.h"
#include "yaHUD.h"
#include "yaPanel.h"
#include "yaTransition.h"
#include "yaLoveSign.h"
#include "yaTime.h"
#include "yaSoundManager.h"
#include "yaSound.h"
#include "yaResources.h"

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
		mTransSound = Resources::Load<Sound>(L"screen_changer", L"..\\Resources\\Sound\\screen_changer_part1.wav");
		//mBgSound = Resources::Load<Sound>(L"Vitality", L"..\\Resources\\Sound\\Vitality.wav");

		SetInitMoveCnt(23);
		SetCurMoveCnt(23);

		TileMap::Initiailize();

		BgImageObject* bg = new BgImageObject();
		bg->SetImage(L"chapterBG01", L"chapterBG0001.bmp");
		bg->Initialize();

		AddGameObject(bg, eColliderLayer::BackGround);

		mPlayer = ya::object::Instantiate<Player>(eColliderLayer::Player);
		TileMap::PushGameObject(Index(7, 2), mPlayer);
		mPlayer->SetPlayScene(this);
		
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
		TileMap::PushGameObject(Index(8, 7), (GameObject*)mNPC);

		flameBases[0] = ya::object::Instantiate<FlameBase>(Vector2{ 556, 260 }, eColliderLayer::FlameBase);
		flameBases[1] = ya::object::Instantiate<FlameBase>(Vector2{ 1056, 465 }, eColliderLayer::FlameBase);
		flameBases[2] = ya::object::Instantiate<FlameBase>(Vector2{ 467, 504 }, eColliderLayer::FlameBase);
		flameBases[2]->SetImage(L"flame02", L"FLAMEbase02.bmp");
		flameBases[3] = ya::object::Instantiate<FlameBase>(Vector2{ 799, 170 }, eColliderLayer::FlameBase);
		flameBases[3]->SetImage(L"flame02", L"FLAMEbase02.bmp");

		LoveSign* lovesign = ya::object::Instantiate<LoveSign>(Vector2{ 1005, 620 }, eColliderLayer::LoveSign);


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

		//TileMap::CheckSuccess(mPlayer);

		if (KEY_DOWN(eKeyCode::N))
		{
			TileMap::MoveGameObject(Index(6, 7), mPlayer);
			mPlayer->SetPos(Vector2{ 880, 640 });
		}

		if (KEY_DOWN(eKeyCode::R))
		{
			mTransSound->Play(false);

			UIManager::Push(eUIType::TPANEL);

			mPlayer->SetState(PlayerState::DEAD);
		}
	}

	void PlayScene::Render(HDC hdc)
	{
		Scene::Render(hdc);

		/*wchar_t szFloat[50] = {};
		swprintf_s(szFloat, 50, L"Play Scene");
		int strLen = wcsnlen_s(szFloat, 50);
		TextOut(hdc, 500, 30, szFloat, strLen);*/

		/*std::wstring pos = L"x : " + std::to_wstring(mPlayerPos.x)
			+ L" y : " + std::to_wstring(mPlayerPos.y);

		TextOut(hdc, 500, 60, pos.c_str(), pos.length());*/

	}

	void PlayScene::Enter()
	{
		mPlayer->SetState(PlayerState::DEAD);

		mBGMSound->Play(true);
		mTransSound->Play(false);

		// UI
		UIManager::Push(eUIType::LEFTBG);
		HUD* hud3 = UIManager::GetUiInstant<HUD>(eUIType::LEFTBG);
		hud3->SetTarget(mPlayer);
		hud3->SetPlayScene(this);

		UIManager::Push(eUIType::RIGHTBG);
		HUD* hud4 = UIManager::GetUiInstant<HUD>(eUIType::RIGHTBG);
		hud4->SetTarget(mPlayer);
		hud4->SetPlayScene(this);

		UIManager::Push(eUIType::STEP);
		HUD* hud = UIManager::GetUiInstant<HUD>(eUIType::STEP);
		hud->SetTarget(mPlayer);
		hud->SetPlayScene(this);

		UIManager::Push(eUIType::ROUND);
		HUD* hud2 = UIManager::GetUiInstant<HUD>(eUIType::ROUND);
		hud2->SetTarget(mPlayer);
		hud2->SetPlayScene(this);

		UIManager::Push(eUIType::FUNC);

		UIManager::Push(eUIType::TPANEL);
	}

	void PlayScene::Exit()
	{
		mPlayer->SetState(PlayerState::DEAD);

		UIManager::Pop(eUIType::STEP);
		UIManager::Pop(eUIType::ROUND);
		UIManager::Pop(eUIType::LEFTBG);
		UIManager::Pop(eUIType::RIGHTBG);
		UIManager::Pop(eUIType::FUNC);
	}

	void PlayScene::Restart()
	{
		TileMap::SetCheckClear(true);

		if (mons[0]->IsDeath())
		{
			mons[0] = ya::object::Instantiate<Monster>(Vector2{ 800, 320 }, eColliderLayer::Monster);
			TileMap::PushGameObject(Index(5, 3), (GameObject*)mons[0]);
		}
		else
		{
			TileMap::MoveGameObject(Index(5, 3), (GameObject*)mons[0]);
			mons[0]->SetPos(Vector2{ 800, 320 });
		}

		if (mons[1]->IsDeath())
		{
			mons[1] = ya::object::Instantiate<Monster>(Vector2{ 720, 400 }, eColliderLayer::Monster);
			TileMap::PushGameObject(Index(4, 4), (GameObject*)mons[1]);
		}
		else
		{
			TileMap::MoveGameObject(Index(4, 4), (GameObject*)mons[1]);
			mons[1]->SetPos(Vector2{ 720, 400 });
		}

		if (mons[2]->IsDeath())
		{
			mons[2] = ya::object::Instantiate<Monster>(Vector2{ 880, 400 }, eColliderLayer::Monster);
			TileMap::PushGameObject(Index(6, 4), (GameObject*)mons[2]);
		}
		else
		{
			TileMap::MoveGameObject(Index(6, 4), (GameObject*)mons[2]);
			mons[2]->SetPos(Vector2{ 880, 400 });
		}

		TileMap::MoveGameObject(Index(3, 6), rocks[1]);
		TileMap::MoveGameObject(Index(6, 6), rocks[0]);
		TileMap::MoveGameObject(Index(3, 7), rocks[2]);
		TileMap::MoveGameObject(Index(5, 7), rocks[3]);

		rocks[0]->SetPos(Vector2{ 880, 560 });
		rocks[1]->SetPos(Vector2{ 640, 560 });
		rocks[2]->SetPos(Vector2{ 640, 640 });
		rocks[3]->SetPos(Vector2{ 800, 640 });

	}


	
}
