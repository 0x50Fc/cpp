//
//  CSDownlinkService.cpp
//  hcppservice
//
//  Created by zhang hailong on 12-12-26.
//  Copyright (c) 2012年 9vteam. All rights reserved.
//

#include "hconfig.h"
#include "CSDownlinkService.h"

using namespace HCPP;

namespace CS {
    
    IMP_CLASS(CSDownlinkService, CSService)
    
    CSDownlinkService::CSDownlinkService(void){
        _cache = NULL;
    }
    
    CSDownlinkService::~CSDownlinkService(void){
        if(_cache){
            _cache->release();
        }
    }
    
    CSCache * CSDownlinkService::cache(){
        if(_cache == NULL){
            _cache = new CSCache(context(),CSCacheTypeTemp,clazz()->name);
        }
        return _cache;
    }
    
    void CSDownlinkService::didReceiveMemoryWarning(){
        if(_cache){
            _cache->release();
            _cache = NULL;
        }
        CSService::didReceiveMemoryWarning();
    }
    
    Value * CSDownlinkService::cacheValueKey(CSDownlinkTask * task,Class * taskType){
        Value * v = new Value(taskType->name);
        return (Value *)v->autorelease();
    }
    
    void CSDownlinkService::downlinkTaskDidLoadedFormCache(CSDownlinkTask * task,Class * taskType){
        Value * v = cacheValueKey(task, taskType);
        Object * data = NULL;
        double timestamp = 0;
        CSDownlinkTaskDelegate d = task->downlinkDelegate();
        
        if(v){
            Dictionary * d = (Dictionary * )cache()->objectForKey(v->stringValue());
            if(d){
                data = d->objectForKey("data");
                v = (Value *)d->objectForKey("timestamp");
                if(v){
                    timestamp = v->doubleValue();
                }
            }
        }
        
        if(d.target && d.didLoadedFromCache && data){
            (d.target->*d.didLoadedFromCache)(context(),task,data,timestamp,taskType);
        }
    }
    
    void CSDownlinkService::downlinkTaskDidLoaded(CSDownlinkTask * task,Class * taskType,Object * data,bool allowCache){
        if(allowCache){
            Value * v = cacheValueKey(task, taskType);
            if(v){
                Dictionary * d = new Dictionary();
                struct timeval tm;
                
                gettimeofday(&tm, NULL);
                
                d->setObjectForKey("data", data);
                
                d->setObjectForKey("timestamp", Value::newValue((double) tm.tv_sec + (double)tm.tv_usec / 1000000.0));
                
                cache()->setObjectForKey(v->stringValue(), d);
                
                d->release();
            }
        }
        CSDownlinkTaskDelegate d = task->downlinkDelegate();
        if(d.target && d.didLoaded){
            (d.target->*d.didLoaded)(context(),task,data,taskType);
        }
    }
    
    void CSDownlinkService::downlinkTaskDidFital(CSDownlinkTask * task,Class * taskType,int errorCode,const char * error){
        CSDownlinkTaskDelegate d = task->downlinkDelegate();
        if(d.target && d.didFital){
            (d.target->*d.didFital)(context(),task,errorCode,error,taskType);
        }
    }
    
}

