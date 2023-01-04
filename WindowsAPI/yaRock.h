#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Image;
	class Sound;
	class Rock : public GameObject
	{
	public:
		enum class State
		{
			IDLE,
			MOVE,
			DAMAGED,
			DEAD,
		};

		Rock();
		Rock(Vector2 position);
		~Rock();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		void Idle();
		void Move(Direction dir);
		void Damaged(Direction dir);
		void Dead();

		void SetImage(const std::wstring& key, const std::wstring& fileName);

	private:
		State mState;
		Direction mDir;
		Vector2 mDest;

		Animator* mAnimator;
		Image* mImage;

		Sound* mMoveSound;
	};

}