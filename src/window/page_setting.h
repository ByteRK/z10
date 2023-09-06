#pragma once
#include <widget/cdwindow.h>

#include <homewindow.h>

// #include "page/lvxin.h"
// #include "page/screenlight.h"
// #include "page/network.h"
// #include "page/mode.h"

class Page_setting : public Window
{
private:
    Switch *sw_cryogen;
    Switch *sw_ice;
    Switch *sw_lock;

protected:
    void onWashOptionClick(View &);
    void onSettingImgClick(View &);
    void onSettingBtClick(View &);

public:
    Page_setting();
    ~Page_setting();
};
