//
//  CSHttpStateMessageTask.cpp
//  hcppservice
//
//  Created by zhang hailong on 13-2-5.
//  Copyright (c) 2013年 9vteam. All rights reserved.
//
#include "hconfig.h"
#include "CSHttpStateMessageTask.h"


namespace CS {
    
    IMP_CLASS(CSHttpStateMessageTask, CSMessageTask)
    
    CSHttpStateMessageTask::CSHttpStateMessageTask(void){
        _httpState = CSHttpStateNone;
    }
    
    CSHttpStateMessageTask::CSHttpStateMessageTask(CSHttpState httpState){
        _httpState = httpState;
    }
    
    CSHttpStateMessageTask::~CSHttpStateMessageTask(void){
        
    }
    
    CSHttpState CSHttpStateMessageTask::httpState(){
        return _httpState;
    }
    
    
    CSHttpStateMessageTask * CSHttpStateMessageTask::newHttpStateMessageTask(CSHttpState httpState){
        CSHttpStateMessageTask * task = new CSHttpStateMessageTask(httpState);
        return (CSHttpStateMessageTask *) task->autorelease();
    }
    
    
}