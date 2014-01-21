//
//  CDExpIn.h
//  hcppdata
//
//  Created by zhang hailong on 12-12-21.
//  Copyright (c) 2012年 9vteam. All rights reserved.
//

#ifndef __hcppdata__CDExpIn__
#define __hcppdata__CDExpIn__

#include "CDValue.h"
#include "CDField.h"
#include "Array.h"

namespace CD {
    
    class CDExpIn : public CDExp{
        
    public:
        
        CDExpIn(void);
        
        CDExpIn(CDField * field,Array * values);
        
        virtual ~CDExpIn(void);
        
        virtual CDField * field();
        
        virtual Array * values();
        
        virtual Value * sql(const char * prefix,const char * suffix);
        
        virtual bool result(CDRawData * rawData);
        
        DEC_CLASS
        
    private:
        CDField * _field;
        Array * _values;
    };
    
}

#endif /* defined(__hcppdata__CDExpIn__) */
