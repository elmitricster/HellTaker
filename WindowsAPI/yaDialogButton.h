#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Image;
	class DialogButton : public GameObject
	{
	public:
		DialogButton();
		DialogButton(Vector2 position);
		~DialogButton();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

	private:
		Animator* mAnimator;
		Image* mImage;
	};
}


