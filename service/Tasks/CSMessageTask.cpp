//
//  CSMessageTask.cpp
//  hcppservice
//
//  Created by zhang hailong on 13-2-5.
//  Copyright (c) 2013年 9vteam. All rights reserved.
//
#include "hconfig.h"
#include "CSMessageTask.h"
#include "Value.h"
#include "Dictionary.h"

using namespace HCPP;

namespace CS {
    
    IMP_CLASS(CSMessageTask, CSTask)
    
    CSMessageTask::CSMessageTask(void){
        
    }
    
    CSMessageTask::~CSMessageTask(void){
        
    }
    
    CSMessageTask * CSMessageTask::newMessageTask(Object * config){
        
        CSMessageTask * task = NULL;
        
        if(config){
            Value * v = (Value *) config->objectForKeyPath("class");
            if(v && v->stringValue()){
                Class * clazz = GetClass(v->stringValue());
                if(clazz && ClassIsInherit(clazz, &CSMessageTask::oClass)){
                    task = (CSMessageTask *) OBJ_ALLOC(clazz);
                    
                    if(config->isKindOfClass(&Dictionary::oClass)){
                        Dictionary * propertys = (Dictionary *) config;
                        if(propertys){
                            DictionaryIterator i = propertys->begin();
                            while(i != propertys->end()){
                                task->setObjectForKeyPath(i->first.c_str(), i->second);
                                i++;
                            }
                        }
                    }
                    
                    task->autorelease();
                }
            }
        }
        
        if(task == NULL){
            task = new CSMessageTask();
            task->autorelease();
        }
        
        return task;
    }
}
