//
//  CSDownlinkTask.cpp
//  hcppservice
//
//  Created by zhang hailong on 12-12-26.
//  Copyright (c) 2012年 9vteam. All rights reserved.
//
#include "hconfig.h"
#include "CSDownlinkTask.h"


namespace CS {
    
    IMP_CLASS(CSDownlinkTask, CSSyncTask)
    
    CSDownlinkTask::CSDownlinkTask(void){
        
    }
    
    CSDownlinkTask::~CSDownlinkTask(void){
        
    }
    
    CSDownlinkTaskDelegate CSDownlinkTask::downlinkDelegate(){
        return _delegate;
    }
    
    void CSDownlinkTask::setDownlinkDelegate(CSDownlinkTaskDelegate delegate){
        _delegate = delegate;
    }

    
}
