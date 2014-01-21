//
//  CSUplinkTask.cpp
//  hcppservice
//
//  Created by zhang hailong on 12-12-26.
//  Copyright (c) 2012年 9vteam. All rights reserved.
//
#include "hconfig.h"
#include "CSUplinkTask.h"

namespace CS {

	IMP_CLASS(CSUplinkTask,CSSyncTask)

    CSUplinkTask::CSUplinkTask(void){
        _delegate.target = NULL;
        _delegate.didFinish = NULL;
        _delegate.didFail = NULL;
    }
    
    CSUplinkTask::~CSUplinkTask(void){
        
    }
    
    CSUplinkTaskDelegate CSUplinkTask::uplinkDelegate(){
        return _delegate;
    }
    
    void CSUplinkTask::setUplinkDelegate(CSUplinkTaskDelegate delegate){
        _delegate = delegate;
    }
    
}
