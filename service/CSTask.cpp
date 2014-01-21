//
//  CSTask.cpp
//  hcppservice
//
//  Created by zhang hailong on 12-12-20.
//  Copyright (c) 2012年 9vteam. All rights reserved.
//

#include "hconfig.h"
#include "CSTask.h"

using namespace HCPP;

namespace CS {
    
    IMP_CLASS(CSTask, Object)
    
    CSTask::CSTask(void){
        _parentTask = NULL;
        _parentTaskType = NULL;
        _userInfo = NULL;
    }
    
    CSTask::~CSTask(void){
        if(_parentTask){
            _parentTask->release();
        }
        if(_userInfo){
            _userInfo->release();
        }
    }
    
    HCPP::Class * CSTask::parentTaskType(){
        return _parentTaskType;
    }
    
    CSTask * CSTask::parentTask(){
        return _parentTask;
    }
    
    void CSTask::setParent(CSTask * task,HCPP::Class * taskType){
        if(task){
            task->retain();
        }
        if(_parentTask){
            _parentTask->release();
        }
        _parentTask = task;
        _parentTaskType = taskType;
    }
 
    bool CSTask::isKindOfParentTask(CSTask * parentTask){
        CSTask * p = _parentTask;
        while(p){
            if(p == parentTask){
                return true;
            }
            p = p->parentTask();
        }
        return false;
    }
    
    bool CSTask::isKindOfParentTaskType(HCPP::Class * parentTaskType){
        CSTask * p = this;
        while(p){
            if(p->_parentTaskType == parentTaskType){
                return true;
            }
            p = p->parentTask();
        }
        return false;
    }
    
    Object * CSTask::userInfo(){
        return _userInfo;
    }
    
    void CSTask::setUserInfo(Object * userInfo){
        if(userInfo){
            userInfo->retain();
        }
        if(_userInfo){
            _userInfo->release();
        }
        _userInfo = userInfo;
    }
}