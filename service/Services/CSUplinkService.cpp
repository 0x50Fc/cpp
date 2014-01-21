//
//  CSUplinkService.cpp
//  hcppservice
//
//  Created by zhang hailong on 12-12-26.
//  Copyright (c) 2012年 9vteam. All rights reserved.
//
#include "hconfig.h"
#include "CSUplinkService.h"

using namespace HCPP;

namespace CS {
    
    IMP_CLASS(CSUplinkService, CSService)
    
    CSUplinkService::CSUplinkService(void){
        
    }
    
    CSUplinkService::~CSUplinkService(void){
        
    }
    
    void CSUplinkService::uplinkTaskDidFinish(CSUplinkTask * task,Class * taskType,Object * data){
        CSUplinkTaskDelegate d = task->uplinkDelegate();
        if(d.target && d.didFinish){
            (d.target->*d.didFinish)(context(),task,data,taskType);
        }
    }
    
    void CSUplinkService::uplinkTaskDidFail(CSUplinkTask * task,Class * taskType,int errorCode,const char * error){
        CSUplinkTaskDelegate d = task->uplinkDelegate();
        if(d.target && d.didFail){
            (d.target->*d.didFail)(context(),task,errorCode,error,taskType);
        }
    }
}
