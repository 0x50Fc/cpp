//
//  CSHttpTask.h
//  hcppservice
//
//  Created by zhang hailong on 12-12-25.
//  Copyright (c) 2012年 9vteam. All rights reserved.
//

#ifndef __hcppservice__CSHttpTask__
#define __hcppservice__CSHttpTask__

#include "CSTask.h"
#include "Value.h"
#include "Dictionary.h"
#include "CSContext.h"

#include <string>
#include <map>
#include <vector>

struct _buffer_t;

namespace CS {
    
    struct CSHttpTaskItem{
        std::string name;
        std::string value;
    };
    
    struct CSHttpTaskItemFile{
        std::string name;
        std::string contentType;
        std::string filePath;
    };
    
    struct CSHttpTaskItemFileData{
        std::string name;
        std::string contentType;
        char * data;
        int length;
    };
    
    enum CSHttpTaskItemType{
        CSHttpTaskItemTypeParam,CSHttpTaskItemTypePostData,CSHttpTaskItemTypePostFile,CSHttpTaskItemTypePostFileData
    };
    
    enum CSHttpTaskEncodeType{
        CSHttpTaskEncodeTypeNone,CSHttpTaskEncodeTypeMcrypt
    };
    
    struct CSHttpTaskItemKey{
        CSHttpTaskItemType type;
        void * ptr;
    };

    class CSHttpTask;
    
    typedef void (HCPP::Object:: * CSHttpTaskDelegateWillRequestFun)(CSContext * context, CSHttpTask * httpTask);
    typedef void (HCPP::Object:: * CSHttpTaskDelegateDidFailFun)(CSContext * context,CSHttpTask * httpTask,int errorCode,const char * error);
    typedef void (HCPP::Object:: * CSHttpTaskDelegateDidFinishLoadingFun)(CSContext * context,CSHttpTask * httpTask);
    typedef void (HCPP::Object:: * CSHttpTaskDelegateDidReceiveResponseFun)(CSContext * context,CSHttpTask * httpTask,int statusCode,const char * status,HCPP::Dictionary * headers);
    typedef void (HCPP::Object:: * CSHttpTaskDelegateDidReceiveDataFun)(CSContext * context,CSHttpTask * httpTask,void * data,int length);
    typedef void (HCPP::Object:: * CSHttpTaskDelegateDidSendBodyDataFun)(CSContext * context,CSHttpTask * httpTask,int bytesWritten,int totalBytesWritten);
    
    struct CSHttpTaskDelegate{
        HCPP::Object * target;
        CSHttpTaskDelegateWillRequestFun willRequest;
        CSHttpTaskDelegateDidFailFun didFail;
        CSHttpTaskDelegateDidFinishLoadingFun didFinishLoading;
        CSHttpTaskDelegateDidReceiveResponseFun didReceiveResponse;
        CSHttpTaskDelegateDidReceiveDataFun didReceiveData;
        CSHttpTaskDelegateDidSendBodyDataFun didSendBodyData;
        
        CSHttpTaskDelegateDidFinishLoadingFun didBackgroundFinishLoading;
        CSHttpTaskDelegateDidReceiveDataFun didBackgroundReceiveData;
        CSHttpTaskDelegateDidReceiveResponseFun didBackgroundReceiveResponse;
    };
    
    enum CSHttpTaskResponseType{
        CSHttpTaskResponseTypeNone,CSHttpTaskResponseTypeString,CSHttpTaskResponseTypeJSON
    };
    
    class CSHttpTask : public CSTask{
      
    public:
        
        CSHttpTask(void);
        
        virtual ~CSHttpTask(void);
        
        virtual void setBaseUrl(const char * baseUrl);
        
        virtual void removeKey(const char * key);
        
        virtual void addURLParam(const char * name,const char * format,...);
        
        virtual void setURLParam(const char * name,const char * format,...);
        
        virtual void addPostData(const char * name,const char * format,...);
        
        virtual void setPostData(const char * name,const char * format,...);
        
        virtual void addPostFile(const char * name,const char * contentType,const char * filePath,...);
        
        virtual void setPostFile(const char * name,const char * contentType,const char * filePath,...);
        
        virtual void addPostFile(const char * name,const char * contentType,void * data,int length);
        
        virtual void setPostFile(const char * name,const char * contentType,void * data,int length);
        
        virtual const char * contentType();
        
        virtual const char * httpHethod();
        
        virtual CSHttpTaskDelegate httpDelegate();
        
        virtual void setHttpDelegate(CSHttpTaskDelegate delegate);
        
        virtual void onWillRequest(CSContext * context);
        
        virtual void onDidFail(CSContext * context,int errorCode,const char * error);
        
        virtual void onDidFinishLoading(CSContext * context);
        
        virtual void onDidReceiveResponse(CSContext * context,int statusCode,const char * status,HCPP::Dictionary * headers);
        
        virtual void onDidReceiveData(CSContext * context,void * data,int length);
        
        virtual void onDidSendBodyData(CSContext * context,int bytesWritten,int totalBytesWritten);
        
        virtual void onDidBackgroundFinishLoading(CSContext * context);
        
        virtual void onDidBackgroundReceiveData(CSContext * context,void * data,int length);
        
        virtual void onDidBackgroundReceiveResponse(CSContext * context,int statusCode,const char * status,HCPP::Dictionary * headers);
        
        virtual void setHeader(const char * key,const char * value);
        
        virtual const char * getHeader(const char * key);
        
        virtual HCPP::Dictionary * headers();
        
        // string Value
        virtual HCPP::Value * url();
        
        // bytes Value
        virtual HCPP::Value * body();
        
        virtual Object * responseValue();
        
        virtual CSHttpTaskResponseType responseType();
        
        virtual struct _buffer_t * responseBuffer();
        
        virtual CSHttpTaskEncodeType responseEncodeType();
        
        virtual void setResponseType(CSHttpTaskResponseType type);
        
        virtual CSHttpTaskEncodeType encodeType();
        
        virtual void setEncodeType(CSHttpTaskEncodeType encodeType);
        
        DEC_CLASS
        
    private:
        
        void setItem(const char * key,CSHttpTaskItemType type,void * ptr);
        
        CSHttpTaskDelegate _delegate;
        std::string _contentType;
        std::string _httpMethod;
        std::string _baseUrl;
        std::map<std::string,CSHttpTaskItemKey> _itemKeys;
        std::vector<CSHttpTaskItem *> _urlParams;
        std::vector<CSHttpTaskItem *> _postDatas;
        std::vector<CSHttpTaskItemFile *> _postFiles;
        std::vector<CSHttpTaskItemFileData *> _postFileDatas;
        struct {
            CSHttpTaskResponseType type;
            CSHttpTaskEncodeType encodeType;
            struct _buffer_t * buffer;
            Object * value;
        } _response;
        HCPP::Dictionary * _headers;
        CSHttpTaskEncodeType _encodeType;
    };
}

#endif /* defined(__hcppservice__CSHttpTask__) */
