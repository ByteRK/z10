#include <page_setting.h>
#include <cdroid.h>
#include <R.h>
#include <cdlog.h>

Page_setting::Page_setting():Window(0, 0, -1, -1) {
    LayoutInflater::from(getContext())->inflate("@layout/page_setting", this);
    LinearLayout* sv = (LinearLayout*)findViewById(z10::R::id::linearLayout);

    auto img_click_func = std::bind(&Page_setting::onSettingImgClick, this, std::placeholders::_1);
    auto bt_click_func = std::bind(&Page_setting::onSettingBtClick, this, std::placeholders::_1);

    ImageView* img_icon = (ImageView*)findViewById(z10::R::id::setting_screenLight);
    img_icon->setOnClickListener(img_click_func);
    img_icon = (ImageView*)findViewById(z10::R::id::setting_washTime);
    img_icon->setOnClickListener(img_click_func);
    img_icon = (ImageView*)findViewById(z10::R::id::setting_modechoose);
    img_icon->setOnClickListener(img_click_func);
    img_icon = (ImageView*)findViewById(z10::R::id::setting_net);
    img_icon->setOnClickListener(img_click_func);
    img_icon = (ImageView*)findViewById(z10::R::id::setting_time);
    img_icon->setOnClickListener(img_click_func);
    img_icon = (ImageView*)findViewById(z10::R::id::setting_uv);
    img_icon->setOnClickListener(img_click_func);
    img_icon = (ImageView*)findViewById(z10::R::id::setting_lvxin);
    img_icon->setOnClickListener(img_click_func);
    img_icon = (ImageView*)findViewById(z10::R::id::setting_version);
    img_icon->setOnClickListener(img_click_func);
    img_icon = (ImageView*)findViewById(z10::R::id::setting_reset);
    img_icon->setOnClickListener(img_click_func);
    img_icon = (ImageView*)findViewById(z10::R::id::setting_back);
    img_icon->setOnClickListener(img_click_func);

    sw_cryogen = (Switch*)findViewById(z10::R::id::setting_bt_cryogen);
    sw_cryogen->setOnClickListener(bt_click_func);
    sw_cryogen->setChecked(g_appData.zhileng == PRO_STATE_COOL_NONE ? false : true);

    sw_ice = (Switch*)findViewById(z10::R::id::setting_bt_ice);
    sw_ice->setOnClickListener(bt_click_func);
    sw_ice->setChecked(g_appData.zhibing == PRO_STATE_ICE_NONE ? false : true);

    sw_lock = (Switch*)findViewById(z10::R::id::setting_bt_lock);
    sw_lock->setOnClickListener(bt_click_func);
    sw_lock->setChecked(g_appData.childLocked == PRO_STATE_NONE ? false : true);

}

Page_setting::~Page_setting() {
   
}

void Page_setting::onSettingImgClick(View& v) {
    LOGD("click %d", v.getId());
    switch (v.getId()) {
        case z10::R::id::setting_screenLight:{
            ScreenLightWindow *w = new ScreenLightWindow;
            break;
        }
            
        case z10::R::id::setting_washTime:{
            break;
        }
            

        case z10::R::id::setting_modechoose:{
            ModeWindow * w=new ModeWindow;
            break;
        }
            

        case z10::R::id::setting_net:{
            NetWorkWindow *w = new NetWorkWindow;
            break;
        }
            

        case z10::R::id::setting_time:{
            Page_set_time *w = new Page_set_time;
            break;
        }
            

        case z10::R::id::setting_uv:{
            Page_uv *w = new Page_uv();
            break;
        }
            

        case z10::R::id::setting_lvxin:{
            LvXinWindow *w = new LvXinWindow;
            break;

        }
            
        case z10::R::id::setting_version:{
            break;
        }
            

        case z10::R::id::setting_reset:{
            break;
        }
            
        case z10::R::id::setting_back:{
            Activity_header::ins()->upHeader();
            // MyPageAdapter::notifyDataChanged();
            this->close();
            break;
        }
            
        default:
            break;
    }
}

void Page_setting::onSettingBtClick(View& v) {
    switch (v.getId()) {
        case z10::R::id::setting_bt_cryogen:
        {
            if (!sw_cryogen->isChecked() && !!sw_ice->isChecked()) {
                LOGD("关闭制冷同时关闭制冰");
                sw_ice->setChecked(false);
                g_appData.zhibing =PRO_STATE_ICE_NONE;
            }

            g_appData.zhileng = sw_cryogen->isChecked() ? PRO_STATE_COOL_ING : PRO_STATE_COOL_NONE;
            g_appData.isChange = true;
            LOGD(sw_cryogen->isChecked() ? "开启制冷" : "关闭制冷");
            break;
        };
        case z10::R::id::setting_bt_ice:
        {
            if (!!sw_ice->isChecked() && !sw_cryogen->isChecked()) {
                LOGD("关闭制冷同时关闭制冰");
                sw_cryogen->setChecked(true);
                g_appData.zhileng = PRO_STATE_COOL_ING;
            }

            g_appData.zhibing = sw_ice->isChecked() ? PRO_STATE_ICE_ING : PRO_STATE_ICE_NONE;
            g_appData.isChange = true;
            LOGD(sw_cryogen->isChecked() ? "开启制冰" : "关闭制冰");
            break;
        };
        case z10::R::id::setting_bt_lock:
        {
            g_appData.childLocked = sw_lock->isChecked() ? PRO_STATE_TONGSUO : PRO_STATE_NONE;
            g_appData.isChange = true;
            LOGD(sw_lock->isChecked() ? "开启童锁" : "关闭童锁");
            break;
        };

        default:
            break;
    }
}