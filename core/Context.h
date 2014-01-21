//
//  Context.h
//  hcpp
//
//  Created by zhang hailong on 12-12-20.
//  Copyright (c) 2012年 hailong.org. All rights reserved.
//

#ifndef __hcpp__Context__
#define __hcpp__Context__

#include "Object.h"


namespace HCPP {
    
   
    
    class Context : public Object{
        
    public:
        
        Context(void);
        
        virtual ~Context(void);
        
        virtual Context * rootContext();
        
        virtual Context * parentContext();
        
        virtual void setParentContext(Context * parentContext);
        
        virtual void setConfig(Object * config);
        
        DEC_CLASS
    private:
        Context * _rootContext;
        Context * _parentContext;
    };
    
}



#endif /* defined(__hcpp__Context__) */
