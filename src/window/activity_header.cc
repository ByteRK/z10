#include <activity_header.h>

ViewGroup *Activity_header::parent = nullptr;

Activity_header::Activity_header(){

    header_tongsuo = (ImageView *)parent->findViewById(z10::R::id::icon_tongsuo);                                           
    auto func=std::bind(&Activity_header::onButtonClick,this,std::placeholders::_1);
    header_tongsuo->setOnClickListener(func);

    header_lvxin = (ImageView *)parent->findViewById(z10::R::id::icon_lvxin);
    header_lvxin->setOnClickListener(func);

    header_top_uv = (TextView *)parent->findViewById(z10::R::id::text_top_uv);
    header_top_uv->setOnClickListener(func);

    header_top_tds = (TextView *)parent->findViewById(z10::R::id::text_top_tds);              //不能点击

    header_zhaoming = (ImageView *)parent->findViewById(z10::R::id::icon_zhaoming);
    header_zhaoming->setOnClickListener(func);

    header_zhileng = (TextView *)parent->findViewById(z10::R::id::text_top_zhileng);
    header_zhileng->setOnClickListener(func);

    header_zhibing = (TextView *)parent->findViewById(z10::R::id::text_top_zhibing);
    header_zhibing->setOnClickListener(func);
 
    header_time = (TextView *)parent->findViewById(z10::R::id::text_top_time);                //不能点击
    // WindowTime::ins()->addView(header_time);
    // WindowTime::ins()->updTime();
    mRunnable = [this](){
        std::string showTime = getTimeStr();
        header_time->setText(showTime);
        header_time->postDelayed(mRunnable,1000);
        parent->invalidate();
        LOGD("update time···   %s",showTime.c_str());
    };
    header_time->post(mRunnable);

    header_wifi = (ImageView *)parent->findViewById(z10::R::id::icon_wifi);                   //不能点击

    header_setup = (ImageView *)parent->findViewById(z10::R::id::icon_setup);       
    header_setup->setOnClickListener(func);

    upHeader();
}

Activity_header::~Activity_header()
{
}

//监听控件
void Activity_header::onButtonClick(View&v){
    switch(v.getId())
    {
        case z10::R::id::icon_tongsuo:{
            LOGD("case z10::R::id::icon_tongsuo");
            if(g_appData.childLocked == PRO_STATE_TONGSUO){
                if(!Screen_saver::isPresent()){
                    Screen_saver *wd = new Screen_saver;
                }
            }    
            break;
        }
            
        
        case z10::R::id::icon_lvxin:{
            LOGD("case z10::R::id::icon_lvxin");
            break;
        }
            

        case z10::R::id::text_top_uv:{
            Page_uv *w = new Page_uv;
            break;
        }
            

        case z10::R::id::icon_zhaoming:{
            break;
        }
            

        case z10::R::id::text_top_zhileng:
            break;

        case z10::R::id::text_top_zhibing:
            break;

        case z10::R::id::text_top_time:{
            Page_set_time *wt = new Page_set_time;
            break;
        }
            

        case z10::R::id::icon_setup:{
            Page_setting *sw = new Page_setting;
            LOGD("***************************************************");
            upHeader();
            break;
        }
            
    }
}

//更新状态
void Activity_header::upHeader(){
    if(g_appData.isChange){         //判断是否有更新状态
        if(g_appData.childLocked == PRO_STATE_TONGSUO)          header_tongsuo->setImageResource("@mipmap/icon_tongsuo");
        else                                                    header_tongsuo->setImageResource("@mipmap/icon_tongsuo1"); 

        if(g_appData.lvxin == PRO_STATE_LVXIN_NORMAL)           header_lvxin->setImageResource("@mipmap/icon_lvxin");
        else if(g_appData.lvxin == PRO_STATE_LVXIN_SOON)        header_lvxin->setImageResource("@mipmap/icon_lvxin_yellow"); 
        else if(g_appData.lvxin == PRO_STATE_LVXIN_EXPIRED)     header_lvxin->setImageResource("@mipmap/icon_lvxin_red");

        if(g_appData.UVshajun == PRO_STATE_NONE)                header_top_uv->setTextColor(0xFFE7E7E7);
        else                                                    header_top_uv->setTextColor(0xFF64ADF4);

        if(g_appData.TDS == 0){
            header_top_tds->setTextColor(0x00FFFFFF);
            header_top_tds->setText(" ");                 
        }                               
        else{
            header_top_tds->setTextColor(0xFF64ADF4);
            header_top_tds->setText(std::string("TDS:") + std::to_string(g_appData.TDS));
        }

        if(g_appData.zhaoming == PRO_STATE_ZHAOMING)            header_zhaoming->setImageResource("@mipmap/icon_zhaomingopen");
        else                                                    header_zhaoming->setImageResource("@mipmap/icon_zhaoming");

        if(g_appData.zhileng == PRO_STATE_COOL_NONE)            header_zhileng->setCompoundDrawablesWithIntrinsicBounds("@mipmap/icon_close","nullptr","nullptr","nullptr");
        else if(g_appData.zhileng == PRO_STATE_COOL_ING)        header_zhileng->setCompoundDrawablesWithIntrinsicBounds("@mipmap/icon_ing","nullptr","nullptr","nullptr"); 
        else if(g_appData.zhileng == PRO_STATE_COOL_DONE)       header_zhileng->setCompoundDrawablesWithIntrinsicBounds("@mipmap/icon_wancheng","nullptr","nullptr","nullptr");

        if(g_appData.zhibing == PRO_STATE_ICE_NONE)             header_zhibing->setCompoundDrawablesWithIntrinsicBounds("@mipmap/icon_close","nullptr","nullptr","nullptr");
        else if(g_appData.zhibing == PRO_STATE_ICE_ING)         header_zhibing->setCompoundDrawablesWithIntrinsicBounds("@mipmap/icon_ing","nullptr","nullptr","nullptr"); 
        else if(g_appData.zhibing == PRO_STATE_ICE_DONE)        header_zhibing->setCompoundDrawablesWithIntrinsicBounds("@mipmap/icon_wancheng","nullptr","nullptr","nullptr");

        g_appData.isChange = false;
    }
}

//检查状态
void Activity_header::checkState(bool &flag){
    if(g_appData.zhileng == PRO_STATE_COOL_ING && !flag){
        flag = true;
    }
    else if(g_appData.zhibing == PRO_STATE_ICE_ING && !flag){
        flag = true;
    }
    else if(g_appData.zhileng == PRO_STATE_COOL_ING && flag){
        g_appData.zhileng = PRO_STATE_COOL_DONE;
        g_appData.isChange = true;
        Activity_header::ins()->upHeader();
        flag = false;
    }
    else if(g_appData.zhibing == PRO_STATE_ICE_ING && flag){
        g_appData.zhibing = PRO_STATE_ICE_DONE;
        g_appData.isChange = true;
        Activity_header::ins()->upHeader();
        flag = false;
    }
}
