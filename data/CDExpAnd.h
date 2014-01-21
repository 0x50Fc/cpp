//
//  CDExpAnd.h
//  hcppdata
//
//  Created by zhang hailong on 12-12-21.
//  Copyright (c) 2012年 9vteam. All rights reserved.
//

#ifndef __hcppdata__CDExpAnd__
#define __hcppdata__CDExpAnd__

#include "CDExp.h"

namespace CD {
    
    class CDExpAnd : public CDExp{
      
    public:
        CDExpAnd(void);
        
        CDExpAnd(CDExp * left,CDExp * right);
        
        virtual ~CDExpAnd(void);
        
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

#endif /* defined(__hcppdata__CDExpAnd__) */
