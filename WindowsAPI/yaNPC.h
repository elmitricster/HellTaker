#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Image;
	class NPC : public GameObject
	{
	public:
		enum class State
		{
			IDLE,
			SUCCESS,
			DEAD,
		};

		NPC();
		NPC(Vector2 position);
		~NPC();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

	private:
		State mState;

		Animator* mAnimator;
		Image* mImage;
	};

}