//
//  CDCursor.h
//  hcppdata
//
//  Created by zhang hailong on 12-12-21.
//  Copyright (c) 2012年 9vteam. All rights reserved.
//

#ifndef __hcppdata__CDCursor__
#define __hcppdata__CDCursor__

#include "CD.h"
#include "Dictionary.h"

namespace CD {

    class CDCursor : public Object{
      
    public:
        CDCursor(void);
        
        virtual ~CDCursor(void);
        
        virtual bool next();
        
        virtual void close();
        
        virtual CDID rawId();
        
        virtual Dictionary * values();
        
        DEC_CLASS
        
    };

}

#endif /* defined(__hcppdata__CDCursor__) */
