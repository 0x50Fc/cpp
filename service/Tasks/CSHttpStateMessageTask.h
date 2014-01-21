//
//  CSHttpStateMessageTask.h
//  hcppservice
//
//  Created by zhang hailong on 13-2-5.
//  Copyright (c) 2013年 9vteam. All rights reserved.
//

#ifndef __hcppservice__CSHttpStateMessageTask__
#define __hcppservice__CSHttpStateMessageTask__

#include "CSMessageTask.h"

namespace CS {
    
    enum CSHttpState{
        CSHttpStateNone,CSHttpStateConnected
    };
    
    class CSHttpStateMessageTask : public CSMessageTask{
    public:
        
        CSHttpStateMessageTask(void);
        
        CSHttpStateMessageTask(CSHttpState httpState);
        
        virtual ~CSHttpStateMessageTask(void);
        
        virtual CSHttpState httpState();
        
        
        static CSHttpStateMessageTask * newHttpStateMessageTask(CSHttpState httpState);
        
        DEC_CLASS
        
    private:
        CSHttpState _httpState;
    };
}

#endif /* defined(__hcppservice__CSHttpStateMessageTask__) */
