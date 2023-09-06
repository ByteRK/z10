#pragma once
#include <widget/cdwindow.h>

#include <widget/relativelayout.h>
#include <widget/numberpicker.h>
#include <widget/textview.h>

#include <data.h>
#include <arc_seekbar.h>
#include <cdroid.h>
#include <R.h>
#include <cdlog.h>
#include <clocale>



class MyLinearLayout:public LinearLayout{
public:
    MyLinearLayout(WATER &myitem);
    ~MyLinearLayout();

private:
    Runnable mRunnable_ArcWD;
    Runnable mRunnable_btnout;
    void initLinearPage(FrameLayout *linear,WATER &myitem);
    void setLinearData(LinearLayout *linear,WATER &myitem);
    void onChangerListener(View &v, int progress);

    void onCslReduceButtonClick(View&v);
    void onCslAddButtonClick(View&v);

    void onWdReduceClick(View&v);
    void onWdAddClick(View&v);

    void onTextoutClick(View&v);

    ArcSeekBar *mArcWendu = nullptr;                      //温度   的 ArcSeekBar 控件，即 圆形 滑动条
    TextView   *mTextWendu = nullptr;                     //温度   的 textView控件

    ArcSeekBar *mArcChushuiliang = nullptr;               //出水量 的 ArcSeekBar 控件，即 圆形 滑动条
    TextView   *mTextChushuiliang = nullptr;              //出水量 的 textView控件

    ImageView  *Image = nullptr;                          //图片
    ImageView  *Image2 = nullptr;                          //图片2

    Button *btn_out = nullptr;
};