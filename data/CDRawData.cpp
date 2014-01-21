//
//  CDRawData.cpp
//  hcppdata
//
//  Created by zhang hailong on 12-12-21.
//  Copyright (c) 2012年 9vteam. All rights reserved.
//

#include "hconfig.h"
#include "CDRawData.h"

namespace CD {
    
    IMP_CLASS(CDRawData, Object)
    
    CDRawData::CDRawData(void){
        
    }
    
    CDRawData::~CDRawData(void){
        
    }
    
    CDID CDRawData::rawId(){
        return 0;
    }
    
    bool CDRawData::hasChange(){
        return false;
    }
    
    bool CDRawData::isDeleted(){
        return false;
    }
    
    bool CDRawData::isInserted(){
        return false;
    }
    
    Object * CDRawData::value(CDDataEntityField * field){
        return NULL;
    }
    
    void CDRawData::setValue(CDDataEntityField * field,Object * value){
        
    }
    
    CDDataEntity * CDRawData::dataEntity(){
        return NULL;
    }
}