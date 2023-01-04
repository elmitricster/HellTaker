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

		mBgImage = new BgImageObject(Vector2(0.0f, 150.0f));
		mBgImage->SetImage(L"TitleBG01", L"TitleBG01.bmp");
		mBgImage->Initialize();

		AddGameObject(mBgImage, eColliderLayer::BackGround);

		mDialogNPC = ya::object::Instantiate<BeelNPC>(Vector2{ -500, -500 }, eColliderLayer::CutScene);
		mDialogBtn = ya::object::Instantiate<DialogButton>(Vector2{ 800, 800 }, eColliderLayer::CutScene);
		mSelectBtn[0] = ya::object::Instantiate<SelectButton>(Vector2{-500, -500}, eColliderLayer::CutScene);
		mSelectBtn[1] = ya::object::Instantiate<SelectButton>(Vector2{ -500, -500 }, eColliderLayer::CutScene);
		mSelectBtn[2] = ya::object::Instantiate<SelectButton>(Vector2{ -500, -500 }, eColliderLayer::CutScene);
		mSelectBtn[3] = ya::object::Instantiate<SelectButton>(Vector2{ -500, -500 }, eColliderLayer::CutScene);
		mSelectBtn[3]->SetImage(L"selectBtn", L"Button02.bmp");
		mSelectBtn[4] = ya::object::Instantiate<SelectButton>(Vector2{ -500, -500 }, eColliderLayer::CutScene);
		mSelectBtn[4]->SetImage(L"selectBtn", L"Button02.bmp");
		mSelectBtn[5] = ya::object::Instantiate<SelectButton>(Vector2{ -500, -500 }, eColliderLayer::CutScene);
		mSelectBtn[5]->SetImage(L"selectBtn", L"Button02.bmp");
	}

	void TitleScene::Tick()
	{
		Scene::Tick();

		/*if (KEY_DOWN(eKeyCode::N))
		{
			SceneManager::ChangeScene(eSceneType::Play);
		}*/

		if (KEY_DOWN(eKeyCode::ENTER))
		{
			cutSceneNum++;

			mEnterSound->Play(false);
		}

		if (cutSceneNum == 1)
		{
			mDialogNPC->SetPos(Vector2{ 790, 291 });
			//mDialogBtn->Death();
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

		std::wstring npcName = L"�� ������ �ĸ� �������� ��";
		std::wstring titleDialog = L"����� ���㿡 �۽��� ���� ������.\n��� �Ϸ��� [ENTER]Ű�� �����ÿ�.";
		std::wstring titleDialog2 = L"�ݰ��� �ΰ��̿�. ���� ����ġ ����.\n���� ���� ģ�� ���������ϼ�.";
		std::wstring titleDialog3 = L"�� ������Ŀ�� �̾߱⸦ ����޶��? ����ֱ�...";
		std::wstring titleDialog4 = L"Ȥ�� �ؼ��ڰ� �ʿ����� ������?";
		std::wstring titleDialog5 = L"������شٸ� �� ���ھ�.";
		std::wstring titleDialog6 = L"����� ����� �Ǹ���� ������ �Ϸ���\n�޲ٰ� �Ͼ��.";
		std::wstring titleDialog7 = L"������ ���� �̷�� ���� ���� ������.\n��¼�� �� ����� �Ѿư����� �𸣰�.";
		std::wstring titleDialog8 = L"\"�Ǹ� �Ϸ��� �޷ȴٸ�, �� � �밡�� ����.\"\n�׸��Ͽ� ����� �������� ������ ������.";

		std::wstring titleBtn = L"�� ����";
		std::wstring titleBtn2 = L"é�� ����";
		std::wstring titleBtn3 = L"������";

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
		// ī���� ��Ʈ �ε�
		std::wstring path = std::wstring(L"..\\Resources\\\Font\\HeirofLightRegular.ttf");
		AddFontResource(path.c_str());

		LOGFONT lf = LOGFONT{};
		lf.lfHeight = 150;			// ��Ʈ ũ��
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
		lstrcpy(lf.lfFaceName, TEXT("���� ����� Regular"));

		mCounterFont = CreateFontIndirect(&lf);

		// �̸� ��Ʈ �ε�
		path = std::wstring(L"..\\Resources\\\Font\\HeirofLightBold.ttf");
		AddFontResource(path.c_str());

		lf = LOGFONT{};
		lf.lfHeight = 40;			// ��Ʈ ũ��
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
		lstrcpy(lf.lfFaceName, TEXT("���� ����� Bold"));

		mNameFont = CreateFontIndirect(&lf);

		// �ؽ�Ʈ ��Ʈ �ε�
		path = std::wstring(L"..\\Resources\\\Font\\HeirofLightRegular.ttf");
		AddFontResource(path.c_str());

		lf = LOGFONT{};
		lf.lfHeight = 35;			// ��Ʈ ũ��
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
		lstrcpy(lf.lfFaceName, TEXT("���� ����� Regular"));

		mScriptFont = CreateFontIndirect(&lf);
	}

	void TitleScene::WriteCounterText(HDC hdc, int posX, int posY, std::wstring _szMessage)
	{
		// ���� ��� ����, ����� ����
		SetBkMode(hdc, 1);
		SetTextAlign(hdc, TA_CENTER);

		// ���� ����, ��Ʈ ����
		COLORREF oldTextColor = SetTextColor(hdc, RGB(255, 255, 255));
		HFONT oldFont = (HFONT)SelectObject(hdc, mCounterFont);

		// ���ڿ� ���
		TextOut(hdc, posX, posY, _szMessage.c_str(), (int)_szMessage.length());

		// restore text color and font
		SetTextColor(hdc, oldTextColor);
		SelectObject(hdc, oldFont);
	}

	void TitleScene::WriteNameText(HDC hdc, int posX, int posY, int width, int height, std::wstring _szMessage)
	{
		// ���� ��� ����, ����� ����
		SetBkMode(hdc, 1);
		SetTextAlign(hdc, TA_CENTER);

		// ���� ����, ��Ʈ ����
		COLORREF oldTextColor = SetTextColor(hdc, RGB(112, 12, 41));
		HFONT oldFont = (HFONT)SelectObject(hdc, mNameFont);

		// ���ڿ� ���
		RECT rt = { posX, posY, posX + width, posY + height };
		DrawText(hdc, _szMessage.c_str(), -1, &rt, DT_LEFT | DT_NOCLIP);

		// restore text color and font
		SetTextColor(hdc, oldTextColor);
		SelectObject(hdc, oldFont);
	}

	void TitleScene::WriteScriptText(HDC hdc, int posX, int posY, int width, int height, std::wstring _szMessage)
	{
		// ���� ��� ����, ����� ����
		SetBkMode(hdc, 1);
		SetTextAlign(hdc, TA_CENTER);

		// ���� ����, ��Ʈ ����
		COLORREF oldTextColor = SetTextColor(hdc, RGB(255, 255, 255));
		HFONT oldFont = (HFONT)SelectObject(hdc, mScriptFont);

		// ���ڿ� ���
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

	}

	void TitleScene::Exit()
	{
		mBgSound->Stop(true);

		RemoveFontResource(L"HeirofLightRegular.ttf");
		RemoveFontResource(L"HeirofLightBold.ttf");

		DeleteObject(mCounterFont);
		DeleteObject(mNameFont);
		DeleteObject(mScriptFont);
	}
}
