#pragma once
#include "yaScene.h"
#include "yaPlayer.h"
//#include "yaCounter.h"

namespace ya
{
	class Monster;
	class Rock;
	class NPC;
	class FlameBase;
	class PlayScene : public Scene
	{
	public:
		PlayScene();
		~PlayScene();

		void Initialize() override;
		void Tick() override;
		void Render(HDC hdc) override;

		virtual void Enter();
		virtual void Exit();

		void SetInitMoveCnt(int move) { InitMoveCnt = move; }
		int GetInitMoveCnt() { return InitMoveCnt; }
		void SetCurMoveCnt(int move) { CurMoveCnt = move; }
		int GetCurMoveCnt() { return CurMoveCnt; }
		int GetChapterNum() { return ChapterNum; }

		void Restart();

	private:
		Player* mPlayer;
		Vector2 mPlayerPos;
		Monster* mons[3];
		Rock* rocks[4];
		NPC* mNPC;
		FlameBase* flameBases[4];
		//Counter* counter;

		int InitMoveCnt;
		int CurMoveCnt;
		int ChapterNum = 0;
		int mSumTime = 0.0f;
	};

}
