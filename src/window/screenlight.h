#pragma once
#include <widget/cdwindow.h>

class ScreenLightWindow : public Window
{
private:
   int mCurScrollX;
   int mOldScrollX;
   int screenWidth;
   ValueAnimator *anim;

protected:

public:
   ScreenLightWindow();
   ~ScreenLightWindow();
};
