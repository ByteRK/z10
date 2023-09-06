#pragma once
#include <widget/cdwindow.h>

#include <widget/relativelayout.h>
#include <widget/numberpicker.h>
#include <widget/textview.h>

#include <cdroid.h>
#include <R.h>
#include <cdlog.h>
#include <clocale>

class Page_uv:public Window{
private:
    NumberPicker *picker_star_hour;
    NumberPicker *picker_star_min;
    NumberPicker *picker_end_hour;
    NumberPicker *picker_end_min;

    void onClickBackListener(View&v);
    void setFormatter(NumberPicker *p);
public:
    Page_uv();
    ~Page_uv();
};

