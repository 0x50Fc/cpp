//
//  Dictionary.h
//  hcpp
//
//  Created by zhang hailong on 12-12-7.
//  Copyright (c) 2012年 hailong.org. All rights reserved.
//

#ifndef HCPP__Dictionary__
#define HCPP__Dictionary__

#include "Object.h"
#include "Array.h"
#include "Value.h"
#include <map>
#include <string>

namespace HCPP {
    
    typedef std::map<std::string,Object *>::iterator DictionaryIterator;
    
    class Dictionary : public Object{
        
    public :
        
        Dictionary(void);
        
        Dictionary(const char * key,Object * value,...);
        
        virtual ~Dictionary(void);
        
        int count();
        
        Array * keys();
        
        virtual Object * objectForKey(const char * key);
        
        virtual void setObjectForKey(const char * key,Object * value);
        
        void removeObjectForKey(const char * key);
        
        void removeObject(Object * value);
        
        void removeAllObjects();
        
        DictionaryIterator begin();
        
        DictionaryIterator end();
        
        virtual Object * objectForKeyPath(const char * keyPath);
        
        virtual void setObjectForKeyPath(const char * keyPath,Object * value);
        
        static Dictionary * newDictionary(const char * key,Object * value,...);
        
        static Dictionary * newDictionary();
        
        
        virtual Object * copy();
        
        DEC_CLASS
        
    protected:
        void _Dictionary(const char * key,Object * value,va_list va);
    private:
        std::map<std::string,Object *> _map;
    };
    
}

#endif /* defined(__hcpp__Dictionary__) */
