#pragma once
#include "yaScene.h"

namespace ya
{
	class DialogueNPC;
	class DialogButton;
	class SelectButton;
	class DialogDeath;
	class SuccessEffect;
	class DialogScene_Pand : public Scene
	{
	public:
		DialogScene_Pand();
		~DialogScene_Pand();

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
		DialogueNPC* mDialogNPC;
		DialogButton* mDialogBtn;
		SelectButton* mSelectBtn[4];
		BgImageObject* mBgImage;
		DialogDeath* mDeathEffect;
		SuccessEffect* mSuccessEffect;

		HFONT mCounterFont;
		HFONT mNameFont;
		HFONT mScriptFont;

		int cutSceneNum = 0;
		int cutSceneDeathNum = 0;
		int btnState = 0;
		bool mCheck = true;
	};

}
