//
//  CSContextDefault.cpp
//  hcppservice
//
//  Created by zhang hailong on 12-12-20.
//  Copyright (c) 2012年 9vteam. All rights reserved.
//

#include "hconfig.h"
#include "CSContextDefault.h"
#include "hlog.h"
#include "Dictionary.h"

using namespace HCPP;

namespace CS {
    
    IMP_CLASS(CSContextDefault, CSContext)
    
    CSContextDefault::CSContextDefault(void){
        _deviceType = CSDeviceTypeNone;
        _bundle = NULL;
    }
    
    CSContextDefault::~CSContextDefault(void){
        if(_bundle){
            _bundle->release();
        }
    }
    
    bool CSContextDefault::handle(HCPP::Class * taskType,CSTask * task,int priority){
        HCPP::ArrayIterator i = _containers.begin();
        
        while(i != _containers.end()){
            CSContainer * container = (CSContainer *) (* i);
            if(container->hasTaskType(taskType)){
                CSService * s = container->instance();
                if(s){
                    if(! s->handle(taskType, task, priority)){
                        return false;
                    }
                }
                else{
                    hlog("CSContextDefault::handle Not Found CSService %s",container->instanceClass()->name);
                }
            }
            i++;
        }
        
        return true;
    }
    
    bool CSContextDefault::cancelHandle(HCPP::Class * taskType,CSTask * task){
        
        HCPP::ArrayIterator i = _containers.begin();
        while(i != _containers.end()){
            CSContainer * container = (CSContainer *) (* i);
            if(container->hasTaskType(taskType)){
                CSService * s = container->instance();
                if(s){
                    if(! s->cancelHandle(taskType, task)){
                        return false;
                    }
                }
                else{
                    hlog("CSContextDefault::handle Not Found CSService %s",container->instanceClass()->name);
                }
            }
            i++;
        }
        
        return true;
    }
    
    bool CSContextDefault::cancelHandle(HCPP::Class * taskType){
        HCPP::ArrayIterator i = _containers.begin();
        while(i != _containers.end()){
            CSContainer * container = (CSContainer *) (* i);
            if(container->hasTaskType(taskType)){
                CSService * s = container->instance();
                if(s){
                    if(! s->cancelHandle(taskType)){
                        return false;
                    }
                }
                else{
                    hlog("CSContextDefault::handle Not Found CSService %s",container->instanceClass()->name);
                }
            }
            i++;
        }
        
        return true;

    }
    
    bool CSContextDefault::cancelHandleForParentTask(HCPP::Class * taskType,CSTask * parentTask){
        HCPP::ArrayIterator i = _containers.begin();
        while(i != _containers.end()){
            CSContainer * container = (CSContainer *) (* i);
            if(container->hasTaskType(taskType)){
                CSService * s = container->instance();
                if(s){
                    if(! s->cancelHandleForParentTask(taskType, parentTask)){
                        return false;
                    }
                }
                else{
                    hlog("CSContextDefault::handle Not Found CSService %s",container->instanceClass()->name);
                }
            }
            i++;
        }
        
        return true;
    }
    
    bool CSContextDefault::cancelHandleForParentTaskType(HCPP::Class * taskType,Class * parentTaskType){
        HCPP::ArrayIterator i = _containers.begin();
        while(i != _containers.end()){
            CSContainer * container = (CSContainer *) (* i);
            if(container->hasTaskType(taskType)){
                CSService * s = container->instance();
                if(s){
                    if(! s->cancelHandleForParentTaskType(taskType, parentTaskType)){
                        return false;
                    }
                }
                else{
                    hlog("CSContextDefault::handle Not Found CSService %s",container->instanceClass()->name);
                }
            }
            i++;
        }
        
        return true;
    }
    
    void CSContextDefault::setConfig(Object * config){
        if(config){
            
            HCPP::Array * services = NULL;

            if(config->isKindOfClass(&HCPP::Array::oClass)){
                services = (HCPP::Array *) config;
            }
            else if(config->isKindOfClass(&HCPP::Dictionary::oClass)){
                services = (HCPP::Array *) ((Dictionary *) config)->objectForKey("services");
            }
            
            if(services){
                HCPP::ArrayIterator i = services->begin();
                
                while(i != services->end()){
                    
                    HCPP::Dictionary * service = (HCPP::Dictionary *) (* i);
                    
                    HCPP::Value * vClass = (HCPP::Value *)service->objectForKey("class");
                    if(vClass && vClass->stringValue()){
                        HCPP::Class * clazz = HCPP::GetClass(vClass->stringValue());
                        if(clazz){
                            if(ClassIsInherit(clazz, &CSService::oClass)){
                                CSContainer * container = addService(clazz);
                                
                                container->setConfig(service->objectForKey("config"));
                                
                                HCPP::Value * vInherit = (HCPP::Value *)service->objectForKey("inherit");
                                if(vInherit){
                                    container->setInherit(vInherit->booleanValue());
                                }
                                
                                HCPP::Value * vInstance = (HCPP::Value *) service->objectForKeyPath("instance");
                                
                                if(vInstance && vInstance->booleanValue()){
                                    container->instance();
                                }
                                
                                HCPP::Array * taskTypes = (HCPP::Array *) service->objectForKey("taskTypes");
                                if(taskTypes){
                                    HCPP::ArrayIterator ti = taskTypes->begin();
                                    while(ti != taskTypes->end()){
                                        
                                        vClass = (HCPP::Value *) * ti;
                                        
                                        if(vClass->stringValue()){
                                            clazz = HCPP::GetClass(vClass->stringValue());
                                            if(clazz){
                                                if(ClassIsInherit(clazz, &CSTask::oClass)){
                                                    container->addTaskType(clazz);
                                                }
                                                else{
                                                    hlog("CSContextDefault::setConfig %s not inherit CSTask\n",vClass->stringValue());
                                                }
                                            }
                                            else{
                                                hlog("CSContextDefault::setConfig Not Found CSTask %s\n",vClass->stringValue());
                                            }
                                        }
                                        
                                        ti++;
                                    }
                                }
                            }
                            else{
                                hlog("CSContextDefault::setConfig %s not inherit CSService\n",vClass->stringValue());
                            }
                        }
                        else{
                            hlog("CSContextDefault::setConfig Not Found CSService %s\n",vClass->stringValue());
                        }
                    }
                    
                    i++;
                }
            }
        }
    }
    
    CSContainer * CSContextDefault::addService(HCPP::Class * serviceClass){
        
        CSContainer * container = new CSContainer();
        container->setInstanceClass(serviceClass);
        container->setContext(this);
        _containers.addObject(container);
        container->release();
        
        return container;
    }
    
    const char * CSContextDefault::tempDir(){
        return _tempDir.c_str();
    }
    
    const char * CSContextDefault::documentDir(){
        return _documentDir.c_str();
    }
    
    const char * CSContextDefault::resourceDir(){
        return _resourceDir.c_str();
    }
    
    void CSContextDefault::setTempDir(const char * tempDir){
        _tempDir = tempDir;
    }
    
    void CSContextDefault::setDocumentDir(const char * documentDir){
        _documentDir = documentDir;
    }

    void CSContextDefault::setResourceDir(const char * resourceDir){
        _resourceDir = resourceDir;
    }
    
    void CSContextDefault::didReceiveMemoryWarning(){
        HCPP::ArrayIterator i = _containers.begin();
        while(i != _containers.end()){
            CSContainer * container = (CSContainer *) (* i);
            if(container->isInstance()){
                CSService * s = container->instance();
                if(s){
                    s->didReceiveMemoryWarning();
                }
                if(s->isDisplaced()){
                    container->removeInstance();
                }
            }
            i++;
        }
        CSContext::didReceiveMemoryWarning();
    }
    
    const char * CSContextDefault::deviceId(){
        return _deviceId.c_str();
    }
    
    void CSContextDefault::setDeviceId(const char * deviceId){
        _deviceId = deviceId;
    }
    
    const char * CSContextDefault::deviceName(){
        return _deviceName.c_str();
    }
    
    void CSContextDefault::setDeviceName(const char * deviceName){
        _deviceName = deviceName;
    }
    
    const char * CSContextDefault::deviceOS(){
        return _deviceOS.c_str();
    }
    
    void CSContextDefault::setDeviceOS(const char * deviceOS){
        _deviceOS = deviceOS;
    }
    
    const char * CSContextDefault::deviceOSVersion(){
        return _deviceOSVersion.c_str();
    }
    
    void CSContextDefault::setDeviceOSVerstion(const char * deviceOSVersion){
        _deviceOSVersion = deviceOSVersion;
    }
    
    const char * CSContextDefault::deviceModel(){
        return _deviceModel.c_str();
    }
    
    void CSContextDefault::setDeviceModel(const char * deviceModel){
        _deviceModel = deviceModel;
    }
    
    CSDeviceType CSContextDefault::deviceType(){
        return _deviceType;
    }
    
    void CSContextDefault::setDeviceType(CSDeviceType deviceType){
        _deviceType = deviceType;
    }
    
    HCPP::Bundle * CSContextDefault::bundle(){
        return _bundle;
    }
    
    void CSContextDefault::setBundle(HCPP::Bundle * bundle){
        if(bundle){
            bundle->retain();
        }
        if(_bundle){
            _bundle->release();
        }
        _bundle = bundle;
    }
}