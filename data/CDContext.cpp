//
//  CDContext.cpp
//  hcppdata
//
//  Created by zhang hailong on 12-12-25.
//  Copyright (c) 2012年 9vteam. All rights reserved.
//
#include "hconfig.h"
#include "CDContext.h"

namespace CD {
    
    int CDBatchSizeMin = 0;
    int CDBatchSizeNormal = 200;
    int CDBatchSizeMax = 500;
    
    
    IMP_CLASS(CDContext, Context)
    
    
    CDContext::CDContext(void){
        _dataModel = NULL;
        _dataStorage = NULL;
    }
    
    CDContext::CDContext(CDDataStorage * dataStorage,CDDataModel * dataModel){
        if(dataStorage){
            dataStorage->retain();
        }
        if(dataModel){
            dataModel->retain();
        }
        _dataStorage = dataStorage;
        _dataModel = dataModel;
        if(_dataModel && _dataStorage){
            CDDataEntityVectorIterator i = _dataModel->begin();
            while(i != _dataModel->end()){
                _dataStorage->registerEntity(*i);
                i++;
            }
        }
    }
    
    CDContext::~CDContext(void){
        if(_dataStorage){
            _dataStorage->release();
        }
        if(_dataModel){
            _dataModel->release();
        }
    }
    
    CDDataStorage * CDContext::dataStorage(){
        return _dataStorage;
    }
    
    CDDataModel * CDContext::dataModel(){
        return _dataModel;
    }
    
    bool CDContext::hasChanged(){
        std::map<CDDataEntity *,CDEntityContext *>::iterator i = _entityContexts.begin();
        while(i != _entityContexts.end()){
            if(i->second->hasChanged()){
                return true;
            }
            i++;
        }
        return false;
    }
    
    void CDContext::save(){
        std::map<CDDataEntity *,CDEntityContext *>::iterator i = _entityContexts.begin();
        while(i != _entityContexts.end()){
            CDEntityContext * entityContext = i->second;
            if(entityContext->hasChanged()){
                entityContext->save();
            }
            i++;
        }
    }
    
    CDDataObject * CDContext::insertDataObject(CDDataEntity * dataEntity){
        std::map<CDDataEntity *,CDEntityContext *>::iterator i = _entityContexts.find(dataEntity);
        CDEntityContext * entityContext = NULL;
        if(i == _entityContexts.end()){
            entityContext = new CDEntityContext(_dataStorage, _dataModel, dataEntity);
            _entityContexts[dataEntity] = entityContext;
        }
        else{
            entityContext = i->second;
        }
        return entityContext->insertDataObject();
    }
    
    CDDataObject * CDContext::dataObjectForRawId(CDDataEntity * dataEntity, CDID rawId){
        std::map<CDDataEntity *,CDEntityContext *>::iterator i = _entityContexts.find(dataEntity);
        CDEntityContext * entityContext = NULL;
        if(i == _entityContexts.end()){
            entityContext = new CDEntityContext(_dataStorage, _dataModel, dataEntity);
            _entityContexts[dataEntity] = entityContext;
        }
        else{
            entityContext = i->second;
        }
        return entityContext->dataObjectForRawId(rawId);

    }
    
    Array * CDContext::executeFetchRequest(CDFetchRequest * fetchRequest,int batchSize){
        CDDataEntity * dataEntity = fetchRequest->dataEntity();
        std::map<CDDataEntity *,CDEntityContext *>::iterator i = _entityContexts.find(dataEntity);
        CDEntityContext * entityContext = NULL;
        if(i == _entityContexts.end()){
            entityContext = new CDEntityContext(_dataStorage, _dataModel, dataEntity);
            _entityContexts[dataEntity] = entityContext;
        }
        else{
            entityContext = i->second;
        }
        return entityContext->executeFetchRequest(fetchRequest, batchSize);
    }
    
    CDFetchedResults * CDContext::executeFetchRequestResults(CDFetchRequest * fetchRequest,int batchSize){
        CDDataEntity * dataEntity = fetchRequest->dataEntity();
        std::map<CDDataEntity *,CDEntityContext *>::iterator i = _entityContexts.find(dataEntity);
        CDEntityContext * entityContext = NULL;
        if(i == _entityContexts.end()){
            entityContext = new CDEntityContext(_dataStorage, _dataModel, dataEntity);
            _entityContexts[dataEntity] = entityContext;
        }
        else{
            entityContext = i->second;
        }
        return entityContext->executeFetchRequestResults(fetchRequest, batchSize);
    }
    
    bool CDContext::deleteDataObject(CDDataObject * dataObject){
        CDDataEntity * dataEntity = dataObject->dataEntity();
        std::map<CDDataEntity *,CDEntityContext *>::iterator i = _entityContexts.find(dataEntity);
        CDEntityContext * entityContext = NULL;
        if(i == _entityContexts.end()){
            CDEntityContext * entityContext = new CDEntityContext(_dataStorage, _dataModel, dataEntity);
            _entityContexts[dataEntity] = entityContext;
        }
        else{
            entityContext = i->second;
        }
        return entityContext->deleteDataObject(dataObject);
    }
    
    CDDataEntity * CDContext::dataEntity(const char * name){
        return _dataModel->dataEntity(name);
    }
    
}