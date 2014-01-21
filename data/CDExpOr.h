//
//  CDExpOr.h
//  hcppdata
//
//  Created by zhang hailong on 12-12-25.
//  Copyright (c) 2012年 9vteam. All rights reserved.
//

#ifndef __hcppdata__CDExpOr__
#define __hcppdata__CDExpOr__

#include "CDExp.h"

namespace CD {
    
    class CDExpOr : public CDExp{
        
    public:
        CDExpOr(void);
        
        CDExpOr(CDExp * left,CDExp * right);
        
        virtual ~CDExpOr(void);
        
        virtual CDExp * left();
        
        virtual CDExp * right();
        
        virtual Value * sql(const char * prefix,const char * suffix);
        
        virtual bool result(CDRawData * rawData);
        
        DEC_CLASS
        
    private:
        CDExp * _left;
        CDExp * _right;
    };
    
}

#endif /* defined(__hcppdata__CDExpOr__) */
