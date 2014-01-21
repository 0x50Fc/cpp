//
//  CSDownlinkPageTask.cpp
//  hcppservice
//
//  Created by zhang hailong on 12-12-26.
//  Copyright (c) 2012年 9vteam. All rights reserved.
//
#include "hconfig.h"
#include "CSDownlinkPageTask.h"


namespace CS {
    
    IMP_CLASS(CSDownlinkPageTask, CSDownlinkTask)
    
    CSDownlinkPageTask::CSDownlinkPageTask(void){
        _pageSize = 20;
        _pageIndex = 1;
        _minId = 0;
        _maxId = 0;
    }
    
    CSDownlinkPageTask::~CSDownlinkPageTask(void){
        
    }
    
    int CSDownlinkPageTask::pageSize(){
        return _pageSize;
    }
    
    void CSDownlinkPageTask::setPageSize(int pageSize){
        _pageSize = pageSize;
    }
    
    int CSDownlinkPageTask::pageIndex(){
        return _pageIndex;
    }
    
    void CSDownlinkPageTask::setPageIndex(int pageIndex){
        _pageIndex = pageIndex;
    }
    
    long long CSDownlinkPageTask::maxId(){
        return _maxId;
    }
    
    void CSDownlinkPageTask::setMaxId(long long maxId){
        _maxId = maxId;
    }
    
    long long CSDownlinkPageTask::minId(){
        return _minId;
    }
    
    void CSDownlinkPageTask::setMinId(long long minId){
        _minId = minId;
    }
    
}