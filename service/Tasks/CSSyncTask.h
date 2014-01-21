//
//  CSSyncTask.h
//  hcppservice
//
//  Created by zhang hailong on 13-1-25.
//  Copyright (c) 2013年 9vteam. All rights reserved.
//

#ifndef __hcppservice__CSSyncTask__
#define __hcppservice__CSSyncTask__

#include "CSTask.h"

namespace CS {
    
    class CSSyncTask : public CSTask{
    public:
        
        CSSyncTask(void);
        
        virtual ~CSSyncTask(void);
        
        DEC_CLASS
    
    };
}

#endif /* defined(__hcppservice__CSSyncTask__) */
