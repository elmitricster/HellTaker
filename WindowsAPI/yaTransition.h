#pragma once
#include "yaGameObject.h"

namespace ya
{	
	class Animator;
	class Image;
	class Sound;
	class Transition : public GameObject
	{
	public:
		Transition();
		~Transition();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		void TransitionComplete();

	private:
		Animator* mAnimator;
		Image* mImage;
	};
}


