//
//  CDExpGreater.cpp
//  hcppdata
//
//  Created by zhang hailong on 12-12-21.
//  Copyright (c) 2012年 9vteam. All rights reserved.
//
#include "hconfig.h"
#include "CDExpGreater.h"
#include "hbuffer.h"

namespace CD {
    
    IMP_CLASS(CDExpGreater, CDExp)
    
    CDExpGreater::CDExpGreater(void){
        _left = NULL;
        _right = NULL;
    }
    
    CDExpGreater::CDExpGreater(CDValue * left,CDValue * right){
        if(left){
            left->retain();
        }
        if(right){
            right->retain();
        }
        _left = left;
        _right = right;
    }
    
    CDExpGreater::~CDExpGreater(void){
        if(_left){
            _left->release();
        }
        if(_right){
            _right->release();
        }
    }
    
    CDValue * CDExpGreater::left(){
        return _left;
    }
    
    CDValue * CDExpGreater::right(){
        return _right;
    }
    
    Value * CDExpGreater::sql(const char * prefix,const char * suffix){
        InvokeTickBegin
        hbuffer_t buf = buffer_alloc(128, 128);
        Value * v = NULL;
        
        buffer_append_str(buf, "(");
        
        v = _left->sql(prefix, suffix);
        
        if(v){
            buffer_append_str(buf, v->stringValue());
        }
        
        buffer_append_str(buf, " > ");
        
        v = _right->sql(prefix, suffix);
        
        if(v){
            buffer_append_str(buf, v->stringValue());
        }
        
        
        buffer_append_str(buf, ")");
        
        
        v = (Value *)(new Value(buffer_to_str(buf)))->autorelease();
        
        buffer_dealloc(buf);
        
        return v;
    }
    
    bool CDExpGreater::result(CDRawData * rawData){
        return _left->compare(rawData,_right) > 0.0;
    }
    
}
