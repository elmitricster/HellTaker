#include "yaUIManager.h"
#include "yaHUD.h"
#include "yaButton.h"
#include "yaPanel.h"
#include "yaPlayer.h"
#include "yaTransition.h"
#include "yaPlayScene.h"

namespace ya
{
	std::unordered_map<eUIType, UiBase*> UIManager::mUIs;
	std::queue<eUIType> UIManager::mRequestUIQueue;
	std::stack<UiBase*> UIManager::mUIBases;
	UiBase* UIManager::mCurrentData = nullptr;

	void UIManager::Initialize()
	{
		// 여기에서 ui 메모리에 할당하면 된다.
		Button* button = new Button(eUIType::FUNC);
		mUIs.insert(std::make_pair(eUIType::FUNC, button));
		button->SetPos(Vector2(480.0f, 810.0f));
		button->ImageLoad(L"FuncUI", L"..\\Resources\\Image\\Func.bmp");
		
		HUD* leftHud = new HUD(eUIType::STEP);
		mUIs.insert(std::make_pair(eUIType::STEP, leftHud));
		leftHud->SetPos(Vector2(0.0f, 325.0f));
		leftHud->ImageLoad(L"mainUI", L"..\\Resources\\Image\\mainUI01.bmp");

		HUD* rightHud = new HUD(eUIType::ROUND);
		mUIs.insert(std::make_pair(eUIType::ROUND, rightHud));
		rightHud->SetPos(Vector2(1200.0f, 325.0f));
		rightHud->ImageLoad(L"mainUI2", L"..\\Resources\\Image\\mainUI02.bmp");

		HUD* leftHud2 = new HUD(eUIType::LEFTBG);
		mUIs.insert(std::make_pair(eUIType::LEFTBG, leftHud2));
		leftHud2->SetPos(Vector2(0.0f, 0.0f));
		leftHud2->ImageLoad(L"mainUI3", L"..\\Resources\\Image\\mainUI03.bmp");

		HUD* rightHud2 = new HUD(eUIType::RIGHTBG);
		mUIs.insert(std::make_pair(eUIType::RIGHTBG, rightHud2));
		rightHud2->SetPos(Vector2(1335.0f, 0.0f));
		rightHud2->ImageLoad(L"mainUI4", L"..\\Resources\\Image\\mainUI04.bmp");

		Panel* panel = new Panel(eUIType::TPANEL);
		mUIs.insert(std::make_pair(eUIType::TPANEL, panel));
		//panel->ImageLoad(L"TransParent", L"..\\Resources\\Image\\BackPack.bmp");
		//panel->SetPos(Vector2(-1.0f, -1.0f));

		Transition* trans = new Transition();
		panel->AddGameObject(trans);
		
	}

	void UIManager::OnLoad(eUIType type)
	{
		std::unordered_map<eUIType, UiBase*>::iterator iter = mUIs.find(type);
		if (iter == mUIs.end())
		{
			OnFail();
			return;
		}

		OnComplete(iter->second);
	}

	void UIManager::Tick()
	{
		std::stack<UiBase*> uiBases = mUIBases;
		while (!uiBases.empty())
		{
			UiBase* uiBase = uiBases.top();
			if (uiBase != nullptr)
			{
				uiBase->Tick();
			}
			uiBases.pop();
		}

		if (mRequestUIQueue.size() > 0)
		{
			//UI 로드 해줘
			eUIType requestUI = mRequestUIQueue.front();
			mRequestUIQueue.pop();

			OnLoad(requestUI);
		}
	}


	void UIManager::Render(HDC hdc)
	{
		std::stack<UiBase*> uiBases = mUIBases;
		std::stack<UiBase*> tempStack;

		// 뒤집어서 렌더링을 해준다.
		while (!uiBases.empty())
		{
			UiBase* uiBase = uiBases.top();
			tempStack.push(uiBase);
			uiBases.pop();
		}

		while (!tempStack.empty())
		{
			UiBase* uiBase = tempStack.top();
			if (uiBase != nullptr)
			{
				uiBase->Render(hdc);
			}
			tempStack.pop();
		}
	}

	void UIManager::OnComplete(UiBase* addUI)
	{
		if (addUI == nullptr)
			return;

		addUI->Initialize();
		addUI->Active();
		addUI->Tick();

		if (addUI->GetIsFullScreen())
		{
			std::stack<UiBase*> uiBases = mUIBases;
			while (!uiBases.empty())
			{
				UiBase* uiBase = uiBases.top();
				uiBases.pop();

				if (uiBase->GetIsFullScreen())
				{
					uiBase->InActive();
				}
			}
		}

		mUIBases.push(addUI);
	}

	void UIManager::OnFail()
	{
		mCurrentData = nullptr;
	}

	void UIManager::Release()
	{
		for (auto ui : mUIs)
		{
			delete ui.second;
			ui.second = nullptr;
		}
	}

	void UIManager::Push(eUIType type)
	{
		mRequestUIQueue.push(type);
	}

	void UIManager::Pop(eUIType type)
	{
		if (mUIBases.size() <= 0)
			return;

		std::stack<UiBase*> tempStack;

		UiBase* uiBase = nullptr;
		while (mUIBases.size() > 0)
		{
			uiBase = mUIBases.top();
			mUIBases.pop();
		
			// pop하는 ui가 전체화면 일경우에,
			// 남은 ui중에 전체화면인 가장 상단의 ui 를 활성화 해주어야한다.
			if (uiBase->GetType() == type)
			{
				if (uiBase->GetIsFullScreen())
				{
					std::stack<UiBase*> uiBases = mUIBases;
					while (!uiBases.empty())
					{
						UiBase* uiBase = uiBases.top();
						uiBases.pop();

						if (uiBase->GetIsFullScreen())
						{
							uiBase->Active();
							break;
						}
					}
				}
				uiBase->InActive();
				uiBase->UIClear();
			}
			else
			{
				tempStack.push(uiBase);
			}
		}

		while (tempStack.size())
		{
			uiBase = tempStack.top();
			tempStack.pop();
			mUIBases.push(uiBase);
		}

	}
	
}