#pragma once
#include <widget/cdwindow.h>

#include <widget/relativelayout.h>
#include <widget/numberpicker.h>
#include <widget/textview.h>

#include <homewindow.h>
#include <cdroid.h>
#include <R.h>
#include <cdlog.h>
#include <clocale>

// 弹窗中 需要开启的功能
typedef enum Open_Func {
    OPEN_FUNC_COOL,
    OPEN_FUNC_ICE,
    OPEN_FUNC_COOL_ICE
}Func;


class Popwindiw_text_hint:public Window{
private:
    TextView *text_view;
    TextView *text_cancel;
    TextView *text_enter;
    int setting_fun;

    void onClickBackListener(View&v);
public:
    Popwindiw_text_hint(int func,std::string text,std::string enter = "确定",std::string cancel = "取消");
    ~Popwindiw_text_hint();
};


class Popwindiw_tip_hint:public Window{
private:
    void onClickBackListener(View&v);
public:
    Popwindiw_tip_hint(int func);
    ~Popwindiw_tip_hint();
};
