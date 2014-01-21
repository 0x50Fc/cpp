//
//  CSSDeviceService.cpp
//  hcppservice
//
//  Created by zhang hailong on 13-1-25.
//  Copyright (c) 2013年 9vteam. All rights reserved.
//

#include "hconfig.h"
#include "CSSDeviceService.h"

#include "CSSyncRequestTask.h"
#include "CSSyncResponseTask.h"
#include "CSCache.h"

#include "Value.h"

using namespace HCPP;

namespace CS {

    IMP_CLASS(CSSDeviceService,CSService)
    
    CSSDeviceService::CSSDeviceService(void){
        
    }
    
    CSSDeviceService::~CSSDeviceService(void){
        
    }
    
    bool CSSDeviceService::handle(HCPP::Class * taskType,CSTask * task,int priority){
        
        
        if(taskType == &CSSyncRequestTask::oClass){
            
            CSSyncRequestTask * reqTask = (CSSyncRequestTask *) task;
            
            CSContext * ctx = context();
            
            CSCache * cache = ctx->appCache();
            
            Value * v = (Value *)cache->objectForKey("device-did");
            
            if(v && v->int64Value()){
                reqTask->addPostData("device-did", "%lld",v->int64Value());
            }
            else{
                reqTask->addPostData("device-unique", ctx->deviceId());
                reqTask->addPostData("device-name", ctx->deviceName());
                reqTask->addPostData("device-systemName", ctx->deviceOS());
                reqTask->addPostData("device-systemVersion", ctx->deviceOSVersion());
                reqTask->addPostData("device-model", ctx->deviceModel());
                reqTask->addPostData("device-type", "%d",ctx->deviceType());
            }
            
            v = (Value *) cache->objectForKey("device-token");
            
            if(v && v->stringValue()){
                reqTask->addPostData("device-token", v->stringValue());
            }
            
        }
        else if(taskType == &CSSyncResponseTask::oClass){
            
            CSSyncResponseTask * respTask = (CSSyncResponseTask *)task;
            
            Object * body = respTask->body();
            
            if(body){
                Value * v = (Value *)body->objectForKeyPath("error-code");
                if(v && v->intValue() == BS_NOT_FOUND_DEVICE_ERROR){
                    CSContext * ctx = context();
                    CSCache * cache = ctx->appCache();
                    cache->removeForKey("device-did");
                    
                    respTask->setContinueSync(true);
                }
                else{
                    v =  (Value *)body->objectForKeyPath("device-did");
                    if(v){
                        CSContext * ctx = context();
                        CSCache * cache = ctx->appCache();
                        cache->setObjectForKey("device-did", v);
                    }
                }
            }
        }
        
        return true;
    }
    
}
