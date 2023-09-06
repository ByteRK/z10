#include <cdroid.h>
#include <R.h>
#include <cdlog.h>

#include "mode.h"

ModeWindow::ModeWindow():Window(0, 0, -1, -1) {
    LayoutInflater::from(getContext())->inflate("@layout/setting_mode", this);

    ModeAdapter* adapter = new ModeAdapter(this);
    GridView* lv = (GridView*)findViewById(z10::R::id::setting_mode_listView);
    lv->setVerticalScrollBarEnabled(true);

    lv->setAdapter(adapter);
    adapter->notifyDataSetChanged();

    TextView* tv = (TextView*)findViewById(z10::R::id::setting_modeadd);
    tv->setOnClickListener([this, adapter](View& view) mutable {adapter->buildadd(); });

    ImageView* q_mode = (ImageView*)this->findViewById(z10::R::id::mode_back);
    q_mode->setOnClickListener([this](View& view)mutable {this->close();});
}

ModeWindow::~ModeWindow() {
    // delete anim;
}

// 初始化数据
ModeAdapter::ModeAdapter(ViewGroup* container){
    // std::vector<std::string> mode_img;
    // std::vector<std::string> mode_img2;
    // std::vector<std::string> mode_name;
    // std::vector<int> mode_warm;
    // std::vector<int> mode_water;
    // std::vector<int> mode_type;

    // container->getContext()->getArray("@array/mode_img", mode_img);
    // container->getContext()->getArray("@array/mode_img2", mode_img2);
    // container->getContext()->getArray("@array/mode_name", mode_name);
    // container->getContext()->getArray("@array/mode_warm", mode_warm);
    // container->getContext()->getArray("@array/mode_water", mode_water);
    // container->getContext()->getArray("@array/mode_type", mode_type);

    // LOGD("MODE_NUM: %d", mode_img.size());

    // for (int i = 0; i < mode_img.size(); i++) {
    //     modedata.push_back({ mode_img.at(i),mode_img2.at(i),mode_name.at(i), mode_warm.at(i), mode_water.at(i), mode_type.at(i) });
    // };
}

void ModeWindow::ModeWindowClick(View& view) {
    LOGD("click %d", view.getId());
    switch (view.getId()) {
    case z10::R::id::mode_back:
        LOGD("窗口即将关闭");
        this->close();
        break;
    default:
        break;
    }
}

int ModeAdapter::getCount() const {
    return modeData.size();
}

void* ModeAdapter::getItem(int position) const {
    return nullptr;
}

// 事件点击监听
void ModeAdapter::ViewClick(View& view) {
    LOGD("click %d", view.getId());
    switch (view.getId()) {
    case z10::R::id::mode_back:
        LOGD("窗口即将关闭");
        // this->close();
        break;
    
    case z10::R::id::mode_edit_back:
        
    default:
        break;
    }
}

// 删除弹窗
void ModeAdapter::DelPop(int position) {
    PopModeWindow* popdel = new PopModeWindow();
    TextView* tv = (TextView*)popdel->findViewById(z10::R::id::mode_del_cancel);
    tv->setOnClickListener([this, popdel](View& view) {
        LOGD("页面已关闭");
        popdel->close();
        });
    tv = (TextView*)popdel->findViewById(z10::R::id::mode_del_enter);
    tv->setOnClickListener([this, popdel, position](View& view) {
        if (!modeData.at(position).type) {
            popdel->close();
            return;
        }
        LOGD("delete ------------ %d", position);
        deldata(position);
        LOGD("%d数据已删除", position);
        popdel->close();
        });

    tv = (TextView*)popdel->findViewById(z10::R::id::mode_del_title);
    tv->setText("确认删除“" + modeData.at(position).item + "”模式？");

    tv = (TextView*)popdel->findViewById(z10::R::id::mode_del_warm);
    tv->setText(std::to_string(modeData.at(position).wendu) + "℃");
    tv = (TextView*)popdel->findViewById(z10::R::id::mode_del_water);
    tv->setText(std::to_string(modeData.at(position).chushuiliang) + "mL");

}

// 构建页面
View* ModeAdapter::getView(int position, View* convertView, ViewGroup* parent) {
    // 创建页面
    View* view = LayoutInflater::from(parent->getContext())->inflate("@layout/setting_mode_list", nullptr, false);

    // 设置背景图
    ImageView* mode_img = (ImageView*)view->findViewById(z10::R::id::mode_img);
    mode_img->setBackgroundResource(modeData.at(position).picture_2);
    mode_img->setOnClickListener([this, position](View& view) mutable { buildedit(position); });

    // 设置内容
    TextView* name = (TextView*)view->findViewById(z10::R::id::mode_name);
    TextView* warm = (TextView*)view->findViewById(z10::R::id::mode_warm);
    TextView* water = (TextView*)view->findViewById(z10::R::id::mode_water);
    name->setText(modeData.at(position).item);
    warm->setText(std::to_string(modeData.at(position).wendu) + "℃");
    water->setText(std::to_string(modeData.at(position).chushuiliang) + "mL");

    // modeData
    if (modeData.at(position).type) {
        ImageView* mode_del = (ImageView*)view->findViewById(z10::R::id::mode_del);
        mode_del->setBackgroundResource("@mipmap/icon_del");
        mode_del->setOnClickListener([this, position](View& view) mutable {DelPop(position);});
    };

    // 左移按钮
    ImageView* turnleft = (ImageView*)view->findViewById(z10::R::id::mode_turnleft);
    turnleft->setBackgroundResource(position == 0 ? "@mipmap/icon_noleft" : "@mipmap/icon_left");
    turnleft->setOnClickListener([this, position](View& view) mutable {changedata(position, 0); });

    // 右移按钮
    ImageView* turnright = (ImageView*)view->findViewById(z10::R::id::mode_turnright);
    turnright->setBackgroundResource(position == 0 ? "@mipmap/icon_noright" : "@mipmap/icon_noright");
    turnright->setOnClickListener([this, position](View& view) mutable {changedata(position, 1); });

    return view;
}

// 删除数据
void ModeAdapter::deldata(int location) {
    if (!!modeData.at(location).type) {
        if (location >= 0 && location < getCount()) {
            modeData.erase(modeData.begin() + location);
            LOGD("删除第%d项成功", location);
        } else {
            LOGD("第%d项不存在", location);
        }
        notifyDataSetChanged();
    }
}

// 交换位置
void ModeAdapter::changedata(int location, int dir) {
    if (dir && location >= 0 && location < getCount() - 1) {
        std::swap(modeData[location], modeData[location + 1]);
    } else if (!dir && location > 0 && location < getCount()) {
        std::swap(modeData[location], modeData[location - 1]);
    } else {
        LOGD("%d无法%s | %d", location, dir ? "右移" : "左移", dir);
        return;
    }
    LOGD("交换成功");
    notifyDataSetChanged();
}

// 创建编辑页面
void ModeAdapter::buildedit(int position) {
    tocache(position);
    auto vClick = std::bind(&ModeAdapter::ViewClick, this, std::placeholders::_1);

    Window* modeEdit = new ModeEditWindow();

    ImageView* edit_img = (ImageView*)modeEdit->findViewById(z10::R::id::mode_edit_img);
    edit_img->setBackgroundResource(datacache.picture);

    TextView* tv = (TextView*)modeEdit->findViewById(z10::R::id::mode_edit_name);
    tv->setText(datacache.item);
    tv = (TextView*)modeEdit->findViewById(z10::R::id::mode_edit_warm_text);
    tv->setText(std::to_string(datacache.wendu) + "℃");
    tv = (TextView*)modeEdit->findViewById(z10::R::id::mode_edit_water_text);
    tv->setText(std::to_string(datacache.chushuiliang) + "mL");

    ImageView* q_mode_edit = (ImageView*)modeEdit->findViewById(z10::R::id::mode_edit_back);
    q_mode_edit->setOnClickListener([this, modeEdit](View& view)mutable {
        LOGD("窗口即将关闭");
        modeEdit->close();
        });

    tv = (TextView*)modeEdit->findViewById(z10::R::id::mode_edit_warm_text);
    ImageView* button = (ImageView*)modeEdit->findViewById(z10::R::id::mode_edit_warm_down);
    button->setOnClickListener([this, tv](View& view)mutable {
        LOGD("温度减");
        datacache.wendu -= 1;
        tv->setText(std::to_string(datacache.wendu) + "℃");
        });
    button = (ImageView*)modeEdit->findViewById(z10::R::id::mode_edit_warm_up);
    button->setOnClickListener([this, tv](View& view)mutable {
        LOGD("温度加");
        datacache.wendu += 1;
        tv->setText(std::to_string(datacache.wendu) + "℃");
        });

    tv = (TextView*)modeEdit->findViewById(z10::R::id::mode_edit_water_text);
    button = (ImageView*)modeEdit->findViewById(z10::R::id::mode_edit_water_down);
    button->setOnClickListener([this, tv](View& view)mutable {
        LOGD("水量减");
        datacache.chushuiliang -= 10;
        tv->setText(std::to_string(datacache.chushuiliang) + "mL");
        });
    button = (ImageView*)modeEdit->findViewById(z10::R::id::mode_edit_water_up);
    button->setOnClickListener([this, tv](View& view)mutable {
        LOGD("水量加");
        datacache.chushuiliang += 10;
        tv->setText(std::to_string(datacache.chushuiliang) + "mL");
        });

    tv = (TextView*)modeEdit->findViewById(z10::R::id::mode_edit_enter);
    tv->setOnClickListener([this, modeEdit, position](View& view) mutable {
        savecache(position);
        LOGD("保存成功");
        modeEdit->close();
        notifyDataSetChanged();
        }
    );

    button = (ImageView*)modeEdit->findViewById(z10::R::id::mode_edit_del);
    button->setOnClickListener([this, modeEdit, position](View& view)mutable {
        PopModeWindow* popdel = new PopModeWindow();
        TextView* tv = (TextView*)popdel->findViewById(z10::R::id::mode_del_cancel);
        tv->setOnClickListener([this, popdel](View& view) {
            LOGD("页面已关闭");
            popdel->close();
            });
        tv = (TextView*)popdel->findViewById(z10::R::id::mode_del_enter);
        tv->setOnClickListener([this, popdel, modeEdit, position](View& view) {
            if (!modeData.at(position).type) {
                popdel->close();
                return;
            }
            deldata(position);
            LOGD("%d数据已删除", position);
            popdel->close();
            modeEdit->close();
            });

        tv = (TextView*)popdel->findViewById(z10::R::id::mode_del_title);
        tv->setText("确认删除“" + datacache.item + "”模式？");

        tv = (TextView*)popdel->findViewById(z10::R::id::mode_del_warm);
        tv->setText(std::to_string(datacache.wendu) + "℃");
        tv = (TextView*)popdel->findViewById(z10::R::id::mode_del_water);
        tv->setText(std::to_string(datacache.chushuiliang) + "mL");


        });


}

// 创建增加页面
void ModeAdapter::buildadd() {
    tocache();

    Window* modeAdd = new ModeAddWindow();

    ImageView* add_img = (ImageView*)modeAdd->findViewById(z10::R::id::mode_add_img);
    add_img->setBackgroundResource(datacache.picture);

    TextView* tv = (TextView*)modeAdd->findViewById(z10::R::id::mode_add_name);
    tv->setText(datacache.item);

    tv = (TextView*)modeAdd->findViewById(z10::R::id::mode_add_warm_text);
    tv->setText(std::to_string(datacache.wendu) + "℃");
    tv = (TextView*)modeAdd->findViewById(z10::R::id::mode_add_water_text);
    tv->setText(std::to_string(datacache.chushuiliang) + "mL");

    ImageView* q_add_back = (ImageView*)modeAdd->findViewById(z10::R::id::mode_add_back);
    q_add_back->setOnClickListener([this, modeAdd](View& view)mutable {
        LOGD("窗口即将关闭");
        modeAdd->close();
        });

    tv = (TextView*)modeAdd->findViewById(z10::R::id::mode_add_warm_text);
    ImageView* button = (ImageView*)modeAdd->findViewById(z10::R::id::mode_add_warm_down);
    button->setOnClickListener([this, tv](View& view)mutable {
        LOGD("温度减");
        datacache.wendu -= 1;
        tv->setText(std::to_string(datacache.wendu) + "℃");
        });
    button = (ImageView*)modeAdd->findViewById(z10::R::id::mode_add_warm_up);
    button->setOnClickListener([this, tv](View& view)mutable {
        LOGD("温度加");
        datacache.wendu += 1;
        tv->setText(std::to_string(datacache.wendu) + "℃");
        });

    tv = (TextView*)modeAdd->findViewById(z10::R::id::mode_add_water_text);
    button = (ImageView*)modeAdd->findViewById(z10::R::id::mode_add_water_down);
    button->setOnClickListener([this, tv](View& view)mutable {
        LOGD("水量减");
        datacache.chushuiliang -= 10;
        tv->setText(std::to_string(datacache.chushuiliang) + "mL");
        });
    button = (ImageView*)modeAdd->findViewById(z10::R::id::mode_add_water_up);
    button->setOnClickListener([this, tv](View& view)mutable {
        LOGD("水量加");
        datacache.chushuiliang += 10;
        tv->setText(std::to_string(datacache.chushuiliang) + "mL");
        });

    tv = (TextView*)modeAdd->findViewById(z10::R::id::mode_add_enter);
    tv->setOnClickListener([this, modeAdd](View& view) mutable {
        savecache();
        LOGD("保存成功");
        modeAdd->close();
        notifyDataSetChanged();
        }
    );
}



