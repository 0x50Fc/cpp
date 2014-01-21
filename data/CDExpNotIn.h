//
//  CDExpNotIn.h
//  hcppdata
//
//  Created by zhang hailong on 12-12-25.
//  Copyright (c) 2012年 9vteam. All rights reserved.
//

#ifndef __hcppdata__CDExpNotIn__
#define __hcppdata__CDExpNotIn__

#include "CDValue.h"
#include "CDField.h"
#include "Array.h"

namespace CD {
    
    class CDExpNotIn : public CDExp{
        
    public:
        
        CDExpNotIn(void);
        
        CDExpNotIn(CDField * field,Array * values);
        
        virtual ~CDExpNotIn(void);
        
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
#endif /* defined(__hcppdata__CDExpNotIn__) */
