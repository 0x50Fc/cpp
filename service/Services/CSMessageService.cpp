//
//  CSMessageService.cpp
//  hcppservice
//
//  Created by zhang hailong on 13-2-5.
//  Copyright (c) 2013年 9vteam. All rights reserved.
//
#include "hconfig.h"
#include "CSMessageService.h"

#include "CSMessageTask.h"
#include "CSMessageListenerTask.h"

using namespace HCPP;

namespace CS {
    
    
    IMP_CLASS(CSMessageService, CSService)
    
    CSMessageService::CSMessageService(void){
        _listeners = NULL;
    }
    
    CSMessageService::~CSMessageService(void){
        if(_listeners){
            _listeners->release();
        }
    }
    
    bool CSMessageService::handle(HCPP::Class * taskType,CSTask * task,int priority){
        
        if(ClassIsInherit(taskType, &CSMessageTask::oClass)){

            if(_listeners){
                CSContext * ctx = context();
                Array listeners(* _listeners);
                ArrayIterator i = listeners.begin();
                while(i != listeners.end()){
                    CSMessageListenerTask * listenerTask = (CSMessageListenerTask *) * i;
                    HCPP::Class * tType = listenerTask->taskType();
                    if(tType &&
                       (listenerTask->isInherit() ? ClassIsInherit(task->clazz(), tType) : task->clazz() == tType )){
                        listenerTask->onMessage(ctx, (CSMessageTask *)task, tType);
                    }
                    i++;
                }
            }
            
            return false;
        }
        
        if(taskType == &CSMessageListenerTask::oClass){
            
            if(_listeners == NULL){
                _listeners = new Array();
            }
            
            _listeners->addObject(task);
            
            return false;
        }
        
        return true;
    }
    
    bool CSMessageService::cancelHandle(HCPP::Class * taskType,CSTask * task){
        
        if(taskType == &CSMessageListenerTask::oClass){
            
            if(_listeners){
                _listeners->removeObject(task);
            }
            
            return false;
        }
        
        return true;
    }
    
    bool CSMessageService::cancelHandle(HCPP::Class * taskType){
        
        if(taskType == &CSMessageListenerTask::oClass){
            
            if(_listeners){
                _listeners->removeAllObjects();
            }
            
            return false;
        }
        
        return true;
    }
    
    bool CSMessageService::cancelHandleForParentTask(HCPP::Class * taskType,CSTask * parentTask){
        
        if(taskType == &CSMessageListenerTask::oClass){
            
            if(_listeners){
                
                ArrayIterator i = _listeners->begin();
                while(i != _listeners->end()){
                    CSTask * t = (CSTask *) * i;
                    if(t->parentTask() == parentTask){
                        i = _listeners->erase(i);
                    }
                    else{
                        i++;
                    }
                }
            }
            
            return false;
        }
        
        return true;
    }
    
    bool CSMessageService::cancelHandleForParentTaskType(HCPP::Class * taskType,HCPP::Class * parentTaskType){
        
        
        if(taskType == &CSMessageListenerTask::oClass){
            
            if(_listeners){
                
                ArrayIterator i = _listeners->begin();
                while(i != _listeners->end()){
                    CSTask * t = (CSTask *) * i;
                    if(t->parentTaskType() == parentTaskType){
                        i = _listeners->erase(i);
                    }
                    else{
                        i++;
                    }
                }
            }
            
            return false;
        }
        
        return true;
    }
    
}