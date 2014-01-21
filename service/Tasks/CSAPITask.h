//
//  CSAPITask.h
//  hcppservice
//
//  Created by zhang hailong on 12-12-26.
//  Copyright (c) 2012年 9vteam. All rights reserved.
//

#ifndef __hcppservice__CSAPITask__
#define __hcppservice__CSAPITask__

#include "CSHttpTask.h"

namespace CS {
    
    class CSAPITask : public CSHttpTask{
    public:
        
        CSAPITask(void);
        
        virtual ~CSAPITask(void);
        
        DEC_CLASS
    };
}

#endif /* defined(__hcppservice__CSAPITask__) */
