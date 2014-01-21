//
//  CSTask.h
//  hcppservice
//
//  Created by zhang hailong on 12-12-20.
//  Copyright (c) 2012年 9vteam. All rights reserved.
//

#ifndef __hcppservice__CSTask__
#define __hcppservice__CSTask__

#include "CS.h"

namespace CS {
    
    class CSTask : public HCPP::Object{
      
    public:
        
        CSTask(void);
        
        virtual ~CSTask(void);
        
        virtual HCPP::Class * parentTaskType();
        
        virtual CSTask * parentTask();
        
        virtual void setParent(CSTask * task,HCPP::Class * taskType);
        
        virtual bool isKindOfParentTask(CSTask * parentTask);
        
        virtual bool isKindOfParentTaskType(HCPP::Class * parentTaskType);
        
        virtual Object * userInfo();
        
        virtual void setUserInfo(Object * userInfo);
        
        DEC_CLASS
        
    private:
        CSTask * _parentTask;
        HCPP::Class * _parentTaskType;
        Object * _userInfo;
    };
}

#endif /* defined(__hcppservice__CSTask__) */
