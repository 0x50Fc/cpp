//
//  CDValue.cpp
//  hcppdata
//
//  Created by zhang hailong on 12-12-21.
//  Copyright (c) 2012年 9vteam. All rights reserved.
//

#include "hconfig.h"
#include "CDValue.h"
#include "hbuffer.h"

#include "CDExpEqual.h"
#include "CDExpNotEqual.h"
#include "CDExpGreater.h"
#include "CDExpGreaterEqual.h"
#include "CDExpLess.h"
#include "CDExpLessEqual.h"

namespace CD {
    
    IMP_CLASS(CDValue, Value)
    
    CDValue::CDValue(void){
        
    }

    
    CDValue::CDValue(void * v,int length,ValueType valueType):Value(v,length,valueType){
        
    }

    CDValue::CDValue(void * v,ValueType valueType):Value(v,valueType){
        
    }
    
    CDValue::CDValue(const char * value):Value(value){
        
    }

    
    CDValue::CDValue(int value):Value(value){
        
    }

    
    CDValue::CDValue(long long value):Value(value){
        
    }

    
    CDValue::CDValue(float value):Value(value){
        
    }

    
    CDValue::CDValue(double value):Value(value){
        
    }

    
    CDValue::CDValue(bool value):Value(value){
        
    }
    
    CDValue::CDValue(void * ptr):Value(ptr){
        
    }
    
    CDValue::~CDValue(void){

    }
    
    
    Object * CDValue::value(CDRawData * rawData){
        return this;
    }
    
    Value * CDValue::sql(const char * prefix,const char * suffix){
        ValueType t = valueType();
        if(t == ValueTypeString){
            InvokeTickBegin
            hbuffer_t buf = buffer_alloc(128, 128);
            hchar * p = (hchar *) stringValue();
            Value * v = NULL;
            buffer_append_str(buf, "'");
            while(p && *p != '\0'){
                if(*p == '\n'){
                    buffer_append_str(buf, "\\n");
                }
                else if(*p == '\r'){
                    buffer_append_str(buf, "\\r");
                }
                else if(*p == '\t'){
                    buffer_append_str(buf, "\\t");
                }
                else if(*p == '\''){
                    buffer_append_str(buf, "''");
                }
                else{
                    buffer_append(buf,p,1);
                }
                p++;
            }
            
            buffer_append_str(buf, "'");
            
            v =  (Value *)((new Value(buffer_to_str(buf)))->autorelease());
            
            buffer_dealloc(buf);
            
            return v;
        }
        else{
            return toStringValue();
        }
    }
    
    // ==
    CDExp * CDValue::eq(CDValue * value){
        return (CDExp *)(new CDExpEqual(this, value))->autorelease();
    }
    
    // !=
    CDExp * CDValue::notEq(CDValue * value){
        return (CDExp *)(new CDExpNotEqual(this, value))->autorelease();
    }

    
    // >
    CDExp * CDValue::g(CDValue * value){
        return (CDExp *)(new CDExpGreater(this, value))->autorelease();
    }

    
    // >=
    CDExp * CDValue::ge(CDValue * value){
        return (CDExp *)(new CDExpGreaterEqual(this, value))->autorelease();
    }

    
    // <
    CDExp * CDValue::l(CDValue * value){
        return (CDExp *)(new CDExpLess(this, value))->autorelease();
    }
    
    // <=
    CDExp * CDValue::le(CDValue * value){
        return (CDExp *)(new CDExpLessEqual(this, value))->autorelease();
    }

    
    CDValue * CDValue::newValue(const char * value){
        CDValue * v = new CDValue(value);
        return (CDValue *) v->autorelease();
    }
    
    CDValue * CDValue::newValue(int value){
        CDValue * v = new CDValue(value);
        return (CDValue *) v->autorelease();
    }
    
    CDValue * CDValue::newValue(long long value){
        CDValue * v = new CDValue(value);
        return (CDValue *) v->autorelease();
    }
    
    CDValue * CDValue::newValue(float value){
        CDValue * v = new CDValue(value);
        return (CDValue *) v->autorelease();
    }
    
    CDValue * CDValue::newValue(double value){
        CDValue * v = new CDValue(value);
        return (CDValue *) v->autorelease();
    }
    
    CDValue * CDValue::newValue(bool value){
        CDValue * v = new CDValue(value);
        return (CDValue *) v->autorelease();
    }
    
    CDValue * CDValue::newValue(void * v,ValueType valueType){
        CDValue * r = new CDValue(v,valueType);
        return (CDValue *) r->autorelease();
    }
    
    CDValue * CDValue::newValue(void * ptr){
        CDValue * v = new CDValue(ptr);
        return (CDValue *) v->autorelease();
    }

    double CDValue::compare(CDRawData * rawData,CDValue * value){
        Value * v1 = (Value *) this->value(rawData);
        Value * v2 = (Value *) value->value(rawData);
        if(v1 == NULL){
            if(v2 == NULL){
                return true;
            }
            return - v2->compare(v1);
        }
        return v1->compare(v2);
    }
}