//
//  Array.cpp
//  hcpp3d
//
//  Created by Zhang Hailong on 12-11-26.
//  Copyright (c) 2012年 9vteam. All rights reserved.
//

#include "hconfig.h"
#include "Array.h"

namespace HCPP {
    
    IMP_CLASS(Array, Object)
    
    Array::Array(){
        
    }
    
    Array::Array(Array & array){
        _items = array._items;
        std::vector<Object *>::iterator begin = _items.begin();
        while(begin != _items.end()){
            (* begin)->retain();
            begin ++;
        }
    }
    
    Array::Array(Object * object,...){
        va_list ap;
        va_start(ap, object);
        _Array(object, ap);
    }
    
    Array::~Array(void){
        std::vector<Object *>::iterator begin = _items.begin();
        while(begin != _items.end()){
            (* begin)->release();
            begin ++;
        }
    }
    
    int Array::count(){
        return _items.size();
    }
    
    Object * Array::objectAtIndex(int index){
        return _items.at(index);
    }
    
    Object * Array::lastObject(){
        if(!_items.empty()){
            return (* (-- _items.end()));
        }
        return NULL;
    }
    
    void Array::addObject(Object * object){
        object->retain();
        _items.insert(_items.end(), object);
    }
    
    void Array::addArray(Array * array){
        ArrayIterator i = array->begin();
        while(i != array->end()){
            addObject((Object  *) * i);
            i++;
        }
    }
    
    void Array::insertObject(Object * object,int atIndex){
        object->retain();
        _items.insert(_items.begin() + atIndex, object);
    }
    
    void Array::removeObject(Object * object){
        std::vector<Object *>::iterator begin = _items.begin();
        while(begin != _items.end()){
            if(* begin == object){
                (* begin)->release();
                _items.erase(begin);
            }
            else{
                begin ++;
            }
        }
    }
    
    void Array::removeObjectAtIndex(int index){
        std::vector<Object *>::iterator at = _items.begin() + index;
        (* at)->release();
        _items.erase(at);
    }
    
    void Array::removeLastObject(){
        if(!_items.empty()){
            std::vector<Object *>::iterator at = _items.end() - 1;
            (* at)->release();
            _items.erase(at);
        }
    }
    
    void Array::removeAllObjects(){
        std::vector<Object *>::iterator begin = _items.begin();
        while(begin != _items.end()){
            (* begin)->release();
            begin ++;
        }
        _items.clear();
    }

    ArrayIterator Array::begin(){
        return _items.begin();
    }
    
    ArrayIterator Array::end(){
        return _items.end();
    }
    
    void Array::_Array(Object * object,va_list va){
        Object * next = NULL;
        object->retain();
        _items.insert(_items.end(), object);
        while((next = va_arg(va, Object *))){
            next->retain();
            _items.insert(_items.end(), next);
        }
    }
    
    
    Array * Array::newArray(){
        return (Array *) (new Array())->autorelease();
    }
    
    Array * Array::newArray(Object * object,...){
        Array * r = new Array();
        va_list va;
        va_start(va, object);
        r->_Array(object, va);
        return (Array *) r->autorelease();
    }
    
    ArrayIterator Array::erase(ArrayIterator i){
        (* i)->release();
        return _items.erase(i);
    }
    
    Object * Array::copy(){
        Array * a = new Array();
        ArrayIterator i = _items.begin();
        while(i != _items.end()){
            a->addObject((* i)->copy());
            i++;
        }
        return (Array *) a->autorelease();
    }
    
    Object * Array::objectForKey(const char * key){
        int index = atoi(key);
        if(index >=0 && index < _items.size()){
            return _items.at(index);
        }
        return Object::objectForKey(key);
    }

}

