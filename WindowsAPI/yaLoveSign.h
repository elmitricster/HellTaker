#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Image;
	class LoveSign : public GameObject
	{
	public:
		LoveSign();
		LoveSign(Vector2 position);
		~LoveSign();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		void ChangePos();

	private:
		Animator* mAnimator;
		Image* mImage;
		bool mGravity = true;
		float sum = 0.0f;
	};



}

