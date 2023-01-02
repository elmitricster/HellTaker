#pragma once
#include "yaGameObject.h"
#include "yaPlayScene.h"

namespace ya
{
	class Animator;
	class Image;
	class Player : public GameObject
	{
	public:
		Player();
		~Player();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(Collider* other) override;
		virtual void OnCollisionStay(Collider* other) override;
		virtual void OnCollisionExit(Collider* other) override;

		void AttackComplete();
		void DeathComplete();
		void SetState(PlayerState state) { mState = state; }
		PlayerState GetState() { return mState; }

		void Idle();
		void Attack();
		void Move(Direction dir);
		void Victory();
		void DeadStart();
		void Dead();
		void GetDamaged(int damage);

		void SetPlayScene(PlayScene* scene) { mpScene = scene; }

		Direction GetDir() { return mDir; }

	private:
		PlayerState mState;
		Direction mDir;
		Vector2 mDest;
		float mSumTime = 0.0f;

		float mCoff;
		float mSpeed;
		Image* mImage;
		Animator* mAnimator;

		Collider* mCollider;
		Collider* mCollider2;
	
		PlayScene* mpScene;

	private:
		void CountDown(int mNum = 1);
	};

}