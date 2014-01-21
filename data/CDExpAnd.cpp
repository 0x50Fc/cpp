//
//  CDExpAnd.cpp
//  hcppdata
//
//  Created by zhang hailong on 12-12-21.
//  Copyright (c) 2012年 9vteam. All rights reserved.
//

#include "hconfig.h"
#include "CDExpAnd.h"
#include "hbuffer.h"

namespace CD {
    
    IMP_CLASS(CDExpAnd, CDExp)
    
    CDExpAnd::CDExpAnd(void){
        _left = NULL;
        _right = NULL;
    }
    
    CDExpAnd::CDExpAnd(CDExp * left,CDExp * right){
        if(left){
            left->retain();
        }
        if(right){
            right->retain();
        }
        _left = left;
        _right = right;
    }
    
    CDExpAnd::~CDExpAnd(void){
        if(_left){
            _left->release();
        }
        if(_right){
            _right->release();
        }
    }
    
    CDExp * CDExpAnd::left(){
        return _left;
    }
    
    CDExp * CDExpAnd::right(){
        return _right;
    }
    
    Value * CDExpAnd::sql(const char * prefix,const char * suffix){
        InvokeTickBegin
        hbuffer_t buf = buffer_alloc(128, 128);
        Value * v = NULL;
        
        buffer_append_str(buf, "(");
        
        v = _left->sql(prefix, suffix);
        
        if(v){
            buffer_append_str(buf, v->stringValue());
        }
        
        buffer_append_str(buf, " AND ");
        
        v = _right->sql(prefix, suffix);
        
        if(v){
            buffer_append_str(buf, v->stringValue());
        }
        
        
        buffer_append_str(buf, ")");
        
        
        v = (Value *)(new Value(buffer_to_str(buf)))->autorelease();
        
        buffer_dealloc(buf);
        
        return v;
    }
    
    bool CDExpAnd::result(CDRawData * rawData){
        return _left->result(rawData) && _right->result(rawData);
    }
    
}
