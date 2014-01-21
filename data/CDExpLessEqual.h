//
//  CDExpLessEqual.h
//  hcppdata
//
//  Created by zhang hailong on 12-12-21.
//  Copyright (c) 2012年 9vteam. All rights reserved.
//

#ifndef __hcppdata__CDExpLessEqual__
#define __hcppdata__CDExpLessEqual__

#include "CDValue.h"

namespace CD {
    
    class CDExpLessEqual : public CDExp{
        
    public:
        CDExpLessEqual(void);
        
        CDExpLessEqual(CDValue * left,CDValue * right);
        
        virtual ~CDExpLessEqual(void);
        
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
#endif /* defined(__hcppdata__CDExpLessEqual__) */
