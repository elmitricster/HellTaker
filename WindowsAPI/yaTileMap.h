#pragma once
//#include "Common.h"

namespace ya
{	
	class GameObject;
	class TileMap
	{
	public:
		static void Initiailize();
		static void Tick();

		static void PushGameObject(const Index idx, GameObject* obj);
		static void MoveGameObject(const Index idx, GameObject* obj);
		static GameObject* GetGameObject(const Index idx);
		static void CheckSuccess(GameObject* obj);

		static void SetCheckClear(bool check) { mCheckClear = check; }
		static bool GetCheckClear() { return mCheckClear; }

	private:
		TileMap() = default;
		~TileMap() = default;

	private:
		static std::vector<std::vector<GameObject*>> mMap;
		static bool mCheckClear;

		static float mSumTime;
	};

}

