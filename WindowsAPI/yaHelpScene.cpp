#include "yaHelpScene.h"
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
#include "yaBeelNPC.h"
#include "Common.h"
#include "yaResources.h"
#include "yaAnimator.h"
#include "yaImage.h"
#include "yaDialogButton.h"
#include "yaSound.h"

namespace ya
{
	HelpScene::HelpScene()
	{
	}

	HelpScene::~HelpScene()
	{
	}

	void HelpScene::Initialize()
	{
		mEnterSound = Resources::Load<Sound>(L"dialogue_text_end", L"..\\Resources\\Sound\\dialogue_text_end_01.wav");
		mDialogStartSound = Resources::Load<Sound>(L"dialogue_start", L"..\\Resources\\Sound\\dialogue_start_01.wav");
	}

	void HelpScene::Tick()
	{
		Scene::Tick();

		if (KEY_DOWN(eKeyCode::ENTER))
		{
			cutSceneNum++;
			mEnterSound->Play(false);
		}

		if (cutSceneNum == 4)
		{
			SceneManager::ChangeScene(eSceneType::Play);
		}

	}

	void HelpScene::Render(HDC hdc)
	{
		Scene::Render(hdc);

		std::wstring npcName = L"�� ������ �ĸ� �������� ��";
		std::wstring helpDialog = L"������ ���ϰ� ���� ��������� ��� �̰� ������.";
		std::wstring helpDialog2 = L"���� �Ϳ��� �Ǹ����� ã�� �� ����.";
		std::wstring helpDialog3 = L"�׸��� �󸶳� �Ϳ��� ����, �� �ؼ����� ������.";
		std::wstring helpDialog4 = L"���� �Ϸ��� ��︮�� ó�ڸ� ã�Ƽ� ������ ���� �����̳� ������.";


		if (cutSceneNum == 0)
		{
			WriteNameText(hdc, 800, 610, 100, 100, npcName);
			WriteScriptText(hdc, 800, 670, 100, 100, helpDialog);
		}
		else if (cutSceneNum == 1)
		{
			WriteNameText(hdc, 800, 610, 100, 100, npcName);
			WriteScriptText(hdc, 800, 670, 100, 100, helpDialog2);
		}
		else if (cutSceneNum == 2)
		{
			WriteNameText(hdc, 800, 610, 100, 100, npcName);
			WriteScriptText(hdc, 800, 670, 100, 100, helpDialog3);
		}
		else if (cutSceneNum == 3)
		{
			WriteNameText(hdc, 800, 610, 100, 100, npcName);
			WriteScriptText(hdc, 800, 670, 100, 100, helpDialog4);
		}

	}

	void HelpScene::Enter()
	{
		mDialogStartSound->Play(false);

		LoadFont();

		cutSceneNum = 0;

		mBgImage = new BgImageObject(Vector2(0.0f, 150.0f));
		mBgImage->SetImage(L"dialogueBG01", L"dialogueBG01.bmp");
		mBgImage->Initialize();

		AddGameObject(mBgImage, eColliderLayer::BackGround);

		mDialogNPC = ya::object::Instantiate<BeelNPC>(Vector2{ 790, 291 }, eColliderLayer::CutScene);
		mDialogBtn = ya::object::Instantiate<DialogButton>(Vector2{ 800, 800 }, eColliderLayer::CutScene);
	}

	void HelpScene::Exit()
	{
		RemoveFontResource(L"HeirofLightRegular.ttf");
		RemoveFontResource(L"HeirofLightBold.ttf");

		DeleteObject(mCounterFont);
		DeleteObject(mNameFont);
		DeleteObject(mScriptFont);

		mDialogNPC->Death();
		mDialogBtn->Death();
		mBgImage->Death();
	}

	void HelpScene::LoadFont()
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

	void HelpScene::WriteCounterText(HDC hdc, int posX, int posY, std::wstring _szMessage)
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

	void HelpScene::WriteNameText(HDC hdc, int posX, int posY, int width, int height, std::wstring _szMessage)
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

	void HelpScene::WriteScriptText(HDC hdc, int posX, int posY, int width, int height, std::wstring _szMessage)
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
}