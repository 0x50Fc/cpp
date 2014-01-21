//
//  CSMessageTask.h
//  hcppservice
//
//  Created by zhang hailong on 13-2-5.
//  Copyright (c) 2013年 9vteam. All rights reserved.
//

#ifndef __hcppservice__CSMessageTask__
#define __hcppservice__CSMessageTask__

#include "CSTask.h"

namespace CS {
    
    class CSMessageTask : public CSTask{
    public:
        
        CSMessageTask(void);
        
        virtual ~CSMessageTask(void);

        static CSMessageTask * newMessageTask(Object * config);
        
        DEC_CLASS
    };
}
#endif /* defined(__hcppservice__CSMessageTask__) */
