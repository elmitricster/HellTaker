#pragma once
#include "yaScene.h"

namespace ya
{
	class DialogButton;
	class BgImageObject;
	class Sound;
	class EndScene : public Scene
	{
	public:
		EndScene();
		~EndScene();

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
		BgImageObject* mBgImage;
		DialogButton* mDialogBtn;

		HFONT mCounterFont;
		HFONT mNameFont;
		HFONT mScriptFont;

		int cutSceneNum = 0;
		bool mCheck = true;

		Sound* mTransSound;
		Sound* mBgSound;
		Sound* mEnterSound;

	};
}


