#pragma once
#include "yaScene.h"

namespace ya
{
	class BgImageObject;
	class BeelNPC;
	class DialogButton;
	class HelpScene : public Scene
	{
	public:
		HelpScene();
		~HelpScene();

		void Initialize() override;
		void Tick() override;
		void Render(HDC hdc) override;

		virtual void Enter();
		virtual void Exit();

		void LoadFont();

		void WriteCounterText(HDC hdc, int posX, int posY, std::wstring _szMessage);
		void WriteNameText(HDC hdc, int posX, int posY, int width, int height, std::wstring _szMessage);
		void WriteScriptText(HDC hdc, int posX, int posY, int width, int height, std::wstring _szMessage);


	private:
		BeelNPC* mDialogNPC;
		DialogButton* mDialogBtn;
		BgImageObject* mBgImage;

		int cutSceneNum = 0;

		HFONT mCounterFont;
		HFONT mNameFont;
		HFONT mScriptFont;

		Sound* mEnterSound;
		Sound* mDialogStartSound;
	};
}


