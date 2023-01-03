#include "yaPanel.h"
#include "yaImage.h"
#include "yaUIManager.h"
#include "yaPlayer.h"
#include "yaAnimator.h"
#include "yaResources.h"
#include "Common.h"
#include "yaPlayScene.h"
#include "yaEndScene.h"

namespace ya
{
    Panel::Panel(eUIType type)
        : UiBase(type)
    {
        SetScale({ 0.8333f, 0.8333f });
    }

    Panel::~Panel()
    {
    }

    void Panel::OnInit()
    {
    }

    void Panel::OnActive()
    {

    }

    void Panel::OnInActive()
    {

    }

    void Panel::OnTick()
    {

    }

    void Panel::OnRender(HDC hdc)
    {
        if (mImage == nullptr)
            return;

        if (mTarget == nullptr)
            return;

       /* BLENDFUNCTION func = {};
        func.BlendOp = AC_SRC_OVER;
        func.BlendFlags = 0;
        func.AlphaFormat = AC_SRC_ALPHA;
        func.SourceConstantAlpha = 255;

        AlphaBlend(hdc, (int)mScreenPos.x, (int)mScreenPos.y
            , mImage->GetWidth(), mImage->GetHeight()
            , mImage->GetDC(), 0, 0, mImage->GetWidth(), mImage->GetHeight(), func);*/

        /*TransparentBlt(hdc, (int)mScreenPos.x, (int)mScreenPos.y
            , mImage->GetWidth() * GetScale().x, mImage->GetHeight() * GetScale().y
            , mImage->GetDC(), 0, 0, mImage->GetWidth(), mImage->GetHeight(), RGB(255, 0, 255));*/

        TransparentBlt(hdc, (int)mScreenPos.x, (int)mScreenPos.y
            , mImage->GetWidth() * GetScale().x, mImage->GetHeight() * GetScale().y
            , mImage->GetDC(), 0, 0, mImage->GetWidth(), mImage->GetHeight(), RGB(255, 0, 255));
    }

    void Panel::OnClear()
    {

    }


}
