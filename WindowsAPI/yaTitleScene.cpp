#include "yaTitleScene.h"
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
#include "yaBeelNPC.h"
#include "yaSelectButton.h"
#include "yaSound.h"
#include "yaSoundManager.h"

namespace ya
{
	TitleScene::TitleScene()
	{
	}

	TitleScene::~TitleScene()
	{
	}

	void TitleScene::Initialize()
	{
		mBgSound = Resources::Load<Sound>(L"Apropos", L"..\\Resources\\Sound\\Apropos.wav");
		mEnterSound = Resources::Load<Sound>(L"dialogue_text_end", L"..\\Resources\\Sound\\dialogue_text_end_01.wav");
		mBtnChangeSound = Resources::Load<Sound>(L"button_menu_highlight", L"..\\Resources\\Sound\\button_menu_highlight_01.wav");
		mBtnSelectSound = Resources::Load<Sound>(L"button_menu_confirm", L"..\\Resources\\Sound\\button_menu_confirm_01.wav");
	}

	void TitleScene::Tick()
	{
		Scene::Tick();

		//mBgImage->SetPos(mBgImage->GetPos() + Vector2(10.0f * Time::DeltaTime(), 0.0f));
		//mBgImage2->SetPos(mBgImage2->GetPos() + Vector2(10.0f * Time::DeltaTime(), 0.0f));

		if (KEY_DOWN(eKeyCode::ENTER))
		{
			cutSceneNum++;

			mEnterSound->Play(false);
		}

		if (cutSceneNum == 1)
		{
			mDialogNPC->SetPos(Vector2{ 790, 291 });
		}

		if (cutSceneNum == 2)
		{
			mDialogBtn->SetPos(Vector2{ -500, -500 });
			mSelectBtn[0]->SetPos(Vector2{ 800, 700 });
			mSelectBtn[1]->SetPos(Vector2{ 800, 770 });
			mSelectBtn[2]->SetPos(Vector2{ 800, 840 });

			if (KEY_DOWN(eKeyCode::S))
			{
				mBtnChangeSound->Play(false);

				if (btnState < 3)
					btnState += 1;
			}

			if (KEY_DOWN(eKeyCode::W))
			{
				mBtnChangeSound->Play(false);

				if (btnState > 0)
					btnState -= 1;
			}

			if (btnState == 0)
			{
				mSelectBtn[3]->SetPos(Vector2{ 800, 700 });
				mSelectBtn[4]->SetPos(Vector2{ -500, -500 });
				mSelectBtn[5]->SetPos(Vector2{ -500, -500 });
			}
			else if (btnState == 1)
			{
				mSelectBtn[4]->SetPos(Vector2{ 800, 770 });
				mSelectBtn[3]->SetPos(Vector2{ -500, -500 });
				mSelectBtn[5]->SetPos(Vector2{ -500, -500 });
			}
			else if (btnState == 2)
			{
				mSelectBtn[5]->SetPos(Vector2{ 800, 840 });
				mSelectBtn[3]->SetPos(Vector2{ -500, -500 });
				mSelectBtn[4]->SetPos(Vector2{ -500, -500 });

				if (KEY_DOWN(eKeyCode::SPACE))
				{
					ExitProcess(0);
				}
			}
		}

		if (cutSceneNum == 3)
		{
			if (mCheck)
			{
				mBtnSelectSound->Play(false);
				mCheck = false;
			}

			mDialogBtn->SetPos(Vector2{ 800, 800 });

			mSelectBtn[0]->Death();
			mSelectBtn[1]->Death();
			mSelectBtn[2]->Death();
			mSelectBtn[3]->Death();

		}

		if (cutSceneNum == 4)
		{
			
		}

		if (cutSceneNum == 5)
		{
			mDialogNPC->SetPos(Vector2{ -500, -500 });
		}

		if (cutSceneNum == 6)
		{
			mBgImage->SetImage(L"titleCS01", L"title_CutScene01.bmp");
			mBgImage->SetPos(Vector2{ 0.0f, 0.0f });
		}

		if (cutSceneNum == 7)
		{
			mBgImage->SetImage(L"titleCS02", L"title_CutScene02.bmp");
			mBgImage->SetPos(Vector2{ 0.0f, 0.0f });
		}

		if (cutSceneNum == 8)
		{
			mBgImage->SetImage(L"titleCS03", L"title_CutScene03.bmp");
			mBgImage->SetPos(Vector2{ 0.0f, 0.0f });
		}

		if (cutSceneNum == 9)
		{
			SceneManager::ChangeScene(eSceneType::Play);
		}

		
	}

	void TitleScene::Render(HDC hdc)
	{
		Scene::Render(hdc);

		/*wchar_t szFloat[50] = {};
		swprintf_s(szFloat, 50, L"Title Scene");
		int strLen = wcsnlen_s(szFloat, 50);
		TextOut(hdc, 10, 30, szFloat, strLen);*/

		std::wstring npcName = L"● 위대한 파리 베엘제붑 ●";
		std::wstring titleDialog = L"당신은 공허에 휩싸인 것을 느꼈다.\n계속 하려면 [ENTER]키를 누르시오.";
		std::wstring titleDialog2 = L"반갑네 인간이여. 나를 괘념치 말게.\n그저 오랜 친구 베엘제붑일세.";
		std::wstring titleDialog3 = L"또 헬테이커의 이야기를 들려달라고? 재미있군...";
		std::wstring titleDialog4 = L"혹시 해설자가 필요하진 않은가?";
		std::wstring titleDialog5 = L"허락해준다면 참 고맙겠어.";
		std::wstring titleDialog6 = L"어느날 당신은 악마들로 가득찬 하렘을\n꿈꾸고 일어났네.";
		std::wstring titleDialog7 = L"하지만 결코 이루기 쉽지 않은 꿈이지.\n어쩌면 네 목숨을 앗아갈지도 모르고.";
		std::wstring titleDialog8 = L"\"악마 하렘이 달렸다면, 그 어떤 대가도 싸지.\"\n그리하여 당신은 지옥으로 모험을 떠났네.";

		std::wstring titleBtn = L"새 게임";
		std::wstring titleBtn2 = L"챕터 선택";
		std::wstring titleBtn3 = L"나가기";

		if (cutSceneNum == 0)
		{
			WriteScriptText(hdc, 800, 670, 100, 100, titleDialog);
		}
		else if (cutSceneNum == 1)
		{
			WriteNameText(hdc, 800, 610, 100, 100, npcName);
			WriteScriptText(hdc, 800, 670, 100, 100, titleDialog2);
		}
		else if (cutSceneNum == 2)
		{
			WriteNameText(hdc, 800, 610, 100, 100, npcName);
			WriteScriptText(hdc, 800, 680, 100, 100, titleBtn);
			WriteScriptText(hdc, 800, 750, 100, 100, titleBtn2);
			WriteScriptText(hdc, 800, 820, 100, 100, titleBtn3);
		}
		else if (cutSceneNum == 3)
		{
			WriteNameText(hdc, 800, 610, 100, 100, npcName);
			WriteScriptText(hdc, 800, 670, 100, 100, titleDialog3);
		}
		else if (cutSceneNum == 4)
		{
			WriteNameText(hdc, 800, 610, 100, 100, npcName);
			WriteScriptText(hdc, 800, 670, 100, 100, titleDialog4);
		}
		else if (cutSceneNum == 5)
		{
			WriteScriptText(hdc, 800, 670, 100, 100, titleDialog5);
		}
		else if (cutSceneNum == 6)
		{
			WriteScriptText(hdc, 800, 670, 100, 100, titleDialog6);
		}
		else if (cutSceneNum == 7)
		{
			WriteScriptText(hdc, 800, 670, 100, 100, titleDialog7);
		}
		else if (cutSceneNum == 8)
		{
			WriteScriptText(hdc, 800, 670, 100, 100, titleDialog8);
		}
	}

	void TitleScene::LoadFont()
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
		path = std::wstring(L"..\\Resources\\\Font\\HeirofLightBold.ttf");
		AddFontResource(path.c_str());

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

	void TitleScene::WriteCounterText(HDC hdc, int posX, int posY, std::wstring _szMessage)
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

	void TitleScene::WriteNameText(HDC hdc, int posX, int posY, int width, int height, std::wstring _szMessage)
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

	void TitleScene::WriteScriptText(HDC hdc, int posX, int posY, int width, int height, std::wstring _szMessage)
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


	void TitleScene::Enter()
	{
		LoadFont();

		mBgSound->Play(true);
		
		cutSceneNum = 0;

		mBgImage = new BgImageObject(Vector2(0.0f, 150.0f));
		mBgImage->SetImage(L"TitleBG01", L"TitleBG01.bmp");
		mBgImage->SetScale(Vector2{ 0.833f, 0.833f });

		/*mBgImage2 = new BgImageObject(Vector2(0.0f, 300.0f));
		mBgImage2->SetImage(L"TitleBG02", L"TitleBG02.bmp");
		mBgImage2->SetScale(Vector2{ 0.833f, 0.833f });*/
		
		AddGameObject(mBgImage, eColliderLayer::BackGround);
		//AddGameObject(mBgImage2, eColliderLayer::BackGround);
		

		mDialogNPC = ya::object::Instantiate<BeelNPC>(Vector2{ -500, -500 }, eColliderLayer::CutScene);
		mDialogBtn = ya::object::Instantiate<DialogButton>(Vector2{ 800, 800 }, eColliderLayer::CutScene);
		mSelectBtn[0] = ya::object::Instantiate<SelectButton>(Vector2{ -500, -500 }, eColliderLayer::CutScene);
		mSelectBtn[1] = ya::object::Instantiate<SelectButton>(Vector2{ -500, -500 }, eColliderLayer::CutScene);
		mSelectBtn[2] = ya::object::Instantiate<SelectButton>(Vector2{ -500, -500 }, eColliderLayer::CutScene);
		mSelectBtn[3] = ya::object::Instantiate<SelectButton>(Vector2{ -500, -500 }, eColliderLayer::CutScene);
		mSelectBtn[3]->SetImage(L"selectBtn", L"Button02.bmp");
		mSelectBtn[4] = ya::object::Instantiate<SelectButton>(Vector2{ -500, -500 }, eColliderLayer::CutScene);
		mSelectBtn[4]->SetImage(L"selectBtn", L"Button02.bmp");
		mSelectBtn[5] = ya::object::Instantiate<SelectButton>(Vector2{ -500, -500 }, eColliderLayer::CutScene);
		mSelectBtn[5]->SetImage(L"selectBtn", L"Button02.bmp");

	}

	void TitleScene::Exit()
	{
		mBgSound->Stop(true);

		RemoveFontResource(L"HeirofLightRegular.ttf");
		RemoveFontResource(L"HeirofLightBold.ttf");

		DeleteObject(mCounterFont);
		DeleteObject(mNameFont);
		DeleteObject(mScriptFont);
		
		mBgImage->Death();
		mDialogNPC->Death();
		mDialogBtn->Death();
		mSelectBtn[0]->Death();
		mSelectBtn[1]->Death();
		mSelectBtn[2]->Death();
		mSelectBtn[3]->Death();
		mSelectBtn[4]->Death();
		mSelectBtn[5]->Death();
	}
}
