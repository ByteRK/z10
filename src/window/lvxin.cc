#include <cdroid.h>
#include <R.h>
#include <cdlog.h>

#include "lvxin.h"

LvXinWindow::LvXinWindow() : Window(0, 0, -1, -1) {
    LayoutInflater::from(getContext())->inflate("@layout/lvxin", this);

    LinearLayout* sv = (LinearLayout*)findViewById(z10::R::id::linearLayout);

    TextView* reset = (TextView*)findViewById(z10::R::id::lvXin_reSet_HPCC);
    ArcSeekBar* arc_HPCC = (ArcSeekBar*)findViewById(z10::R::id::lvXin_arc_HPCC);
    reset->setOnClickListener([this, arc_HPCC](View& view) {
        LOGD("click %d", view.getId());
        arc_HPCC->setProgress(0);
        });

    reset = (TextView*)findViewById(z10::R::id::lvXin_reSet_RO);
    ArcSeekBar* arc_RO = (ArcSeekBar*)findViewById(z10::R::id::lvXin_arc_RO);
    reset->setOnClickListener([this, arc_RO](View& view) {
        LOGD("click %d", view.getId());
        arc_RO->setProgress(0);
        });

    ImageView* q_lvxin = (ImageView*)findViewById(z10::R::id::lvXin_back);
    q_lvxin->setOnClickListener([this](View& view)mutable {
        LOGD("窗口即将关闭");
        this->close();
        });
}

LvXinWindow::~LvXinWindow() {
    // delete anim;
}
