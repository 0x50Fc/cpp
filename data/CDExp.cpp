//
//  CDExp.cpp
//  hcppdata
//
//  Created by zhang hailong on 12-12-21.
//  Copyright (c) 2012年 9vteam. All rights reserved.
//

#include "hconfig.h"
#include "CDExp.h"

#include "CDExpAnd.h"
#include "CDExpOr.h"
#include "CDExpNot.h"

namespace CD {
    
    IMP_CLASS(CDExp, Object)
    
    CDExp::CDExp(void) {
        
    }
    
    CDExp::~CDExp(void){
        
    }
    
    Value * CDExp::sql(const char * prefix,const char * suffix){
        return NULL;
    }
    
    bool CDExp::result(CDRawData * rawData){
        return false;
    }
    
    // and
    CDExp * CDExp::a(CDExp * exp){
        return (CDExp *)(new CDExpAnd(this,exp))->autorelease();
    }
    // or
    CDExp * CDExp::o(CDExp * exp){
        return (CDExp *)(new CDExpOr(this,exp))->autorelease();
    }
    // not
    CDExp * CDExp::n(){
        return (CDExp *)(new CDExpNot(this))->autorelease();
    }
}

