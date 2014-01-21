//
//  CDExpNot.h
//  hcppdata
//
//  Created by zhang hailong on 12-12-21.
//  Copyright (c) 2012年 9vteam. All rights reserved.
//

#ifndef __hcppdata__CDExpNot__
#define __hcppdata__CDExpNot__

#include "CDValue.h"

namespace CD {
    
    class CDExpNot : public CDExp{
        
    public:
        CDExpNot(void);
        
        CDExpNot(CDExp * exp);
        
        virtual ~CDExpNot(void);
        
        virtual CDExp * exp();
        
        virtual Value * sql(const char * prefix,const char * suffix);
        
        virtual bool result(CDRawData * rawData);
        
        DEC_CLASS
        
    private:
        CDExp * _exp;
    };
    
}

#endif /* defined(__hcppdata__CDExpNot__) */
