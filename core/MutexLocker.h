//
//  MutexLocker.h
//  hcpp
//
//  Created by zhang hailong on 13-1-24.
//  Copyright (c) 2013年 hailong.org. All rights reserved.
//

#ifndef __hcpp__MutexLocker__
#define __hcpp__MutexLocker__

#include "Locker.h"

struct _mutex_t;

namespace HCPP {
    
    class MutexLocker : public Locker{
    public:
        
        MutexLocker(void);
        
        virtual ~MutexLocker(void);
        
        virtual void lock();
        
        virtual void unlock();
        
        DEC_CLASS
        
    private:
        struct _mutex_t * _mutex;
    };
}

#endif /* defined(__hcpp__MutexLocker__) */
