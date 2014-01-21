//
//  CDField.cpp
//  hcppdata
//
//  Created by zhang hailong on 12-12-21.
//  Copyright (c) 2012年 9vteam. All rights reserved.
//

#include "hconfig.h"
#include "CDField.h"
#include "hbuffer.h"

#include "CDExpIn.h"
#include "CDExpNotIn.h"

namespace CD {
    
    IMP_CLASS(CDField, CDValue)
    
    CDField::CDField(void){
        _field = NULL;
    }
    
    CDField::CDField(CDDataEntityField * field){
        _field = field;
    }
    
    CDField::~CDField(void){
        
    }
    
    CDDataEntityField * CDField::field(){
        return _field;
    }
    
    Object * CDField::value(CDRawData * rawData){
        return rawData->value(_field);
    }
    
    Value * CDField::sql(const char * prefix,const char * suffix){
        InvokeTickBegin
        hbuffer_t buf = buffer_alloc(128, 128);
        Value * v = NULL;
        buffer_append_str(buf, prefix);
        buffer_append_str(buf, _field->name);
        buffer_append_str(buf, suffix);
        
        v = (Value *) (new Value(buffer_to_str(buf)))->autorelease();
        
        buffer_dealloc(buf);
        
        return v;
    }
    
    CDExp * CDField::inValues(Value * value,...){
        va_list va;
        Array * values = new Array();
        Value * v;
        values->addObject(value);
        
        va_start(va, value);
        
        while((v = va_arg(va, Value *))){
            values->addObject(value);
        }
        
        va_end(va);
        
        CDExp * exp = inValues(values);
        
        values->release();
        
        return exp;
    }
    
    CDExp * CDField::inValues(Array * values){
        return (CDExp *)(new CDExpIn(this, values))->autorelease();
    }
    
    CDExp * CDField::notInValues(Value * value,...){
        va_list va;
        Array * values = new Array();
        Value * v;
        values->addObject(value);
        
        va_start(va, value);
        
        while((v = va_arg(va, Value *))){
            values->addObject(value);
        }
        
        va_end(va);
        
        CDExp * exp = notInValues(values);
        
        values->release();
        
        return exp;
    }
    
    CDExp * CDField::notInValues(Array * values){
        return (CDExp *)(new CDExpNotIn(this, values))->autorelease();
    }
    
    CDField * CDField::newField(CDDataEntityField * field){
        CDField * f = new CDField(field);
        return (CDField *) f->autorelease();
    }
    
}