#include "project.h"

AppGlobalData  g_appData;

void WindowTime::delView(TextView *timeView){
    if (!timeView)
        return;
    for (auto it = mTimeView.begin(); it != mTimeView.end(); it++)
    {
        if (*it == timeView)
        {
            mTimeView.erase(it);
            return;
        }
    }
    LOG(ERROR) << "not find the timeView. id=" << timeView->getId();
}

void WindowTime::addView(TextView *timeView)
{
    timeView->setText(getTimeStr());
    mTimeView.push_back(timeView);
}

void WindowTime::updTime()
{   
    std::string showTime = getTimeStr();

    for (int i = 0, j = mTimeView.size(); i < j; i++)
    {
        mTimeView[i]->post([this,i,showTime](){
            mTimeView[i]->setText(showTime);
        });
        
    }
}
// postDelayed(mRunnable_btnout,3000);

// mRunnable_btnout =[this,&myitem](){
//     btn_out->setEnabled(true);
//     if(myitem.item == "冰块")
//         btn_out->setText("出冰");
//     else
//         btn_out->setText("出水");
// };

