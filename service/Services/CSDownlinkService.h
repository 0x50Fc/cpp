//
//  CSDownlinkService.h
//  hcppservice
//
//  Created by zhang hailong on 12-12-26.
//  Copyright (c) 2012年 9vteam. All rights reserved.
//

#ifndef __hcppservice__CSDownlinkService__
#define __hcppservice__CSDownlinkService__

#include "CSDownlinkTask.h"
#include "CSService.h"
#include "CSCache.h"

namespace CS {
    
    class CSDownlinkService : public CSService{
    public:
        
        CSDownlinkService(void);
        
        virtual ~CSDownlinkService(void);
        
        virtual void didReceiveMemoryWarning();
        
        virtual HCPP::Value * cacheValueKey(CSDownlinkTask * task,HCPP::Class * taskType);
        
        virtual void downlinkTaskDidLoadedFormCache(CSDownlinkTask * task,HCPP::Class * taskType);
        
        virtual void downlinkTaskDidLoaded(CSDownlinkTask * task,HCPP::Class * taskType,Object * data,bool allowCache);
        
        virtual void downlinkTaskDidFital(CSDownlinkTask * task,HCPP::Class * taskType,int errorCode,const char * error);
        
        DEC_CLASS
        
    private:
        CSCache * cache();
        CSCache * _cache;
    };
}

#endif /* defined(__hcppservice__CSDownlinkService__) */
