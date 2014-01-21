//
//  CSService.h
//  hcppservice
//
//  Created by zhang hailong on 12-12-20.
//  Copyright (c) 2012年 9vteam. All rights reserved.
//

#ifndef __hcppservice__CSService__
#define __hcppservice__CSService__

#include "CS.h"
#include "CSTask.h"
#include "CSContext.h"

namespace CS {
    
    class CSService : public HCPP::Object{
        
    public:
        
        CSService(void);
        
        virtual ~CSService(void);
        
        virtual HCPP::Object * config();
        
        virtual void setConfig(HCPP::Object * config);
        
        virtual bool isDisplaced();
        
        virtual bool handle(HCPP::Class * taskType,CSTask * task,int priority);
        
        virtual bool cancelHandle(HCPP::Class * taskType,CSTask * task);
        
        virtual bool cancelHandle(HCPP::Class * taskType);
        
        virtual bool cancelHandleForParentTask(HCPP::Class * taskType,CSTask * parentTask);
        
        virtual bool cancelHandleForParentTaskType(HCPP::Class * taskType,HCPP::Class * parentTaskType);
        
        virtual void didReceiveMemoryWarning();
        
        virtual CSContext * context();
        
        virtual void setContext(CSContext * context);
        
        DEC_CLASS
    private:
        HCPP::Object * _config;
        CSContext * _context;
    };
    
}

#endif /* defined(__hcppservice__CSService__) */
