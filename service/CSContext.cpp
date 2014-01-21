//
//  CSContext.cpp
//  hcppservice
//
//  Created by zhang hailong on 12-12-20.
//  Copyright (c) 2012年 9vteam. All rights reserved.
//

#include "hconfig.h"
#include "CSContext.h"
#include "CSCache.h"
#include "Value.h"

using namespace HCPP;

namespace CS {
    
    IMP_CLASS(CSContext, Context)
    
    
    CSContext::CSContext(void){
        _appCache = NULL;
        _userCache = NULL;
    }
    
    CSContext::~CSContext(void){
        if(_appCache){
            _appCache->release();
        }
        if(_userCache){
            _userCache->release();
        }
    }
    
    bool CSContext::handle(HCPP::Class * taskType,CSTask * task,int priority){
        return false;
    }
    
    bool CSContext::cancelHandle(HCPP::Class * taskType,CSTask * task){
        return false;
    }
    
    bool CSContext::cancelHandle(HCPP::Class * taskType){
        return false;
    }
    
    bool CSContext::cancelHandleForParentTask(HCPP::Class * taskType,CSTask * parentTask){
        return false;
    }
    
    bool CSContext::cancelHandleForParentTaskType(HCPP::Class * taskType,HCPP::Class * parentTaskType){
        return false;
    }
    
    const char * CSContext::tempDir(){
        return NULL;
    }
    
    const char * CSContext::documentDir(){
        return NULL;
    }
    
    const char * CSContext::resourceDir(){
        return NULL;
    }
    
    void CSContext::didReceiveMemoryWarning(){
        if(_appCache){
            _appCache->release();
            _appCache = NULL;
        }
        if(_userCache){
            _userCache->release();
            _userCache = NULL;
        }
    }
    
    long long CSContext::uid(){
        
        CSCache * cache = appCache();
        
        Value * v = (Value *) cache->objectForKey("uid");
        
        if(v ){
            return v->int64Value();
        }
        
        return 0;
    }
    
    const char * CSContext::uidStr(){
        CSCache * cache = appCache();
        
        Value * v = (Value *) cache->objectForKey("uid");
        
        if(v ){
            return v->stringValue();
        }
        
        return NULL;
    }
    
    bool CSContext::setUid(long long uid){
        char s[128];
        
        sprintf(s, "%lld",uid);
        
        return setUid(s);
    }
    
    bool CSContext::setUid(const char * uid){
 
        CSCache * cache = appCache();
        
        Value * v = (Value *)cache->objectForKey("uid");
        
        if(!v || !v->stringValue() || strcmp(v->stringValue(), uid) !=0){
            
            cache->setObjectForKey("uid",  Value::newValue(uid));
            
            if(_userCache){
                _userCache->release();
                _userCache = NULL;
            }
            
            return true;
        }
        
        return false;
    }
    
    CSCache * CSContext::appCache(){
        if(_appCache == NULL){
            _appCache = new CSCache(this,CSCacheTypeStorage,"app");
        }
        return _appCache;
    }
    
    CSCache * CSContext::userCache(){
        if(_userCache == NULL){
            std::string name = "u";
            
            CSCache * cache = appCache();
            
            Value * v = (Value *)cache->objectForKey("uid");
            
            if(v){
                
                name += "_" ;
                name += v->toStringValue()->stringValue();
            }
            
            _userCache = new CSCache(this,CSCacheTypeStorage,name.c_str());
        }
        return _userCache;
    }
    
    const char * CSContext::deviceId(){
        return "";
    }
    
    const char * CSContext::deviceName(){
        return "";
    }
    
    const char * CSContext::deviceOS(){
        return "";
    }
    
    const char * CSContext::deviceOSVersion(){
        return "";
    }
    
    const char * CSContext::deviceModel(){
        return "";
    }
    
    CSDeviceType CSContext::deviceType(){
        return CSDeviceTypeNone;
    }
    
    
    HCPP::Bundle * CSContext::bundle(){
        return NULL;
    }

}