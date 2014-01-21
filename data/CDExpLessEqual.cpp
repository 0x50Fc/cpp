//
//  CDExpLessEqual.cpp
//  hcppdata
//
//  Created by zhang hailong on 12-12-21.
//  Copyright (c) 2012年 9vteam. All rights reserved.
//
#include "hconfig.h"
#include "CDExpLessEqual.h"
#include "hbuffer.h"

namespace CD {
    
    IMP_CLASS(CDExpLessEqual, CDExp)
    
    CDExpLessEqual::CDExpLessEqual(void){
        _left = NULL;
        _right = NULL;
    }
    
    CDExpLessEqual::CDExpLessEqual(CDValue * left,CDValue * right){
        if(left){
            left->retain();
        }
        if(right){
            right->retain();
        }
        _left = left;
        _right = right;
    }
    
    CDExpLessEqual::~CDExpLessEqual(void){
        if(_left){
            _left->release();
        }
        if(_right){
            _right->release();
        }
    }
    
    CDValue * CDExpLessEqual::left(){
        return _left;
    }
    
    CDValue * CDExpLessEqual::right(){
        return _right;
    }
    
    Value * CDExpLessEqual::sql(const char * prefix,const char * suffix){
        InvokeTickBegin
        hbuffer_t buf = buffer_alloc(128, 128);
        Value * v = NULL;
        
        buffer_append_str(buf, "(");
        
        v = _left->sql(prefix, suffix);
        
        if(v){
            buffer_append_str(buf, v->stringValue());
        }
        
        buffer_append_str(buf, " <= ");
        
        v = _right->sql(prefix, suffix);
        
        if(v){
            buffer_append_str(buf, v->stringValue());
        }
        
        
        buffer_append_str(buf, ")");
        
        
        v = (Value *)(new Value(buffer_to_str(buf)))->autorelease();
        
        buffer_dealloc(buf);
        
        return v;
    }
    
    bool CDExpLessEqual::result(CDRawData * rawData){
        return _left->compare(rawData,_right) <= 0.0;
    }
    
}