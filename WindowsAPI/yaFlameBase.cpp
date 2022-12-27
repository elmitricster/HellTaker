#include "yaFlameBase.h"
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
	FlameBase::FlameBase()
	{

	}

	FlameBase::FlameBase(Vector2 position)
	{
		mGameObjType = eGameObjectType::FlameBase;
		SetName(L"FlameBase");
		SetPos(position);
		SetScale({ 0.8333f, 0.8333f });

		if (mImage == nullptr)
		{
			mImage = Resources::Load<Image>(L"FlameBase", L"..\\Resources\\Image\\FLAMEbase01.bmp");
		}

		//AddComponent(new Collider());
	}

	FlameBase::~FlameBase()
	{

	}

	void FlameBase::Tick()
	{
		GameObject::Tick();
	}

	void FlameBase::Render(HDC hdc)
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

		TransparentBlt(hdc, finalPos.x, finalPos.y, rect.x, rect.y
			, mImage->GetDC(), 0, 0, mImage->GetWidth(), mImage->GetHeight()
			, RGB(255, 0, 255));

		GameObject::Render(hdc);
	}

	void FlameBase::SetImage(const std::wstring& key, const std::wstring& fileName)
	{
		std::wstring path = L"..\\Resources\\Image\\";
		path += fileName;

		mImage = Resources::Load<Image>(key, path);
	}


}