//
//  Buffer.cpp
//  hcpp
//
//  Created by zhang hailong on 13-2-21.
//  Copyright (c) 2013年 hailong.org. All rights reserved.
//

#include "hconfig.h"
#include "Buffer.h"

#include "hbuffer.h"

namespace HCPP {

    Buffer::Buffer(void){
        InvokeTickBegin
        _buf = buffer_alloc(128, 128);
    }
    
    Buffer::Buffer(unsigned int capacity){
        InvokeTickBegin
        _buf = buffer_alloc(capacity, 128);
    }
    
    Buffer::Buffer(unsigned int capacity,unsigned int extendSize){
        InvokeTickBegin
        _buf = buffer_alloc(capacity, extendSize);
    }
    
    Buffer::~Buffer(void){
        InvokeTickBegin
        buffer_dealloc(_buf);
    }
    
    void Buffer::append(void * data,unsigned int length){
        InvokeTickBegin
        buffer_append(_buf, data, length);
    }
    
    void Buffer::appendFormatV(const char * format,va_list va){
        InvokeTickBegin
        buffer_append_format_va_list(_buf, format, va);
    }
    
    void Buffer::appendFormat(const char * format,...){
        va_list va;
        va_start(va, format);
        appendFormatV(format, va);
        va_end(va);
    }
    
    void Buffer::append(const char * str){
        InvokeTickBegin
        buffer_append_str(_buf, str);
    }
    
    void * Buffer::data(){
        InvokeTickBegin
        return buffer_data(_buf);
    }
    
    unsigned int Buffer::length(){
        InvokeTickBegin
        return buffer_length(_buf);
    }
    
    void Buffer::setLength(unsigned int length){
        InvokeTickBegin
        buffer_length_set(_buf, length);
    }
    
    void Buffer::clear(){
        InvokeTickBegin
        buffer_clear(_buf);
    }
    
    Value * Buffer::toStringValue(){
        InvokeTickBegin
        return Value::newValue(buffer_to_str(_buf));
    }
    
    const char * Buffer::toString(){
        InvokeTickBegin
        return buffer_to_str(_buf);
    }
}
