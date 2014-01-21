//
//  CSQService.cpp
//  hcppservice
//
//  Created by zhang hailong on 12-12-26.
//  Copyright (c) 2012年 9vteam. All rights reserved.
//
#include "hconfig.h"
#include "CSQService.h"

using namespace HCPP;

namespace CS {
    
    IMP_CLASS(CSQService, CSService)
    
    CSQService::CSQService(void){
        _taskQueues = NULL;
    }
    
    CSQService::~CSQService(void){
        if(_taskQueues){
            _taskQueues->release();
        }
    }
    
    CSTaskQueue * CSQService::taskQueue(HCPP::Class * taskType,bool allowCreate){
        CSTaskQueue * tQueue = _taskQueues ? (CSTaskQueue *)_taskQueues->objectForKey(taskType->name) : NULL;
        if(tQueue == NULL){
            if(allowCreate){
                tQueue = new CSTaskQueue();
                if(_taskQueues == NULL){
                    _taskQueues = new Dictionary();
                }
                _taskQueues->setObjectForKey(taskType->name, tQueue);
                tQueue->autorelease();
            }
        }
        return tQueue;
    }
    
    bool CSQService::isDisplaced(){
        if(_taskQueues){
            DictionaryIterator i = _taskQueues->begin();
            while(i != _taskQueues->end()){
                CSTaskQueue * tQueue = (CSTaskQueue *) i->second;
                if(tQueue->count() >0){
                    return false;
                }
                i ++;
            }
        }
        return true;
    }
    
    void CSQService::didCancelHandleTask(HCPP::Class * taskType,CSTask * task){
        
    }
    
    void CSQService::didNeedHandleTask(HCPP::Class * taskType,CSTask * focusTask){
        
    }
    
    bool CSQService::handle(HCPP::Class * taskType,CSTask * task,int priority){
        
        CSTaskQueue * queue = taskQueue(taskType, true);
        
        queue->joinTask(task, priority);
        
        if(!queue->hasFocusTask()){
            didNeedHandleTask(taskType,queue->focusTask());
        }
        
        return false;
    }
    
    bool CSQService::cancelHandle(HCPP::Class * taskType,CSTask * task){
        
        CSTaskQueue * queue = taskQueue(taskType, false);
        
        if(queue){
            CSTask * focusTask = queue->remove(task);
            if(focusTask){
                didCancelHandleTask(taskType, focusTask);
                didNeedHandleTask(taskType,queue->focusTask());
            }
        }
        
        return false;
    }
    
    bool CSQService::cancelHandle(HCPP::Class * taskType){
        
        CSTaskQueue * queue = taskQueue(taskType, false);
        
        if(queue){
            CSTask * focusTask = queue->removeAllTask();
            if(focusTask){
                didCancelHandleTask(taskType, focusTask);
                didNeedHandleTask(taskType,queue->focusTask());
            }
        }
        
        return false;
    }
    
    bool CSQService::cancelHandleForParentTask(HCPP::Class * taskType,CSTask * parentTask){
        
        CSTaskQueue * queue = taskQueue(taskType, false);
        
        if(queue){
            CSTask * focusTask = queue->removeForParentTask(parentTask);
            if(focusTask){
                didCancelHandleTask(taskType, focusTask);
                didNeedHandleTask(taskType,queue->focusTask());
            }
        }
        
        return false;
    }
    
    bool CSQService::cancelHandleForParentTaskType(HCPP::Class * taskType,HCPP::Class * parentTaskType){
        
        CSTaskQueue * queue = taskQueue(taskType, false);
        
        if(queue){
            CSTask * focusTask = queue->removeForParentTaskType(parentTaskType);
            if(focusTask){
                didCancelHandleTask(taskType, focusTask);
                didNeedHandleTask(taskType,queue->focusTask());
            }
        }
        
        return false;
    }
    
    void CSQService::removeFocusTask(HCPP::Class * taskType,CSTask * task){
        CSTaskQueue * queue = taskQueue(taskType, false);
        
        if(queue){
            queue->removeFocusTask();
            didNeedHandleTask(taskType,queue->focusTask());
        }
    }
    
}