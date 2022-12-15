#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Image;
	class NPC : public GameObject
	{
	public:
		NPC();
		NPC(Vector2 position);
		~NPC();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(Collider* other) override;
		virtual void OnCollisionStay(Collider* other) override;
		virtual void OnCollisionExit(Collider* other) override;

		//void Dead();

	private:
		Animator* mAnimator;
		Image* mImage;
	};

}