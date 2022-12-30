#include "yaLoveSign.h"
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
	LoveSign::LoveSign()
	{
	}

	LoveSign::LoveSign(Vector2 position)
	{
		mGameObjType = eGameObjectType::LoveSign;
		SetName(L"LoveSign");
		SetPos(position);
		SetScale({ 0.8333f, 0.8333f });

		if (mImage == nullptr)
		{
			mImage = Resources::Load<Image>(L"LoveSign", L"..\\Resources\\Image\\LoveSign.bmp");
		}
	}

	LoveSign::~LoveSign()
	{
	}

	void LoveSign::Tick()
	{
		ChangePos();
		GameObject::Tick();
	}

	void LoveSign::Render(HDC hdc)
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

	void LoveSign::ChangePos()
	{

		sum += Time::DeltaTime();

		if (sum > 0.5f)
		{
			if (mGravity)
			{
				mGravity = false;
			}
			else
			{
				mGravity = true;
			}

			sum = 0.0f;
		}


		if (mGravity)
		{
			SetPos(GetPos() + Vector2(0.0, 10.0f * Time::DeltaTime()) );
		}
		else
		{
			SetPos(GetPos() + Vector2(0.0, -10.0f * Time::DeltaTime()) );
		}
	}
}