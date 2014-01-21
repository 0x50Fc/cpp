//
//  CSResourceTask.cpp
//  hcppservice
//
//  Created by zhang hailong on 12-12-26.
//  Copyright (c) 2012年 9vteam. All rights reserved.
//

#include "hconfig.h"
#include "CSResourceTask.h"

#include "hbuffer.h"
#include "hfile.h"

#include "htime.h"
#include "hfile.h"

using namespace HCPP;

namespace CS {
    
    
    IMP_CLASS(CSResourceTask, CSHttpTask)
    
    CSResourceTask::CSResourceTask(void){
        _checkContentLength = true;
        _resourceDelegate.target = NULL;
        _resourceDelegate.progressRate = NULL;
        _resourceDelegate.localFilePath = NULL;
        _downloadLength = 0;
        _contentLength = 0;
        _checkkLastModified = false;
        _lastModified = 0;
        _statusCode = 0;
    }
    
    CSResourceTask::~CSResourceTask(void){
        
    }

    bool CSResourceTask::isCheckContentLength(){
        return _checkContentLength;
    }
    
    void CSResourceTask::setCheckContentLength(bool checkContentLength){
        _checkContentLength = checkContentLength;
    }
    
    static void CSResourceTaskURLToLocalFilePath(CSContext * context,const char * url,hbuffer_t buf,InvokeTickDeclare){
        buffer_append_str(buf, context->tempDir());
        buffer_append_md5_str(buf, url);
    }
    
    void CSResourceTask::onWillRequest(CSContext * context){
        CSHttpTask::onWillRequest(context);
        
        InvokeTickBegin
        
        Value * v = url();
        hbuffer_t buf = buffer_alloc(MAX_PATH, 128);
        
        if(v){
            CSResourceTaskURLToLocalFilePath(context,v->stringValue(),buf,InvokeTickArg);
            
            if(isCheckLastModified() && file_exist(buffer_to_str(buf))){
                time_t time = file_last_modified_get(buffer_to_str(buf));
                char buf[128];
                
                time_to_gmt_str(&time, buf, sizeof(buf));
                
                setHeader("If-Modified-Since", buf);
            }
            
            buffer_append_str(buf, ".t");
            _tmpFile = buffer_to_str(buf);
            
            file_delete(_tmpFile.c_str());
        }
        else{
            _tmpFile = "";
        }
        
        buffer_dealloc(buf);
    }
    
    CSResourceTaskDelegate CSResourceTask::resourceDelegate(){
        return _resourceDelegate;
    }
    
    void CSResourceTask::setResourceDelegate(CSResourceTaskDelegate delegate){
        _resourceDelegate = delegate;
    }

    void CSResourceTask::onDidBackgroundReceiveData(CSContext * context,void * data,int length){
    
        FILE * f = NULL;
        
        if(_downloadLength ==0){
            f = fopen(_tmpFile.c_str(), "w");
        }
        else{
            f = fopen(_tmpFile.c_str(), "a");
        }

        if(f){
            
            fwrite(data, 1, length, f);
            
            fclose(f);
        }
        
        _downloadLength += length;
        
        CSHttpTask::onDidBackgroundReceiveData(context, data, length);
    }
    
    void CSResourceTask::onDidReceiveData(CSContext * context,void * data,int length){
        
        if(_resourceDelegate.target && _resourceDelegate.progressRate){
            (_resourceDelegate.target->*_resourceDelegate.progressRate)(context,this,_downloadLength,_contentLength);
        }
        
        CSHttpTask::onDidReceiveData(context, data, length);
    }
    
    void CSResourceTask::onDidBackgroundReceiveResponse(CSContext * context,int statusCode,const char * status,Dictionary * headers){
        
        Value * v = (Value *) headers->objectForKey("Content-Length");
        
        if(v){
            _contentLength = v->intValue();
        }
        
        v = (Value *) headers->objectForKeyPath("Last-Modified");
        
        if(v){
            _lastModified = gmt_parse(v->stringValue());
        }
        
        _statusCode = statusCode;
        
        CSHttpTask::onDidBackgroundReceiveResponse(context, statusCode, status, headers);
    }
    
    void CSResourceTask::onDidFinishLoading(CSContext * context){
        
        if(_statusCode == 200){
            if(!_checkContentLength || (_contentLength == 0 || _downloadLength == _contentLength)){
                InvokeTickBegin
                
                Value * v = url();
                
                hbuffer_t buf = buffer_alloc(MAX_PATH, 128);
                
                if(v){
                    CSResourceTaskURLToLocalFilePath(context,v->stringValue(),buf,InvokeTickArg);
                }
                
                file_rename(_tmpFile.c_str(), buffer_to_str(buf));
                
                if(_lastModified){
                    file_last_modified_set(buffer_to_str(buf), _lastModified);
                }
                
                if(_resourceDelegate.target && _resourceDelegate.localFilePath){
                    (_resourceDelegate.target->*_resourceDelegate.localFilePath)(context,this,buffer_to_str(buf));
                }
                
                buffer_dealloc(buf);
            }
            else{
                file_delete(_tmpFile.c_str());
            }
        }
        else if(_statusCode == 304){
            
            InvokeTickBegin
            Value * v = url();
            
            hbuffer_t buf = buffer_alloc(MAX_PATH, 128);
            
            if(v){
                CSResourceTaskURLToLocalFilePath(context,v->stringValue(),buf,InvokeTickArg);
            }
           
            if(_resourceDelegate.target && _resourceDelegate.localFilePath){
                (_resourceDelegate.target->*_resourceDelegate.localFilePath)(context,this,buffer_to_str(buf));
            }
            
            buffer_dealloc(buf);
        }
        
        CSHttpTask::onDidFinishLoading(context);
    }
    
    void CSResourceTask::onDidFail(CSContext * context,int errorCode,const char * error){
        
        if(_resourceDelegate.target && _resourceDelegate.didFial){
            (_resourceDelegate.target->*_resourceDelegate.didFial)(context,this,errorCode,error);
        }
        
        CSHttpTask::onDidFail(context, errorCode, error);
    }
    
    void CSResourceTask::RemoveLocalResource(CSContext * context,const char * url){
        InvokeTickBegin

        hbuffer_t buf = buffer_alloc(MAX_PATH, 128);

        CSResourceTaskURLToLocalFilePath(context,url,buf,InvokeTickArg);

        file_delete(buffer_to_str(buf));
        
        buffer_dealloc(buf);
    }
    
    void CSResourceTask::MoveToLocaResource(CSContext * context,const char * url,const char * filePath){
        InvokeTickBegin
        
        hbuffer_t buf = buffer_alloc(MAX_PATH, 128);
        
        CSResourceTaskURLToLocalFilePath(context,url,buf,InvokeTickArg);
        
        file_rename(filePath, buffer_to_str(buf));
        
        buffer_dealloc(buf);
    }
    
    void CSResourceTask::WriteLocalResourceData(CSContext * context,const char * url,void * data,int length){
        InvokeTickBegin
        
        hbuffer_t buf = buffer_alloc(MAX_PATH, 128);
        
        CSResourceTaskURLToLocalFilePath(context,url,buf,InvokeTickArg);
        
        FILE * f = fopen(buffer_to_str(buf), "w");
        
        if(f){
            fwrite(data, 1, length, f);
            fclose(f);
        }
        
        buffer_dealloc(buf);
    }
    
    Value * CSResourceTask::LocalResourcePath(CSContext * context,const char * url){
        InvokeTickBegin
        
        hbuffer_t buf = buffer_alloc(MAX_PATH, 128);
        
        CSResourceTaskURLToLocalFilePath(context,url,buf,InvokeTickArg);

        Value * v = new Value(buffer_to_str(buf));
        
        buffer_dealloc(buf);

        return (Value *)v->autorelease();
    }
    
    bool CSResourceTask::isCheckLastModified(){
        return _checkkLastModified;
    }
    
    void CSResourceTask::setCheckListModifed(bool checkkLastModified){
        _checkkLastModified = checkkLastModified;
    }
    
}

