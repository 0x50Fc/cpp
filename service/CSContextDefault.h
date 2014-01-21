//
//  CSContextDefault.h
//  hcppservice
//
//  Created by zhang hailong on 12-12-20.
//  Copyright (c) 2012年 9vteam. All rights reserved.
//

#ifndef __hcppservice__CSContextDefault__
#define __hcppservice__CSContextDefault__

#include "CSContext.h"
#include "Array.h"
#include "CSContainer.h"

#include <string>

namespace CS {
    
    
    class CSContextDefault: public CSContext{
      
    public:
        
        CSContextDefault(void);
        
        virtual ~CSContextDefault(void);
        
        virtual bool handle(HCPP::Class * taskType,CSTask * task,int priority);
        
        virtual bool cancelHandle(HCPP::Class * taskType,CSTask * task);
        
        virtual bool cancelHandle(HCPP::Class * taskType);
        
        virtual bool cancelHandleForParentTask(HCPP::Class * taskType,CSTask * parentTask);
        
        virtual bool cancelHandleForParentTaskType(HCPP::Class * taskType,HCPP::Class * parentTaskType);
        
        virtual CSContainer * addService(HCPP::Class * serviceClass);
        
        virtual const char * tempDir();
        
        virtual const char * documentDir();
        
        virtual const char * resourceDir();

        virtual void setTempDir(const char * tempDir);
        
        virtual void setDocumentDir(const char * documentDir);
        
        virtual void setResourceDir(const char * resourceDir);
        
        virtual void didReceiveMemoryWarning();
        
        virtual void setConfig(Object * config);
        
        virtual const char * deviceId();
        
        virtual void setDeviceId(const char * deviceId);
        
        virtual const char * deviceName();
        
        virtual void setDeviceName(const char * deviceName);
        
        virtual const char * deviceOS();
        
        virtual void setDeviceOS(const char * deviceOS);
        
        virtual const char * deviceOSVersion();
        
        virtual void setDeviceOSVerstion(const char * deviceOSVersion);
        
        virtual const char * deviceModel();
        
        virtual void setDeviceModel(const char * deviceModel);
        
        virtual CSDeviceType deviceType();
        
        virtual void setDeviceType(CSDeviceType deviceType);
        
        virtual HCPP::Bundle * bundle();
        
        virtual void setBundle(HCPP::Bundle * bundle);
        
        DEC_CLASS
        
    private:
        HCPP::Array _containers;
        std::string _tempDir;
        std::string _documentDir;
        std::string _resourceDir;
        std::string _deviceId;
        std::string _deviceName;
        std::string _deviceOS;
        std::string _deviceOSVersion;
        std::string _deviceModel;
        CSDeviceType _deviceType;
        HCPP::Bundle * _bundle;
    };
}

#endif /* defined(__hcppservice__CSContextDefault__) */
