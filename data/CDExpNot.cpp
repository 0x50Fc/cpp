//
//  CDExpNot.cpp
//  hcppdata
//
//  Created by zhang hailong on 12-12-21.
//  Copyright (c) 2012年 9vteam. All rights reserved.
//
#include "hconfig.h"
#include "CDExpNot.h"
#include "hbuffer.h"

namespace CD {
    
    IMP_CLASS(CDExpNot, CDExp)
    
    CDExpNot::CDExpNot(void){
        _exp = NULL;
    }
    
    CDExpNot::CDExpNot(CDExp * exp){
        if(exp){
            exp->retain();
        }
        _exp = exp;
    }
    
    CDExpNot::~CDExpNot(void){
        if(_exp){
            _exp->release();
        }
    }
    
    CDExp * CDExpNot::exp(){
        return _exp;
    }
    
    Value * CDExpNot::sql(const char * prefix,const char * suffix){
        InvokeTickBegin
        hbuffer_t buf = buffer_alloc(128, 128);
        Value * v = NULL;
        
        buffer_append_str(buf, "( NOT ");
        
        v = _exp->sql(prefix, suffix);
        
        if(v){
            buffer_append_str(buf, v->stringValue());
        }
        
        buffer_append_str(buf, " )");
        
        v = (Value *)(new Value(buffer_to_str(buf)))->autorelease();
        
        buffer_dealloc(buf);
        
        return v;
    }
    
    bool CDExpNot::result(CDRawData * rawData){
        return ! _exp->result(rawData);
    }
    
}