#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Image;
	class FlameBase : public GameObject
	{
	public:
		FlameBase();
		FlameBase(Vector2 position);
		~FlameBase();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		void SetImage(const std::wstring& key, const std::wstring& fileName);

	private:
		Animator* mAnimator;
		Image* mImage;
	};

}