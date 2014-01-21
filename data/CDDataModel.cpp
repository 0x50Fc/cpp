//
//  CDDataModel.cpp
//  hcppdata
//
//  Created by zhang hailong on 12-12-25.
//  Copyright (c) 2012年 9vteam. All rights reserved.
//
#include "hconfig.h"
#include "CDDataModel.h"


namespace CD {
    
    IMP_CLASS(CDDataModel, Object)
    
    CDDataModel::CDDataModel(void){
    
    }
    
    CDDataModel::~CDDataModel(void){
        
    }
    
    void CDDataModel::addDataEntity(CDDataEntity * dataEntity,Class * objectClass){
        _dataEntitys.insert(_dataEntitys.end(), dataEntity);
        _dataObjectClasss[dataEntity] = objectClass;
        std::string sKey(dataEntity->name);
        _dataEntitysMap[sKey] = dataEntity;
    }
    
    CDDataEntityVectorIterator CDDataModel::begin(){
        return _dataEntitys.begin();
    }
    
    CDDataEntityVectorIterator CDDataModel::end(){
        return _dataEntitys.end();
    }
    
    Class * CDDataModel::dataObjectClass(CDDataEntity * dataEntity){
        std::map<CDDataEntity *,Class *>::iterator i = _dataObjectClasss.find(dataEntity);
        if(i != _dataObjectClasss.end()){
            return i->second;
        }
        return NULL;
    }
    
    CDDataEntity * CDDataModel::dataEntity(const char * name){
        std::string sKey(name);
        std::map<std::string,CDDataEntity *>::iterator i =  _dataEntitysMap.find(sKey);
        if(i != _dataEntitysMap.end()){
            return i->second;
        }
        return NULL;
    }
}