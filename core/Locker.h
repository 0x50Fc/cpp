//
//  Locker.h
//  hcpp
//
//  Created by zhang hailong on 13-1-24.
//  Copyright (c) 2013年 hailong.org. All rights reserved.
//

#ifndef __hcpp__Locker__
#define __hcpp__Locker__

#include "Object.h"

namespace HCPP {
    
    class Locker : public Object{
    public:
        
        Locker(void);
        
        virtual ~Locker(void);
        
        virtual void lock();
        
        virtual void unlock();
        
        DEC_CLASS
          
    };
}

#endif /* defined(__hcpp__Locker__) */
