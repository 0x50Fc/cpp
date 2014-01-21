//
//  CDContext.h
//  hcppdata
//
//  Created by zhang hailong on 12-12-25.
//  Copyright (c) 2012年 9vteam. All rights reserved.
//

#ifndef __hcppdata__CDContext__
#define __hcppdata__CDContext__

#include "CD.h"
#include "Context.h"
#include "CDDataStorage.h"
#include "CDDataModel.h"
#include "CDEntityContext.h"

#include <map>
namespace CD {
    
    extern int CDBatchSizeMin;
    extern int CDBatchSizeNormal;
    extern int CDBatchSizeMax;
    
    class CDContext : public Context{
    public:
        
        CDContext(void);
        
        CDContext(CDDataStorage * dataStorage,CDDataModel * dataModel);
        
        virtual ~CDContext(void);
    
        virtual CDDataStorage * dataStorage();
        
        virtual CDDataModel * dataModel();
        
        virtual bool hasChanged();
        
        virtual void save();
        
        virtual CDDataObject * insertDataObject(CDDataEntity * dataEntity);
        
        virtual Array * executeFetchRequest(CDFetchRequest * fetchRequest,int batchSize);
        
        virtual CDFetchedResults * executeFetchRequestResults(CDFetchRequest * fetchRequest,int batchSize);
        
        virtual bool deleteDataObject(CDDataObject * dataObject);
        
        virtual CDDataEntity * dataEntity(const char * name);
        
        virtual CDDataObject * dataObjectForRawId(CDDataEntity * dataEntity, CDID rawId);
        
        DEC_CLASS
    private:
        std::map<CDDataEntity *,CDEntityContext *> _entityContexts;
        CDDataStorage * _dataStorage;
        CDDataModel * _dataModel;
    };
}

#endif /* defined(__hcppdata__CDContext__) */
