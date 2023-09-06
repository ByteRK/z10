#include <page_uv.h>

Page_uv::Page_uv():Window(0,0,-1,-1){


    LayoutInflater::from(getContext())->inflate("@layout/page_uvshajun",this);
    picker_star_hour = (NumberPicker *)findViewById(z10::R::id::numberpicker_star_hour);
    picker_star_min = (NumberPicker *)findViewById(z10::R::id::numberpicker_star_min);
    picker_end_hour = (NumberPicker *)findViewById(z10::R::id::numberpicker_end_hour);
    picker_end_min = (NumberPicker *)findViewById(z10::R::id::numberpicker_end_min);
    
    setFormatter(picker_star_hour);
    setFormatter(picker_star_min);
    setFormatter(picker_end_hour);
    setFormatter(picker_end_min);

    ImageView *back = (ImageView *)findViewById(z10::R::id::icon_back);
    back->setOnClickListener(std::bind(&Page_uv::onClickBackListener,this,std::placeholders::_1));

    Button *btn_keep = (Button *)findViewById(z10::R::id::btn_keep);
    btn_keep->setOnClickListener(std::bind(&Page_uv::onClickBackListener,this,std::placeholders::_1));
}

Page_uv::~Page_uv()
{
}
void Page_uv::onClickBackListener(View&v){
    LOGD("close page_uvshajun");
    this->close();
}



void Page_uv::setFormatter(NumberPicker *p){
    p->setFormatter([](int v)->std::string{
        char data[3];
        sprintf(data,"%02d",v);
        return std::string(data);
    });
}
