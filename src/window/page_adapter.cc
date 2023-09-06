#include <page_adapter.h>

MyPageAdapter::MyPageAdapter(ViewGroup* container):LinearLayout(0,0,-1,-1){
    readModeData(container);
}

int MyPageAdapter::getCount(){
    return modeData.size();
}
bool MyPageAdapter::isViewFromObject(View* view, void*object){ 
    return view==object;
}

void* MyPageAdapter::instantiateItem(ViewGroup* container, int position) {
    LOGD("instantiateItem positino=%d",position);

    View*itemview=new MyLinearLayout(modeData.at(position));
    container->addView(itemview);

    return itemview;
}

void MyPageAdapter::setPrimaryItem(ViewGroup* container, int position, void* object){ }

void MyPageAdapter::destroyItem(ViewGroup* container, int position,void* object){
    container->removeView((View*)object);
    delete (View*)object;
}

float MyPageAdapter::getPageWidth(int position){
    return 1.f;
}

std::string MyPageAdapter::getPageTitle(int position){
    return modeData.at(position).item;
}

std::vector<WATER> MyPageAdapter::getitems(){
    return modeData;
}

void MyPageAdapter::notifyDataChanged(){
    notifyDataChanged();
}
