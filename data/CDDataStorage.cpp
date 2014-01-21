//
//  CDDataStorage.cpp
//  hcppdata
//
//  Created by zhang hailong on 12-12-21.
//  Copyright (c) 2012年 9vteam. All rights reserved.
//

#include "hconfig.h"
#include "CDDataStorage.h"

namespace CD {
    
    IMP_CLASS(CDDataStorage, Object)
    
    CDDataStorage::CDDataStorage(void){
        
    }
    
    CDDataStorage::~CDDataStorage(void){
        
    }
    
    void CDDataStorage::beginTransaction(){
        
    }
    
    void CDDataStorage::commentTransaction(){
        
    }
    
    void CDDataStorage::rerollTransaction(){
        
    }
    
    void CDDataStorage::registerEntity(CDDataEntity * dataEntity){
        
    }
    
    void CDDataStorage::remove(CDDataEntity * dataEntity,CDID rawId){
        
    }
    
    CDID CDDataStorage::insert(CDDataEntity * dataEntity,Dictionary * values){
        return 0;
    }
    
    void CDDataStorage::update(CDDataEntity * dataEntity,CDID rawId,Dictionary * values){
        
    }
    
    Dictionary * CDDataStorage::get(CDDataEntity * dataEntity,CDID rawId){
        return NULL;
    }
    
    CDCursor * CDDataStorage::query(CDFetchRequest * fetchRequest){
        return NULL;
    }

    
    
}