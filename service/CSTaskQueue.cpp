//
//  CSTaskQueue.cpp
//  hcppservice
//
//  Created by zhang hailong on 12-12-26.
//  Copyright (c) 2012年 9vteam. All rights reserved.
//

#include "hconfig.h"
#include "CSTaskQueue.h"


namespace CS {
    
    IMP_CLASS(CSTaskQueue, Object);
    
    CSTaskQueue::CSTaskQueue(void){
        _focusTask = NULL;
    }
    
    CSTaskQueue::~CSTaskQueue(void){
        std::vector<CSTaskQueueItem>::iterator i = _items.begin();
        while(i != _items.end()){
            CSTaskQueueItem item = *i;
            item.task->release();
            i++;
        }
    }
    
    CSTask * CSTaskQueue::focusTask(){
        if(_focusTask == NULL){
            std::vector<CSTaskQueueItem>::iterator i = _items.begin();
            if(i != _items.end()){
                CSTaskQueueItem item = *i;
                _focusTask = item.task;
            }
        }
        return _focusTask;
    }
    
    bool CSTaskQueue::hasFocusTask(){
        return _focusTask != NULL;
    }
    
    void CSTaskQueue::removeFocusTask(){
        if(_focusTask){
            _items.erase(_items.begin());
            _focusTask->release();
            _focusTask = NULL;
        }
    }
    
    void CSTaskQueue::joinTask(CSTask * task,int priority){
        std::vector<CSTaskQueueItem>::iterator i = _items.begin();
        if(_focusTask && i != _items.end()){
            i ++;
        }
        while(i != _items.end()){
            CSTaskQueueItem item = *i;
            if(item.priority > priority){
                break;
            }
            i++;
        }
        CSTaskQueueItem item = {(CSTask *)task->retain(),priority};
        _items.insert(i, item);
    }
    
    CSTask * CSTaskQueue::remove(HCPP::Class * taskClass,bool inherit){
        CSTask * focusTask = NULL;
        if(_focusTask && (inherit ? _focusTask->isKindOfClass(taskClass) : _focusTask->clazz() == taskClass)){
            focusTask = _focusTask;
            focusTask->retain();
            focusTask->autorelease();
            _focusTask = NULL;
        }
        std::vector<CSTaskQueueItem>::iterator i = _items.begin();
        while(i != _items.end()){
            CSTaskQueueItem item = *i;
            if((inherit ? item.task->isKindOfClass(taskClass) : item.task->clazz() == taskClass)){
                item.task->release();
                i = _items.erase(i);
            }
            else{
                i++;
            }
        }
        return focusTask;
    }
    
    CSTask * CSTaskQueue::remove(CSTask * task){
        CSTask * focusTask = NULL;
        if(_focusTask == task){
            focusTask = _focusTask;
            focusTask->retain();
            focusTask->autorelease();
            _focusTask = NULL;
        }
        std::vector<CSTaskQueueItem>::iterator i = _items.begin();
        while(i != _items.end()){
            CSTaskQueueItem item = *i;
            if(item.task ==task){
                item.task->release();
                i = _items.erase(i);
            }
            else{
                i++;
            }
        }
        return focusTask;
    }
    
    CSTask * CSTaskQueue::removeForParentTask(CSTask * parentTask){
        CSTask * focusTask = NULL;
        if(_focusTask && _focusTask->isKindOfParentTask(parentTask)){
            focusTask = _focusTask;
            focusTask->retain();
            focusTask->autorelease();
            _focusTask = NULL;
        }
        std::vector<CSTaskQueueItem>::iterator i = _items.begin();
        while(i != _items.end()){
            CSTaskQueueItem item = *i;
            if(item.task->isKindOfParentTask(parentTask)){
                item.task->release();
                i = _items.erase(i);
            }
            else{
                i++;
            }
        }
        return focusTask;
    }
    
    CSTask * CSTaskQueue::removeForParentTaskType(HCPP::Class * parentTaskType){
        CSTask * focusTask = NULL;
        if(_focusTask &&  _focusTask->isKindOfParentTaskType(parentTaskType)){
            focusTask = _focusTask;
            focusTask->retain();
            focusTask->autorelease();
            _focusTask = NULL;
        }
        std::vector<CSTaskQueueItem>::iterator i = _items.begin();
        while(i != _items.end()){
            CSTaskQueueItem item = *i;
            if(item.task->isKindOfParentTaskType(parentTaskType)){
                item.task->release();
                i = _items.erase(i);
            }
            else{
                i++;
            }
        }
        return focusTask;
    }
    
    CSTask * CSTaskQueue::removeAllTask(){
        CSTask * focusTask = NULL;
        if(_focusTask){
            focusTask = _focusTask;
            focusTask->retain();
            focusTask->autorelease();
            _focusTask = NULL;
        }
        std::vector<CSTaskQueueItem>::iterator i = _items.begin();
        while(i != _items.end()){
            CSTaskQueueItem item = *i;
            item.task->release();
            i = _items.erase(i);
        }
        return focusTask;
    }
    
    int CSTaskQueue::count(){
        return _items.size();
    }
    
}

