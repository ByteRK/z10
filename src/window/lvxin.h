#pragma once
#include <widget/cdwindow.h>

#include <arc_seekbar.h>

class LvXinWindow :public Window {
private:
    int mCurScrollX;
    int mOldScrollX;
    int screenWidth;
    ValueAnimator* anim;
protected:
public:
    LvXinWindow();
    ~LvXinWindow();
};
