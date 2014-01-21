//
//  CDDataEntity.cpp
//  hcppdata
//
//  Created by zhang hailong on 12-12-21.
//  Copyright (c) 2012年 9vteam. All rights reserved.
//
#include "hconfig.h"
#include "CDDataEntity.h"

namespace CD {
    
    CDDataEntityField * CDDataEntityFieldFind(CDDataEntity * entity,const char * name){
        if(entity){
            for (int i = 0; i<entity->fieldCount; i++) {
                CDDataEntityField * field = entity->fields + i;
                if(strcmp(field->name,name) ==0){
                    return field;
                }
            }
        }
        return NULL;
    }
}
