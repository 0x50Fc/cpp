//
//  CSSDeviceService.h
//  hcppservice
//
//  Created by zhang hailong on 13-1-25.
//  Copyright (c) 2013年 9vteam. All rights reserved.
//

#ifndef __hcppservice__CSSDeviceService__
#define __hcppservice__CSSDeviceService__

#include "CSService.h"

namespace CS {
    
    class CSSDeviceService : public CSService{
    public:
        
        CSSDeviceService(void);
        
        virtual ~CSSDeviceService(void);
        
        virtual bool handle(HCPP::Class * taskType,CSTask * task,int priority);
        
        DEC_CLASS
    };
}

#endif /* defined(__hcppservice__CSSDeviceService__) */
