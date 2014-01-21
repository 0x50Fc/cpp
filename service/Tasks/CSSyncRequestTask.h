//
//  CSSyncRequestTask.h
//  hcppservice
//
//  Created by zhang hailong on 13-1-25.
//  Copyright (c) 2013年 9vteam. All rights reserved.
//

#ifndef __hcppservice__CSSyncRequestTask__
#define __hcppservice__CSSyncRequestTask__

#include "CSAPITask.h"
#include "CSSyncTask.h"

namespace CS {
    
    class CSSyncRequestTask : public CSAPITask{
      
    public:
        
        CSSyncRequestTask(void);
        
        virtual ~CSSyncRequestTask(void);

        DEC_CLASS

    };
}

#endif /* defined(__hcppservice__CSSyncRequestTask__) */
