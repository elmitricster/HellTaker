#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Image;
	class SelectButton : public GameObject
	{
	public:
		SelectButton();
		SelectButton(Vector2 position);
		~SelectButton();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		void SetImage(const std::wstring& key, const std::wstring& fileName);

	private:
		Animator* mAnimator;
		Image* mImage;
	};
}


