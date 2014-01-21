//
//  CSMessageListenerTask.cpp
//  hcppservice
//
//  Created by zhang hailong on 13-2-5.
//  Copyright (c) 2013年 9vteam. All rights reserved.
//
#include "hconfig.h"
#include "CSMessageListenerTask.h"


namespace CS {
    
    IMP_CLASS(CSMessageListenerTask, CSTask)
    
    
    CSMessageListenerTask::CSMessageListenerTask(void){
        memset(&_delegate, 0,sizeof(_delegate));
        _inherit = true;
        _taskType = &CSMessageTask::oClass;
    }
    
    CSMessageListenerTask::CSMessageListenerTask(HCPP::Class * taskType,bool inherit,HCPP::Object * target,CSMessageListenerTaskDelegateOnMessageFun onMessage){
        memset(&_delegate, 0,sizeof(_delegate));
        _delegate.target = target;
        _delegate.onMessage = onMessage;
        _inherit = inherit;
        _taskType = taskType;
    }
    
    CSMessageListenerTask::~CSMessageListenerTask(void){
        
    }
    
    CSMessageListenerTaskDelegate CSMessageListenerTask::delegate(){
        return _delegate;
    }
    
    void CSMessageListenerTask::setDelegate(CSMessageListenerTaskDelegate delegate){
        _delegate = delegate;
    }
    
    HCPP::Class * CSMessageListenerTask::taskType(){
        return _taskType;
    }
    
    void CSMessageListenerTask::setTaskType(HCPP::Class * taskType){
        _taskType = taskType;
    }
    
    bool CSMessageListenerTask::isInherit(){
        return _inherit;
    }
    
    void CSMessageListenerTask::setInherit(bool inherit){
        _inherit = inherit;
    }
    
    void CSMessageListenerTask::onMessage(CSContext * context,CSMessageTask * task,HCPP::Class * taskType){
        
        if(_delegate.target && _delegate.onMessage){
            (_delegate.target->*_delegate.onMessage)(context,this,task,taskType);
        }
    }
    
    CSMessageListenerTask * CSMessageListenerTask::newMessageListenerTask(HCPP::Class * taskType,bool inherit,HCPP::Object * target,CSMessageListenerTaskDelegateOnMessageFun onMessage){
        CSMessageListenerTask * t = new CSMessageListenerTask(taskType,inherit,target,onMessage);
        return (CSMessageListenerTask *)t->autorelease();
    }
}