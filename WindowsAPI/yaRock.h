#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Image;
	class Rock : public GameObject
	{
	public:
		Rock();
		Rock(Vector2 position);
		~Rock();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

	private:
		Animator* mAnimator;
		Image* mImage;
	};

}