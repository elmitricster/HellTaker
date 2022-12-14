#pragma once
#include "yaScene.h"
#include "yaTilePalette.h"

namespace ya
{
	class Image;
	class ToolScene : public Scene
	{
	public:
		ToolScene();
		~ToolScene();

		void Initialize() override;
		void Tick() override;
		void Render(HDC hdc) override;

		virtual void Enter();
		virtual void Exit();

		void SaveTilePalette();
		void LoadTilePalette();
		void LoadTilePalette(const std::wstring& path);

		Image* GetAtalasImage() { return mTilePalette->GetAtlasImage(); }
		void SetTileIndex(UINT index) { mTileIndex = index; }
		UINT GetTileIndex() { return mTileIndex; }

	private:
		TilePalette* mTilePalette;
		UINT mTileIndex;
	};

}