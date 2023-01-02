#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Image;
	class DialogueNPC : public GameObject
	{
	public:
		DialogueNPC();
		DialogueNPC(Vector2 position);
		~DialogueNPC();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		void SetImage(const std::wstring& key, const std::wstring& fileName);

	private:
		Animator* mAnimator;
		Image* mImage;
	};

}

