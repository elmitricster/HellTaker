#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Image;
	class SuccessEffect : public GameObject
	{
	public:
		SuccessEffect();
		SuccessEffect(Vector2 position);
		~SuccessEffect();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		void EffectComplete();

	private:
		Animator* mAnimator;
		Image* mImage;
	};
}

