#include "yaTileMap.h"
#include "Common.h"
#include "yaGameObject.h"
#include "yaSceneManager.h"
#include "yaUIManager.h"

namespace ya
{
	std::vector<std::vector<GameObject*>> TileMap::mMap;

	void TileMap::Initiailize()
	{	
		//stage1
		mMap.resize(9);
		for (size_t i = 0; i < 9; i++)
			mMap[i].resize(11);
	}

	void TileMap::Tick()
	{

	}

	void TileMap::PushGameObject(const Index idx, GameObject* obj)
	{
		mMap[idx.y][idx.x] = obj;

		if (obj != nullptr)
			obj->SetIndex(idx);
	}

	void TileMap::MoveGameObject(const Index idx, GameObject* obj)
	{
		for (size_t y = 0; y < 9; y++)
		{
			for (size_t x = 0; x < 11; x++)
			{
				if (mMap[y][x] == obj)
				{
					mMap[y][x] = nullptr;
				}
			}
		}

		PushGameObject(idx, obj);
	}

	GameObject* TileMap::GetGameObject(const Index idx)
	{
		return mMap[idx.y][idx.x];
	}

	void TileMap::CheckSuccess(GameObject* obj)
	{
		if (mMap[7][7] == nullptr)
		{
			return;
		}
		else if (mMap[7][7]->GetObjType() == eGameObjectType::Player)
		{
			/*SceneManager::ChangeScene(eSceneType::End);
			UIManager::Pop(eUIType::STEP);
			UIManager::Pop(eUIType::ROUND);*/
		}
	}

}