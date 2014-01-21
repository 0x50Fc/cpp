//
//  CDExpEqual.h
//  hcppdata
//
//  Created by zhang hailong on 12-12-21.
//  Copyright (c) 2012年 9vteam. All rights reserved.
//

#ifndef __hcppdata__CDExpEqual__
#define __hcppdata__CDExpEqual__

#include "CDValue.h"

namespace CD {
    
    class CDExpEqual : public CDExp{
        
    public:
        CDExpEqual(void);
        
        CDExpEqual(CDValue * left,CDValue * right);
        
        virtual ~CDExpEqual(void);
        
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
#endif /* defined(__hcppdata__CDExpEqual__) */
