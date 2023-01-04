#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Image;
	class DialogDeath : public GameObject
	{
	public:
		DialogDeath();
		DialogDeath(Vector2 position);
		~DialogDeath();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		void AnimeComplete();

	private:
		Animator* mAnimator;
		Image* mImage;
	};

}

