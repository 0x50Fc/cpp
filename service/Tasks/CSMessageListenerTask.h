//
//  CSMessageListenerTask.h
//  hcppservice
//
//  Created by zhang hailong on 13-2-5.
//  Copyright (c) 2013年 9vteam. All rights reserved.
//

#ifndef __hcppservice__CSMessageListenerTask__
#define __hcppservice__CSMessageListenerTask__

#include "CSMessageTask.h"

namespace CS {
    
    class CSMessageListenerTask;
    class CSContext;
    
    typedef void (HCPP::Object::* CSMessageListenerTaskDelegateOnMessageFun)(CSContext * context, CSMessageListenerTask * listener,CSMessageTask * task,HCPP::Class * taskType);
    
    struct CSMessageListenerTaskDelegate{
        HCPP::Object * target;
        CSMessageListenerTaskDelegateOnMessageFun onMessage;
    };
    
    class CSMessageListenerTask : public CSTask{
    public:
        
        CSMessageListenerTask(void);
        
        CSMessageListenerTask(HCPP::Class * taskType,bool inherit,HCPP::Object * target,CSMessageListenerTaskDelegateOnMessageFun onMessage);
        
        virtual ~CSMessageListenerTask(void);
        
        virtual CSMessageListenerTaskDelegate delegate();
        
        virtual void setDelegate(CSMessageListenerTaskDelegate delegate);
        
        virtual HCPP::Class * taskType();
        
        virtual void setTaskType(HCPP::Class * taskType);
        
        virtual bool isInherit();
        
        virtual void setInherit(bool inherit);
        
        virtual void onMessage(CSContext * context,CSMessageTask * task,HCPP::Class * taskType);
        
        static CSMessageListenerTask * newMessageListenerTask(HCPP::Class * taskType,bool inherit,HCPP::Object * target,CSMessageListenerTaskDelegateOnMessageFun onMessage);
        
        DEC_CLASS
        
    private:
        CSMessageListenerTaskDelegate _delegate;
        HCPP::Class * _taskType;
        bool _inherit;
    };
}

#endif /* defined(__hcppservice__CSMessageListenerTask__) */
