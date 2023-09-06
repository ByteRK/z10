#include <cdroid.h>
#include <R.h>
#include <cdlog.h>

#include "mode_edit.h"

ModeEditWindow::ModeEditWindow() : Window(0, 0, -1, -1) {
    LayoutInflater::from(getContext())->inflate("@layout/mode_edit", this);
    LinearLayout* sv = (LinearLayout*)findViewById(z10::R::id::linearLayout);
}

ModeEditWindow::~ModeEditWindow() {
    // delete anim;
}