#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Image;
	class MoveEffect : public GameObject
	{
	public:
		MoveEffect();
		MoveEffect(Vector2 position);
		~MoveEffect();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		void EffectComplete();

	private:
		Animator* mAnimator;
		Image* mImage;
	};
}


