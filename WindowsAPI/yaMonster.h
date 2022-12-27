#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Image;
	class Monster : public GameObject
	{
	public:
		enum class State
		{
			IDLE,
			MOVE,
			DAMAGED,
			DEAD,
		};

		//Monster();
		Monster(Vector2 position);
		~Monster();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(Collider* other) override;
		virtual void OnCollisionStay(Collider* other) override;
		virtual void OnCollisionExit(Collider* other) override;

		void WalkComplete();

		void Idle();
		void Move(Direction dir);
		void Damaged(Direction dir);
		void Dead();

	private:
		State mState;
		Direction mDir;
		Vector2 mDest;
		Collider* mCollider;

		Animator* mAnimator;
		Image* mImage;
	};

}