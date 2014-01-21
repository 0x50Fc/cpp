//
//  CDRawData.h
//  hcppdata
//
//  Created by zhang hailong on 12-12-21.
//  Copyright (c) 2012年 9vteam. All rights reserved.
//

#ifndef __hcppdata__CDRawData__
#define __hcppdata__CDRawData__

#include "CD.h"
#include "CDDataEntity.h"

namespace CD {
    
    
    class CDRawData : public Object{
    
    public:
        
        CDRawData(void);
        
        virtual ~CDRawData(void);
        
        virtual CDID rawId();
        
        virtual bool hasChange();
        
        virtual bool isDeleted();
        
        virtual bool isInserted();
    
        virtual Object * value(CDDataEntityField * field);
    
        virtual void setValue(CDDataEntityField * field,Object * value);
        
        virtual CDDataEntity * dataEntity();
        
        DEC_CLASS
    
    };
}

#endif /* defined(__hcppdata__CDRawData__) */
