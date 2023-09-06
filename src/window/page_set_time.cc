#include <page_set_time.h>

Page_set_time::Page_set_time():Window(0,0,-1,-1){

    LayoutInflater::from(getContext())->inflate("@layout/page_setting_time",this);
    picker_set_year = (NumberPicker *)findViewById(z10::R::id::numberpicker_set_year);
    picker_set_mon = (NumberPicker *)findViewById(z10::R::id::numberpicker_set_mon);
    picker_set_day = (NumberPicker *)findViewById(z10::R::id::numberpicker_set_day);
    picker_set_hour = (NumberPicker *)findViewById(z10::R::id::numberpicker_set_hour);
    picker_set_min = (NumberPicker *)findViewById(z10::R::id::numberpicker_set_min);
    
    setFormatter(picker_set_mon);
    setFormatter(picker_set_day);
    setFormatter(picker_set_hour);
    setFormatter(picker_set_min);

    picker_set_year->setOnValueChangedListener(std::bind(&Page_set_time::onValueChangedListener,this,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3));
    picker_set_mon->setOnValueChangedListener(std::bind(&Page_set_time::onValueChangedListener,this,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3));

    Button *btn_cancle = (Button *)findViewById(z10::R::id::btn_set_time_cancle);
    Button *btn_verify = (Button *)findViewById(z10::R::id::btn_set_time_verify);
    ImageView *icon_back = (ImageView *)findViewById(z10::R::id::icon_back);

    btn_cancle->setOnClickListener(std::bind(&Page_set_time::onButtonClicnListener,this,std::placeholders::_1));
    btn_verify->setOnClickListener(std::bind(&Page_set_time::onButtonClicnListener,this,std::placeholders::_1));
    icon_back->setOnClickListener(std::bind(&Page_set_time::onButtonClicnListener,this,std::placeholders::_1));
}

Page_set_time::~Page_set_time()
{
    
}

void Page_set_time::onButtonClicnListener(View&v){
    switch (v.getId()){
    case z10::R::id::btn_set_time_cancle:
    case z10::R::id::icon_back:
        this->close();
        break;
    case z10::R::id::btn_set_time_verify:
        timeSet(picker_set_year->getValue(),
                picker_set_mon->getValue(),
                picker_set_day->getValue(),
                picker_set_hour->getValue(),
                picker_set_min->getValue(),
                getTodayTimeSec());
        this->close();
        break;

    default:
        break;
    }
}

void Page_set_time::onValueChangedListener(NumberPicker& picker,int num_old,int num_new){
    LOGD("onValueChangedListener num_old = %d  num_new = %d",num_old,num_new);
    static int year = picker_set_year->getValue();
    static int mon = picker_set_mon->getValue();
    switch(picker.getId()){
        case z10::R::id::numberpicker_set_year:
            if(year != picker.getValue()){
                year = picker.getValue();
                setMaxDay(year,mon); 
            }
            
        case z10::R::id::numberpicker_set_mon:
            if(mon != picker.getValue()){
                mon = picker.getValue();
                setMaxDay(year,mon); 
            }
    }
}

//通过年 月，来设置 最大的日期（如 2月份只有29或28天）
void Page_set_time::setMaxDay(int year,int mon){
    std::tm timeinfo = {0};
    timeinfo.tm_year = year - 1900; // 年份从1900开始
    timeinfo.tm_mon = mon - 1; // 月份从0开始，所以减去1

    std::time_t time = std::mktime(&timeinfo);

    int maxDays = std::localtime(&time)->tm_mday;
    picker_set_day->setMaxValue(maxDays);
}

void Page_set_time::setFormatter(NumberPicker *p){
    p->setFormatter([](int v)->std::string{
        char data[3];
        sprintf(data,"%02d",v);
        return std::string(data);
    });
}
