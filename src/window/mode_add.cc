#include <cdroid.h>
#include <R.h>
#include <cdlog.h>

#include "mode_add.h"

ModeAddWindow::ModeAddWindow() : Window(0, 0, -1, -1) {
    LayoutInflater::from(getContext())->inflate("@layout/mode_add", this);
    LinearLayout* sv = (LinearLayout*)findViewById(z10::R::id::linearLayout);
}

ModeAddWindow::~ModeAddWindow() {
   
}
