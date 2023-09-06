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

class Activity_header{
private:
    Runnable mRunnable;

    ImageView *header_tongsuo;
    ImageView *header_lvxin;
    TextView  *header_top_uv;
    TextView  *header_top_tds;
    ImageView *header_zhaoming;
    TextView  *header_zhileng;
    TextView  *header_zhibing;
    TextView  *header_time;
    ImageView *header_wifi;
    ImageView *header_setup;

    void onButtonClick(View&v);
public:
    static ViewGroup* parent;
    static Activity_header *ins() {
        static Activity_header ins;
        return &ins;
    }
    static void set_Parentview(ViewGroup* container){
        parent = container;
    }
    void upHeader();
    void checkState(bool &flag);

    Activity_header();
    ~Activity_header();
};