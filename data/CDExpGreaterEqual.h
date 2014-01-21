//
//  CDExpGreaterEqual.h
//  hcppdata
//
//  Created by zhang hailong on 12-12-21.
//  Copyright (c) 2012年 9vteam. All rights reserved.
//

#ifndef __hcppdata__CDExpGreaterEqual__
#define __hcppdata__CDExpGreaterEqual__

#include "CDValue.h"

namespace CD {
    
    class CDExpGreaterEqual : public CDExp{
        
    public:
        CDExpGreaterEqual(void);
        
        CDExpGreaterEqual(CDValue * left,CDValue * right);
        
        virtual ~CDExpGreaterEqual(void);
        
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
#endif /* defined(__hcppdata__CDExpGreaterEqual__) */
