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

class Screen_saver:public Window{
private:
    Runnable mRunnable;

    void onSeekBarChange(cdroid::AbsSeekBar& seekbar, int progress, bool fromUser);
public:
    static Screen_saver *mins;

    static Screen_saver *ins() {
        if(mins == nullptr)
            mins = new Screen_saver;
        return mins;
    }

    static bool isPresent();
    Screen_saver();
    ~Screen_saver();
};