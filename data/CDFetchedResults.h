//
//  CDFetchedResults.h
//  hcppdata
//
//  Created by zhang hailong on 12-12-25.
//  Copyright (c) 2012年 9vteam. All rights reserved.
//

#ifndef __hcppdata__CDFetchedResults__
#define __hcppdata__CDFetchedResults__

#include "CD.h"
#include "Array.h"
#include "CDFetchRequest.h"
#include "CDDataObject.h"

namespace CD {
    
    class CDFetchedResults;
    
    typedef void (Object:: * CDFetchedResultsDelegateOnDataObjectDeletedFun)(CDFetchedResults * fetchedResults, CDDataObject * dataObjecct);
    
    typedef void (Object:: * CDFetchedResultsDelegateOnDataObjectInsertedFun)(CDFetchedResults * fetchedResults,CDDataObject * dataObjecct);
    
    typedef void (Object:: * CDFetchedResultsDelegateOnDataObjectUpdatedFun)(CDFetchedResults * fetchedResults,CDDataObject * dataObjecct);
    
    typedef void (Object:: * CDFetchedResultsDelegateOnDataContentChangingFun)(CDFetchedResults * fetchedResults);
    
    typedef void (Object:: * CDFetchedResultsDelegateOnDataContentChangedFun)(CDFetchedResults * fetchedResults);
    
    struct CDFetchedResultsDelegate{
        Object * target;
        CDFetchedResultsDelegateOnDataObjectDeletedFun onDeleted;
        CDFetchedResultsDelegateOnDataObjectInsertedFun onInserted;
        CDFetchedResultsDelegateOnDataObjectUpdatedFun onUpdated;
        CDFetchedResultsDelegateOnDataContentChangingFun onChanging;
        CDFetchedResultsDelegateOnDataContentChangedFun onChanged;
    };
    
    extern CDFetchedResultsDelegate CDFetchedResultsDelegateNil;
    
    class CDFetchedResults : public Object{
      
    public:
        
        CDFetchedResults(void);
        
        virtual ~CDFetchedResults(void);
        
        virtual Array * dataObjects();
        
        virtual CDFetchRequest * fetchRequest();
        
        virtual CDFetchedResultsDelegate delegate();
        
        virtual void setDelegate(CDFetchedResultsDelegate delegate);
        
        DEC_CLASS
        
    private:
        CDFetchedResultsDelegate _delegate;
    };
}

#endif /* defined(__hcppdata__CDFetchedResults__) */
