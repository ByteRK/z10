#ifndef __PROJECT_H__
#define __PROJECT_H__

#include <comm_func.h>
#include <common.h>

#include "R.h"

// 程序状态
typedef enum ProgramState {
    PRO_STATE_NONE = 0,                     // 某个功能无状态
    PRO_STATE_TONGSUO,                      // 开启童锁

    PRO_STATE_LVXIN_NORMAL,                 // 滤芯正常
    PRO_STATE_LVXIN_SOON,                   // 滤芯准备过期
    PRO_STATE_LVXIN_EXPIRED,                // 滤芯已经过期

    PRO_STATE_UV_KEEP_ENABLED,              // UV杀菌 保持开启
    PRO_STATE_UV_RESERVATION,               // UV杀菌 预约时间开启

    PRO_STATE_TDS,                          // TDS
    PRO_STATE_ZHAOMING,                     // 照明开启

    PRO_STATE_COOL_NONE,                    // 没有开启制冷
    PRO_STATE_COOL_ING,                     // 正在制冷
    PRO_STATE_COOL_DONE,                    // 已完成制冷

    PRO_STATE_ICE_NONE,                     // 没有开启制冰
    PRO_STATE_ICE_ING,                      // 正在制冰
    PRO_STATE_ICE_DONE,                     // 已完成制冰

    PRO_STATE_WIFI,                         // WIFI
    PRO_STATE_SETING                        // 设置
    
}State;

// 应用全局数据
typedef struct tagAppGlobalData {
    bool isChange;      //检查是否更新了状态

    int  childLocked;   // 童锁
    int  lvxin;         // 滤芯
    int  UVshajun;      // UV杀菌
    int  TDS;           // TDS 
    int  zhaoming;      // 照明
    int  zhileng;       // 制冷
    int  zhibing;       // 制冰

    tagAppGlobalData()
        : isChange(true),childLocked(PRO_STATE_NONE),lvxin(PRO_STATE_LVXIN_SOON),UVshajun(PRO_STATE_UV_KEEP_ENABLED),TDS(0),zhaoming(PRO_STATE_ZHAOMING),
            zhileng(PRO_STATE_COOL_NONE),zhibing(PRO_STATE_ICE_NONE){}
} AppGlobalData, APPGLOBALDATA, *LPAPPGLOBALDATA;

extern AppGlobalData g_appData;

///////////////////////////////////////////////////////////////////////////////////////////////
// 所有页面的时间更新
class WindowTime {
public:
    static WindowTime *ins() {
        static WindowTime ins;
        return &ins;
    }

    void delView(TextView *timeView);
    void addView(TextView *timeView);
    void updTime();

protected:
    WindowTime() {}
    ~WindowTime() {}

private:
    std::vector<TextView *> mTimeView;
    int mtime_state;
};

#endif