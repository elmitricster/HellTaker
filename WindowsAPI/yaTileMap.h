#pragma once

namespace ya
{	
	class GameObject;
	class TileMap
	{
	public:
		TileMap();
		~TileMap();

		static void Initiailize();
		static void Tick();

		void SetTileMap(GameObject* obj, int row, int col) { stage[row][col] = obj; }
		GameObject* GetTileMap(int row, int col) { return stage[row][col]; }

		/*void ChangeTileMap(GameObject* obj, int y, int x)
		{ 
			stage[row + y][col + x] = obj;
			stage[row][col] = nullptr;
		}*/


	private:
		//static std::vector<std::vector<GameObject*>> stage;
		static GameObject* stage[7][9];
		//static int row;
		//static int col;
	};

}

