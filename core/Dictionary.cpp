//
//  Dictionary.cpp
//  hcpp
//
//  Created by zhang hailong on 12-12-7.
//  Copyright (c) 2012年 hailong.org. All rights reserved.
//
#include "hconfig.h"
#include "Dictionary.h"

namespace HCPP {
    
    IMP_CLASS(Dictionary, Object)
    
    Dictionary::Dictionary(){
        
    }
    
    Dictionary::Dictionary(const char * key,Object * value,...){
        va_list ap;
        va_start(ap, value);
        _Dictionary(key, value, ap);
    }
    
    Dictionary::~Dictionary(){
        std::map<std::string,Object *>::iterator begin = _map.begin();
        while(begin != _map.end()){
            begin->second->release();
            begin ++;
        }
    }
    
    int Dictionary::count(){
        return _map.size();
    }
    
    void Dictionary::removeAllObjects(){
        std::map<std::string,Object *>::iterator begin = _map.begin();
        while(begin != _map.end()){
            begin->second->release();
            begin ++ ;
        }
        _map.clear();
    }
    
    Array * Dictionary::keys(){
        Value * keyValue;
        Array * keys = new Array();
        std::map<std::string,Object *>::iterator begin = _map.begin();
        while(begin != _map.end()){
            keyValue = new Value(begin->first.c_str());
            keys->addObject(keyValue);
            keyValue->release();
            begin ++;
        }
        return (Array *)keys->autorelease();
    }
    
    Object * Dictionary::objectForKey(const char * key){
        DictionaryIterator i = _map.find(std::string(key));
        return  i == _map.end() ? NULL : i->second;
    }
    
    void Dictionary::setObjectForKey(const char * key,Object * value){
        std::string sKey(key);
        Object * v = objectForKey(key);
        if(value){
            value->retain();
        }
        if(v){
            v->release();
        }
        if(value){
            _map[sKey] = value;
        }
        else if(v){
            _map.erase(sKey);
        }
    }
    
    void Dictionary::removeObjectForKey(const char * key){
        _map.erase(std::string(key));
    }
    
    void Dictionary::removeObject(Object * value){
        std::map<std::string,Object *>::iterator begin = _map.begin();
        while(begin != _map.end()){
            if(value == begin->second){
                _map.erase(begin);
                break;
            }
            begin ++;
        }
    }

    DictionaryIterator Dictionary::begin(){
        return _map.begin();
    }
    
    DictionaryIterator Dictionary::end(){
        return _map.end();
    }
    
    Object * Dictionary::objectForKeyPath(const char * keyPath){
        char * p = (char *)keyPath;
        int l =0;
        while( *p != '\0' ){
            if(*p == '.'){
                break;
            }
            p ++;
            l ++;
        }
        std::string key(keyPath,0,l);
        DictionaryIterator i = _map.find(key);
        Object * v =  i == _map.end() ? NULL : i->second;
        if(*p =='\0'){
            return v;
        }
        if(v){
            return v->objectForKeyPath(p +1);
        }
        return NULL;
    }
    
    void Dictionary::setObjectForKeyPath(const char * keyPath,Object * value){
        char * p = (char *)keyPath;
        int l =0;
        while( *p != '\0' ){
            if(*p == '.'){
                break;
            }
            p ++;
            l ++;
        }
        if(*p =='\0'){
            setObjectForKey(keyPath, value);
        }
        else{
            std::string key(keyPath,0,l);
            DictionaryIterator i = _map.find(key);
            Object * v=  i == _map.end() ? NULL: i->second;
            if(v){
                v->setObjectForKeyPath(p +1, value);
            }
        }
    }
    
    void Dictionary::_Dictionary(const char * key,Object * value,va_list va){
        const char * nextKey;
        Object * next = NULL;
        setObjectForKey(key, value);
        while((nextKey = va_arg(va, const char *))){
            if((next = va_arg(va, Object *))){
                setObjectForKey(nextKey, next);
            }
            else{
                break;
            }
        }
    }
    
    Dictionary * Dictionary::newDictionary(const char * key,Object * value,...){
        Dictionary * r = new Dictionary();
        va_list ap;
        va_start(ap, value);

        r->_Dictionary(key, value, ap);
        
        return (Dictionary *)r->autorelease();
    }
    
    Dictionary * Dictionary::newDictionary(){
        return (Dictionary *) (new Dictionary())->autorelease();
    }
    
    Object * Dictionary::copy(){
        Dictionary * d = new Dictionary();
        DictionaryIterator i = _map.begin();
        while(i != _map.end()){
            d->setObjectForKey(i->first.c_str(), i->second->copy());
            i++;
        }
        return (Dictionary *) d->autorelease();
    }
}

