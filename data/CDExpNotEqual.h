//
//  CDExpNotEqual.h
//  hcppdata
//
//  Created by zhang hailong on 12-12-25.
//  Copyright (c) 2012年 9vteam. All rights reserved.
//

#ifndef __hcppdata__CDExpNotEqual__
#define __hcppdata__CDExpNotEqual__

#include "CDValue.h"

namespace CD {
    
    class CDExpNotEqual : public CDExp{
        
    public:
        CDExpNotEqual(void);
        
        CDExpNotEqual(CDValue * left,CDValue * right);
        
        virtual ~CDExpNotEqual(void);
        
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

#endif /* defined(__hcppdata__CDExpNotEqual__) */
