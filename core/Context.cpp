//
//  Context.cpp
//  hcpp
//
//  Created by zhang hailong on 12-12-20.
//  Copyright (c) 2012年 hailong.org. All rights reserved.
//

#include "hconfig.h"
#include "Context.h"

namespace HCPP {
    
    IMP_PROPERTY_BEGIN(Context)
    
    IMP_PROPERTY(rootContext, ValueTypeObject, &Context::rootContext, NULL)
    
    IMP_PROPERTY(parentContext, ValueTypeObject, &Context::parentContext, &Context::setParentContext)
    
    IMP_PROPERTY(config, ValueTypeObject, NULL, &Context::setConfig)
    
    IMP_PROPERTY_END(Context)
    
    IMP_CLASS_P(Context, Object)
    
    Context::Context(void){
        _parentContext = NULL;
        _rootContext = NULL;
    }
    
    Context::~Context(void){
        
    }
    
    Context * Context::rootContext(){
        return _rootContext;
    }
    
    Context * Context::parentContext(){
        return _parentContext;
    }
    
    void Context::setParentContext(Context * parentContext){
        _parentContext = parentContext;
        if(parentContext){
            _rootContext = parentContext->rootContext();
        }
        else{
            _rootContext = NULL;
        }
    }
    
    void Context::setConfig(Object * config){
        
    }
    
}

