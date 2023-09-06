#pragma once
#include <widget/cdwindow.h>

#include <widget/relativelayout.h>
#include <widget/numberpicker.h>
#include <widget/textview.h>


#include <page_item.h>
#include <cdroid.h>
#include <R.h>
#include <cdlog.h>
#include <clocale>

class MyPageAdapter:public PagerAdapter,public LinearLayout{
    
public:
    MyPageAdapter(ViewGroup* container);
    int getCount()override;
    bool isViewFromObject(View* view, void*object)override;
    void* instantiateItem(ViewGroup* container, int position)override;
    void setPrimaryItem(ViewGroup* container, int position, void* object)override;
    void destroyItem(ViewGroup* container, int position,void* object)override;
    float getPageWidth(int position)override;

    std::string getPageTitle(int position);
    std::vector<WATER> getitems();


    static void notifyDataChanged();
private:
    Runnable mRunnable_btnout;
};
