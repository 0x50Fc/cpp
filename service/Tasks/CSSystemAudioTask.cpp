//
//  CSSystemAudioTask.cpp
//  hcppservice
//
//  Created by zhang hailong on 13-2-6.
//  Copyright (c) 2013年 9vteam. All rights reserved.
//

#include "hconfig.h"
#include "CSSystemAudioTask.h"

namespace CS {
    
    IMP_CLASS(CSSystemAudioTask, CSTask);
    
    CSSystemAudioTask::CSSystemAudioTask(void){
        
    }
    
    CSSystemAudioTask::~CSSystemAudioTask(void){
        
    }
    
    const char * CSSystemAudioTask::audioKey(){
        return _audioKey.c_str();
    }
    
    void CSSystemAudioTask::setAudioKey(const char * audioKey){
        _audioKey = audioKey;
    }
    
}