//
//  CSUserChangedTask.h
//  hcppservice
//
//  Created by zhang hailong on 13-2-25.
//  Copyright (c) 2013年 9vteam. All rights reserved.
//

#ifndef __hcppservice__CSUserChangedTask__
#define __hcppservice__CSUserChangedTask__

#include "CSMessageTask.h"

namespace CS {
    
    class CSUserChangedTask : public CSMessageTask{
    public:
        
        CSUserChangedTask(void);
        
        virtual ~CSUserChangedTask(void);
        
        DEC_CLASS
    };
}

#endif /* defined(__hcppservice__CSUserChangedTask__) */
