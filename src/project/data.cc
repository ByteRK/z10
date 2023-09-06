#include "data.h"

std::vector<WATER> modeData;
//读取数据
void readModeData(ViewGroup* container){
    std::vector<int>            array_type;
    std::vector<std::string>    array_item;
    std::vector<std::string>    array_picture;
    std::vector<std::string>    array_picture_2;
    std::vector<int>            array_wendu;
    std::vector<int>            array_chushuiliang;

    container->getContext()->getArray("@array/type",array_type);
    LOGD("array.size()=%d ",array_type.size());

    container->getContext()->getArray("@array/item",array_item);
    container->getContext()->getArray("@array/picture",array_picture);
    container->getContext()->getArray("@array/picture_2",array_picture_2);
    container->getContext()->getArray("@array/wendu",array_wendu);
    container->getContext()->getArray("@array/chushuiliang",array_chushuiliang);
    
    for(int i=0;i<array_type.size();i++){
        modeData.push_back({array_type.at(i),array_item.at(i),array_picture.at(i),array_picture_2.at(i),array_wendu.at(i),array_chushuiliang.at(i)});
    } 
}


