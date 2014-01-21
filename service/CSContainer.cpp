//
//  CSContainer.cpp
//  hcppservice
//
//  Created by zhang hailong on 12-12-20.
//  Copyright (c) 2012年 9vteam. All rights reserved.
//

#include "hconfig.h"
#include "CSContainer.h"


namespace CS {
    
    IMP_CLASS(CSContainer, Object)
    
    CSContainer::CSContainer(void) {
        _instance = NULL;
        _config = NULL;
        _instanceClass = NULL;
        _inherit = false;
        _context = NULL;
    }
    
    CSContainer::~CSContainer(void){
        if(_config){
            _config->release();
        }
        if(_instance){
            _instance->release();
        }
    }
    
    void CSContainer::addTaskType(HCPP::Class * taskType){
        _taskTypes.insert(_taskTypes.end(), taskType);
    }
    
    void CSContainer::removeTaskType(HCPP::Class * taskType){
        std::vector<HCPP::Class *>::iterator i = _taskTypes.begin();
        while(i != _taskTypes.end()){
            if(* i == taskType){
                i = _taskTypes.erase(i);
            }
            else{
                i++;
            }
        }
    }
    
    bool CSContainer::hasTaskType(HCPP::Class * taskType){
        std::vector<HCPP::Class *>::iterator i = _taskTypes.begin();
        while(i != _taskTypes.end()){
            HCPP::Class * clazz = * i;
            if(clazz== taskType || (_inherit && ClassIsInherit(taskType, clazz))){
                return true;
            }
            i++;
        }
        return false;
    }
    
    bool CSContainer::isInstance(){
        return _instance != NULL;
    }
    
    CSService * CSContainer::instance(){
        if(_instance == NULL){
            if(_instanceClass){
                _instance = (CSService *) OBJ_ALLOC(_instanceClass);
                if(_instance){
                    _instance->setContext(_context);
                    _instance->setConfig(_config);
                }
            }
        }
        return _instance;
    }
    
    HCPP::Object * CSContainer::config(){
        return _config;
    }
    
    void CSContainer::setConfig(Object * config){
        if(config){
            config->retain();
        }
        if(_config){
            _config->release();
        }
        _config = config;
    }
    
    bool CSContainer::isInherit(){
        return _inherit;
    }
    
    void CSContainer::setInherit(bool inherit){
        _inherit = inherit;
    }
    
    HCPP::Class * CSContainer::instanceClass(){
        return _instanceClass;
    }
    
    void CSContainer::setInstanceClass(HCPP::Class * instanceClass){
        _instanceClass = instanceClass;
    }
    
    CSContext * CSContainer::context(){
        return _context;
    }
    
    void CSContainer::setContext(CSContext * context){
        _context = context;
    }
    
    void CSContainer::removeInstance(){
        if(_instance){
            _instance->release();
            _instance = NULL;
        }
    }
}