//
//  CDField.h
//  hcppdata
//
//  Created by zhang hailong on 12-12-21.
//  Copyright (c) 2012年 9vteam. All rights reserved.
//

#ifndef __hcppdata__CDField__
#define __hcppdata__CDField__

#include "CDValue.h"
#include "Array.h"

namespace CD {
    
    class CDField : public CDValue{
        
    public:
        CDField(void);
        
        CDField(CDDataEntityField * field);
        
        virtual ~CDField(void);
        
        virtual CDDataEntityField * field();
      
        virtual Object * value(CDRawData * rawData);
        
        virtual Value * sql(const char * prefix,const char * suffix);
        
        virtual CDExp * inValues(Value * value,...);
        
        virtual CDExp * inValues(Array * values);
        
        virtual CDExp * notInValues(Value * value,...);
        
        virtual CDExp * notInValues(Array * values);
        
        static CDField * newField(CDDataEntityField * field);
        
        DEC_CLASS
        
    private:
        CDDataEntityField * _field;
        
    };
}

#endif /* defined(__hcppdata__CDField__) */
