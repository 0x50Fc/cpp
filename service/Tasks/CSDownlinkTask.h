//
//  CSDownlinkTask.h
//  hcppservice
//
//  Created by zhang hailong on 12-12-26.
//  Copyright (c) 2012年 9vteam. All rights reserved.
//

#ifndef __hcppservice__CSDownlinkTask__
#define __hcppservice__CSDownlinkTask__

#include "CSSyncTask.h"
#include "CSContext.h"

namespace CS {
    
    class CSDownlinkTask;
    
    typedef void (HCPP::Object:: * CSDownlinkTaskDelegateDidLoadedFromCacheFun)(CSContext * context,CSDownlinkTask * task,HCPP::Object * data,double timestamp,HCPP::Class * taskType);
    typedef void (HCPP::Object:: * CSDownlinkTaskDelegateDidLoadedFun)(CSContext * context,CSDownlinkTask * task,HCPP::Object * data,HCPP::Class * taskType);
    typedef void (HCPP::Object:: * CSDownlinkTaskDelegateDidFitalFun)(CSContext * context,CSDownlinkTask * task,int errorCode,const char * error,HCPP::Class * taskType);
    
    struct CSDownlinkTaskDelegate{
        HCPP::Object * target;
        CSDownlinkTaskDelegateDidLoadedFromCacheFun didLoadedFromCache;
        CSDownlinkTaskDelegateDidLoadedFun didLoaded;
        CSDownlinkTaskDelegateDidFitalFun didFital;
    };
    
    class CSDownlinkTask : public CSSyncTask{
        
    public:
        
        CSDownlinkTask(void);
    
        virtual ~CSDownlinkTask(void);
        
        virtual CSDownlinkTaskDelegate downlinkDelegate();
        
        virtual void setDownlinkDelegate(CSDownlinkTaskDelegate delegate);
        
        DEC_CLASS
    private:
        CSDownlinkTaskDelegate _delegate;
    };
    
}

#endif /* defined(__hcppservice__CSDownlinkTask__) */
