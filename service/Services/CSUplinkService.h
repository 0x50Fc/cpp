//
//  CSUplinkService.h
//  hcppservice
//
//  Created by zhang hailong on 12-12-26.
//  Copyright (c) 2012年 9vteam. All rights reserved.
//

#ifndef __hcppservice__CSUplinkService__
#define __hcppservice__CSUplinkService__

#include "CSService.h"
#include "CSUplinkTask.h"

namespace CS {
    
    class CSUplinkService : public CSService{
    public:
        
        CSUplinkService(void);
        
        virtual ~CSUplinkService(void);
        
        virtual void uplinkTaskDidFinish(CSUplinkTask * task,HCPP::Class * taskType,Object * data);
        
        virtual void uplinkTaskDidFail(CSUplinkTask * task,HCPP::Class * taskType,int errorCode,const char * error);
        
        DEC_CLASS
        
    };
}

#endif /* defined(__hcppservice__CSUplinkService__) */
