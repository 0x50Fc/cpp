//
//  Buffer.h
//  hcpp
//
//  Created by zhang hailong on 13-2-21.
//  Copyright (c) 2013年 hailong.org. All rights reserved.
//

#ifndef __hcpp__Buffer__
#define __hcpp__Buffer__

#include "Value.h"

struct _buffer_t;

namespace HCPP {

    
    class Buffer : public Object{
    public:
        
        Buffer(void);
        
        Buffer(unsigned int capacity);
        
        Buffer(unsigned int capacity,unsigned int extendSize);

        virtual ~Buffer(void);
        
        virtual void append(void * data,unsigned int length);
        
        virtual void appendFormatV(const char * format,va_list va);
        
        virtual void appendFormat(const char * format,...);
        
        virtual void append(const char * str);
    
        virtual void * data();
        
        virtual unsigned int length();
        
        virtual void setLength(unsigned int length);
        
        virtual void clear();
        
        virtual Value * toStringValue();
        
        virtual const char * toString();
        
        
    private:
        struct _buffer_t * _buf;
    };
}

#endif /* defined(__hcpp__Buffer__) */
