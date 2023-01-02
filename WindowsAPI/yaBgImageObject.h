#pragma once
#include "yaGameObject.h"


namespace ya
{
	class Player;
	class Image;
	class BgImageObject : public GameObject
	{
	public:
		BgImageObject();
		BgImageObject(Vector2 position);
		~BgImageObject();

		virtual void Initialize() override;
		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		void SetImage(const std::wstring& key ,const std::wstring& fileName);

		Player* mPlayer;

	private:
		Image* mImage;
		Image* mPixelImage;
	};
}
