//
//  CDExpLess.h
//  hcppdata
//
//  Created by zhang hailong on 12-12-21.
//  Copyright (c) 2012年 9vteam. All rights reserved.
//

#ifndef __hcppdata__CDExpLess__
#define __hcppdata__CDExpLess__

#include "CDValue.h"

namespace CD {
    
    class CDExpLess : public CDExp{
        
    public:
        CDExpLess(void);
        
        CDExpLess(CDValue * left,CDValue * right);
        
        virtual ~CDExpLess(void);
        
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
#endif /* defined(__hcppdata__CDExpLess__) */
