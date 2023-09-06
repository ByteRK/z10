#include <cdroid.h>
#include <R.h>
#include <cdlog.h>

#include "network.h"

NetWorkWindow::NetWorkWindow() : Window(0, 0, -1, -1) {
    LayoutInflater::from(getContext())->inflate("@layout/network", this);

    ImageView* q_network = (ImageView*)findViewById(z10::R::id::netWork_back);
    q_network->setOnClickListener([this](View& view)mutable {
        LOGD("窗口即将关闭");
        this->close();
        });

    MyAdapter* adapter = new MyAdapter(this);
    ListView* lv = (ListView*)findViewById(z10::R::id::setting_network_listView);
    lv->setVerticalScrollBarEnabled(true);

    getConnectInfo(this, lv);



    lv->setAdapter(adapter);
    adapter->notifyDataSetChanged();
    lv->setOnItemClickListener([ ](AdapterView& lv, View& v, int pos, long id) { LOGD("clicked %d", pos); });
}

void NetWorkWindow::getConnectInfo(ViewGroup* container, ListView* listview) {
    std::string now_status = container->getContext()->getString("@string/network_now_status");
    wlanConnect.status = std::stoi(now_status);

    // 已连接
    if (wlanConnect.status == 0 && HEADERVIEW != nullptr) {
        listview->removeView(HEADERVIEW);
        HEADERVIEW = nullptr;
        return;
    } else if (wlanConnect.status == 0) {
        return;
    }
    std::string now_signal = container->getContext()->getString("@string/network_now_signal");
    std::string now_name = container->getContext()->getString("@string/network_now_name");
    std::string now_lock = container->getContext()->getString("@string/network_now_lock");

    setConnectInfo(std::stoi(now_signal), now_name, std::stoi(now_lock));
    createConnect(listview);
}

void NetWorkWindow::createConnect(ListView* listview) {
    View* view = LayoutInflater::from(this->getContext())->inflate("@layout/network_now", nullptr, false);

    ImageView* icon = (ImageView*)view->findViewById(z10::R::id::wifi_icon);
    icon->setBackgroundResource(signalIcon(wlanConnect.detail.signal));

    TextView* name = (TextView*)view->findViewById(z10::R::id::wifi_name);
    name->setText(wlanConnect.detail.name);

    if (!!wlanConnect.detail.lock) {
        icon = (ImageView*)view->findViewById(z10::R::id::wifi_lock);
        icon->setImageResource("@mipmap/icon_lock");
    }

    listview->addHeaderView(view, nullptr, false);
    HEADERVIEW = view;
}

NetWorkWindow::~NetWorkWindow() {
    // delete anim;
}

MyAdapter::MyAdapter(ViewGroup* container) {

    std::vector<int> signal;
    std::vector<std::string> name;
    std::vector<int> lock;

    container->getContext()->getArray("@array/network_list_signal", signal);
    container->getContext()->getArray("@array/network_list_name", name);
    container->getContext()->getArray("@array/network_list_lock", lock);

    LOGD("detanum: %d", signal.size());

    for (int i = 0; i < signal.size(); i++) {
        wlanList.push_back({ signal.at(i), name.at(i), lock.at(i) });
    };
}

int MyAdapter::getCount() const {
    return wlanList.size();
}

View* MyAdapter::getView(int position, View* convertView, ViewGroup* parent) {

    View* view = LayoutInflater::from(parent->getContext())->inflate("@layout/network_list", nullptr, false);

    // 网络名
    TextView* tv = (TextView*)view->findViewById(z10::R::id::network_list_name);
    tv->setText(wlanList.at(position).name);

    // 信号图标
    ImageView* icon = (ImageView*)view->findViewById(z10::R::id::wifi_icon);
    icon->setImageResource(signalIcon(wlanList.at(position).signal));

    // 显示网络名
    if (!!wlanList.at(position).lock) {
        icon = (ImageView*)view->findViewById(z10::R::id::wifi_lock);
        icon->setImageResource("@mipmap/icon_lock");
    };

    LOGD("%s-%d-%d", wlanList.at(position).name.c_str(), wlanList.at(position).signal, wlanList.at(position).lock);

    // parent->addView(view);
    return view;
}

void* MyAdapter::getItem(int position) const {
    return nullptr;
}

std::string signalIcon(int signal) {
    switch (signal) {
    case 4:
        return "@mipmap/icon_wifi";
        break;
    case 3:
        return  "@mipmap/icon_wifi_three";
        break;
    case 2:
        return "@mipmap/icon_wifi_two";
        break;
    case 1:
        return "@mipmap/icon_wifi_one";
        break;
    default:
        return "@mipmap/icon_wifi_off";
        break;
    };
}
