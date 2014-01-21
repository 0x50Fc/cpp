//
//  CDFetchRequest.h
//  hcppdata
//
//  Created by zhang hailong on 12-12-21.
//  Copyright (c) 2012年 9vteam. All rights reserved.
//

#ifndef __hcppdata__CDFetchRequest__
#define __hcppdata__CDFetchRequest__

#include "CD.h"
#include "CDDataEntity.h"
#include "CDExp.h"
#include "Array.h"

#include <vector>

namespace CD {
    
    enum CDDataSortType{
        CDDataSortTypeASC,CDDataSortTypeDESC
    };
    
    struct CDDataSort{
        CDDataEntityField * field;
        CDDataSortType type;
    };
    
    class CDEntityContext;
    class CDFetchedResultsImpl;

    class CDFetchRequest : public Object{
      
    public:
        
        CDFetchRequest(void);
        
        virtual ~CDFetchRequest(void);
        
        virtual void setDataSorts(CDDataSort * dataSorts,int length);
        
        virtual CDDataSort * dataSorts(int * length);
        
        virtual CDDataEntity * dataEntity();
        
        virtual void setDataEntity(CDDataEntity * dataEntity);
        
        virtual int fetchLimit();
        
        virtual void setFetchLimit(int fetchLimit);
        
        virtual int fetchOffset();
        
        virtual void setFetchOffset(int fetchOffset);
        
        virtual CDExp * dataPredicate();
        
        virtual void setDataPredicate(CDExp * predicate);
        
        DEC_CLASS
        
    private:
        
        bool filter(CDRawData * rawData);
        
        void store(std::vector<CDRawData *>  & datas,std::vector<std::vector<CDRawData *>::iterator> & indexs);
        
        friend class CDEntityContext;
        friend class CDFetchedResultsImpl;
        
    private:
        CDDataEntity * _dataEntity;
        int _fetchLimit;
        int _fetchOffset;
        CDExp * _dataPredicate;
        CDDataSort * _dataSorts;
        int _dataSortLength;
    };
}

#endif /* defined(__hcppdata__CDFetchRequest__) */
