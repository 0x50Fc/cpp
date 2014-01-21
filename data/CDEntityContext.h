//
//  CDEntityContext.h
//  hcppdata
//
//  Created by zhang hailong on 12-12-25.
//  Copyright (c) 2012年 9vteam. All rights reserved.
//

#ifndef __hcppdata__CDEntityContext__
#define __hcppdata__CDEntityContext__

#include "CD.h"
#include "Array.h"
#include "CDDataStorage.h"
#include "CDDataModel.h"
#include "CDFetchedResults.h"
#include <vector>
#include <map>

namespace CD {
    
    class CDRawDataImpl;
    class CDFetchedResultsImpl;
    
    class CDEntityContext : public Object{
      
    public:
        CDEntityContext(void);
        
        CDEntityContext(CDDataStorage * dataStorage,CDDataModel * dataModel,CDDataEntity * dataEntity);
        
        virtual ~CDEntityContext(void);
        
        virtual CDDataStorage * dataStorage();
        
        virtual CDDataModel * dataModel();
        
        virtual bool hasChanged();
        
        virtual bool save();
        
        virtual CDDataObject * insertDataObject();
        
        virtual Array * executeFetchRequest(CDFetchRequest * fetchRequest,int batchSize);
        
        virtual CDFetchedResults * executeFetchRequestResults(CDFetchRequest * fetchRequest,int batchSize);
        
        virtual bool deleteDataObject(CDDataObject * dataObject);
        
        virtual CDDataObject * dataObjectForRawId(CDID rawId);
        
        DEC_CLASS
    private:
        virtual void removeRawData(CDRawDataImpl * rawData);
        virtual void removeFetchedResults(CDFetchedResultsImpl * fetchedResults);
        virtual CDDataObject * newDataObject(CDRawData * rawData);
        virtual void addUpdatedRawData(CDRawDataImpl * rawData);
        virtual void removeUpdatedRawData(CDRawDataImpl * rawData);
        friend class CDRawDataImpl;
        friend class CDFetchedResultsImpl;
    private:
        HCPP::Class * _dataObjectClass;
        CDDataEntity * _dataEntity;
        std::map<CDID,CDRawDataImpl *> _rawDatas;
        std::vector<CDFetchedResultsImpl *> _fetchedResults;
        Array * _insertedRawDatas;
        Array * _deletedRawDatas;
        Array * _updatedRawDatas;
        CDDataStorage * _dataStorage;
        CDDataModel * _dataModel;
    };
}

#endif /* defined(__hcppdata__CDEntityContext__) */
