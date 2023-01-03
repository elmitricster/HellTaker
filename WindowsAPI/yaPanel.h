#pragma once
#include "yaUiBase.h"

namespace ya
{
	class GameObject;
	class Panel : public UiBase
	{
	public:
		Panel(eUIType type);
		~Panel();

		virtual void OnInit() override;
		virtual void OnActive() override;
		virtual void OnInActive() override;
		virtual void OnTick() override;
		virtual void OnRender(HDC hdc) override;
		virtual void OnClear() override;

		void SetTarget(GameObject* target) { mTarget = target; }

		void SetPlayScene(PlayScene* scene) { mpScene = scene; }

	private:
		GameObject* mTarget;
		PlayScene* mpScene;
	};

}
