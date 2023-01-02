#pragma once
#include "yaUiBase.h"
//#include "yaPlayScene.h"
//#include "yaEndScene.h"

namespace ya
{
	class GameObject;
	class HUD : public UiBase
	{
	public:
		HUD(eUIType type);
		~HUD();

		virtual void OnInit() override;
		virtual void OnActive() override;
		virtual void OnInActive() override;
		virtual void OnTick() override;
		virtual void OnRender(HDC hdc) override;
		virtual void OnClear() override;

		void SetTarget(GameObject* target) { mTarget = target; }

		void SetPlayScene(PlayScene* scene) { mpScene = scene; }

		void LoadFont();

		void WriteCounterText(HDC hdc, int posX, int posY, std::wstring _szMessage);
		void WriteNameText(HDC hdc, int posX, int posY, int width, int height, std::wstring _szMessage);
		void WriteScriptText(HDC hdc, int posX, int posY, int width, int height, std::wstring _szMessage);

		void Exit();

	private:
		GameObject* mTarget;
		PlayScene* mpScene;

		std::wstring mStageName[9] = { L"グ", L"ケ", L"ゲ", L"コ", L"ゴ", L"サ", L"ザ", L"シ", L"ジ" };

		HFONT mCounterFont;
		HFONT mNameFont;
		HFONT mScriptFont;
	};

}