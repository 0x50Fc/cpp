//
//  CSHttpTask.cpp
//  hcppservice
//
//  Created by zhang hailong on 12-12-25.
//  Copyright (c) 2012年 9vteam. All rights reserved.
//

#include "hconfig.h"
#include "CSHttpTask.h"
#include "hbuffer.h"
#include "hstr.h"
#include "hfile.h"

#include "Coder.h"
#include "hlog.h"


using namespace HCPP;

namespace CS {

#define HTTP_MULTIPART_TOKEN    "8jej23fkdxxd"
    
    IMP_CLASS(CSHttpTask, CSTask)
    
    CSHttpTask::CSHttpTask(void){
        memset(&_delegate, 0, sizeof(_delegate));
        _response.type = CSHttpTaskResponseTypeNone;
        _encodeType = CSHttpTaskEncodeTypeNone;
        _response.buffer = NULL;
        _response.value = NULL;
        _response.encodeType = CSHttpTaskEncodeTypeNone;
        _headers = NULL;
    }
    
    CSHttpTask::~CSHttpTask(void){
        InvokeTickBegin
        
        {
            std::vector<CSHttpTaskItem *>::iterator i = _urlParams.begin();
            while(i != _urlParams.end()){
                delete * i;
                i++;
            }
        }
        
        
        {
            std::vector<CSHttpTaskItem *>::iterator i = _postDatas.begin();
            while(i != _postDatas.end()){
                delete * i;
                i++;
            }
        }
        
        {
            std::vector<CSHttpTaskItemFile *>::iterator i = _postFiles.begin();
            while(i != _postFiles.end()){
                delete * i;
                i++;
            }
        }
        
        {
            std::vector<CSHttpTaskItemFileData *>::iterator i = _postFileDatas.begin();
            while(i != _postFileDatas.end()){
                delete [] (* i)->data;
                delete * i;
                i++;
            }
        }

        if(_response.buffer){
            buffer_dealloc(_response.buffer);
        }
        if(_response.value){
            _response.value->release();
        }
        if(_headers){
            _headers->release();
        }
    }
    
    void CSHttpTask::setBaseUrl(const char * baseUrl){
        _baseUrl = std::string(baseUrl);
    }
    
    void CSHttpTask::removeKey(const char * key){
        std::string sKey(key);
        std::map<std::string,CSHttpTaskItemKey>::iterator iter = _itemKeys.find(sKey);
        if(iter != _itemKeys.end()){
            CSHttpTaskItemKey * itemKey = &iter->second;
            switch (itemKey->type) {
                case CSHttpTaskItemTypeParam:
                {
                    std::vector<CSHttpTaskItem *>::iterator i = _urlParams.begin();
                    while(i != _urlParams.end()){
                        if(itemKey->ptr == * i){
                            i = _urlParams.erase(i);
                        }
                        else{
                            i++;
                        }
                    }
                }
                    break;
                case CSHttpTaskItemTypePostData:
                {
                    std::vector<CSHttpTaskItem *>::iterator i = _postDatas.begin();
                    while(i != _postDatas.end()){
                        if(itemKey->ptr == * i){
                            delete * i;
                            i = _postDatas.erase(i);
                        }
                        else{
                            i++;
                        }
                    }
                }
                    break;
                case CSHttpTaskItemTypePostFile:
                {
                    std::vector<CSHttpTaskItemFile *>::iterator i = _postFiles.begin();
                    while(i != _postFiles.end()){
                        if(itemKey->ptr == * i){
                            delete *i;
                            i = _postFiles.erase(i);
                        }
                        else{
                            i++;
                        }
                    }
                }
                    break;
                case CSHttpTaskItemTypePostFileData:
                {
                    std::vector<CSHttpTaskItemFileData *>::iterator i = _postFileDatas.begin();
                    while(i != _postFileDatas.end()){
                        if(itemKey->ptr == * i){
                            delete [] (* i)->data;
                            delete *i;
                            i = _postFileDatas.erase(i);
                        }
                        else{
                            i++;
                        }
                    }
                }
                    break;
                default:
                    break;
            }
        }
    }
    
    void CSHttpTask::setItem(const char * key,CSHttpTaskItemType type,void * ptr){
        CSHttpTaskItemKey itemKey = {type,ptr};
        _itemKeys[std::string(key)] = itemKey;
    }
    
    void CSHttpTask::addURLParam(const char * name,const char * format,...){
        InvokeTickBegin
        hbuffer_t v = buffer_alloc(128, 128);
        CSHttpTaskItem * i = new CSHttpTaskItem();
        va_list va;
        
        va_start(va, format);
        
        buffer_append_format_va_list(v, format, va);
        
        va_end(va);
        
        i->name = std::string(name);
        i->value = std::string(buffer_to_str(v));
        
        _urlParams.insert(_urlParams.end(), i);
        
        buffer_dealloc(v);
    }
    
    void CSHttpTask::setURLParam(const char * name,const char * format,...){
        InvokeTickBegin
        hbuffer_t v = buffer_alloc(128, 128);
        CSHttpTaskItem * i = new CSHttpTaskItem();
        va_list va;
        
        va_start(va, format);
        
        buffer_append_format_va_list(v, format, va);
        
        va_end(va);
        
        i->name = std::string(name);
        i->value = std::string(buffer_to_str(v));
        
        removeKey(name);
        setItem(name, CSHttpTaskItemTypeParam, i);
        
        _urlParams.insert(_urlParams.end(), i);
        
        buffer_dealloc(v);
    }
    
    void CSHttpTask::addPostData(const char * name,const char * format,...){
        InvokeTickBegin
        hbuffer_t v = buffer_alloc(128, 128);
        CSHttpTaskItem * i = new CSHttpTaskItem();
        va_list va;
        
        va_start(va, format);
        
        buffer_append_format_va_list(v, format, va);
        
        va_end(va);
        
        i->name = std::string(name);
        i->value = std::string(buffer_to_str(v));
        
        _postDatas.insert(_postDatas.end(), i);
        
        buffer_dealloc(v);

    }
    
    void CSHttpTask::setPostData(const char * name,const char * format,...){
        InvokeTickBegin
        hbuffer_t v = buffer_alloc(128, 128);
        CSHttpTaskItem * i = new CSHttpTaskItem();
        va_list va;
        
        va_start(va, format);
        
        buffer_append_format_va_list(v, format, va);
        
        va_end(va);
        
        i->name = std::string(name);
        i->value = std::string(buffer_to_str(v));
        
        removeKey(name);
        setItem(name, CSHttpTaskItemTypePostData, i);
        
        _postDatas.insert(_postDatas.end(), i);
        
        buffer_dealloc(v);
        
    }
    
    void CSHttpTask::addPostFile(const char * name,const char * contentType,const char * filePath,...){
        InvokeTickBegin
        CSHttpTaskItemFile * i = new CSHttpTaskItemFile();
        hbuffer_t v = buffer_alloc(128, 128);
        va_list va;
        
        va_start(va, filePath);
        
        buffer_append_format_va_list(v, filePath, va);
        
        va_end(va);
        
        i->name = std::string(name);
        i->contentType = std::string(contentType);
        i->filePath = std::string(buffer_to_str(v));

        _postFiles.insert(_postFiles.end(), i);
        
        buffer_dealloc(v);
    }
    
    void CSHttpTask::setPostFile(const char * name,const char * contentType,const char * filePath,...){
        InvokeTickBegin
        CSHttpTaskItemFile * i = new CSHttpTaskItemFile();
        hbuffer_t v = buffer_alloc(128, 128);
        va_list va;
        
        va_start(va, filePath);
        
        buffer_append_format_va_list(v, filePath, va);
        
        va_end(va);
        
        i->name = std::string(name);
        i->contentType = std::string(contentType);
        i->filePath = std::string(buffer_to_str(v));
        
        removeKey(name);
        setItem(name, CSHttpTaskItemTypePostFile, i);
        
        _postFiles.insert(_postFiles.end(), i);
        
        buffer_dealloc(v);
    }
    
    void CSHttpTask::addPostFile(const char * name,const char * contentType,void * data,int length){
        CSHttpTaskItemFileData * i = new CSHttpTaskItemFileData();
        
        i->name = std::string(name);
        i->contentType = std::string(contentType);
        i->data = new char[length];
        i->length = length;
        
        memcpy(i->data, data, length);
        
        _postFileDatas.insert(_postFileDatas.end(), i);
    }
    
    void CSHttpTask::setPostFile(const char * name,const char * contentType,void * data,int length){
        CSHttpTaskItemFileData * i = new CSHttpTaskItemFileData();
        
        i->name = std::string(name);
        i->contentType = std::string(contentType);
        i->data = new char[length];
        i->length = length;
        
        memcpy(i->data, data, length);
        
        removeKey(name);
        setItem(name, CSHttpTaskItemTypePostFileData, i);
        
        _postFileDatas.insert(_postFileDatas.end(), i);
    }
    
    const char * CSHttpTask::contentType(){
               
        if(_postFiles.size() >0 || _postFileDatas.size() >0){
            _contentType = "multipart/form-data; boundary=CSHTTPTask";
            _contentType += HTTP_MULTIPART_TOKEN;
        }
        else if(_postDatas.size() >0){
            if(_encodeType == CSHttpTaskEncodeTypeMcrypt){
                _contentType = "mcrypt";
            }
            else{
                _contentType = "application/x-www-form-urlencoded";
            }
        }
        else{
            _contentType = "html/text";
        }
        return _contentType.c_str();
    }
    
    const char * CSHttpTask::httpHethod(){
        
        if(_postFiles.size() >0 || _postFileDatas.size() >0 || _postDatas.size() >0){
            _httpMethod = "POST";
        }
        else {
            _httpMethod = "GET";
        }
        
        return _httpMethod.c_str();
    }
    
    Value * CSHttpTask::url(){
        InvokeTickBegin
        hbuffer_t buf = buffer_alloc(128, 128);
        Value * v = NULL;
        
        buffer_append_str(buf, _baseUrl.c_str());
        
        std::vector<CSHttpTaskItem *>::iterator i = _urlParams.begin();
        if(i != _urlParams.end()){
            if(!str_exist(_baseUrl.c_str(), "?")){
                buffer_append_str(buf, "?");
            }
        }
        while(i != _urlParams.end()){
            CSHttpTaskItem * item = * i;
            buffer_append_str(buf,"&");
            buffer_append_str(buf, item->name.c_str());
            buffer_append_str(buf, "=");
            buffer_append_url_encode(buf, item->value.c_str());
            i++;
        }
        
        v = new Value((const char *)buffer_to_str(buf));
        
        v->autorelease();
        
        hlog("%s\n",buffer_to_str(buf));
        
        buffer_dealloc(buf);
        
        return v;
    }
    
    Value * CSHttpTask::body(){
        InvokeTickBegin
        hbuffer_t buf = buffer_alloc(128, 128);
        Value * v = NULL;

        if(_postFiles.size() >0 || _postFileDatas.size() >0){
            
            {
                std::vector<CSHttpTaskItem *>::iterator i = _postDatas.begin();
                while(i != _postDatas.end()){
                    CSHttpTaskItem * item = * i;

                    buffer_append_str(buf, "--");
                    buffer_append_str(buf, HTTP_MULTIPART_TOKEN);
                    buffer_append_str(buf, "\r\n");
                    buffer_append_str(buf, "Content-Disposition: form-data; name=\"");
                    buffer_append_str(buf, item->name.c_str());
                    buffer_append_str(buf, "\"\r\n");
                    
                    buffer_append_url_encode(buf, item->value.c_str());
                    
                    buffer_append_str(buf, "\r\n");
                    
                    i++;
                    
                    hlog("%s=%s\n",item->name.c_str(),item->value.c_str());
                }
            }
            
            {
                std::vector<CSHttpTaskItemFile *>::iterator i = _postFiles.begin();
                char fbuf[MAX_READ_BUF];
                FILE * f;
                int len;
                while(i != _postFiles.end()){
                    CSHttpTaskItemFile * item = * i;
                    
                    f = fopen(item->filePath.c_str(), "r");

                    if(f){
                        
                        buffer_append_str(buf, "--");
                        buffer_append_str(buf, HTTP_MULTIPART_TOKEN);
                        buffer_append_str(buf, "\r\n");
                        buffer_append_str(buf, "Content-Disposition: form-data; name=\"");
                        buffer_append_str(buf, item->name.c_str());
                        buffer_append_str(buf, "\"; filename=\"");
                        buffer_append_str(buf,file_name(item->filePath.c_str()));
                        buffer_append_str(buf, "\"\r\n");
                        buffer_append_str(buf, "Content-Type: ");
                        buffer_append_str(buf, item->contentType.c_str());
                        buffer_append_str(buf, "\r\n");
                        buffer_append_str(buf, "Content-Transfer-Encoding: binary\r\n\r\n");
                        
                        if((len = fread(fbuf, 1, sizeof(fbuf), f))>0){
                            buffer_append(buf,fbuf,len);
                        }
                        
                        buffer_append_str(buf, "\r\n");
                        
                        fclose(f);
                        
                        hlog("%s=%s\n",item->name.c_str(),item->filePath.c_str());
                    }
                    
                    i++;
                }
            }
            
            {
                std::vector<CSHttpTaskItemFileData *>::iterator i = _postFileDatas.begin();
                while(i != _postFileDatas.end()){
                    CSHttpTaskItemFileData * item = * i;
                    
                    buffer_append_str(buf, "--");
                    buffer_append_str(buf, HTTP_MULTIPART_TOKEN);
                    buffer_append_str(buf, "\r\n");
                    buffer_append_str(buf, "Content-Disposition: form-data; name=\"");
                    buffer_append_str(buf, item->name.c_str());
                    buffer_append_str(buf, "\"; filename=\"");
                    buffer_append_str(buf,  item->name.c_str());
                    buffer_append_str(buf, "\"\r\n");
                    buffer_append_str(buf, "Content-Type: ");
                    buffer_append_str(buf, item->contentType.c_str());
                    buffer_append_str(buf, "\r\n");
                    buffer_append_str(buf, "Content-Transfer-Encoding: binary\r\n\r\n");
                    
                    buffer_append(buf, item->data, item->length);
                    
                    buffer_append_str(buf, "\r\n");
                        
                    i++;
                    
                    hlog("%s=#%d#\n",item->name.c_str(),item->length);
                }
            }
            
            buffer_append_str(buf, "--");
            buffer_append_str(buf, HTTP_MULTIPART_TOKEN);
            buffer_append_str(buf, "--\r\n");

        }
        else if(_postDatas.size() >0){
            std::vector<CSHttpTaskItem *>::iterator i = _postDatas.begin();
            while(i != _postDatas.end()){
                CSHttpTaskItem * item = * i;
                buffer_append_str(buf,"&");
                buffer_append_str(buf, item->name.c_str());
                buffer_append_str(buf, "=");
                buffer_append_url_encode(buf, item->value.c_str());
                i++;
            }
            hlog("%s\n",buffer_to_str(buf));
        }
        
        if(buffer_length(buf)){
            
            v = new Value(buffer_data(buf),buffer_length(buf),ValueTypeBytes);
            
            v->autorelease();
        }
        
        buffer_dealloc(buf);
        
        return v;

    }
    
    CSHttpTaskDelegate CSHttpTask::httpDelegate(){
        return _delegate;
    }
    
    void CSHttpTask::setHttpDelegate(CSHttpTaskDelegate delegate){
        _delegate = delegate;
    }
    
    void CSHttpTask::onWillRequest(CSContext * context){
        if(_delegate.target && _delegate.willRequest){
            (_delegate.target->*_delegate.willRequest)(context,this);
        }
    }
    
    void CSHttpTask::onDidFail(CSContext * context,int errorCode,const char * error){
        if(_delegate.target && _delegate.didFail){
            (_delegate.target->*_delegate.didFail)(context,this,errorCode,error);
        }
    }
    
    void CSHttpTask::onDidFinishLoading(CSContext * context){
        if(_delegate.target && _delegate.didFinishLoading){
            (_delegate.target->*_delegate.didFinishLoading)(context,this);
        }
    }
    
    void CSHttpTask::onDidReceiveResponse(CSContext * context,int statusCode,const char * status,Dictionary * headers){
        if(_delegate.target && _delegate.didReceiveResponse){
            (_delegate.target->*_delegate.didReceiveResponse)(context,this,statusCode,status,headers);
        }
    }
    
    void CSHttpTask::onDidReceiveData(CSContext * context,void * data,int length){
        if(_delegate.target && _delegate.didReceiveData){
            (_delegate.target->*_delegate.didReceiveData)(context,this,data,length);
        }
    }
    
    void CSHttpTask::onDidSendBodyData(CSContext * context,int bytesWritten,int totalBytesWritten){
        if(_delegate.target && _delegate.didSendBodyData){
            (_delegate.target->*_delegate.didSendBodyData)(context,this,bytesWritten ,totalBytesWritten);
        }
    }
    
    void CSHttpTask::onDidBackgroundFinishLoading(CSContext * context){
        InvokeTickBegin
        switch (_response.type) {
            case CSHttpTaskResponseTypeString:
            {
                if(_response.value){
                    _response.value->release();
                    _response.value = NULL;
                }
                if(buffer_length(_response.buffer)){
                    _response.value = new Value(buffer_to_str(_response.buffer));
                }
                hlog("%s\n",buffer_to_str(_response.buffer));
                buffer_dealloc(_response.buffer);
                _response.buffer = NULL;
            }
                break;
            case CSHttpTaskResponseTypeJSON:
            {
                if(_response.value){
                    _response.value->release();
                    _response.value = NULL;
                }
                
                if(buffer_length(_response.buffer)){
                    
                    JSONCoder coder;

                    coder.setJSONString(buffer_to_str(_response.buffer));
                    _response.value = coder.decode();
                    if(_response.value){
                        
                        _response.value->retain();
                        
                        #ifdef DEBUG
                        
                        coder.encode(_response.value);
                        hlog("%s\n",coder.JSONString());
                        
                        
                        #endif
                    }
                    else{
                        hlog("%s\n",buffer_to_str(_response.buffer));
                    }
                }
                
                //hlog("%s\n",buffer_to_str(_response.buffer));
                buffer_dealloc(_response.buffer);
                _response.buffer = NULL;
            }
                break;
            default:
                break;
        }
        
        if(_delegate.target && _delegate.didBackgroundFinishLoading){
            (_delegate.target->*_delegate.didBackgroundFinishLoading)(context,this);
        }
    }
    
    void CSHttpTask::onDidBackgroundReceiveData(CSContext * context,void * data,int length){
        InvokeTickBegin
        if(_response.type){
            buffer_append(_response.buffer, data, length);
        }
        
        if(_delegate.target && _delegate.didBackgroundReceiveData){
            (_delegate.target->*_delegate.didBackgroundReceiveData)(context,this,data,length);
        }
    }
    
    void CSHttpTask::onDidBackgroundReceiveResponse(CSContext * context,int statusCode,const char * status,Dictionary * headers){
        if(_delegate.target && _delegate.didBackgroundReceiveResponse){
            (_delegate.target->*_delegate.didBackgroundReceiveResponse)(context,this,statusCode,status,headers);
        }
        InvokeTickBegin
        
        _response.encodeType = CSHttpTaskEncodeTypeNone;
        
        Value * v = (Value *)headers->objectForKey("Content-Type");
        if(v && v->stringValue()){
            if(strcmp(v->stringValue(), "mcrypt") == 0){
                _response.encodeType = CSHttpTaskEncodeTypeMcrypt;
            }
        }
        if(_response.type){
            if(_response.buffer == NULL){
                Value * v = (Value *)headers->objectForKey("Content-Length");
                if(v){
                    _response.buffer = buffer_alloc(v->intValue(), 128);
                }
                else{
                    _response.buffer = buffer_alloc(MAX_READ_BUF, 128);
                }
            }
        }
    }
    
    Object * CSHttpTask::responseValue(){
        return _response.value;
    }
    
    CSHttpTaskResponseType CSHttpTask::responseType(){
        return _response.type;
    }
    
    void CSHttpTask::setResponseType(CSHttpTaskResponseType type){
        _response.type = type;
    }
    
    struct _buffer_t * CSHttpTask::responseBuffer(){
        return _response.buffer;
    }
    
    void CSHttpTask::setHeader(const char * key,const char * value){
        if(_headers == NULL){
            _headers = new Dictionary();
        }
        _headers->setObjectForKey(key, Value::newValue(value));
    }
    
    const char * CSHttpTask::getHeader(const char * key){
        if(_headers){
            Value * v = (Value *) _headers->objectForKey(key);
            if(v){
                return v->stringValue();
            }
        }
        return NULL;
    }
    
    HCPP::Dictionary * CSHttpTask::headers(){
        return _headers;
    }
    
    CSHttpTaskEncodeType CSHttpTask::encodeType(){
        return _encodeType;
    }
    
    void CSHttpTask::setEncodeType(CSHttpTaskEncodeType encodeType){
        _encodeType = encodeType;
    }
    
    CSHttpTaskEncodeType CSHttpTask::responseEncodeType(){
        return _response.encodeType;
    }
    
}