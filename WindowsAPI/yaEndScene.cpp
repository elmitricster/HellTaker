#include "yaEndScene.h"
#include "yaInput.h"
#include "yaSceneManager.h"
#include "yaBgImageObject.h"
#include "yaObject.h"
#include "yaUIManager.h"
#include "yaHUD.h"
#include "yaPanel.h"
#include "yaTransition.h"
#include "yaTime.h"
#include "yaPlayScene.h"
#include "Common.h"
#include "yaResources.h"
#include "yaAnimator.h"
#include "yaImage.h"
#include "yaDialogButton.h"
#include "yaSound.h"

namespace ya
{
	EndScene::EndScene()
	{
	}

	EndScene::~EndScene()
	{
	}

	void EndScene::Initialize()
	{
		mTransSound = Resources::Load<Sound>(L"screen_changer", L"..\\Resources\\Sound\\screen_changer_part1.wav");
		mBgSound = Resources::Load<Sound>(L"Luminescent", L"..\\Resources\\Sound\\Luminescent.wav");
		mEnterSound = Resources::Load<Sound>(L"dialogue_text_end", L"..\\Resources\\Sound\\dialogue_text_end_01.wav");
	}

	void EndScene::Tick()
	{
		Scene::Tick();

		if (KEY_DOWN(eKeyCode::ENTER))
		{
			cutSceneNum++;
			mEnterSound->Play(false);
		}

		if (cutSceneNum == 1)
		{
			mBgImage->SetPos(Vector2{ 0.0f, 0.0f });
		}

		if (cutSceneNum == 2)
		{
			mBgImage->SetImage(L"EndBG02", L"end_CutScene02.bmp");
		}

		if (cutSceneNum == 3)
		{
			mBgImage->SetImage(L"EndBG03", L"end_CutScene03.bmp");
		}

		if (cutSceneNum == 4)
		{
			if (mCheck)
			{
				mBgSound->Play(true);
				mCheck = false;
			}

			mBgImage->Death();
		}

		if (cutSceneNum == 5)
		{
			UIManager::Push(eUIType::TPANEL);
			mTransSound->Play(false);
			SceneManager::ChangeScene(eSceneType::Title);
		}


	}

	void EndScene::Render(HDC hdc)
	{
		Scene::Render(hdc);

		std::wstring endDialog = L"그리하여 당신의 여정은 끝이 났다.";
		std::wstring endDialog2 = L"악마들을 지옥에서 무사히 데려왔다.\n그리고 헬테이커라고 알려지게 됐지.";
		std::wstring endDialog3 = L"하지만 쉽지 않은 삶일 터이다.\n분명 짧고, 또 고난으로 가득하리.";
		std::wstring endDialog4 = L"하지만 어떻게 살아가든 삶이란 고달픈 법.\n그러니 그 순간만큼은 즐기는 게 낫겠지.";
		std::wstring endDialog5 = L"플레이 해주셔서 감사합니다!";

		std::wstring endName = L"게임 제작";
		std::wstring endName2 = L"어소트락 44기 박주빈";
		


		if (cutSceneNum == 0)
		{
			WriteScriptText(hdc, 800, 670, 100, 100, endDialog);
		}
		else if (cutSceneNum == 1)
		{
			WriteScriptText(hdc, 800, 670, 100, 100, endDialog2);
		}
		else if (cutSceneNum == 2)
		{
			WriteScriptText(hdc, 800, 670, 100, 100, endDialog3);
		}
		else if (cutSceneNum == 3)
		{
			WriteScriptText(hdc, 800, 670, 100, 100, endDialog4);
		}
		else if (cutSceneNum == 4)
		{
			WriteNameText(hdc, 800, 150, 100, 100, endName);
			WriteScriptText(hdc, 800, 250, 100, 100, endName2);
			WriteCounterText(hdc, 800, 650, endDialog5);
		}
	}

	void EndScene::Enter()
	{
		LoadFont();

		mTransSound->Play(false);
		UIManager::Push(eUIType::TPANEL);

		mBGMSound->Stop(true);

		cutSceneNum = 0;
		mCheck = true;

		mBgImage = new BgImageObject(Vector2(-500.0f, -500.0f));
		mBgImage->SetImage(L"EndBG01", L"end_CutScene01.bmp");
		mBgImage->Initialize();

		AddGameObject(mBgImage, eColliderLayer::BackGround);

		mDialogBtn = ya::object::Instantiate<DialogButton>(Vector2{ 800, 800 }, eColliderLayer::CutScene);
	}

	void EndScene::Exit()
	{
		RemoveFontResource(L"HeirofLightRegular.ttf");
		RemoveFontResource(L"HeirofLightBold.ttf");

		DeleteObject(mCounterFont);
		DeleteObject(mNameFont);
		DeleteObject(mScriptFont);

		mBgSound->Stop(true);
	}

	void EndScene::LoadFont()
	{
		// 카운터 폰트 로드
		std::wstring path = std::wstring(L"..\\Resources\\\Font\\HeirofLightRegular.ttf");
		AddFontResource(path.c_str());

		LOGFONT lf = LOGFONT{};
		lf.lfHeight = 50;			// 폰트 크기
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
		path = std::wstring(L"..\\Resources\\\Font\\HeirofLightBold.ttf");
		AddFontResource(path.c_str());

		lf = LOGFONT{};
		lf.lfHeight = 80;			// 폰트 크기
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
		path = std::wstring(L"..\\Resources\\\Font\\HeirofLightRegular.ttf");
		AddFontResource(path.c_str());

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

	void EndScene::WriteCounterText(HDC hdc, int posX, int posY, std::wstring _szMessage)
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

	void EndScene::WriteNameText(HDC hdc, int posX, int posY, int width, int height, std::wstring _szMessage)
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

	void EndScene::WriteScriptText(HDC hdc, int posX, int posY, int width, int height, std::wstring _szMessage)
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
}