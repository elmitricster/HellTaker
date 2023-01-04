#include "yaDialogScene_Pand.h"
#include "yaInput.h"
#include "yaSceneManager.h"
#include "yaBgImageObject.h"
#include "yaObject.h"
#include "yaUIManager.h"
#include "yaHUD.h"
#include "yaPanel.h"
#include "yaTransition.h"
#include "yaTime.h"
#include "yaPlayer.h"
#include "yaPlayScene.h"
#include "yaDialogueNPC.h"
#include "Common.h"
#include "yaResources.h"
#include "yaAnimator.h"
#include "yaImage.h"
#include "yaDialogButton.h"
#include "yaSelectButton.h"
#include "yaSuccessEffect.h"
#include "yaDialogDeath.h"

namespace ya
{
	DialogScene_Pand::DialogScene_Pand()
	{
	}

	DialogScene_Pand::~DialogScene_Pand()
	{
	}

	void DialogScene_Pand::Initialize()
	{
		/*mBgImage = new BgImageObject(Vector2(0.0f, 150.0f));
		mBgImage->SetImage(L"dialogueBG01", L"dialogueBG01.bmp");
		mBgImage->Initialize();

		AddGameObject(mBgImage, eColliderLayer::BackGround);

		mDialogNPC = ya::object::Instantiate<DialogueNPC>(Vector2{ 790, 332 }, eColliderLayer::CutScene);
		mDialogBtn = ya::object::Instantiate<DialogButton>(Vector2{ 800, 800 }, eColliderLayer::CutScene);

		mSelectBtn[0] = ya::object::Instantiate<SelectButton>(Vector2{ -500, -500 }, eColliderLayer::CutScene);
		mSelectBtn[1] = ya::object::Instantiate<SelectButton>(Vector2{ -500, -500 }, eColliderLayer::CutScene);
		mSelectBtn[2] = ya::object::Instantiate<SelectButton>(Vector2{ -500, -500 }, eColliderLayer::CutScene);
		mSelectBtn[2]->SetImage(L"selectBtn", L"Button02.bmp");
		mSelectBtn[3] = ya::object::Instantiate<SelectButton>(Vector2{ -500, -500 }, eColliderLayer::CutScene);
		mSelectBtn[3]->SetImage(L"selectBtn", L"Button02.bmp");*/

	}

	void DialogScene_Pand::Tick()
	{
		Scene::Tick();

		if (KEY_DOWN(eKeyCode::ENTER))
		{
			cutSceneNum++;
		}

		if (cutSceneNum == 0)
		{

		}

		if (cutSceneNum == 1)
		{
			mDialogBtn->SetPos(Vector2{ -500.0f, -500.0f });

			mSelectBtn[0]->SetPos(Vector2{ 800, 770 });
			mSelectBtn[1]->SetPos(Vector2{ 800, 850 });

			if (KEY_DOWN(eKeyCode::S))
			{
				if (btnState < 2)
					btnState += 1;
			}

			if (KEY_DOWN(eKeyCode::W))
			{
				if (btnState > 0)
					btnState -= 1;
			}

			if (btnState == 0)
			{
				mSelectBtn[2]->SetPos(Vector2{ 800, 770 });
				mSelectBtn[3]->SetPos(Vector2{ -500, -500 });

				if (KEY_DOWN(eKeyCode::SPACE))
				{
					cutSceneNum = 5;
					mSelectBtn[0]->SetPos(Vector2{ -500, -500 });
					mSelectBtn[1]->SetPos(Vector2{ -500, -500 });
					mSelectBtn[2]->SetPos(Vector2{ -500, -500 });
					mSelectBtn[3]->SetPos(Vector2{ -500, -500 });

					mDialogBtn->SetPos(Vector2{ 800.0f, 800.0f });

				}
			}
			else if (btnState == 1)
			{
				mSelectBtn[2]->SetPos(Vector2{ -500, -500 });
				mSelectBtn[3]->SetPos(Vector2{ 800, 850 });
			}
		}
			
		if (cutSceneNum == 2 && mCheck)
		{
			mDialogNPC->SetImage(L"Pand_flust", L"Pand_flust.bmp");
			mDialogNPC->SetPos(Vector2{ 790, 352 });

			mSelectBtn[0]->SetPos(Vector2{ -500, -500 });
			mSelectBtn[1]->SetPos(Vector2{ -500, -500 });
			mSelectBtn[2]->SetPos(Vector2{ -500, -500 });

			mSuccessEffect = ya::object::Instantiate<SuccessEffect>(Vector2{ 900, 820 }, eColliderLayer::Effect);
			
			mCheck = false;
		}

		if (cutSceneNum == 3)
		{
			mSuccessEffect->Death();
			SceneManager::ChangeScene(eSceneType::End);
		}

		if (cutSceneNum == 6 && mCheck)
		{
			mDialogBtn->SetPos(Vector2{ -500, -500 });
			mBgImage->SetPos(Vector2{ -500, -500 });
			mDialogNPC->SetPos(Vector2{ -500, -500 });

			mDeathEffect = ya::object::Instantiate<DialogDeath>(Vector2{ 900, 450 }, eColliderLayer::Effect);

			mCheck = false;
		}

		if (cutSceneNum == 7)
		{
			mDeathEffect->Death();
			SceneManager::ChangeScene(eSceneType::Play);
		}
	}
	void DialogScene_Pand::Render(HDC hdc)
	{
		Scene::Render(hdc);

		/*wchar_t szFloat[50] = {};
		swprintf_s(szFloat, 50, L"End Scene");
		int strLen = wcsnlen_s(szFloat, 50);
		TextOut(hdc, 50, 30, szFloat, strLen);*/
		
		std::wstring npcName = L"● 피곤한 악마 판데모니카 ●";
		std::wstring npcDialog = L"지옥 고객센터의 판데모니카라고 합니다.\n무엇을 도와드릴까요?";
		std::wstring npcDialog2 = L"참 달콤한 제안이에요. 커피를 마시고 싶네요.\n피곤해서 정신을 못 차리겠어요.";
		std::wstring npcDialog3 = L"지옥을 살아서 빠져나갈 수 있으리라 생각한 거야?.\n꿈도 크셔라.";
		std::wstring npcDialog4 = L"판데모니카는 당신의 얼굴을 손아귀로 가져가더니\n전문가다운 부드러운 동작으로 목을 꺾어 버렸다.";

		std::wstring dialogBtn = L"우리 집에 가면 알 수 있겠지.";
		std::wstring dialogBtn2 = L"글쎄, 내가 널 도와줘야겠는데?";

		if (cutSceneNum == 0)
		{
			WriteNameText(hdc, 800, 610, 100, 100, npcName);
			WriteScriptText(hdc, 800, 650, 100, 100, npcDialog);
		}
		else if (cutSceneNum == 1)
		{
			WriteNameText(hdc, 800, 610, 100, 100, npcName);
			WriteScriptText(hdc, 800, 650, 100, 100, npcDialog);

			WriteScriptText(hdc, 800, 750, 100, 100, dialogBtn);
			WriteScriptText(hdc, 800, 830, 100, 100, dialogBtn2);
		}
		else if (cutSceneNum == 2)
		{
			WriteNameText(hdc, 800, 610, 100, 100, npcName);
			WriteScriptText(hdc, 800, 650, 100, 100, npcDialog2);
		}
		else if (cutSceneNum == 5)
		{
			WriteNameText(hdc, 800, 610, 100, 100, npcName);
			WriteScriptText(hdc, 800, 650, 100, 100, npcDialog3);
		}
		else if (cutSceneNum == 6)
		{
			WriteNameText(hdc, 800, 650, 100, 100, npcDialog4);
		}
		
	}

	void DialogScene_Pand::LoadFont()
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

	void DialogScene_Pand::WriteCounterText(HDC hdc, int posX, int posY, std::wstring _szMessage)
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

	void DialogScene_Pand::WriteNameText(HDC hdc, int posX, int posY, int width, int height, std::wstring _szMessage)
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

	void DialogScene_Pand::WriteScriptText(HDC hdc, int posX, int posY, int width, int height, std::wstring _szMessage)
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

	void DialogScene_Pand::Enter()
	{
		LoadFont();

		cutSceneNum = 0;
		mCheck = true;

		mBgImage = new BgImageObject(Vector2(0.0f, 150.0f));
		mBgImage->SetImage(L"dialogueBG01", L"dialogueBG01.bmp");
		mBgImage->Initialize();

		AddGameObject(mBgImage, eColliderLayer::BackGround);

		mDialogNPC = ya::object::Instantiate<DialogueNPC>(Vector2{ 790, 332 }, eColliderLayer::CutScene);
		mDialogBtn = ya::object::Instantiate<DialogButton>(Vector2{ 800, 800 }, eColliderLayer::CutScene);

		mSelectBtn[0] = ya::object::Instantiate<SelectButton>(Vector2{ -500, -500 }, eColliderLayer::CutScene);
		mSelectBtn[1] = ya::object::Instantiate<SelectButton>(Vector2{ -500, -500 }, eColliderLayer::CutScene);
		mSelectBtn[2] = ya::object::Instantiate<SelectButton>(Vector2{ -500, -500 }, eColliderLayer::CutScene);
		mSelectBtn[2]->SetImage(L"selectBtn", L"Button02.bmp");
		mSelectBtn[3] = ya::object::Instantiate<SelectButton>(Vector2{ -500, -500 }, eColliderLayer::CutScene);
		mSelectBtn[3]->SetImage(L"selectBtn", L"Button02.bmp");
	}

	void DialogScene_Pand::Exit()
	{
		RemoveFontResource(L"HeirofLightRegular.ttf");
		RemoveFontResource(L"HeirofLightBold.ttf");

		DeleteObject(mCounterFont);
		DeleteObject(mNameFont);
		DeleteObject(mScriptFont);

		mDialogNPC->Death();
		mDialogBtn->Death();
		mSelectBtn[0]->Death();
		mSelectBtn[1]->Death();
		mSelectBtn[2]->Death();
		mSelectBtn[3]->Death();
		mBgImage->Death();
	}
}
