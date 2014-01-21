//
//  CDExpNotIn.cpp
//  hcppdata
//
//  Created by zhang hailong on 12-12-25.
//  Copyright (c) 2012年 9vteam. All rights reserved.
//
#include "hconfig.h"
#include "CDExpNotIn.h"
#include "hbuffer.h"

namespace CD {
    
    IMP_CLASS(CDExpNotIn, CDExp)
    
    CDExpNotIn::CDExpNotIn(void){
        _field = NULL;
        _values = NULL;
    }
    
    CDExpNotIn::CDExpNotIn(CDField * field,Array * values){
        if(field){
            field->retain();
        }
        if(values){
            values->retain();
        }
        _field = field;
        _values = values;
    }
    
    CDExpNotIn::~CDExpNotIn(void){
        if(_field){
            _field->release();
        }
        if(_values){
            _values->release();
        }
    }
    
    CDField * CDExpNotIn::field(){
        return _field;
    }
    
    Array * CDExpNotIn::values(){
        return _values;
    }
    
    Value * CDExpNotIn::sql(const char * prefix,const char * suffix){
        InvokeTickBegin
        hbuffer_t buf = buffer_alloc(128, 128);
        Value * v = NULL;
        
        buffer_append_str(buf, "(");
        
        v = _field->sql(prefix, suffix);
        
        if(v){
            buffer_append_str(buf, v->stringValue());
        }
        
        buffer_append_str(buf, " NOT IN (");
        
        ArrayIterator i = _values->begin();
        
        while(i != _values->end()){
            
            CDValue * cdv = (CDValue *) * i;
            
            v = cdv->sql(prefix, suffix);
            
            if(v){
                if(i != _values->begin()){
                    buffer_append_str(buf, ",");
                }
                buffer_append_str(buf, v->stringValue());
            }
            
            i++;
        }
        
        if(v){
            buffer_append_str(buf, v->stringValue());
        }
        
        
        buffer_append_str(buf, ")");
        
        
        v = (Value *)(new Value(buffer_to_str(buf)))->autorelease();
        
        buffer_dealloc(buf);
        
        return v;
    }
    
    bool CDExpNotIn::result(CDRawData * rawData){
        ArrayIterator i = _values->begin();
        
        while(i != _values->end()){
            
            CDValue * cdv = (CDValue *) * i;
            
            if(_field->compare(rawData,cdv) == 0.0){
                return false;
            }
            
            i++;
        }
        return true;
    }
    
}
