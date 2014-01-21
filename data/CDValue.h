//
//  CDValue.h
//  hcppdata
//
//  Created by zhang hailong on 12-12-21.
//  Copyright (c) 2012年 9vteam. All rights reserved.
//

#ifndef __hcppdata__CDValue__
#define __hcppdata__CDValue__

#include "CDExp.h"
#include "CDRawData.h"

namespace CD {
    
    class CDValue : public Value{
    public:
        
        CDValue(void);

        CDValue(void * v,int length,ValueType valueType);
        
        CDValue(void * v,ValueType valueType);
        
        CDValue(const char * value);
        
        CDValue(int value);
        
        CDValue(long long value);
        
        CDValue(float value);
        
        CDValue(double value);
        
        CDValue(bool value);
        
        CDValue(void * ptr);
        
        virtual ~CDValue(void);

        
        virtual Object * value(CDRawData * rawData);
        
        virtual Value * sql(const char * prefix,const char * suffix);

        virtual double compare(CDRawData * rawData,CDValue * value);
        
        // ==
        virtual CDExp * eq(CDValue * value);
        
        // !=
        virtual CDExp * notEq(CDValue * value);
        
        // >
        virtual CDExp * g(CDValue * value);
        
        // >=
        virtual CDExp * ge(CDValue * value);
        
        // <
        virtual CDExp * l(CDValue * value);
        
        // <=
        virtual CDExp * le(CDValue * value);
        
        static CDValue * newValue(const char * value);
        
        static CDValue * newValue(int value);
        
        static CDValue * newValue(long long value);
        
        static CDValue * newValue(float value);
        
        static CDValue * newValue(double value);
        
        static CDValue * newValue(bool value);
        
        static CDValue * newValue(void * v,ValueType valueType);
        
        static CDValue * newValue(void * ptr);
        
        DEC_CLASS
        
    };
    
}

#endif /* defined(__hcppdata__CDValue__) */
