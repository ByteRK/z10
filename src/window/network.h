#pragma once
#include <widget/cdwindow.h>

typedef struct {
    int signal;
    std::string name;
    int lock;
} WLANLIST;

typedef struct {
    int status;
    WLANLIST detail;
} WLANCONNECT;

class NetWorkWindow : public Window {
private:
    WLANCONNECT wlanConnect;

    bool CONNECT;
    View* HEADERVIEW;
protected:
public:
    NetWorkWindow();
    ~NetWorkWindow();
    void getConnectInfo(ViewGroup* container, ListView* view);
    void createConnect(ListView* view);

    void setConnectInfo(int signal, std::string name, int lock, int status = 1) {
        wlanConnect.status = status;
        wlanConnect.detail.signal = signal;
        wlanConnect.detail.name = name;
        wlanConnect.detail.lock = lock;
    };

    void setConnect(int status) {
        CONNECT = status == 1 ? true : false;
    };
};

class MyAdapter : public Adapter {
private:
    std::vector<WLANLIST> wlanList;
public:
    MyAdapter(ViewGroup* container);
    int getCount() const override;
    View* getView(int position, View* convertView, ViewGroup* parent) override;
    void* getItem(int position) const override;
};

std::string signalIcon(int signal);
