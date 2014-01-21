//
//  CDCursor.cpp
//  hcppdata
//
//  Created by zhang hailong on 12-12-21.
//  Copyright (c) 2012年 9vteam. All rights reserved.
//

#include "hconfig.h"
#include "CDCursor.h"


namespace CD {
    
    IMP_CLASS(CDCursor, Object)
    
    CDCursor::CDCursor(void){
        
    }
    
    CDCursor::~CDCursor(void){
        
    }
    
    bool CDCursor::next(){
        return false;
    }
    
    void CDCursor::close(){
        
    }
    
    CDID CDCursor::rawId(){
        return 0;
    }
    
    Dictionary * CDCursor::values(){
        return NULL;
    }
}