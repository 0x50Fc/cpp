//
//  Coder.h
//  hcpp
//
//  Created by zhang hailong on 12-12-11.
//  Copyright (c) 2012年 hailong.org. All rights reserved.
//

#ifndef __hcpp__Coder__
#define __hcpp__Coder__

#include "Object.h"

struct _buffer_t;

namespace HCPP {
    
    class Coder {
    public:
    	virtual ~Coder(void);
        virtual Object * decode() = 0;
        virtual void encode(Object * object) = 0;
        virtual const char * signature(Object * object) =0;
    };
    
    class JSONCoder : public Coder{
        
    public:
        
        JSONCoder(void);
        
        virtual ~JSONCoder(void);
        
        virtual Object * decode();
        
        virtual void encode(Object * object) ;
        
        virtual const char * JSONString();
        
        virtual void setJSONString(const char * string);
        
        virtual void setJSONFile(const char * filePath);
        
        virtual const char * signature(Object * object);
        
    private:
        struct _buffer_t * _JSONString;
        char _signature[64];
    };
    
}

#endif /* defined(__hcpp__Coder__) */
