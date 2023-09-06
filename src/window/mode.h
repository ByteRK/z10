#pragma once
#include <widget/cdwindow.h>
#include <widget/keyboardview.h>

#include <data.h>
#include "mode_add.h"
#include "mode_edit.h"

// typedef struct {
//     int type;
//     std::string img;
//     std::string img2;
//     std::string name;
//     int warm;
//     int water;
// } MODEDATA;

class ModeWindow : public Window {
private:
protected:
    void ModeWindowClick(View&);
public:
    ModeWindow();
    ~ModeWindow();
};

class ModeAdapter : public Adapter{
    WATER datacache;

    Window* edit;
protected:
    void ViewClick(View& view);
    void DelPop(int position);
public:
    ModeAdapter(ViewGroup* container);
    int getCount() const override;
    View* getView(int position, View* convertView, ViewGroup* parent) override;
    void* getItem(int position) const override;
    void deldata(int location);
    void changedata(int location, int dir);

    void buildedit(int position);
    void buildadd();
    void savecache() {
        modeData.push_back(datacache);
    };
    void savecache(int location) {
        modeData.at(location).picture_2 = datacache.picture_2;
        modeData.at(location).picture = datacache.picture;
        modeData.at(location).item = datacache.item;
        modeData.at(location).wendu = datacache.wendu;
        modeData.at(location).chushuiliang = datacache.chushuiliang;
        modeData.at(location).type = datacache.type;
    };
    void tocache() {
        datacache.picture_2 = "@mipmap/pic_chushui_changwen";
        datacache.picture = "@mipmap/pic_changwenshui";
        datacache.item = "斑痧";
        datacache.wendu = 26;
        datacache.chushuiliang = 250;
        datacache.type = 1;
    };
    void tocache(int location) {
        datacache.picture_2 = modeData.at(location).picture_2;
        datacache.picture = modeData.at(location).picture;
        datacache.item = modeData.at(location).item;
        datacache.wendu = modeData.at(location).wendu;
        datacache.chushuiliang = modeData.at(location).chushuiliang;
        datacache.type = modeData.at(location).type;
    };
};

class PopModeWindow :public Window {
private:
protected:
public:
    PopModeWindow();
    ~PopModeWindow();
};
