#include "yaTileMap.h"
#include "Common.h"
#include "yaGameObject.h"

namespace ya
{
	std::vector<std::vector<GameObject*>> TileMap::mMap;

	void TileMap::Initiailize()
	{	
		//stage1
		mMap.resize(7);
		for (size_t i = 0; i < 7; i++)
			mMap[i].resize(9);
	}

	void TileMap::Tick()
	{

	}

	void TileMap::PushGameObject(const Index idx, GameObject* obj)
	{
		mMap[idx.y][idx.x] = obj;

		obj->SetIndex(idx);
	}

	void TileMap::MoveGameObject(const Index idx, GameObject* obj)
	{
		for (size_t y = 0; y < 7; y++)
		{
			for (size_t x = 0; x < 9; x++)
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
		if (mMap[6][6] == nullptr)
		{
			return;
		}
		else if (mMap[6][6]->GetObjType() == eGameObjectType::Player)
		{
			int a = 0;
		}
	}

}