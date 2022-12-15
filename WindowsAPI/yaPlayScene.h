#pragma once
#include "yaScene.h"
#include "yaPlayer.h"

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

	private:
		Player* mPlayer;
		Vector2 mPlayerPos;
		Monster* mons[3];
		Rock* rocks[4];
		NPC* mNPC;
		FlameBase* flameBases[4];
	};

}
