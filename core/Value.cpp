//
//  Value.cpp
//  hcpp
//
//  Created by zhang hailong on 12-12-7.
//  Copyright (c) 2012年 hailong.org. All rights reserved.
//

#include "hconfig.h"
#include "Value.h"

#include "hbuffer.h"

namespace HCPP {
    
    IMP_CLASS(Value, Object)
    
    void Value::_Value(void * v,int length,ValueType valueType){
        if(v && length >0){
            _value = new char[length];
            memcpy(_value,v,length);
            _length = length;
        }
        else {
            _length = 0;
            _value = NULL;
        }
        _valueType = valueType;

    }
    
    Value::Value(){
        _value = NULL;
        _length = 0;
        _valueType = ValueTypeVoid;
    }
    
    Value::Value(void * v,ValueType valueType){
        _Value(v, valueType->length, valueType);
    }
    
    Value::Value(void * v,int length,ValueType valueType){
        _Value(v,length,valueType);
    }
    
    Value::Value(const char * value){
        _Value((void *)value,strlen(value)+1,ValueTypeString);
    }
    
    Value::Value(int value){
        _Value(&value,sizeof(int),ValueTypeInteger);
    }
    
    Value::Value(long long value){
        _Value(&value,sizeof(long long),ValueTypeInt64);
    }
    
    Value::Value(float value){
        _Value(&value,sizeof(float),ValueTypeFloat);
    }
    
    Value::Value(double value){
        _Value(&value,sizeof(double),ValueTypeDouble);
    }
    
    Value::Value(bool value){
        _Value(&value,sizeof(bool),ValueTypeBoolean);
    }
    
    Value::Value(void * value){
        _Value(&value,sizeof(void *),ValueTypePtr);
    }
    
    Value::~Value(){
        if(_value){
            delete [] _value;
        }
    }
    
    
    void * Value::value(){
        return _value;
    }
    
    void Value::getValue(void * p){
        if(_value){
            memcpy(p, _value, _length);
        }
    }
    
    ValueType Value::valueType(){
        return _valueType;
    }
    
    int Value::length(){
        return _length;
    }
    
    const char * Value::stringValue(){
        if(_valueType == ValueTypeString){
            return (const char *) _value;
        }
        return NULL;
    }
    
    int Value::intValue(){
        if(_valueType == ValueTypeString){
            return atoi((const char *) _value);
        }
        if(_valueType == ValueTypeInt64){
            return * ((long long *) _value);
        }
        if(_valueType == ValueTypeInteger){
            return * ((int *) _value);
        }
        if(_valueType == ValueTypeFloat){
            return * ((float *) _value);
        }
        if(_valueType == ValueTypeDouble){
            return * ((double *) _value);
        }
        if(_valueType == ValueTypeBoolean){
            return * ((bool *) _value);
        }
        return 0;
    }
    
    float Value::floatValue(){
        if(_valueType == ValueTypeString){
            return atof((const char *) _value);
        }
        if(_valueType == ValueTypeInt64){
            return * ((long long *) _value);
        }
        if(_valueType == ValueTypeInteger){
            return * ((int *) _value);
        }
        if(_valueType == ValueTypeFloat){
            return * ((float *) _value);
        }
        if(_valueType == ValueTypeDouble){
            return * ((double *) _value);
        }
        if(_valueType == ValueTypeBoolean){
            return * ((bool *) _value);
        }
        return 0.0f;
    }
    
    double Value::doubleValue(){
        if(_valueType == ValueTypeString){
            return atof((const char *) _value);
        }
        if(_valueType == ValueTypeInt64){
            return * ((long long *) _value);
        }
        if(_valueType == ValueTypeInteger){
            return * ((int *) _value);
        }
        if(_valueType == ValueTypeFloat){
            return * ((float *) _value);
        }
        if(_valueType == ValueTypeDouble){
            return * ((double *) _value);
        }
        if(_valueType == ValueTypeBoolean){
            return * ((bool *) _value);
        }
        return 0.0;
    }
    
    bool Value::booleanValue(){
        if(_valueType == ValueTypeString){
            return strcmp((const char *)_value, "true") ==0 || atof((const char *) _value);
        }
        if(_valueType == ValueTypeInt64){
            return * ((long long *) _value);
        }
        if(_valueType == ValueTypeInteger){
            return * ((int *) _value);
        }
        if(_valueType == ValueTypeFloat){
            return * ((float *) _value);
        }
        if(_valueType == ValueTypeDouble){
            return * ((double *) _value);
        }
        if(_valueType == ValueTypeBoolean){
            return * ((bool *) _value);
        }
        return false;
    }
    
    long long Value::int64Value(){
        if(_valueType == ValueTypeString){
            return atoll((const char *) _value);
        }
        if(_valueType == ValueTypeInt64){
            return * ((long long *) _value);
        }
        if(_valueType == ValueTypeInteger){
            return * ((int *) _value);
        }
        if(_valueType == ValueTypeFloat){
            return * ((float *) _value);
        }
        if(_valueType == ValueTypeDouble){
            return * ((double *) _value);
        }
        if(_valueType == ValueTypeBoolean){
            return * ((bool *) _value);
        }
        return 0;
    }
    
    void * Value::ptrValue(){
        if(_valueType == ValueTypePtr){
            return * (void **)_value;
        }
        return NULL;
    }
    
    double Value::compare(Value * value){
        ValueType t = value->valueType();
        if(_valueType == ValueTypeString || t == ValueTypeString){
            Value * v1 = toStringValue();
            Value * v2 = value->toStringValue();
            if(v1 == NULL && v2 == NULL){
                return 0;
            }
            if(v1 == NULL){
                return -1;
            }
            if(v2 == NULL){
                return 1;
            }
            return strcmp(v1->stringValue(), v2->stringValue());
        }
        return doubleValue() - value->doubleValue();
    }
    
    Value * Value::toStringValue(){

        if(_valueType == ValueTypeString){
            return this;
        }
        if(_valueType == ValueTypeInt64){
            return Value::newFormat("%lld",* ((long long *) _value));
        }
        if(_valueType == ValueTypeInteger){
            return Value::newFormat("%d",* ((int *) _value));
        }
        if(_valueType == ValueTypeFloat){
            return Value::newFormat("%f",* ((float *) _value));
        }
        if(_valueType == ValueTypeDouble){
            return Value::newFormat("%lf",* ((double *) _value));
        }
        if(_valueType == ValueTypeBoolean){
            if(* ((bool *) _value)){
                return (Value *)(new Value((const char *)"true"))->autorelease();
            }
            return (Value *)(new Value((const char *)"false"))->autorelease();
        }
        return NULL;
    }
    
    Value * Value::newValue(int value){
        return (Value *)(new Value(value))->autorelease();
    }
    
    Value * Value::newValue(long long value){
        return (Value *)(new Value(value))->autorelease();
    }
    
    Value * Value::newValue(float value){
        return (Value *)(new Value(value))->autorelease();
    }
    
    Value * Value::newValue(double value){
        return (Value *)(new Value(value))->autorelease();
    }
    
    Value * Value::newValue(bool value){
        return (Value *)(new Value(value))->autorelease();
    }
    
    Value * Value::newValue(void * v,ValueType valueType){
        return (Value *)(new Value(v,valueType))->autorelease();
    }
    
    Value * Value::newValue(void * ptr){
        return (Value *)(new Value(ptr))->autorelease();
    }
    
    Value * Value::newValue(void * v,int length){
        return (Value *)(new Value(v,length,ValueTypeBytes))->autorelease();
    }
    
    Value * Value::newFormat(const char * format,...){
        InvokeTickBegin;
        hbuffer_t buf = buffer_alloc(128, 128);
        va_list va;
        
        va_start(va, format);
        
        buffer_append_format_va_list(buf, format, va);
        
        Value * v = new Value(buffer_to_str(buf));
        
        va_end(va);
        
        buffer_dealloc(buf);
        
        return (Value *)v->autorelease();
    }
    
    Value * Value::newValue(const char * value){
        Value * v = new Value(value);
        return (Value *) v->autorelease();
    }
    
    Value * Value::newDateValue(){
        struct timeval tm;
        gettimeofday(&tm, NULL);
        double t = (double)tm.tv_sec + (double)tm.tv_usec / 1000000.0;
        return Value::newValue(t);
    }
    
    Value * Value::toDateFormat(const char * format){
        time_t t = doubleValue();
        struct tm * tm = localtime(&t);
        char buf[256] = "";
        strftime(buf,sizeof(buf),format,tm);
        return Value::newValue((const char *)buf);
    }

    Object * Value::copy(){
        return this;
    }
    
}

