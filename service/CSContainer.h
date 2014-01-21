//
//  CSContainer.h
//  hcppservice
//
//  Created by zhang hailong on 12-12-20.
//  Copyright (c) 2012年 9vteam. All rights reserved.
//

#ifndef __hcppservice__CSContainer__
#define __hcppservice__CSContainer__

#include "CSService.h"
#include "CSContext.h"

#include <vector>

namespace CS {
    
    class CSContainer : public HCPP::Object{
      
    public:
        
        CSContainer(void) ;
        
        virtual ~CSContainer(void);
        
        virtual void addTaskType(HCPP::Class * taskType);
        
        virtual void removeTaskType(HCPP::Class * taskType);
        
        virtual bool isInstance();
        
        virtual CSService * instance();
        
        virtual HCPP::Object * config();
        
        virtual void setConfig(HCPP::Object * config);
        
        virtual bool isInherit();
        
        virtual void setInherit(bool inherit);
        
        virtual HCPP::Class * instanceClass();
        
        virtual void setInstanceClass(HCPP::Class * instanceClass);
        
        virtual CSContext * context();
        
        virtual void setContext(CSContext * context);
        
        virtual bool hasTaskType(HCPP::Class * taskType);
        
        virtual void removeInstance();
        
        DEC_CLASS
        
    private:
        std::vector<HCPP::Class *> _taskTypes;
        CSService * _instance;
        HCPP::Object * _config;
        bool _inherit;
        HCPP::Class * _instanceClass;
        CSContext * _context;
    };
}

#endif /* defined(__hcppservice__CSContainer__) */
