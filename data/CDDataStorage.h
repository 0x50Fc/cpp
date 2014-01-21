//
//  CDDataStorage.h
//  hcppdata
//
//  Created by zhang hailong on 12-12-21.
//  Copyright (c) 2012年 9vteam. All rights reserved.
//

#ifndef __hcppdata__CDDataStorage__
#define __hcppdata__CDDataStorage__

#include "CD.h"
#include "Dictionary.h"
#include "CDDataEntity.h"
#include "CDCursor.h"
#include "CDFetchRequest.h"

namespace CD {
    

    class CDDataStorage : public Object{
      
    public:
        
        CDDataStorage(void);
        
        virtual ~CDDataStorage(void);
        
        virtual void beginTransaction();
        
        virtual void commentTransaction();
        
        virtual void rerollTransaction();
        
        virtual void registerEntity(CDDataEntity * dataEntity);
        
        virtual void remove(CDDataEntity * dataEntity,CDID rawId);
        
        virtual CDID insert(CDDataEntity * dataEntity,Dictionary * values);
        
        virtual void update(CDDataEntity * dataEntity,CDID rawId,Dictionary * values);
        
        virtual Dictionary * get(CDDataEntity * dataEntity,CDID rawId);
        
        virtual CDCursor * query(CDFetchRequest * fetchRequest);

        
        DEC_CLASS
    };
    
}

#endif /* defined(__hcppdata__CDDataStorage__) */
