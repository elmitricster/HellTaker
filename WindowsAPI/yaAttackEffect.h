#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Image;
	class AttackEffect : public GameObject
	{
	public:
		AttackEffect();
		AttackEffect(Vector2 position);
		~AttackEffect();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		void EffectComplete();

	private:
		Animator* mAnimator;
		Image* mImage;
	};

}

