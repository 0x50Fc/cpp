//
//  Bundle.cpp
//  hcpp
//
//  Created by Zhang Hailong on 13-1-17.
//  Copyright (c) 2013年 hailong.org. All rights reserved.
//
#include "hconfig.h"
#include "Bundle.h"
#include "hbuffer.h"
#include "Coder.h"
#include "hfile.h"

namespace HCPP {
    
    IMP_CLASS(Bundle, Object)
    
    Bundle::Bundle(void){
        _parent = NULL;
        _infoObject = NULL;
    }
    
    Bundle::Bundle(Bundle * parent,const char * bundlePath,const char * info){
        _Bundle(parent,bundlePath, info);
    }
    
    Bundle::Bundle(Bundle * parent,const char * bundlePath){
        _Bundle(parent,bundlePath, NULL);
    }
    
    void Bundle::_Bundle(Bundle * parent,const char * bundlePath,const char * info){
        if(parent) {
            parent->retain();
        }
        _parent = parent;
        _bundlePath = bundlePath;
        _infoObject = NULL;
        if(info == NULL || * info == '\0'){
            info = "info";
        }
        Value * v = getFilePath("%s.json",info);
        JSONCoder coder;
        coder.setJSONFile(v->stringValue());
        _infoObject = coder.decode();
        if(_infoObject){
            _infoObject->retain();
        }
    }
    
    Bundle::~Bundle(void){
        if(_infoObject){
            _infoObject->release();
        }
        if(_parent){
            _parent->release();
        }
    }
    
    Bundle * Bundle::parent(){
        return _parent;
    }
    
    const char * Bundle::bundlePath(){
        return _bundlePath.c_str();
    }
    
    Object * Bundle::infoObject(){
        return _infoObject;
    }
    
    Value * Bundle::getStringContent(const char * format,...){
        va_list va;
        
        va_start(va, format);
        
        Value * v = getStringContentV(format, va);
        
        va_end(va);
        
        return v;
    }
    
    Value * Bundle::getStringContentV(const char * format,va_list va){
        Value * path = getFilePathV(format,va);
        
        if(_parent){
            return _parent->getStringContent(path->stringValue());
        }
        
        Value * v = NULL;
        InvokeTickBegin
        hbuffer_t content = buffer_alloc(512, 512);
        FILE * f = fopen(path->stringValue(), "r");
        char buffer[1024];
        int len;
        
        if(f){
            while((len = fread(buffer, 1, sizeof(buffer), f)) >0){
                buffer_append(content, buffer, len);
            }
            fclose(f);
        }
        
        v = Value::newValue(buffer_to_str(content));
        
        buffer_dealloc(content);
        
        return v;
    }
    
    Value * Bundle::getBytesContent(const char * format,...){
        va_list va;
        
        va_start(va, format);
        
        Value * v = getBytesContentV(format, va);
        
        va_end(va);
        
        return v;
    }
    
    Value * Bundle::getBytesContentV(const char * format,va_list va){
        Value * path = getFilePathV(format,va);
        
        if(_parent){
            return _parent->getBytesContent(path->stringValue());
        }
        
        Value * v = NULL;
        InvokeTickBegin
        hbuffer_t content = buffer_alloc(512, 512);
        FILE * f = fopen(path->stringValue(), "r");
        char buffer[1024];
        int len;
        
        if(f){
            while((len = fread(buffer, 1, sizeof(buffer), f)) >0){
                buffer_append(content, buffer, len);
            }
            fclose(f);
        }
        
        if(buffer_length(content) >0){
            v = Value::newValue((void *)buffer_data(content),buffer_length(content));
        }
        
        buffer_dealloc(content);
        
        return v;
    }
    
    Value * Bundle::getFilePath(const char * format,...){
        Value * v = NULL;
        va_list va;
        va_start(va, format);
        v = getFilePathV(format, va);
        va_end(va);
        return v;
    }
    
    Value * Bundle::getFilePathV(const char * format,va_list va){
        InvokeTickBegin
        hbuffer_t path = buffer_alloc(MAX_PATH, 128);
        Value * v = NULL;
        buffer_append_str(path,_bundlePath.c_str());
        if(buffer_length(path) >0 && * (buffer_data(path) + buffer_length(path) -1) != PATH_SPLIT){
            buffer_append_str(path, "/");
        }
        buffer_append_format_va_list(path, format, va);
        if(_parent){
            v = _parent->getFilePath(buffer_to_str(path));
        }
        else{
            v = Value::newValue(buffer_to_str(path));
        }
        buffer_dealloc(path);
        return v;
    }
    
    const char * Bundle::version(){
        if(_infoObject){
            Object * v = _infoObject->objectForKeyPath("version");
            if(v && v->isKindOfClass(&Value::oClass)){
                return ((Value *)v)->stringValue();
            }
        }
        return "";
    }
    
    bool Bundle::isExists(){
        return file_exist(_bundlePath.c_str());
    }
    
    Bundle * Bundle::newBundle(Bundle * parent,const char * bundlePath,const char * info){
        Bundle * bundle = new Bundle(parent,bundlePath,info);
        return (Bundle *) bundle->autorelease();
    }
    
    Bundle * Bundle::newBundle(Bundle * parent,const char * bundlePath){
        Bundle * bundle = new Bundle(parent,bundlePath);
        return (Bundle *) bundle->autorelease();
    }
    
}