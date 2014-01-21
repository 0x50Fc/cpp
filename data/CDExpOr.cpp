//
//  CDExpOr.cpp
//  hcppdata
//
//  Created by zhang hailong on 12-12-25.
//  Copyright (c) 2012年 9vteam. All rights reserved.
//
#include "hconfig.h"
#include "CDExpOr.h"
#include "hbuffer.h"

namespace CD {
    
    IMP_CLASS(CDExpOr, CDExp)
    
    CDExpOr::CDExpOr(void){
        _left = NULL;
        _right = NULL;
    }
    
    CDExpOr::CDExpOr(CDExp * left,CDExp * right){
        if(left){
            left->retain();
        }
        if(right){
            right->retain();
        }
        _left = left;
        _right = right;
    }
    
    CDExpOr::~CDExpOr(void){
        if(_left){
            _left->release();
        }
        if(_right){
            _right->release();
        }
    }
    
    CDExp * CDExpOr::left(){
        return _left;
    }
    
    CDExp * CDExpOr::right(){
        return _right;
    }
    
    Value * CDExpOr::sql(const char * prefix,const char * suffix){
        InvokeTickBegin
        hbuffer_t buf = buffer_alloc(128, 128);
        Value * v = NULL;
        
        buffer_append_str(buf, "(");
        
        v = _left->sql(prefix, suffix);
        
        if(v){
            buffer_append_str(buf, v->stringValue());
        }
        
        buffer_append_str(buf, " OR ");
        
        v = _right->sql(prefix, suffix);
        
        if(v){
            buffer_append_str(buf, v->stringValue());
        }
        
        
        buffer_append_str(buf, ")");
        
        
        v = (Value *)(new Value(buffer_to_str(buf)))->autorelease();
        
        buffer_dealloc(buf);
        
        return v;
    }
    
    bool CDExpOr::result(CDRawData * rawData){
        return _left->result(rawData) || _right->result(rawData);
    }
    
}
