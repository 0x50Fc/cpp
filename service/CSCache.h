//
//  CSCache.h
//  hcppservice
//
//  Created by zhang hailong on 12-12-26.
//  Copyright (c) 2012年 9vteam. All rights reserved.
//

#ifndef __hcppservice__CSCache__
#define __hcppservice__CSCache__

#include "CSContext.h"
#include "Dictionary.h"
#include <string>

namespace CS {
    
    enum CSCacheType{
        CSCacheTypeMem,CSCacheTypeStorage,CSCacheTypeTemp
    };
    
    class CSCache : public HCPP::Object{
    public:
        
        CSCache(void);
        
        CSCache(CSContext * context,CSCacheType type,const char * name);
        
        virtual ~CSCache(void);
        
        virtual HCPP::Object * objectForKey(const char * key);
        
        virtual void setObjectForKey(const char * key,HCPP::Object * value);
        
        virtual void removeForKey(const char * key);
        
        virtual Object * objectForKeyPath(const char * keyPath);
        
        virtual void setObjectForKeyPath(const char * keyPath,Object * value);
        
        virtual CSCacheType type();
        
        virtual void setType(CSCacheType type);
        
        DEC_CLASS
        
    private:
        CSContext * _context;
        HCPP::Dictionary * _content;
        CSCacheType _type;
        std::string _name;
    };
}

#endif /* defined(__hcppservice__CSCache__) */
