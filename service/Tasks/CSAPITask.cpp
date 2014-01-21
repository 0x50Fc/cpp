//
//  CSAPITask.cpp
//  hcppservice
//
//  Created by zhang hailong on 12-12-26.
//  Copyright (c) 2012年 9vteam. All rights reserved.
//
#include "hconfig.h"
#include "CSAPITask.h"

namespace CS {
    
    IMP_CLASS(CSAPITask, CSHttpTask)
    
    CSAPITask::CSAPITask(void){
        setResponseType(CSHttpTaskResponseTypeJSON);
    }
    
    CSAPITask::~CSAPITask(void){
        
    }
}
