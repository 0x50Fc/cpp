//
//  CSSyncService.cpp
//  hcppservice
//
//  Created by zhang hailong on 13-1-25.
//  Copyright (c) 2013年 9vteam. All rights reserved.
//
#include "hconfig.h"
#include "CSSyncService.h"

#include "CSSyncTask.h"
#include "CSSyncRequestTask.h"
#include "CSSyncResponseTask.h"

#include "hlog.h"

#include "Value.h"

using namespace HCPP;

namespace CS {
    
    IMP_CLASS(CSSyncService, CSQService)

    CSSyncService::CSSyncService(void){
        
    }
    
    CSSyncService::~CSSyncService(void){
        
    }
    
    void CSSyncService::didCancelHandleTask(HCPP::Class * taskType,CSTask * task){
        
        context()->cancelHandleForParentTask(&CSAPITask::oClass, task);
        
        CSQService::didCancelHandleTask(taskType, task);
    }
    
    void CSSyncService::didNeedHandleTask(HCPP::Class * taskType,CSTask * focusTask){
        
        if(focusTask){
            CSSyncRequestTask * reqTask = new CSSyncRequestTask();
            reqTask->setResponseType(CSHttpTaskResponseTypeJSON);
            reqTask->setEncodeType(CSHttpTaskEncodeTypeMcrypt);
            
            CSHttpTaskDelegate d = {
                this,
                NULL,
                (CSHttpTaskDelegateDidFailFun)&CSSyncService::onHttpTaskDidFail,
                (CSHttpTaskDelegateDidFinishLoadingFun)&CSSyncService::onHttpTaskDidFinishLoading,
                NULL,NULL,NULL,
                NULL,NULL,NULL,
            };
            
            reqTask->setParent(focusTask, taskType);
            reqTask->setHttpDelegate(d);
            
            Object * cfg = config();
            
            if(cfg){
                Value * v = (Value *) cfg->objectForKeyPath("url");
                if(v && v->stringValue()){
                    reqTask->setBaseUrl(v->stringValue());
                }
                Dictionary * d = (Dictionary * ) cfg->objectForKeyPath("params");
                if(d){
                    DictionaryIterator i = d->begin();
                    while(i != d->end()){
                        reqTask->setPostData(i->first.c_str(), i->second->toStringValue()->stringValue());
                        i++;
                    }
                }
            }
            
            context()->handle(&CSSyncRequestTask::oClass, reqTask, 0);
            
            context()->handle(&CSAPITask::oClass, reqTask, 0);
            
            reqTask->release();
        }
        
        CSQService::didNeedHandleTask(taskType, focusTask);
    }
    
    void CSSyncService::onHttpTaskDidFail(CSContext * context,CSHttpTask * httpTask,int errorCode,const char * error){
    
        removeFocusTask(httpTask->parentTaskType(), httpTask->parentTask());
        
        CSSyncResponseTask * respTask = new CSSyncResponseTask(errorCode,error);
        
        respTask->setParent(httpTask->parentTask(), httpTask->parentTaskType());
        
        context->handle(&CSSyncResponseTask::oClass,respTask,0);
        
        respTask->release();
    }
    
    void CSSyncService::onHttpTaskDidFinishLoading(CSContext * context,CSHttpTask * httpTask){
        
        removeFocusTask(httpTask->parentTaskType(), httpTask->parentTask());
        
        CSSyncResponseTask * respTask = new CSSyncResponseTask(httpTask->responseValue());
        
        respTask->setParent(httpTask->parentTask(), httpTask->parentTaskType());
        
        context->handle(&CSSyncResponseTask::oClass,respTask,0);
        
        if(respTask->isContinueSync()){
            handle(httpTask->parentTaskType(), httpTask->parentTask(), 0);
        }
        
        respTask->release();
    }
    
    bool CSSyncService::handle(HCPP::Class * taskType,CSTask * task,int priority){
        CSQService::handle(taskType, task, priority);
        return true;
    }
}
