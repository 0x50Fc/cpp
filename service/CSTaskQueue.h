//
//  CSTaskQueue.h
//  hcppservice
//
//  Created by zhang hailong on 12-12-26.
//  Copyright (c) 2012年 9vteam. All rights reserved.
//

#ifndef __hcppservice__CSTaskQueue__
#define __hcppservice__CSTaskQueue__


#include "CSTask.h"

#include <vector>

namespace CS {
    
    struct CSTaskQueueItem{
        CSTask * task;
        int priority;
    };
    
    class CSTaskQueue : public HCPP::Object{
        
    public:
        
        CSTaskQueue(void);
        
        virtual ~CSTaskQueue(void);
        
        virtual CSTask * focusTask();
        
        virtual bool hasFocusTask();
        
        virtual void removeFocusTask();
        
        virtual void joinTask(CSTask * task,int priority);
        
        virtual CSTask * remove(HCPP::Class * taskType,bool inherit);
        
        virtual CSTask * remove(CSTask * task);
        
        virtual CSTask * removeForParentTask(CSTask * parentTask);
        
        virtual CSTask * removeForParentTaskType(HCPP::Class * parentTaskType);
        
        virtual CSTask * removeAllTask();
        
        virtual int count();
        
        DEC_CLASS
    private:
        std::vector<CSTaskQueueItem> _items;
        CSTask * _focusTask;
    };
}
#endif /* defined(__hcppservice__CSTaskQueue__) */
