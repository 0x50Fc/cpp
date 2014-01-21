//
//  CSMessageService.h
//  hcppservice
//
//  Created by zhang hailong on 13-2-5.
//  Copyright (c) 2013年 9vteam. All rights reserved.
//

#ifndef __hcppservice__CSMessageService__
#define __hcppservice__CSMessageService__

#include "CSService.h"
#include "Array.h"

namespace CS {
    
    class CSMessageService : public CSService{
    public:
        
        CSMessageService(void);
        
        virtual ~CSMessageService(void);
        
        virtual bool handle(HCPP::Class * taskType,CSTask * task,int priority);
        
        virtual bool cancelHandle(HCPP::Class * taskType,CSTask * task);
        
        virtual bool cancelHandle(HCPP::Class * taskType);
        
        virtual bool cancelHandleForParentTask(HCPP::Class * taskType,CSTask * parentTask);
        
        virtual bool cancelHandleForParentTaskType(HCPP::Class * taskType,HCPP::Class * parentTaskType);
        
        DEC_CLASS
    private:
        HCPP::Array * _listeners;
    };
}
#endif /* defined(__hcppservice__CSMessageService__) */
