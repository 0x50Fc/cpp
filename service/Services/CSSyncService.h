//
//  CSSyncService.h
//  hcppservice
//
//  Created by zhang hailong on 13-1-25.
//  Copyright (c) 2013年 9vteam. All rights reserved.
//

#ifndef __hcppservice__CSSyncService__
#define __hcppservice__CSSyncService__

#include "CSQService.h"
#include "CSHttpTask.h"

namespace CS {
    
    class CSSyncService : public CSQService{
    public:
        
        CSSyncService(void);
        
        virtual ~CSSyncService(void);
        
        virtual void didCancelHandleTask(HCPP::Class * taskType,CSTask * task);
        
        virtual void didNeedHandleTask(HCPP::Class * taskType,CSTask * focusTask);
        
        virtual void onHttpTaskDidFail(CSContext * context,CSHttpTask * httpTask,int errorCode,const char * error);
        
        virtual void onHttpTaskDidFinishLoading(CSContext * context,CSHttpTask * httpTask);
        
        virtual bool handle(HCPP::Class * taskType,CSTask * task,int priority);
        
        DEC_CLASS
    private:
        
    };
}

#endif /* defined(__hcppservice__CSSyncService__) */
