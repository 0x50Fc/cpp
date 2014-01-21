//
//  CDDataObject.h
//  hcppdata
//
//  Created by zhang hailong on 12-12-25.
//  Copyright (c) 2012年 9vteam. All rights reserved.
//

#ifndef __hcppdata__CDDataObject__
#define __hcppdata__CDDataObject__

#include "CDRawData.h"
#include "Dictionary.h"

namespace CD {
    
    class CDEntityContext;
    
    class CDDataObject : public Object{
    public:
        
        CDDataObject(void);
        
        virtual ~CDDataObject(void);
        
        virtual bool isFault();
        
        virtual Object * value(CDDataEntityField * field);
        
        virtual void setValue(CDDataEntityField * field,Object * value);
        
        virtual CDDataEntity * dataEntity();
        
        virtual Dictionary * toDictionary();
        
        virtual void fromDictionary(Dictionary * dictionary);
        
        virtual Object * copy();
        
        virtual Object * objectForKeyPath(const char * keyPath);
        
        virtual void setObjectForKeyPath(const char * keyPath,Object * value);
        
        virtual CDID rawId();
        
        DEC_CLASS

    private:
        virtual CDRawData * rawData();
        virtual void setRawData(CDRawData * rawData);
        friend class CDEntityContext;
    private:
        CDRawData * _rawData;
    };
}

#endif /* defined(__hcppdata__CDDataObject__) */
