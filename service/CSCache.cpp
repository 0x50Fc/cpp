//
//  CSCache.cpp
//  hcppservice
//
//  Created by zhang hailong on 12-12-26.
//  Copyright (c) 2012年 9vteam. All rights reserved.
//

#include "hconfig.h"
#include "CSCache.h"

#include "Coder.h"
#include "hbuffer.h"
#include "hfile.h"

using namespace HCPP;

namespace CS {
    
    IMP_CLASS(CSCache, Object)
    
    CSCache::CSCache(void){
        _content = NULL;
        _context = NULL;
        _type = CSCacheTypeMem;
        _name = clazz()->name;
    }
    
    CSCache::CSCache(CSContext * context,CSCacheType type,const char * name){
        _context = context;
        _content = NULL;
        _type = type;
        _name = name;
        if(_name.size() ==0){
            _name = clazz()->name;
        }
        if(_context && _type != CSCacheTypeMem){
            InvokeTickBegin
            JSONCoder coder;
            hbuffer_t buf = buffer_alloc(MAX_PATH, 128);
            FILE * f;
            char fbuf[MAX_READ_BUF];
            int len;
            if(_type == CSCacheTypeTemp){
                buffer_append_str(buf, _context->tempDir());
            }
            else{
                buffer_append_str(buf, _context->documentDir());
            }
            buffer_append_str(buf, _name.c_str());
            buffer_append_str(buf, ".cache");
            
            f = fopen(buffer_to_str(buf), "r");
            
            if(f){
                
                buffer_clear(buf);
                
                while((len = fread(fbuf, 1, sizeof(fbuf), f)) >0){
                    buffer_append(buf,fbuf,len);
                }
                
                coder.setJSONString(buffer_to_str(buf));
                
                fclose(f);
                
                _content = (Dictionary *) coder.decode();
                if(_content){
                    _content->retain();
                }
            }
            
            buffer_dealloc(buf);
        }
        
    }
    
    CSCache::~CSCache(void){
        if(_context && _content && _type != CSCacheTypeMem){
            InvokeTickBegin
            JSONCoder coder;
            hbuffer_t buf = buffer_alloc(MAX_PATH, 128);
            FILE * f;
            
            if(_type == CSCacheTypeTemp){
                buffer_append_str(buf, _context->tempDir());
            }
            else{
                buffer_append_str(buf, _context->documentDir());
            }
            
            buffer_append_str(buf, _name.c_str());
            buffer_append_str(buf, ".cache");
            
            coder.encode(_content);
            
            const char * s = coder.JSONString();

            if(s){
                f = fopen(buffer_to_str(buf),"w");
                if(f){
                    fwrite(s, 1, strlen(s), f);
                    fclose(f);
                }
            }
            
            buffer_dealloc(buf);
        }
        if(_content){
            _content->release();
        }
    }
    
    Object * CSCache::objectForKey(const char * key){
        if(_content){
            return _content->objectForKey(key);
        }
        return NULL;
    }
    
    void CSCache::setObjectForKey(const char * key,Object * value){
        if(_content == NULL){
            _content = new Dictionary();
        }
        _content->setObjectForKey(key, value);
    }
    
    void CSCache::removeForKey(const char * key){
        if(_content){
            _content->removeObjectForKey(key);
        }
    }
    
    CSCacheType CSCache::type(){
        return _type;
    }
    
    void CSCache::setType(CSCacheType type){
        _type = type;
    }
    
    Object * CSCache::objectForKeyPath(const char * keyPath){
        char * p = (char *)keyPath;
        int l =0;
        while( *p != '\0' ){
            if(*p == '.'){
                break;
            }
            p ++;
            l ++;
        }
        std::string key(keyPath,0,l);
        Object * v =  objectForKey(key.c_str()) ;
        if(*p =='\0'){
            return v;
        }
        if(v){
            return v->objectForKeyPath(p +1);
        }
        return NULL;
    }
    
    void CSCache::setObjectForKeyPath(const char * keyPath,Object * value){
        char * p = (char *)keyPath;
        int l =0;
        while( *p != '\0' ){
            if(*p == '.'){
                break;
            }
            p ++;
            l ++;
        }
        if(*p =='\0'){
            setObjectForKey(keyPath, value);
        }
        else{
            std::string key(keyPath,0,l);
            Object * v=  objectForKey(key.c_str());
            if(v){
                v->setObjectForKeyPath(p +1, value);
            }
        }
    }

    
}