//
//  MutexLocker.cpp
//  hcpp
//
//  Created by zhang hailong on 13-1-24.
//  Copyright (c) 2013年 hailong.org. All rights reserved.
//
#include "hconfig.h"
#include "MutexLocker.h"

#include "hmutex.h"

namespace HCPP {
    
    IMP_CLASS(MutexLocker, Locker)
    
    MutexLocker::MutexLocker(void){
        _mutex = hmutex_alloc();
    }
    
    MutexLocker::~MutexLocker(void){
        hmutex_dealloc(_mutex);
    }
    
    void MutexLocker::lock(){
        hmutex_lock(_mutex);
    }
    
    void MutexLocker::unlock(){
        hmutex_unlock(_mutex);
    }
    
}

