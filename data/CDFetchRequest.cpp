//
//  CDFetchRequest.cpp
//  hcppdata
//
//  Created by zhang hailong on 12-12-21.
//  Copyright (c) 2012年 9vteam. All rights reserved.
//

#include "hconfig.h"
#include "CDFetchRequest.h"

#include "CDField.h"

namespace CD {
    
    IMP_CLASS(CDFetchRequest, Object)
    
    
    CDFetchRequest::CDFetchRequest(void){
        _dataEntity = NULL;
        _fetchLimit = 0;
        _fetchOffset = 0;
        _dataPredicate = NULL;
        _dataSorts = NULL;
        _dataSortLength = 0;
    }
    
    CDFetchRequest::~CDFetchRequest(void){
        if(_dataPredicate){
            _dataPredicate->release();
        }
        if(_dataSorts){
            delete [] _dataSorts;
        }
    }
    

    void CDFetchRequest::setDataSorts(CDDataSort * dataSorts,int length){
        if(_dataSorts){
            delete [] _dataSorts;
            _dataSorts = NULL;
        }
        if(dataSorts && length >0){
            _dataSorts = new CDDataSort[length];
            memcpy(_dataSorts, dataSorts, sizeof(CDDataSort) * length);
            _dataSortLength = length;
        }
    }
    
    CDDataSort * CDFetchRequest::dataSorts(int * length){
        * length = _dataSortLength;
        return _dataSorts;
    }
    
    
    
    CDDataEntity * CDFetchRequest::dataEntity(){
        return _dataEntity;
    }
    
    void CDFetchRequest::setDataEntity(CDDataEntity * dataEntity){
        _dataEntity = dataEntity;
    }
    
    int CDFetchRequest::fetchLimit(){
        return _fetchLimit;
    }
    
    void CDFetchRequest::setFetchLimit(int fetchLimit){
        _fetchLimit = fetchLimit;
    }
    
    int CDFetchRequest::fetchOffset(){
        return _fetchOffset;
    }
    
    void CDFetchRequest::setFetchOffset(int fetchOffset){
        _fetchOffset = fetchOffset;
    }
    
    CDExp * CDFetchRequest::dataPredicate(){
        return _dataPredicate;
    }
    
    void CDFetchRequest::setDataPredicate(CDExp * predicate){
        if(predicate){
            predicate->retain();
        }
        if(_dataPredicate){
            _dataPredicate->release();
        }
        _dataPredicate = predicate;
    }
    
    bool CDFetchRequest::filter(CDRawData * rawData){
        if(_dataPredicate){
            return _dataPredicate->result(rawData);
        }
        return true;
    }
    
    void CDFetchRequest::store(std::vector<CDRawData *>  & datas,std::vector<std::vector<CDRawData *>::iterator> & indexs){
        
        std::vector<CDRawData *>::iterator i = datas.begin();
        
        while(i != datas.end()){
            
            CDRawData * data = * i;
            
            std::vector<std::vector<CDRawData *>::iterator>::iterator ii = indexs.begin();
            while(ii != indexs.end()){
                CDRawData * d = ** ii;
                double rs = 0.0;
                if(_dataSorts && _dataSortLength >0){
                    for(int j = 0;j<_dataSortLength;j++){
                        CDDataSort * dataSort = _dataSorts + j;
                        Value * v1 = (Value *)data->value(dataSort->field);
                        Value * v2 = (Value *)d->value(dataSort->field);
                        if(v1 != v2){
                            if(v1 == NULL){
                                rs = -1;
                            }
                            else if(v2 == NULL){
                                rs = 1;
                            }
                            else {
                                rs = v2->compare(v1);
                            }
                        }
                        if(rs != 0.0){
                            if(dataSort->type == CDDataSortTypeDESC){
                                rs = -rs;
                            }
                            break;
                        }
                    }
                }
                if(rs == 0.0){
                    rs = data->rawId() - d->rawId();
                }
                if(rs > 0.0){
                    break;
                }
                ii++;
            }
            indexs.insert(ii, i);
            
            i ++;
        }
        
    }
    

    
}