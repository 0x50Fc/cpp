//
//  CDSqlitDataStorage.h
//  hcppdata
//
//  Created by zhang hailong on 12-12-25.
//  Copyright (c) 2012年 9vteam. All rights reserved.
//

#ifndef __hcppdata__CDSqlitDataStorage__
#define __hcppdata__CDSqlitDataStorage__

#include "CDDataStorage.h"

struct sqlite3;

namespace CD {
    
    class CDSqlitDataStorage : public CDDataStorage{
      
    public:
        
        CDSqlitDataStorage(void);
        
        CDSqlitDataStorage(const char * dbPath);
        
        virtual ~CDSqlitDataStorage(void);
        
        virtual void beginTransaction();
        
        virtual void commentTransaction();
        
        virtual void rerollTransaction();
        
        virtual void registerEntity(CDDataEntity * dataEntity);
        
        virtual void remove(CDDataEntity * dataEntity,CDID rawId);
        
        virtual CDID insert(CDDataEntity * dataEntity,Dictionary * values);
        
        virtual void update(CDDataEntity * dataEntity,CDID rawId,Dictionary * values);
        
        virtual Dictionary * get(CDDataEntity * dataEntity,CDID rawId);
        
        virtual CDCursor * query(CDFetchRequest * fetchRequest);
        
        virtual int errcode();
        
        virtual const char * errormsg();
        
        DEC_CLASS
        
    private:
        sqlite3 * _sqlite;
    };
}

#endif /* defined(__hcppdata__CDSqlitDataStorage__) */
