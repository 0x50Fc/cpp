//
//  CDDataEntity.h
//  hcppdata
//
//  Created by zhang hailong on 12-12-21.
//  Copyright (c) 2012年 9vteam. All rights reserved.
//

#ifndef __hcppdata__CDDataEntity__
#define __hcppdata__CDDataEntity__

#include "CD.h"

namespace CD {
    
#define DEC_CDENTITY(name)    extern CD::CDDataEntity CDE_##name;
    
#define CDENTITY_NS(name,ns)        (&ns::CDE_##name)
    
#define CDENTITY(name)              (&CDE_##name)
    
#define CDENTITY_FIELD(name,index)        (&CDE_##name.fields[index])
    
#define IMP_CDENTITY(name,fields,fieldCount,indexes,indexCount)    CD::CDDataEntity CDE_##name = {#name,fields,fieldCount,indexes,indexCount};

#define IMP_CDENTITY_FIELD_BEGIN(name)  CD::CDDataEntityField CDE_##name##_FIELDS[] = {
    
#define IMP_CDENTITY_FIELD(name,valueType,length)   {#name,valueType,length},
    
#define IMP_CDENTITY_FIELDD(name,valueType)   IMP_CDENTITY_FIELD(name,valueType,0)
    
#define IMP_CDENTITY_FIELD_END(name)    };
    
#define IMP_CDENTITY_FIELD_AT(name,index)  (&CDE_##name##_FIELDS[index])
    
#define IMP_CDENTITY_INDEX_BEGIN(name)  CD::CDDataEntityIndex CDE_##name##_INDEXES[] = {

#define IMP_CDENTITY_INDEX(name,type,field) {#name,type,field},
    
#define IMP_CDENTITY_INDEX_END(name)    };
    
#define IMP_CDENTITY_F(name)    IMP_CDENTITY(name,CDE_##name##_FIELDS,sizeof(CDE_##name##_FIELDS) / sizeof(CDDataEntityField),NULL,0)
    
#define IMP_CDENTITY_F_I(name)    IMP_CDENTITY(name,CDE_##name##_FIELDS,sizeof(CDE_##name##_FIELDS) / sizeof(CDDataEntityField),CDE_##name##_INDEXES,sizeof(CDE_##name##_INDEXES) / sizeof(CDDataEntityIndex))

    
    struct CDDataEntityField{
        const char * const name;
        ValueType const valueType;
        int const length;
    };
    
    enum CDDataEntityIndexType{
        CDDataEntityIndexTypeASC,CDDataEntityIndexTypeDESC
    };
    
    struct CDDataEntityIndex{
        const char * const name;
        CDDataEntityIndexType const type;
        CDDataEntityField * const field;
    };
    
    struct CDDataEntity{
        const char * const name;
        CDDataEntityField * const fields;
        int const fieldCount;
        CDDataEntityIndex * const indexes;
        int const indexCount;
    };
    
    CDDataEntityField * CDDataEntityFieldFind(CDDataEntity * entity,const char * name);
    
}

#endif /* defined(__hcppdata__CDDataEntity__) */
