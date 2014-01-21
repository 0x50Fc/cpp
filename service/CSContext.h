//
//  CSContext.h
//  hcppservice
//
//  Created by zhang hailong on 12-12-20.
//  Copyright (c) 2012年 9vteam. All rights reserved.
//

#ifndef __hcppservice__CSContext__
#define __hcppservice__CSContext__

#include "CS.h"
#include "Context.h"
#include "CSTask.h"
#include "Bundle.h"

#include <string>

namespace CS {
    
    
    enum CSDeviceType{
        CSDeviceTypeNone=0,CSDeviceTypeIOS = 1,CSDeviceTypeAndroid = 2,CSDeviceTypeWindow = 3
    };
    
    class CSCache;
    
    class CSContext: public HCPP::Context{
      
    public:
        
        CSContext(void);
        
        virtual ~CSContext(void);
        
        virtual bool handle(HCPP::Class * taskType,CSTask * task,int priority);
        
        virtual bool cancelHandle(HCPP::Class * taskType,CSTask * task);
        
        virtual bool cancelHandle(HCPP::Class * taskType);
        
        virtual bool cancelHandleForParentTask(HCPP::Class * taskType,CSTask * parentTask);
        
        virtual bool cancelHandleForParentTaskType(HCPP::Class * taskType,HCPP::Class * parentTaskType);
        
        virtual void didReceiveMemoryWarning();
        
        virtual const char * tempDir();
        
        virtual const char * documentDir();
        
        virtual const char * resourceDir();
        
        virtual const char * deviceId();
        
        virtual const char * deviceName();
        
        virtual const char * deviceOS();
        
        virtual const char * deviceOSVersion();
        
        virtual const char * deviceModel();
        
        virtual CSDeviceType deviceType();
        
        virtual long long uid();
        
        virtual const char * uidStr();
        
        virtual bool setUid(long long uid);
        
        virtual bool setUid(const char * uid);
        
        virtual CSCache * appCache();
        
        virtual CSCache * userCache();
        
        virtual HCPP::Bundle * bundle();
        
        DEC_CLASS
        
    private:
        CSCache * _appCache;
        CSCache * _userCache;
    };

}

#endif /* defined(__hcppservice__CSContext__) */
