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
		enum class State
		{
			IDLE,
			MOVE,
			ATTACK,
			VICTORY,
			DEAD,
			NONE,
		};


		Player();
		~Player();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(Collider* other) override;
		virtual void OnCollisionStay(Collider* other) override;
		virtual void OnCollisionExit(Collider* other) override;

		void AttackComplete();
		void DeathComplete();
		void SetState(State state) { mState = state; }

		void Idle();
		void Attack();
		void Move(Direction dir);
		void Victory();
		void Dead();
		void GetDamaged(int damage);

		void SetScene(PlayScene* scene) { mpScene = scene; }

		Direction GetDir() { return mDir; }

	private:
		State mState;
		Direction mDir;
		Vector2 mDest;

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