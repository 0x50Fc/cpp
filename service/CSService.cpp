//
//  CSService.cpp
//  hcppservice
//
//  Created by zhang hailong on 12-12-20.
//  Copyright (c) 2012年 9vteam. All rights reserved.
//

#include "hconfig.h"
#include "CSService.h"


namespace CS {
    
    IMP_PROPERTY_BEGIN(CSService)
    
    IMP_PROPERTY(config, ValueTypeObject, &CSService::config, &CSService::setConfig)
    
    IMP_PROPERTY(displaced, ValueTypeBoolean, &CSService::isDisplaced, NULL)
    
    IMP_PROPERTY_END(CSService)
    
    IMP_CLASS_P(CSService, Object)
    
    CSService::CSService(void){
        _config = NULL;
        _context = NULL;
    }
    
    CSService::~CSService(void){
        if(_config){
            _config->release();
        }
    }
    
    HCPP::Object * CSService::config(){
        return _config;
    }
    
    void CSService::setConfig(Object * config){
        if(config){
            config->retain();
        }
        if(_config){
            _config->release();
        }
        _config = config;
    }
    
    bool CSService::isDisplaced(){
        return false;
    }
    
    bool CSService::handle(HCPP::Class * taskType,CSTask * task,int priority){
        return true;
    }
    
    bool CSService::cancelHandle(HCPP::Class * taskType,CSTask * task){
        return true;
    }
    
    bool CSService::cancelHandle(HCPP::Class * taskType){
        return true;
    }
    
    bool CSService::cancelHandleForParentTask(HCPP::Class * taskType,CSTask * parentTask){
        return true;
    }
    
    bool CSService::cancelHandleForParentTaskType(HCPP::Class * taskType,HCPP::Class * parentTaskType){
        return true;
    }
    
    CSContext * CSService::context(){
        return _context;
    }
    
    void CSService::setContext(CSContext * context){
        _context = context;
    }
    
    void CSService::didReceiveMemoryWarning(){
        
    }
    
}