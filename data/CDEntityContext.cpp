//
//  CDEntityContext.cpp
//  hcppdata
//
//  Created by zhang hailong on 12-12-25.
//  Copyright (c) 2012年 9vteam. All rights reserved.
//

#include "hconfig.h"
#include "CDEntityContext.h"
#include "Dictionary.h"
#include "hlog.h"

namespace CD {

    class CDRawDataImpl : public CDRawData{
        
    public:
        
        CDRawDataImpl(void);
        
        CDRawDataImpl(CDEntityContext * context,CDDataEntity * dataEntity,CDID rawId,Dictionary * values);
        
        virtual ~CDRawDataImpl(void);
        
        virtual CDID rawId();
        
        virtual bool hasChange();
        
        virtual bool isDeleted();
        
        virtual bool isInserted();
        
        virtual Object * value(CDDataEntityField * field);
        
        virtual void setValue(CDDataEntityField * field,Object * value);
        
        virtual void setRawId(CDID rawId);
        
        virtual void setDeleted(bool deleted);
        
        virtual void setInserted(bool inserted);
        
        virtual CDDataEntity * dataEntity();
        
        virtual void finishChanged();
        
        virtual Dictionary * values();
        
        DEC_CLASS
        
    private:
        CDEntityContext * _context;
        CDDataEntity * _dataEntity;
        CDID _rawId;
        Dictionary * _values;
        bool _isDeleted;
        bool _isInserted;
        bool _isUpdated;
    };
    
    struct CDFetchedResultsImplChangedIndex{
        int index;
        int state;
    };
    
    class CDFetchedResultsImpl : public CDFetchedResults{
    public:
        
        CDFetchedResultsImpl(void);
        
        CDFetchedResultsImpl(CDEntityContext * context,CDFetchRequest * fetchRequest);
        
        virtual ~CDFetchedResultsImpl(void);
        
        virtual Array * dataObjects();
        
        virtual CDFetchRequest * fetchRequest();
        
        virtual bool beginChanged(std::vector<CDRawDataImpl *> & dataVector,std::map<CDID, CDRawDataImpl *> & dataMap);
        
        virtual void endChanged();
        
        virtual CDDataObject * addDataObject(CDRawData * data);
        
        DEC_CLASS
        
    private:
        CDEntityContext * _context;
        CDFetchRequest * _fetchRequest;
        std::vector<CDRawData *> _datas;
        Array * _dataObjects;
        std::vector<CDFetchedResultsImplChangedIndex> _changeIndexs;
        std::vector<CDRawData *> _insertedDatas;
    };
    
    IMP_CLASS(CDRawDataImpl, CDRawData)
    
    IMP_CLASS(CDFetchedResultsImpl, CDFetchedResults)
    
    IMP_CLASS(CDEntityContext, Object)

    CDEntityContext::CDEntityContext(void){
        _insertedRawDatas = NULL;
        _deletedRawDatas = NULL;
        _updatedRawDatas = NULL;
        _dataStorage = NULL;
        _dataModel = NULL;
        _dataEntity = NULL;
        _dataObjectClass = NULL;
    }
    
    CDEntityContext::CDEntityContext(CDDataStorage * dataStorage,CDDataModel * dataModel,CDDataEntity * dataEntity){
        if(dataStorage){
            dataStorage->retain();
        }
        if(dataModel){
            dataModel->retain();
        }
        _dataStorage = dataStorage;
        _dataModel = dataModel;
        _insertedRawDatas = NULL;
        _deletedRawDatas = NULL;
        _updatedRawDatas = NULL;
        _dataEntity = dataEntity;
        _dataObjectClass = _dataModel->dataObjectClass(dataEntity);
    }
    
    CDEntityContext::~CDEntityContext(void){
        if(_insertedRawDatas){
            _insertedRawDatas->release();
        }
        if(_deletedRawDatas){
            _deletedRawDatas->release();
        }
        if(_updatedRawDatas){
            _updatedRawDatas->release();
        }
        if(_dataStorage){
            _dataStorage->release();
        }
        if(_dataModel){
            _dataModel->release();
        }
    }
    
    CDDataStorage * CDEntityContext::dataStorage(){
        return _dataStorage;
    }
    
    
    CDDataModel * CDEntityContext::dataModel(){
        return _dataModel;
    }

    bool CDEntityContext::hasChanged(){
        return (_insertedRawDatas && _insertedRawDatas->count() >0)
            || (_deletedRawDatas && _deletedRawDatas->count() >0)
            || (_updatedRawDatas && _updatedRawDatas->count() >0);
    }
    
    bool CDEntityContext::save(){
        
        std::vector<CDRawDataImpl *> dataVector;
        std::map<CDID, CDRawDataImpl *> dataMap;
        std::vector<CDFetchedResultsImpl *> results ;
        
        bool rs = true;
        
        _dataStorage->beginTransaction();
        
        if(_insertedRawDatas){
            ArrayIterator i = _insertedRawDatas->begin();
            while(i != _insertedRawDatas->end()){
                CDRawDataImpl * data = (CDRawDataImpl *) * i;
                if(data->isInserted()){
                    CDID rawId = _dataStorage->insert(data->dataEntity(), data->values());
                    if(rawId){
                        data->setRawId(rawId);
                    }
                    else{
                        rs = false;
                        break;
                        hlog("CDEntityContext::save insert data %s error",data->dataEntity()->name);
                    }
                    dataVector.insert(dataVector.end(), data);
                    dataMap[rawId] = data;
                }
                i++;
            }
        }
        
        if(!rs){
            _dataStorage->rerollTransaction();
            return rs;
        }
        
        if(_deletedRawDatas){
            ArrayIterator i = _deletedRawDatas->begin();
            while(i != _deletedRawDatas->end()){
                CDRawDataImpl * data = (CDRawDataImpl *) * i;
                if(data->isDeleted()){
                    _dataStorage->remove(data->dataEntity(), data->rawId());
                    dataVector.insert(dataVector.end(), data);
                    dataMap[data->rawId()] = data;
                }
                i++;
            }
        }
        
        if(_updatedRawDatas){
            ArrayIterator i = _updatedRawDatas->begin();
            while(i != _updatedRawDatas->end()){
                CDRawDataImpl * data = (CDRawDataImpl *) * i;
                if(data->hasChange()){
                    _dataStorage->update(data->dataEntity(), data->rawId(),data->values());
                    dataVector.insert(dataVector.end(), data);
                    dataMap[data->rawId()] = data;
                }
                i++;
            }
        }
        
        if(!rs){
            _dataStorage->rerollTransaction();
            return rs;
        }
        
        _dataStorage->commentTransaction();
        
        // todo DataFetchedResultsImpl
        
        
        
        if(_fetchedResults.size() >0){
            std::vector<CDFetchedResultsImpl *>::iterator i = _fetchedResults.begin();
            while(i != _fetchedResults.end()){
                CDFetchedResultsImpl * result = *i;
                if(result->beginChanged(dataVector, dataMap)){
                    results.insert(results.end(), result);
                }
                i++;
            }
        }
        
        {
            std::vector<CDRawDataImpl *>::iterator i = dataVector.begin();
            
            while(i != dataVector.end()){
                
                CDRawDataImpl * data = * i;
                
                if(data->isDeleted()){
                    _rawDatas.erase(data->rawId());
                    _deletedRawDatas->removeObject(data);
                }
                else if(data->isInserted()){
                    data->finishChanged();
                    _rawDatas[data->rawId()] = data;
                    _insertedRawDatas->removeObject(data);
                }
                else if(data->hasChange()){
                    data->finishChanged();
                    _updatedRawDatas->removeObject(data);
                }
                
                i++;
            }
        }
        
        {
            std::vector<CDFetchedResultsImpl *>::iterator i = results.begin();
            while(i != results.end()){
                
                (*i )->endChanged();
                
                i++;
            }
        }
        
        return rs;
    }
    
    CDDataObject * CDEntityContext::newDataObject(CDRawData * rawData){

        CDDataObject * obj = (CDDataObject *)OBJ_ALLOC(_dataObjectClass);
        if(obj){
            obj->setRawData(rawData);
            return (CDDataObject *)obj->autorelease();
        }
        else{
            hlog("CDEntityContext::newDataObject alloc DataObjectClass %s NULL",_dataObjectClass->name);
        }

        return NULL;
    }
    
    void CDEntityContext::removeRawData(CDRawDataImpl * rawData){
        if(_insertedRawDatas){
            _insertedRawDatas->removeObject(rawData);
        }
        _rawDatas.erase(rawData->rawId());
    }
    
    void CDEntityContext::removeFetchedResults(CDFetchedResultsImpl * fetchedResults){
        std::vector<CDFetchedResultsImpl *>::iterator i = _fetchedResults.begin();
        while(i != _fetchedResults.end()){
            if(fetchedResults == * i){
                i = _fetchedResults.erase(i);
            }
            else{
                i++;
            }
        }
    }
    
    CDDataObject * CDEntityContext::insertDataObject(){
        CDRawDataImpl * rawData = new CDRawDataImpl(this,_dataEntity,0,NULL);
        rawData->setInserted(true);
        if(_insertedRawDatas == NULL){
            _insertedRawDatas = new Array();
        }
        _insertedRawDatas->addObject(rawData);
        rawData->release();
        return newDataObject( rawData);
    }
    
    CDDataObject * CDEntityContext::dataObjectForRawId(CDID rawId){
        CDRawDataImpl * rawData = new CDRawDataImpl(this, _dataEntity, rawId, NULL);
        CDDataObject * dataObject = newDataObject(rawData);
        rawData->release();
        return dataObject;
    }
    
    Array * CDEntityContext::executeFetchRequest(CDFetchRequest * fetchRequest,int batchSize){
        Array * dataObjects = new Array();

        CDCursor * cursor = _dataStorage->query(fetchRequest);
        int index = 0;
        if(cursor){
            while(cursor->next()){
                CDID rawId = cursor->rawId();
                CDDataObject * dataObject = NULL;
                std::map<CDID,CDRawDataImpl *>::iterator i = _rawDatas.find(rawId);
                if(i == _rawDatas.end()){
                    CDRawDataImpl * rawData = new CDRawDataImpl(this, _dataEntity, rawId, index < batchSize ? cursor->values() : NULL);
                    dataObject = newDataObject(rawData);
                    _rawDatas[rawId] = rawData;
                    rawData->release();
                }
                else{
                    CDRawDataImpl * rawData = i->second;
                    dataObject = newDataObject( rawData);
                }
                dataObjects->addObject(dataObject);
                index ++;
            }
        }
        
        return (Array *)dataObjects->autorelease();
    }
    
    CDFetchedResults * CDEntityContext::executeFetchRequestResults(CDFetchRequest * fetchRequest,int batchSize){
        CDFetchedResultsImpl * results = new CDFetchedResultsImpl(this, fetchRequest);
        
        _fetchedResults.insert(_fetchedResults.end(), results);
        
        CDDataEntity * dataEntity = fetchRequest->dataEntity();

        CDCursor * cursor = _dataStorage->query(fetchRequest);
        int index = 0;
        if(cursor){
            while(cursor->next()){
                CDID rawId = cursor->rawId();
                std::map<CDID,CDRawDataImpl *>::iterator i = _rawDatas.find(rawId);
                if(i == _rawDatas.end()){
                    CDRawDataImpl * rawData = new CDRawDataImpl(this, dataEntity, rawId, index < batchSize ? cursor->values() : NULL);
                    results->addDataObject(rawData);
                    _rawDatas[rawId] = rawData;
                    rawData->release();
                }
                else{
                    CDRawDataImpl * rawData = i->second;
                    results->addDataObject(rawData);
                }
                index ++;
            }
        }
        
        return (CDFetchedResults * ) results->autorelease();
    }
    
    bool CDEntityContext::deleteDataObject(CDDataObject * dataObject){
        CDRawData * rawData = dataObject->rawData();
        
        if(rawData->isKindOfClass(&CDRawDataImpl::oClass)){
            ((CDRawDataImpl *)rawData)->setDeleted(true);
            if(_deletedRawDatas == NULL){
                _deletedRawDatas = new Array();
            }
            _deletedRawDatas->addObject(rawData);
            return true;
        }
        return false;
    }
    
    void CDEntityContext::addUpdatedRawData(CDRawDataImpl * rawData){
        if(_updatedRawDatas == NULL){
            _updatedRawDatas = new Array();
        }
        _updatedRawDatas->addObject(rawData);
    }
    
    void CDEntityContext::removeUpdatedRawData(CDRawDataImpl * rawData){
        if(_updatedRawDatas){
            _updatedRawDatas->removeObject(rawData);
        }
    }
    
    
    //CDRawDataImpl
    
    CDRawDataImpl::CDRawDataImpl(void){
        _context = NULL;
        _dataEntity = NULL;
        _rawId = 0;
        _values = NULL;
        _isDeleted = false;
        _isInserted = false;
        _isUpdated = false;
    }
    
    CDRawDataImpl::CDRawDataImpl(CDEntityContext * context,CDDataEntity * dataEntity,CDID rawId,Dictionary * values){
        if(values){
            values->retain();
        }
        _context = context;
        _dataEntity = dataEntity;
        _rawId = rawId;
        _values = values;
        _isDeleted = false;
        _isInserted = false;
        _isUpdated = false;
    }
    
    CDRawDataImpl::~CDRawDataImpl(void){
        if(_context){
            _context->removeRawData(this);
        }
        if(_values){
            _values->release();
        }
    }
    
    CDID CDRawDataImpl::rawId(){
        return _rawId;
    }
    
    bool CDRawDataImpl::hasChange(){
        return _isUpdated;
    }
    
    bool CDRawDataImpl::isDeleted(){
        return _isDeleted;
    }
    
    bool CDRawDataImpl::isInserted(){
        return _isInserted;
    }
    
    Object * CDRawDataImpl::value(CDDataEntityField * field){
        if(field && _context){
            Object * v = NULL;
            CDDataStorage * dataStorage = _context->dataStorage();
            if(_values == NULL && !_isInserted && !_isDeleted){
                _values = dataStorage->get(_dataEntity, _rawId);
                if(_values){
                    _values->retain();
                }
            }
            if(_values){
                v = _values->objectForKey(field->name);
            }
        
            return v;
        }
        return NULL;
    }
    
    void CDRawDataImpl::setValue(CDDataEntityField * field,Object * v){
        if(field && !_isDeleted && _context){
            if(_isInserted){
                if(_values == NULL){
                    _values = new Dictionary();
                }
                _values->setObjectForKey(field->name,v);
            }
            else if(!_isDeleted){
                if(_values == NULL){
                    _values = _context->dataStorage()->get(_dataEntity, _rawId);
                    if(_values){
                        _values->retain();
                    }
                }
                if(_values){
                    _values->setObjectForKey(field->name, v);
                }
                if(!_isUpdated){
                    _context->addUpdatedRawData(this);
                    _isUpdated = true;
                }
            }
        }
    }
    
    void CDRawDataImpl::setRawId(CDID rawId){
        _rawId = rawId;
    }
    
    void CDRawDataImpl::setDeleted(bool deleted){
        _isDeleted = deleted;
    }
    
    void CDRawDataImpl::setInserted(bool inserted){
        _isInserted = inserted;
    }
    
    CDDataEntity * CDRawDataImpl::dataEntity(){
        return _dataEntity;
    }
    
    void CDRawDataImpl::finishChanged(){
        if(_isInserted){
            _isInserted = false;
        }
        if(_isDeleted){
            if(_values){
                _values->release();
                _values = NULL;
            }
        }
        if(_isUpdated){
            _isUpdated = false;
        }
    }
    
    Dictionary * CDRawDataImpl::values(){
        return _values;
    }
    
    
    // CDFetchedResultsImpl
    
    CDFetchedResultsImpl::CDFetchedResultsImpl(void){
        _fetchRequest = NULL;
        _dataObjects = NULL;
        _context = NULL;
    }
    
    CDFetchedResultsImpl::CDFetchedResultsImpl(CDEntityContext * context,CDFetchRequest * fetchRequest){
        _context = context;
        _fetchRequest = (CDFetchRequest *)fetchRequest->retain();
        _dataObjects = NULL;
    }
    
    CDFetchedResultsImpl::~CDFetchedResultsImpl(void){
        if(_context){
            _context->removeFetchedResults(this);
        }
        if(_dataObjects){
            _dataObjects->release();
        }
        if(_fetchRequest){
            _fetchRequest->release();
        }
    }
    
    Array * CDFetchedResultsImpl::dataObjects(){
        return _dataObjects;
    }
    
    CDFetchRequest * CDFetchedResultsImpl::fetchRequest(){
        return _fetchRequest;
    }
    
    bool CDFetchedResultsImpl::beginChanged(std::vector<CDRawDataImpl *> & dataVector,std::map<CDID, CDRawDataImpl *> & dataMap){
        if(!_datas.empty()){
            for(int index = 0 ; index < _datas.size();index ++){
                CDRawData * data = _datas.at(index);
                if(dataMap.find(data->rawId()) != dataMap.end()){
                    CDFetchedResultsImplChangedIndex ci = {index,data->isDeleted()?1:2};
                    _changeIndexs.insert(_changeIndexs.end(), ci);
                }
            }
        }
        std::vector<CDRawDataImpl *>::iterator i = dataVector.begin();
        while(i != dataVector.end()){
            CDRawDataImpl * data = * i;
            if(data->isInserted() && _fetchRequest->filter(data)){
                _insertedDatas.insert(_insertedDatas.end(), data);
                data->retain();
            }
            i ++;
        }
        return _changeIndexs.size() > 0 || _insertedDatas.size() > 0;
    }
    
    void CDFetchedResultsImpl::endChanged(){
        CDFetchedResultsDelegate d = delegate();
        if(d.target && d.onChanging){
            (d.target->*d.onChanging)(this);
        }
        if(_changeIndexs.size() >0){
            std::vector<CDFetchedResultsImplChangedIndex>::iterator i = _changeIndexs.begin();
            int offset = 0;
            while(i != _changeIndexs.end()){
                CDFetchedResultsImplChangedIndex index = * i;
                int idx = index.index - offset;
                CDDataObject * dataObject = (CDDataObject *)_dataObjects->objectAtIndex(idx);
                if(index.state == 1){
                    if(d.target && d.onDeleted){
                        (d.target->*d.onDeleted)(this,dataObject);
                    }
                    _datas.erase(_datas.begin() + idx);
                    _dataObjects->removeObjectAtIndex(idx);
                    offset ++;
                }
                else{
                    if(d.target && d.onUpdated){
                        (d.target->*d.onUpdated)(this,dataObject);
                    }
                }
                i++;
            }
            _changeIndexs.clear();
        }
        if(_insertedDatas.size() >0){
            std::vector<CDRawData *>::iterator i = _insertedDatas.begin();
            while(i != _insertedDatas.end()){
                CDRawData * data = *i;
                CDDataObject * dataObject = addDataObject(data);
                data->release();
                if(d.target && d.onInserted){
                    (d.target->*d.onInserted)(this,dataObject);
                }
                i++;
            }
            _insertedDatas.clear();
        }
        
        int dataSortsLength = 0;
        
        if(_fetchRequest->dataSorts(&dataSortsLength) && dataSortsLength >0){
            
            std::vector<std::vector<CDRawData *>::iterator> indexs;
            
            _fetchRequest->store(_datas, indexs);
            
            std::vector<CDRawData *> nDatas;
            Array * nDataObjects = new Array();
            
            std::vector<std::vector<CDRawData *>::iterator>::iterator i = indexs.begin();
            
            while(i != indexs.end()){
                std::vector<CDRawData *>::iterator ii = *i;
                nDatas.insert(nDatas.end(), * ii);
                nDataObjects->addObject(_dataObjects->objectAtIndex(ii - _datas.begin()));
                i++;
            }
            
            _datas = nDatas;
            
            if(_dataObjects ){
                _dataObjects->release();
            }
            
            _dataObjects = nDataObjects;
            
        }

        if(d.target && d.onChanged){
            d.target->afterCaller((Object::FUN_T)d.onChanged, this);
        }
    }
    
    CDDataObject * CDFetchedResultsImpl::addDataObject(CDRawData * data){
        CDDataObject * dataObject = _context->newDataObject( data);
        
        _datas.insert(_datas.end(), data);
        
        if(_dataObjects == NULL){
            _dataObjects = new Array();
        }
        
        _dataObjects->addObject(dataObject);
        
        return dataObject;
    }
    
}