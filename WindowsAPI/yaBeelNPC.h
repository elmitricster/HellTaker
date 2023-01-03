#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Image;
	class BeelNPC : public GameObject
	{
	public:
		BeelNPC();
		BeelNPC(Vector2 position);
		~BeelNPC();


		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		void SetImage(const std::wstring& key, const std::wstring& fileName);

	private:
		Animator* mAnimator;
		Image* mImage;
	};
}


