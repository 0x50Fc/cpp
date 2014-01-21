//
//  CDExpGreater.h
//  hcppdata
//
//  Created by zhang hailong on 12-12-21.
//  Copyright (c) 2012年 9vteam. All rights reserved.
//

#ifndef __hcppdata__CDExpGreater__
#define __hcppdata__CDExpGreater__

#include "CDValue.h"

namespace CD {
    
    class CDExpGreater : public CDExp{
        
    public:
        CDExpGreater(void);
        
        CDExpGreater(CDValue * left,CDValue * right);
        
        virtual ~CDExpGreater(void);
        
        virtual CDValue * left();
        
        virtual CDValue * right();
        
        virtual Value * sql(const char * prefix,const char * suffix);
        
        virtual bool result(CDRawData * rawData);
        
        DEC_CLASS
        
    private:
        CDValue * _left;
        CDValue * _right;
    };
    
}

#endif /* defined(__hcppdata__CDExpGreater__) */
