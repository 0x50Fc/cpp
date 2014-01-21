//
//  CSSyncResponseTask.h
//  hcppservice
//
//  Created by zhang hailong on 13-1-25.
//  Copyright (c) 2013年 9vteam. All rights reserved.
//

#ifndef __hcppservice__CSSyncResponseTask__
#define __hcppservice__CSSyncResponseTask__

#include "CSTask.h"

#include <string>

namespace CS {
    
    class CSSyncResponseTask : public CSTask{
    public:
        CSSyncResponseTask(void);
        
        CSSyncResponseTask(Object * body);
        
        CSSyncResponseTask(int errorCode,const char * error);
        
        virtual ~CSSyncResponseTask(void);
        
        virtual HCPP::Object * body();
        
        virtual int errorCode();
        
        virtual const char * error();
        
        virtual bool isContinueSync();
        
        virtual void setContinueSync(bool continueSync);
        
        DEC_CLASS
        
    private:
        std::string _error;
        int _errorCode;
        HCPP::Object * _body;
        bool _continueSync;
    };
}

#endif /* defined(__hcppservice__CSSyncResponseTask__) */
