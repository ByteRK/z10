#include <popwindow_hint.h>

Popwindiw_text_hint::Popwindiw_text_hint(int func,std::string text,std::string enter,std::string cancel):Window(0,0,-1,-1){

    setting_fun = func;

    LayoutInflater::from(getContext())->inflate("@layout/popwindow_text_hint",this);

    text_view   = (TextView *)findViewById(z10::R::id::popwindow_hint_text);
    text_cancel = (TextView *)findViewById(z10::R::id::popwindow_hint_cancel);
    text_enter  = (TextView *)findViewById(z10::R::id::popwindow_hint_enter);

    text_view->setText(text);
    text_cancel->setText(cancel);
    text_enter->setText(enter);
    
    text_view->setLineHeight(45);

    text_cancel->setOnClickListener(std::bind(&Popwindiw_text_hint::onClickBackListener,this,std::placeholders::_1));
    text_enter->setOnClickListener(std::bind(&Popwindiw_text_hint::onClickBackListener,this,std::placeholders::_1));
}

Popwindiw_text_hint::~Popwindiw_text_hint()
{
    delete text_view;
    delete text_cancel;
    delete text_enter;
}
void Popwindiw_text_hint::onClickBackListener(View&v){
    switch(v.getId()){
        case z10::R::id::popwindow_hint_cancel:
            break;
        case z10::R::id::popwindow_hint_enter:
            switch(setting_fun){
                case OPEN_FUNC_COOL:
                    g_appData.zhileng = PRO_STATE_COOL_ING;         //设置为正在制冷 
                    break;
                case OPEN_FUNC_ICE:
                    g_appData.zhibing = PRO_STATE_ICE_ING;          //设置为正在制冰
                    break;
                case OPEN_FUNC_COOL_ICE:
                    g_appData.zhileng = PRO_STATE_COOL_ING;         //设置为正在制冷
                    g_appData.zhibing = PRO_STATE_ICE_ING;          //设置为正在制冰 
                    break;
            }
            g_appData.isChange = true;
            Activity_header::ins()->upHeader();             //更新主页的图标
            break;
    }
    this->close();
}

Popwindiw_tip_hint::Popwindiw_tip_hint(int func):Window(0,0,-1,-1){

    LayoutInflater::from(getContext())->inflate("@layout/popwindow_tip_hint",this);

    TextView *tip_text    = (TextView *)findViewById(z10::R::id::popwindow_tip_text);
    TextView *tip_text2   = (TextView *)findViewById(z10::R::id::popwindow_tip_text2);
    TextView *tip_text3   = (TextView *)findViewById(z10::R::id::popwindow_tip_text3);

    if(func == OPEN_FUNC_ICE){
        tip_text->setText(std::string("系统制冰中，请稍后"));
        tip_text2->setText(std::string("制冰状态灯变成"));
        tip_text3->setText(std::string("后，可出冰"));
    }
    else if(func == OPEN_FUNC_COOL){
        tip_text->setText(std::string("系统制冷中，请稍后"));
        tip_text2->setText(std::string("制冷状态灯变成"));
        tip_text3->setText(std::string("后，可出冷水"));
    }

    TextView *text_enter = (TextView *)findViewById(z10::R::id::popwindow_tip_hint_enter);
    text_enter->setOnClickListener(std::bind(&Popwindiw_tip_hint::onClickBackListener,this,std::placeholders::_1));
}

Popwindiw_tip_hint::~Popwindiw_tip_hint()
{
}

void Popwindiw_tip_hint::onClickBackListener(View&v){
    this->close();
}