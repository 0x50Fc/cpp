//
//  CSSystemAudioTask.h
//  hcppservice
//
//  Created by zhang hailong on 13-2-6.
//  Copyright (c) 2013年 9vteam. All rights reserved.
//

#ifndef __hcppservice__CSSystemAudioTask__
#define __hcppservice__CSSystemAudioTask__

#include "CSTask.h"

#include <string>

namespace CS {
    
    
    
    class CSSystemAudioTask : public CSTask{
        
    public:
       
        CSSystemAudioTask(void);
        
        virtual ~CSSystemAudioTask(void);
        
        virtual const char * audioKey();
    
        virtual void setAudioKey(const char * audioKey);
        
        DEC_CLASS
        
    private:
        std::string _audioKey;
    };
}

#endif /* defined(__hcppservice__CSSystemAudioTask__) */
