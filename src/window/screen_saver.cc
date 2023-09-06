#include <screen_saver.h>

Screen_saver* Screen_saver::mins = nullptr;

Screen_saver::Screen_saver():Window(0,0,-1,-1){

    LinearLayout *page = (LinearLayout *)LayoutInflater::from(getContext())->inflate("@layout/page_unlock",this);
    LOGD("Create ScreenSaver");

    

    SeekBar*bar=(SeekBar *)findViewById(z10::R::id::unlock_progressBar);
    mRunnable = [this,bar](){
        bar->setProgress(0);
    };
    bar->setOnSeekBarChangeListener(std::bind(&Screen_saver::onSeekBarChange,this,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3));
}


Screen_saver::~Screen_saver(){}

void Screen_saver::onSeekBarChange(cdroid::AbsSeekBar& seekbar, int progress, bool fromUser){
    if((static_cast<float>(progress) / seekbar.getMax()) > 0.9 )
    {
        LOGD("close ScreenSaver");
        this->close();
        InputEventSource::getInstance().closeScreenSaver();
        mins = nullptr;
    }
    seekbar.removeCallbacks(mRunnable);
    seekbar.postDelayed(mRunnable,1000);
}

bool Screen_saver::isPresent(){
    if(mins == nullptr)
        return false;
    else 
        return true;
}
