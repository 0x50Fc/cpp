//
//  CSResourceTask.h
//  hcppservice
//
//  Created by zhang hailong on 12-12-26.
//  Copyright (c) 2012年 9vteam. All rights reserved.
//

#ifndef __hcppservice__CSResourceTask__
#define __hcppservice__CSResourceTask__

#include "CSHttpTask.h"
#include "CSContext.h"

namespace CS {
    
    class CSResourceTask;
    
    typedef void  (HCPP::Object:: * CSResourceTaskDelegateProgressRateFun)(CSContext * context, CSResourceTask * httpTask,int downloadLength,int contentLength);
    
    typedef void  (HCPP::Object:: * CSResourceTaskDelegateLocalFilePath)(CSContext * context, CSResourceTask * httpTask,const char * localFilePath);
    
    typedef void  (HCPP::Object:: * CSResourceTaskDelegateDidFialFun)(CSContext * context, CSResourceTask * httpTask,int errorCode,const char * error);
    
    struct CSResourceTaskDelegate{
        HCPP::Object * target;
        CSResourceTaskDelegateProgressRateFun progressRate;
        CSResourceTaskDelegateLocalFilePath localFilePath;
        CSResourceTaskDelegateDidFialFun didFial;
    };

    class CSResourceTask : public CSHttpTask{
    public:
        
        CSResourceTask(void);
        
        virtual ~CSResourceTask(void);
        
        virtual bool isCheckContentLength();
        
        virtual void setCheckContentLength(bool checkContentLength);
        
        virtual bool isCheckLastModified();
        
        virtual void setCheckListModifed(bool checkkLastModified);
        
        virtual void onWillRequest(CSContext * context);
        
        virtual CSResourceTaskDelegate resourceDelegate();
        
        virtual void setResourceDelegate(CSResourceTaskDelegate delegate);
        
        virtual void onDidBackgroundReceiveData(CSContext * context,void * data,int length);
        
        virtual void onDidBackgroundReceiveResponse(CSContext * context,int statusCode,const char * status,HCPP::Dictionary * headers);
        
        virtual void onDidReceiveData(CSContext * context,void * data,int length);
        
        virtual void onDidFinishLoading(CSContext * context);
        
        virtual void onDidFail(CSContext * context,int errorCode,const char * error);
        
        static void RemoveLocalResource(CSContext * context,const char * url);
        
        static void MoveToLocaResource(CSContext * context,const char * url,const char * filePath);
        
        static void WriteLocalResourceData(CSContext * context,const char * url,void * data,int length);
        
        static HCPP::Value * LocalResourcePath(CSContext * context,const char * url);
        
        DEC_CLASS
        
    private:
        CSResourceTaskDelegate _resourceDelegate;
        bool _checkContentLength;
        std::string _tmpFile;
        int _downloadLength;
        int _contentLength;
        long _lastModified;
        bool _checkkLastModified;
        int _statusCode;
    };
}

#endif /* defined(__hcppservice__CSResourceTask__) */
