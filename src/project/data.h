#ifndef __DATA_H__
#define __DATA_H__

#include <iostream>
#include <stdio.h>
#include <vector>

#include "project.h"

// 预约杀菌
typedef struct tagUVSterilization {
    int         id;             // 标识ID
    int         state;          // uv杀菌的状态 (保持开启、预约时间、不开启)
    std::string time;           // 预约时间   如(10:10-12:20)

} UVSterilization;

// 收藏程序
// void          addCookYourself(CookYourself &item);
// CookYourself *newCookYourself();
// CookYourself *getCookYourself(int id);
// void          updCookYourself(CookYourself *item);
// bool          removeCookYourself(int id);


typedef struct{
    int type;
    std::string item;
    std::string picture;
    std::string picture_2;
    int wendu;
    int chushuiliang;
}WATER;

extern std::vector<WATER> modeData;

//读取数据
void readModeData(ViewGroup* container);

#endif