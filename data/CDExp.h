//
//  CDExp.h
//  hcppdata
//
//  Created by zhang hailong on 12-12-21.
//  Copyright (c) 2012年 9vteam. All rights reserved.
//

#ifndef __hcppdata__CDExp__
#define __hcppdata__CDExp__

#include "CD.h"

namespace CD {
    
    class CDRawData;
    
    class CDExp : public Object{
      
    public:
        CDExp(void) ;
        
        virtual ~CDExp(void);
        
        virtual Value * sql(const char * prefix,const char * suffix);
        
        virtual bool result(CDRawData * rawData);
        
        
        // and
        virtual CDExp * a(CDExp * exp);
        // or
        virtual CDExp * o(CDExp * exp);
        // not
        virtual CDExp * n();
      
        DEC_CLASS
    };
}

#endif /* defined(__hcppdata__CDExp__) */
