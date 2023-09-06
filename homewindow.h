#pragma once
#include <widget/cdwindow.h>

#include <widget/relativelayout.h>
#include <widget/numberpicker.h>
#include <widget/textview.h>
#include <widget/linearlayout.h>
#include <core/inputeventsource.h>

#include <data.h>
#include <mode.h>
#include <lvxin.h>
#include <screenlight.h>
#include <network.h>
#include <page_setting.h>
#include <screen_saver.h>
#include <activity_header.h>
#include <popwindow_hint.h>
#include <page_set_time.h>
#include <page_uv.h>
#include <page_adapter.h>
#include <page_item.h>
#include <arc_seekbar.h>
#include <cdroid.h>
#include <R.h>
#include <cdlog.h>
#include <clocale>

class HomeWindow:public Window{
private:
    ViewPager   *page;
    TabLayout   *tabLayout;
    int prev_position = 2;          //初始化 为 第三个页面
    std::vector<WATER> items;
protected:

    void onTabSelectedListener(TabLayout::Tab& tab);
    void onTabSelected(TabLayout::Tab&tab);
    void screenSaver(bool bEnabled);

public:
   HomeWindow();
   ~HomeWindow();
};
