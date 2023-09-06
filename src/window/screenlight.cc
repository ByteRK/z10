#include <cdroid.h>
#include <R.h>
#include <cdlog.h>

#include "screenlight.h"

ScreenLightWindow::ScreenLightWindow() : Window(0, 0, -1, -1) {
    LayoutInflater::from(getContext())->inflate("@layout/screenlight", this);

    LinearLayout* box = (LinearLayout*)findViewById(z10::R::id::linearLayout);
    box->setOnClickListener([this](View& view)mutable {
        LOGD("窗口即将关闭");
        this->close();
        });

    box = (LinearLayout*)findViewById(z10::R::id::setting_screenLight_Box);
    box->setOnClickListener([this](View& view)mutable {
        LOGD("窗口不关闭");
        });

    TextView* bt = (TextView*)findViewById(z10::R::id::setting_screenLight_cancel);
    bt->setOnClickListener([this](View& view)mutable {
        LOGD("已取消");
        this->close();
        });
    bt = (TextView*)findViewById(z10::R::id::setting_screenLight_enter);
    bt->setOnClickListener([this](View& view)mutable {
        LOGD("已确定");
        this->close();
        });

    SeekBar* seekbar = (SeekBar*)findViewById(z10::R::id::setting_seekbar);
    seekbar->setOnSeekBarChangeListener([this](AbsSeekBar& seek, int progress, bool fromuser) {
        LOGD("Light:%d", progress);
        });
}

ScreenLightWindow::~ScreenLightWindow() {
}
