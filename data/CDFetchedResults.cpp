//
//  CDFetchedResults.cpp
//  hcppdata
//
//  Created by zhang hailong on 12-12-25.
//  Copyright (c) 2012年 9vteam. All rights reserved.
//
#include "hconfig.h"
#include "CDFetchedResults.h"


namespace CD {
    
    
    CDFetchedResultsDelegate CDFetchedResultsDelegateNil = {
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    };
    
    IMP_CLASS(CDFetchedResults, Object)
    
    CDFetchedResults::CDFetchedResults(void){
        _delegate.target = NULL;
        _delegate.onDeleted = NULL;
        _delegate.onInserted = NULL;
        _delegate.onUpdated = NULL;
        _delegate.onChanging = NULL;
        _delegate.onChanged = NULL;
    }
    
    CDFetchedResults::~CDFetchedResults(void){

    }
    
    Array * CDFetchedResults::dataObjects(){
        return NULL;
    }
    
    CDFetchRequest * CDFetchedResults::fetchRequest(){
        return NULL;
    }
    
    CDFetchedResultsDelegate CDFetchedResults::delegate(){
        return _delegate;
    }
    
    void CDFetchedResults::setDelegate(CDFetchedResultsDelegate delegate){
        _delegate = delegate;
    }

}
