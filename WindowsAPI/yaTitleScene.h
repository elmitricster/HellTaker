#pragma once
#include "yaScene.h"

namespace ya
{
	class BeelNPC;
	class DialogButton;
	class SelectButton;
	class Sound;
	class TitleScene : public Scene
	{
	public:
		TitleScene();
		~TitleScene();

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
		SelectButton* mSelectBtn[6];

		HFONT mCounterFont;
		HFONT mNameFont;
		HFONT mScriptFont;

		int cutSceneNum = 0;
		int btnState = 0;
		bool mCheck = true;

		Sound* mBgSound;
		Sound* mEnterSound;
		Sound* mBtnChangeSound;
		Sound* mBtnSelectSound;

	};

}
