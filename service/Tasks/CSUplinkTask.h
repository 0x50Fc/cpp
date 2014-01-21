//
//  CSUplinkTask.h
//  hcppservice
//
//  Created by zhang hailong on 12-12-26.
//  Copyright (c) 2012年 9vteam. All rights reserved.
//

#ifndef __hcppservice__CSUplinkTask__
#define __hcppservice__CSUplinkTask__

#include "CSSyncTask.h"
#include "CSContext.h"

namespace CS {
    
    class CSUplinkTask;
    
    typedef void (HCPP::Object:: * CSUplinkTaskDelegateDidFinishFun)(CSContext * context,CSUplinkTask * task,HCPP::Object * data,HCPP::Class * taskType);
    typedef void (HCPP::Object:: * CSUplinkTaskDelegateDidFailFun)(CSContext * context,CSUplinkTask * task,int errorCode,const char * error,HCPP::Class * taskType);
    
    struct CSUplinkTaskDelegate{
        HCPP::Object * target;
        CSUplinkTaskDelegateDidFinishFun didFinish;
        CSUplinkTaskDelegateDidFailFun didFail;
    };
    
    class CSUplinkTask : public CSSyncTask{
      
    public:
        CSUplinkTask(void);
        
        virtual ~CSUplinkTask(void);
        
        virtual CSUplinkTaskDelegate uplinkDelegate();
        
        virtual void setUplinkDelegate(CSUplinkTaskDelegate delegate);
        
        DEC_CLASS
        
    private:
        CSUplinkTaskDelegate _delegate;
        
    };
}

#endif /* defined(__hcppservice__CSUplinkTask__) */
