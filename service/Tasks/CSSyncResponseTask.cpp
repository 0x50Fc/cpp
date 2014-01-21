//
//  CSSyncResponseTask.cpp
//  hcppservice
//
//  Created by zhang hailong on 13-1-25.
//  Copyright (c) 2013年 9vteam. All rights reserved.
//
#include "hconfig.h"
#include "CSSyncResponseTask.h"

using namespace HCPP;

namespace CS {
    
    IMP_CLASS(CSSyncResponseTask, CSTask)
    
    CSSyncResponseTask::CSSyncResponseTask(void){
        _body = NULL;
        _errorCode = 0;
        _continueSync = false;
    }
    
    CSSyncResponseTask::CSSyncResponseTask(Object * body){
        _errorCode = 0;
        if(body){
            body->retain();
        }
        _body = body;
    }
    
    CSSyncResponseTask::CSSyncResponseTask(int errorCode,const char * error){
        _body = NULL;
        _errorCode = errorCode;
        _error = error;
    }
    
    CSSyncResponseTask::~CSSyncResponseTask(void){
        if(_body){
            _body->release();
        }
    }
    
    Object * CSSyncResponseTask::body(){
        return _body;
    }
    
    int CSSyncResponseTask::errorCode(){
        return _errorCode;
    }
    
    const char * CSSyncResponseTask::error(){
        return _error.c_str();
    }
    
    bool CSSyncResponseTask::isContinueSync(){
        return _continueSync;
    }
    
    void CSSyncResponseTask::setContinueSync(bool continueSync){
        _continueSync = continueSync;
    }
    
    
}