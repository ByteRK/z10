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

class Page_set_time:public Window{
private:
    NumberPicker *picker_set_year;
    NumberPicker *picker_set_mon;
    NumberPicker *picker_set_day;
    NumberPicker *picker_set_hour;
    NumberPicker *picker_set_min;

    void onValueChangedListener(NumberPicker& picker,int num_old,int num_new);
    void setMaxDay(int year,int mon);
    void setFormatter(NumberPicker *p);

    void onButtonClicnListener(View&v);
public:
    Page_set_time();
    ~Page_set_time();
};

