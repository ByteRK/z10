#include <homewindow.h>

typedef struct{
    std::string types;
    int wendu;
    int chushuiliang;
}PAGERINFO;

HomeWindow::HomeWindow():Window(0,0,-1,-1){
    LayoutInflater::from(getContext())->inflate("@layout/home_view",this);
    LinearLayout *s=(LinearLayout *)findViewById(z10::R::id::main_content);

    Activity_header::set_Parentview(this);
    Activity_header::ins()->upHeader();
    page=(ViewPager *)findViewById(z10::R::id::page);
    tabLayout=(TabLayout*)findViewById(z10::R::id::tab);

    MyPageAdapter*adapter=new MyPageAdapter(this);
    page->setAdapter(adapter);
    tabLayout->setupWithViewPager(page);
    tabLayout->getTabAt(2)->select();
    items = adapter->getitems();
    // 重置 TabLayout 的默认属性，可自定义在 tabcustomview.xml 上修改样式
    for (int i = 0; i < tabLayout->getTabCount(); i++) {
        TabLayout::Tab *t = tabLayout->getTabAt(i);
        if (t != nullptr) {
            View *customView = LayoutInflater::from(getContext())->inflate("@layout/tabcustomview", nullptr);
            t->setCustomView(customView);
        }   
    }
    TabLayout::OnTabSelectedListener selectListener;
    selectListener.onTabSelected = std::bind(&HomeWindow::onTabSelectedListener,this,std::placeholders::_1);
    tabLayout->addOnTabSelectedListener(selectListener);

    InputEventSource::getInstance().setScreenSaver(std::bind(&HomeWindow::screenSaver,this,std::placeholders::_1),60000);       //屏保

    // 
    
}   


void HomeWindow::onTabSelectedListener(TabLayout::Tab& tab){
    Popwindiw_text_hint *window;
    Popwindiw_tip_hint  *tip_window;
    switch (tab.getPosition()){
        case 0:
            if(g_appData.zhileng == PRO_STATE_COOL_NONE && g_appData.zhibing == PRO_STATE_ICE_NONE){    //先判断 制冰 是否开启
                LOGD("点击了冰块   未开启制冷和制冰");
                window = new Popwindiw_text_hint(OPEN_FUNC_COOL_ICE,std::string("启用冰块模式需先打开制冷制冰功能"),std::string("开启制冷制冰"));
            }
            else if(g_appData.zhibing == PRO_STATE_ICE_NONE){
                LOGD("点击了冰块   但只开启了制冷，未开启制冰");
                window = new Popwindiw_text_hint(OPEN_FUNC_ICE,std::string("开启制冰功能后，系统将开始制作冰块"),std::string("开启制冰"));
            }
            else if(g_appData.zhibing == PRO_STATE_ICE_ING){
                LOGD("系统制冰中，请稍后");
                tip_window = new Popwindiw_tip_hint(OPEN_FUNC_ICE);
            }
            else if(g_appData.zhibing == PRO_STATE_ICE_DONE){
                prev_position = tab.getPosition();
                break;
            }
            tabLayout->getTabAt(prev_position)->select();
            break;
        case 1:
            if(g_appData.zhileng == PRO_STATE_COOL_NONE){       //先判断 制冷 是否开启
                LOGD("点击了冰块   未开启制冷");
                window = new Popwindiw_text_hint(OPEN_FUNC_COOL,std::string("开启制冷功能后，系统将开始制作冷水"),std::string("开启制冷"));
            }
            else if(g_appData.zhileng == PRO_STATE_COOL_ING){
                LOGD("系统制冷中，请稍后");
                tip_window = new Popwindiw_tip_hint(OPEN_FUNC_COOL);
            }
            else if(g_appData.zhileng == PRO_STATE_COOL_DONE){
                prev_position = tab.getPosition();
                break;
            }
            tabLayout->getTabAt(prev_position)->select();
            break;
        default:
            prev_position = tab.getPosition();
            break;
    }
}

HomeWindow::~HomeWindow(){
   delete page;
   delete tabLayout;
}

//屏保执行的函数 
void HomeWindow::screenSaver(bool bEnabled){
    if(bEnabled && !Screen_saver::isPresent()){
        Screen_saver *wd = new Screen_saver;
    }
    const bool screenSaverActived= InputEventSource::getInstance().isScreenSaverActived();
    LOGD("screenSaver returned  actived=%d bEnabled=%d",screenSaverActived,bEnabled);
}
