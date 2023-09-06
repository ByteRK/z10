#include <page_item.h>


MyLinearLayout::MyLinearLayout(WATER &myitem):LinearLayout(0,0,-1,-1){
        
    LayoutInflater::from(getContext())->inflate("@layout/page_item",this);

    Image = (ImageView *)findViewById(z10::R::id::page_picture);                    //图片
    Image->setImageResource(myitem.picture);

    FrameLayout *linear=(FrameLayout *)findViewById(z10::R::id::framelayout_page);
    
    btn_out = (Button *)findViewById(z10::R::id::page_picture2_btn);
    btn_out->setOnClickListener(std::bind(&MyLinearLayout::onTextoutClick,this,std::placeholders::_1));
    initLinearPage(linear,myitem);

    this->setBackgroundColor(0x00ffffff);

}

MyLinearLayout::~MyLinearLayout(){
    delete Image2;
    delete Image;
    delete mArcWendu;
    delete mTextWendu;
    delete mArcChushuiliang;
    delete mTextChushuiliang;
    delete btn_out;
}

void MyLinearLayout::initLinearPage(FrameLayout *frame,WATER &myitem){
    if( myitem.item == "冰块")
    {
        LinearLayout *linear_page = (LinearLayout *)LayoutInflater::from(getContext())->inflate("@layout/page_item_bingkuai",frame);
        
        btn_out->setText("出冰");

        Image2 = (ImageView *)findViewById(z10::R::id::page_picture2);                    //图片2   右边出冰 或者 出水
        Image2->setImageResource("@mipmap/icon_ice_chubing");
        LOGD("进入了冰块页面");
    }
    else if(myitem.item == "冷水" || myitem.item == "常温水"){
        LOGD("进入了冷水 或 常温水页面");
        LinearLayout *linear_page = (LinearLayout *)LayoutInflater::from(getContext())->inflate("@layout/page_item_lengshui",frame);
        setLinearData(linear_page,myitem);

        mArcWendu->setMax(myitem.wendu);
    }
    else {
        LOGD("进入了其他页面");
        LinearLayout *linear_page = (LinearLayout *)LayoutInflater::from(getContext())->inflate("@layout/page_item_zidingyi",frame);
        setLinearData(linear_page,myitem);

        mRunnable_ArcWD =[this](){
        if(mArcWendu->getProgress() < 45)
            mArcWendu->setProgress(45);
        };

        Button *btn_wendu_reduce=(Button *)linear_page->findViewById(z10::R::id::wendu_reduce);
        Button *btn_wendu_add=(Button *)linear_page->findViewById(z10::R::id::wendu_add);

        btn_wendu_reduce->setOnClickListener(std::bind(&MyLinearLayout::onWdReduceClick,this,std::placeholders::_1));                   //监听 温度 按钮 （-）
        btn_wendu_add->setOnClickListener(std::bind(&MyLinearLayout::onWdAddClick,this,std::placeholders::_1));                         //监听 温度 按钮 （+）

        mArcWendu->setOnChangeListener(std::bind(&MyLinearLayout::onChangerListener,this,std::placeholders::_1,std::placeholders::_2)); //监听 温度 的变化
    }

    mRunnable_btnout =[this,&myitem](){
        btn_out->setEnabled(true);
        if(myitem.item == "冰块")
            btn_out->setText("出冰");
        else
            btn_out->setText("出水");
    };
}

void MyLinearLayout::setLinearData(LinearLayout *linear,WATER &myitem){
    mArcWendu  = (ArcSeekBar *)linear->findViewById(z10::R::id::arc_wendu);                    //温度   的 ArcSeekBar 控件，即 圆形 滑动条
    mTextWendu = (TextView   *)linear->findViewById(z10::R::id::txt_wendu);                      //温度   的 textView控件
    mArcChushuiliang  = (ArcSeekBar *)linear->findViewById(z10::R::id::arc_chushuiliang);      //出水量 的 ArcSeekBar 控件，即 圆形 滑动条
    mTextChushuiliang = (TextView   *)linear->findViewById(z10::R::id::txt_chushuiliang);        //出水量 的 textView控件

    mArcWendu->setProgress(myitem.wendu);
    mTextWendu->setText(std::to_string(myitem.wendu));
    mArcChushuiliang->setProgress(myitem.chushuiliang);
    mTextChushuiliang->setText(std::to_string(myitem.chushuiliang*10));
  
    Image2 = (ImageView *)findViewById(z10::R::id::page_picture2);                      //图片2   右边出冰 或者 出水
    Image2->setImageResource("@mipmap/icon_chushui");

    mArcChushuiliang->setOnChangeListener(std::bind(&MyLinearLayout::onChangerListener,this,std::placeholders::_1,std::placeholders::_2));  //监听 出水量 的变化

    Button *btn_CSL_reduce=(Button *)linear->findViewById(z10::R::id::chushuiliang_reduce);                                
    Button *btn_CSL_add=(Button *)linear->findViewById(z10::R::id::chushuiliang_add);
    btn_CSL_reduce->setOnClickListener(std::bind(&MyLinearLayout::onCslReduceButtonClick,this,std::placeholders::_1));                      //监听 出水量 按钮 （-）
    btn_CSL_add->setOnClickListener(std::bind(&MyLinearLayout::onCslAddButtonClick,this,std::placeholders::_1));                            //监听 出水量 按钮 （+）
        
}

void MyLinearLayout::onChangerListener(View &v, int progress){      
    switch(v.getId()){
        case z10::R::id::arc_wendu:
            mTextWendu->setText(std::to_string(progress));
            LOGD("change wendu progress  = %d ",progress);
            removeCallbacks(mRunnable_ArcWD);
            postDelayed(mRunnable_ArcWD,500);
            break;
        case z10::R::id::arc_chushuiliang:
            mTextChushuiliang->setText(std::to_string(progress*10));        //滚动条每次变化 10ml
            LOGD("change chushuiliang progress  = %d ",progress*10);        //滚动条每次变化 10ml
            break;
    }
}

void MyLinearLayout::onCslReduceButtonClick(View&v){        //按钮每次减少 50 ml
    
    int CSL=mArcChushuiliang->getProgress();
    if((CSL-5) <= 5)
        CSL = 5;
    else
        CSL-=5;

    mArcChushuiliang->setProgress(CSL);
    mTextChushuiliang->setText(std::to_string(CSL*10));

    LOGD("onCslReduceButtonClick()   CSL = %d ",CSL*10);
}

void MyLinearLayout::onCslAddButtonClick(View&v){           //按钮每次添加 50 ml
    int CSL=mArcChushuiliang->getProgress();
    if((CSL+5) >= 100)
        CSL = 100;
    else
        CSL+=5;

    mArcChushuiliang->setProgress(CSL);
    mTextChushuiliang->setText(std::to_string(CSL*10));

    LOGD("onCslAddButtonClick()  CSL = %d ",CSL*10);
}

void MyLinearLayout::onWdReduceClick(View&v){           
    int Wendu=mArcWendu->getProgress();
    if(Wendu >95 && Wendu <= 98)
        Wendu = 95;
    else if( (Wendu-5) <= 45)
        Wendu = 45;
    else 
        Wendu -= 5;
    mArcWendu->setProgress(Wendu);
    mTextWendu->setText(std::to_string(Wendu));
    LOGD("onWdReduceClick()   Wendu = %d ",Wendu);
}

void MyLinearLayout::onWdAddClick(View&v){
    int Wendu=mArcWendu->getProgress();
    if(Wendu >=95 && Wendu <= 98)
        Wendu = 98;
    else if((Wendu+5) >= 95)
        Wendu = 95;
    else 
        Wendu += 5;
    mArcWendu->setProgress(Wendu);
    mTextWendu->setText(std::to_string(Wendu));
    LOGD("onWdAddClick()   Wendu = %d ",Wendu);
}

void MyLinearLayout::onTextoutClick(View&v){
    LOGD("onTextoutClick() ");
    Button& button = dynamic_cast<Button&>(v);
    button.setText("暂停");
    button.setEnabled(false);
    postDelayed(mRunnable_btnout,3000);
}
