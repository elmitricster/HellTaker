#pragma once
#include "yaScene.h"

namespace ya
{
	class DialogueNPC;
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
		DialogueNPC* mDialogNPC;

		HFONT mCounterFont;
		HFONT mNameFont;
		HFONT mScriptFont;

		int cutSceneNum = 0;
	};

}
