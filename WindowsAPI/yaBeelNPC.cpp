#include "yaBeelNPC.h"
#include "yaTime.h"
#include "yaSceneManager.h"
#include "yaInput.h"
#include "yaScene.h"
#include "yaImage.h"
#include "yaResources.h"
#include "yaAnimator.h"
#include "yaCollider.h"
#include "yaCamera.h"

namespace ya
{
	BeelNPC::BeelNPC()
	{
	}

	BeelNPC::BeelNPC(Vector2 position)
	{
		mGameObjType = eGameObjectType::Dialogue_NPC;
		SetName(L"Beelzebub");
		SetPos(position);
		SetScale({ 0.833f, 0.833f });

		if (mImage == nullptr)
		{
			mImage = Resources::Load<Image>(L"Beelzebub", L"..\\Resources\\Image\\Beel_idle.bmp");
		}
	}

	BeelNPC::~BeelNPC()
	{
	}

	void BeelNPC::Tick()
	{
		GameObject::Tick();
	}

	void BeelNPC::Render(HDC hdc)
	{
		Vector2 pos = GetPos();
		Vector2 scale = GetScale();

		Vector2 finalPos;
		finalPos.x = (pos.x - mImage->GetWidth() * (scale.x / 2.0f));
		finalPos.y = (pos.y - mImage->GetHeight() * (scale.y / 2.0f));

		Vector2 rect;
		rect.x = mImage->GetWidth() * scale.x;
		rect.y = mImage->GetHeight() * scale.y;

		finalPos = Camera::CalculatePos(finalPos);

		/*TransparentBlt(hdc, finalPos.x, finalPos.y, rect.x, rect.y
			, mImage->GetDC(), 0, 0, mImage->GetWidth(), mImage->GetHeight()
			, RGB(255, 0, 255));*/

		BLENDFUNCTION func = {};
		func.BlendOp = AC_SRC_OVER;
		func.BlendFlags = 0;
		func.AlphaFormat = AC_SRC_ALPHA;
		func.SourceConstantAlpha = 255; // 0 - 225


		AlphaBlend(hdc, finalPos.x, finalPos.y, rect.x, rect.y,
			mImage->GetDC(), 0, 0, mImage->GetWidth(), mImage->GetHeight()
			, func);

		GameObject::Render(hdc);
	}

	void BeelNPC::SetImage(const std::wstring& key, const std::wstring& fileName)
	{
		std::wstring path = L"..\\Resources\\Image\\";
		path += fileName;

		mImage = Resources::Load<Image>(key, path);
	}
}