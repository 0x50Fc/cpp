//
//  CDDataModel.h
//  hcppdata
//
//  Created by zhang hailong on 12-12-25.
//  Copyright (c) 2012年 9vteam. All rights reserved.
//

#ifndef __hcppdata__CDDataModel__
#define __hcppdata__CDDataModel__

#include "CDDataObject.h"
#include "CDDataEntity.h"

#include <map>
#include <vector>
#include <string>

namespace CD {
    
    typedef std::vector<CDDataEntity *>::iterator CDDataEntityVectorIterator;
    
    class CDDataModel : public Object{
      
    public:
        
        CDDataModel(void);
        
        virtual ~CDDataModel(void);
        
        virtual void addDataEntity(CDDataEntity * dataEntity,HCPP::Class * objectClass);
        
        virtual HCPP::Class * dataObjectClass(CDDataEntity * dataEntity);
        
        virtual CDDataEntityVectorIterator begin();
        
        virtual CDDataEntityVectorIterator end();
        
        virtual CDDataEntity * dataEntity(const char * name);
        
        DEC_CLASS
        
    private:
        std::map<CDDataEntity *,HCPP::Class *> _dataObjectClasss;
        std::vector<CDDataEntity *> _dataEntitys;
        std::map<std::string,CDDataEntity *> _dataEntitysMap;
    };
}

#endif /* defined(__hcppdata__CDDataModel__) */
