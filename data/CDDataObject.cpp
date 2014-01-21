//
//  CDDataObject.cpp
//  hcppdata
//
//  Created by zhang hailong on 12-12-25.
//  Copyright (c) 2012年 9vteam. All rights reserved.
//
#include "hconfig.h"
#include "CDDataObject.h"


namespace CD {
    
    IMP_CLASS(CDDataObject, Object)
    
    CDDataObject::CDDataObject(void){
        _rawData = NULL;
    }
    
    CDDataObject::~CDDataObject(void){
        if(_rawData){
            _rawData->release();
        }
    }
    
    bool CDDataObject::isFault(){
        return _rawData == NULL || _rawData->isDeleted();
    }
    
    Object * CDDataObject::value(CDDataEntityField * field){
        if(_rawData){
            return _rawData->value(field);
        }
        return NULL;
    }
    
    void CDDataObject::setValue(CDDataEntityField * field,Object * value){
        if(_rawData){
            _rawData->setValue(field, value);
        }
    }
    
    CDRawData * CDDataObject::rawData(){
        return _rawData;
    }
    
    void CDDataObject::setRawData(CDRawData * rawData){
        if(rawData){
            rawData->retain();
        }
        if(_rawData){
            _rawData->release();
        }
        _rawData = rawData;
    }
    
    CDDataEntity * CDDataObject::dataEntity(){
        if(_rawData){
            return _rawData->dataEntity();
        }
        return NULL;
    }
    
    Dictionary * CDDataObject::toDictionary(){
        Dictionary * dict = Dictionary::newDictionary();
        CDDataEntity * entity = dataEntity();
        CDDataEntityField * field;
        Object * v;
        if(entity){
            for(int i = 0;i<entity->fieldCount;i++){
                field = entity->fields + i;
                v = value(field);
                if(v){
                    dict->setObjectForKey(field->name, v);
                }
            }
        }
        return dict;
    }
    
    void CDDataObject::fromDictionary(Dictionary * dictionary){
        CDDataEntity * entity = dataEntity();
        CDDataEntityField * field;
        Object * v;
        if(entity && dictionary){
            for(int i = 0;i<entity->fieldCount;i++){
                field = entity->fields + i;
                v = dictionary->objectForKey(field->name);
                if(v){
                    setValue(field, v);
                }
            }
        }
    }
    
    Object * CDDataObject::objectForKeyPath(const char * keyPath){
        Object * v = NULL;
        char * p = (char *)keyPath;
        int l =0;
        while( *p != '\0' ){
            if(*p == '.'){
                break;
            }
            p ++;
            l ++;
        }
        
        std::string sKey = std::string(keyPath,0,l);
        
        Property * prop = getProperty(sKey.c_str());
        
        if(prop){
            v = getPropertyValue(prop);
        }
        else{
            CDDataEntity * entity = dataEntity();
            CDDataEntityField * field = CDDataEntityFieldFind(entity, sKey.c_str());
            if(field){
                v = value(field);
            }
        }
        
        if(*p =='\0'){
            return v;
        }
        if(v){
            return v->objectForKeyPath(p +1);
        }
        
        return NULL;
    }
    
    void CDDataObject::setObjectForKeyPath(const char * keyPath,Object * value){
        char * p = (char *)keyPath;
        int l =0;
        while( *p != '\0' ){
            if(*p == '.'){
                break;
            }
            p ++ ;
            l ++;
        }
        
        if(*p =='\0'){
            Property * prop = getProperty(keyPath);
            if(prop){
                setPropertyValue(prop, value);
            }
            else{
                CDDataEntityField * field = CDDataEntityFieldFind(dataEntity(), keyPath);
                if(field){
                    setValue(field, value);
                }
            }
        }
        else{
            std::string sKey = std::string(keyPath,0,l);
            Property * prop = getProperty(sKey.c_str());
            if(prop){
                Object * v = getPropertyValue(prop);
                if(v){
                    v->setObjectForKeyPath(p +1, value);
                }
            }
            else{
                CDDataEntityField * field = CDDataEntityFieldFind(dataEntity(), keyPath);
                if(field){
                    Object * v =  CDDataObject::value(field);
                    if(v){
                        v->setObjectForKeyPath(p + 1, value);
                    }
                }
            }
        }
    }
    
    CDID CDDataObject::rawId(){
        return rawData()->rawId();
    }
    
    Object * CDDataObject::copy(){
        return toDictionary();
    }
}

