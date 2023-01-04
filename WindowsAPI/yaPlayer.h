#pragma once
#include "yaGameObject.h"
#include "yaPlayScene.h"

namespace ya
{
	class Animator;
	class Image;
	class Sound;
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
		void StageComplete();
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
		bool mClearCheck = true;

		float mCoff;
		float mSpeed;
		Image* mImage;
		Animator* mAnimator;

		Collider* mCollider;
		Collider* mCollider2;
	
		PlayScene* mpScene;

		Sound* mMoveSound;
		Sound* mMonsterAttackSound;
		Sound* mStoneAttackSound;
		Sound* mDeathSound;
		Sound* mSuccessSound;
		Sound* mTransSound;

	private:
		void CountDown(int mNum = 1);
	};

}