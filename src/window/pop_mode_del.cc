#include <cdroid.h>
#include <R.h>
#include <cdlog.h>

#include <widget/cdwindow.h>

class PopModeWindow :public Window {
private:
    
protected:
public:
    PopModeWindow();
    ~PopModeWindow();
};


PopModeWindow::PopModeWindow() : Window(0, 0, -1, -1) {
    LayoutInflater::from(getContext())->inflate("@layout/popwindow_modedel_hint", this);
    LinearLayout* sv = (LinearLayout*)findViewById(z10::R::id::linearLayout);
}

PopModeWindow::~PopModeWindow() {
    
}