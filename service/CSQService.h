//
//  CSQService.h
//  hcppservice
//
//  Created by zhang hailong on 12-12-26.
//  Copyright (c) 2012年 9vteam. All rights reserved.
//

#ifndef __hcppservice__CSQService__
#define __hcppservice__CSQService__

#include "CSService.h"
#include "CSTaskQueue.h"
#include "Dictionary.h"


namespace CS {
    
    class CSQService : public CSService{
    public:
        
        CSQService(void);
        
        virtual ~CSQService(void);
        
        virtual CSTaskQueue * taskQueue(HCPP::Class * taskType,bool allowCreate);
        
        virtual bool isDisplaced();
        
        virtual void didCancelHandleTask(HCPP::Class * taskType,CSTask * task);
        
        virtual void didNeedHandleTask(HCPP::Class * taskType,CSTask * focusTask);
        
        virtual bool handle(HCPP::Class * taskType,CSTask * task,int priority);
        
        virtual bool cancelHandle(HCPP::Class * taskType,CSTask * task);
        
        virtual bool cancelHandle(HCPP::Class * taskType);
        
        virtual bool cancelHandleForParentTask(HCPP::Class * taskType,CSTask * parentTask);
        
        virtual bool cancelHandleForParentTaskType(HCPP::Class * taskType,HCPP::Class * parentTaskType);
        
        virtual void removeFocusTask(HCPP::Class * taskType,CSTask * task);
        
        DEC_CLASS
    private:
        HCPP::Dictionary * _taskQueues;
    };
}

#endif /* defined(__hcppservice__CSQService__) */
