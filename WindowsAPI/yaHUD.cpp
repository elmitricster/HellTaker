#include "yaHUD.h"
#include "yaImage.h"
#include "yaPlayer.h"
#include "yaAnimator.h"
#include "yaResources.h"
#include "Common.h"
#include "yaPlayScene.h"

namespace ya
{
	HUD::HUD(eUIType type)
		: UiBase(type)
	{
		SetScale({ 0.8333f, 0.8333f });
		LoadFont();
	}
	HUD::~HUD()
	{
	}
	void HUD::OnInit()
	{
	}
	void HUD::OnActive()
	{
	}
	void HUD::OnInActive()
	{
	
	}
	void HUD::OnTick()
	{
	}
	
	void HUD::OnRender(HDC hdc)
	{
		if (mImage == nullptr)
			return;

		if (mTarget == nullptr)
			return;

		/*BLENDFUNCTION func = {};
		func.BlendOp = AC_SRC_OVER;
		func.BlendFlags = 0;
		func.AlphaFormat = AC_SRC_ALPHA;
		func.SourceConstantAlpha = 255;*/

		/*AlphaBlend(hdc, (int)mScreenPos.x, (int)mScreenPos.y
			, mImage->GetWidth(), mImage->GetHeight()
			, mImage->GetDC(), 0, 0, mImage->GetWidth() , mImage->GetHeight(), func);*/

		TransparentBlt(hdc, (int)mScreenPos.x, (int)mScreenPos.y
			, mImage->GetWidth() * GetScale().x, mImage->GetHeight() * GetScale().y
			, mImage->GetDC(), 0, 0, mImage->GetWidth(), mImage->GetHeight(), RGB(255, 0, 255));


		std::wstring curCount;

		if (0 >= mpScene->GetCurMoveCnt())
			curCount = L"X";
		else
			curCount = std::to_wstring(mpScene->GetCurMoveCnt());

		std::wstring curChap = mStageName[mpScene->GetChapterNum()];

		WriteCounterText(hdc, 170, 605, curCount);
		WriteCounterText(hdc, 1435, 605, curChap);

	}

	void HUD::OnClear()
	{

	}


	void HUD::LoadFont()
	{
		// 카운터 폰트 로드
		std::wstring path = std::wstring(L"..\\Resources\\\Font\\HeirofLightRegular.ttf");
		AddFontResource(path.c_str());

		LOGFONT lf = LOGFONT{};
		lf.lfHeight = 150;			// 폰트 크기
		lf.lfWeight = 0;
		lf.lfEscapement = 0;
		lf.lfOrientation = 0;
		lf.lfWeight = 0;
		lf.lfItalic = 0;
		lf.lfUnderline = 0;
		lf.lfStrikeOut = 0;
		lf.lfCharSet = HANGEUL_CHARSET;
		lf.lfOutPrecision = 0;
		lf.lfClipPrecision = 0;
		lf.lfQuality = 0;
		lf.lfPitchAndFamily = FIXED_PITCH;
		lstrcpy(lf.lfFaceName, TEXT("빛의 계승자 Regular"));

		mCounterFont = CreateFontIndirect(&lf);

		// 이름 폰트 로드
		path = std::wstring(L"..\\Resources\\\Font\\HeirofLightBold.ttf").c_str();

		lf = LOGFONT{};
		lf.lfHeight = 40;			// 폰트 크기
		lf.lfWeight = 0;
		lf.lfEscapement = 0;
		lf.lfOrientation = 0;
		lf.lfWeight = 0;
		lf.lfItalic = 0;
		lf.lfUnderline = 0;
		lf.lfStrikeOut = 0;
		lf.lfCharSet = HANGEUL_CHARSET;
		lf.lfOutPrecision = 0;
		lf.lfClipPrecision = 0;
		lf.lfQuality = 0;
		lf.lfPitchAndFamily = FIXED_PITCH;
		lstrcpy(lf.lfFaceName, TEXT("빛의 계승자 Bold"));

		mNameFont = CreateFontIndirect(&lf);

		// 텍스트 폰트 로드
		path = std::wstring(L"..\\Resources\\\Font\\HeirofLightRegular.ttf").c_str();

		lf = LOGFONT{};
		lf.lfHeight = 35;			// 폰트 크기
		lf.lfWeight = 0;
		lf.lfEscapement = 0;
		lf.lfOrientation = 0;
		lf.lfWeight = 0;
		lf.lfItalic = 0;
		lf.lfUnderline = 0;
		lf.lfStrikeOut = 0;
		lf.lfCharSet = HANGEUL_CHARSET;
		lf.lfOutPrecision = 0;
		lf.lfClipPrecision = 0;
		lf.lfQuality = 0;
		lf.lfPitchAndFamily = FIXED_PITCH;
		lstrcpy(lf.lfFaceName, TEXT("빛의 계승자 Regular"));

		mScriptFont = CreateFontIndirect(&lf);

	}

	void HUD::WriteCounterText(HDC hdc, int posX, int posY, std::wstring _szMessage)
	{
		// 글자 배경 삭제, 얼라인 센터
		SetBkMode(hdc, 1);
		SetTextAlign(hdc, TA_CENTER);

		// 글자 색상, 폰트 변경
		COLORREF oldTextColor = SetTextColor(hdc, RGB(255, 255, 255));
		HFONT oldFont = (HFONT)SelectObject(hdc, mCounterFont);

		// 문자열 출력
		TextOut(hdc, posX, posY, _szMessage.c_str(), (int)_szMessage.length());

		// restore text color and font
		SetTextColor(hdc, oldTextColor);
		SelectObject(hdc, oldFont);
	}

	void HUD::WriteNameText(HDC hdc, int posX, int posY, int width, int height, std::wstring _szMessage)
	{
		// 글자 배경 삭제, 얼라인 센터
		SetBkMode(hdc, 1);
		SetTextAlign(hdc, TA_CENTER);

		// 글자 색상, 폰트 변경
		COLORREF oldTextColor = SetTextColor(hdc, RGB(112, 12, 41));
		HFONT oldFont = (HFONT)SelectObject(hdc, mNameFont);

		// 문자열 출력
		RECT rt = { posX, posY, posX + width, posY + height };
		DrawText(hdc, _szMessage.c_str(), -1, &rt, DT_LEFT | DT_NOCLIP);

		// restore text color and font
		SetTextColor(hdc, oldTextColor);
		SelectObject(hdc, oldFont);
	}

	void HUD::WriteScriptText(HDC hdc, int posX, int posY, int width, int height, std::wstring _szMessage)
	{
		// 글자 배경 삭제, 얼라인 센터
		SetBkMode(hdc, 1);
		SetTextAlign(hdc, TA_CENTER);

		// 글자 색상, 폰트 변경
		COLORREF oldTextColor = SetTextColor(hdc, RGB(255, 255, 255));
		HFONT oldFont = (HFONT)SelectObject(hdc, mScriptFont);

		// 문자열 출력
		RECT rt = { posX, posY, posX + width, posY + height };
		DrawText(hdc, _szMessage.c_str(), -1, &rt, DT_LEFT | DT_NOCLIP);


		// restore text color and font
		SetTextColor(hdc, oldTextColor);
		SelectObject(hdc, oldFont);
	}



	void HUD::Exit()
	{
		RemoveFontResource(L"HeirofLightRegular.ttf");
		RemoveFontResource(L"HeirofLightBold.ttf");

		DeleteObject(mCounterFont);
		DeleteObject(mNameFont);
		DeleteObject(mScriptFont);
	}

}
