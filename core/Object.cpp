//
//  Object.cpp
//  hcpp3d
//
//  Created by Zhang Hailong on 12-11-26.
//  Copyright (c) 2012年 9vteam. All rights reserved.
//

#include "hconfig.h"
#include "hthread.h"
#include "hlog.h"
#include "hstr.h"
#include "Object.h"
#include "Value.h"
#include "Array.h"
#include "Dictionary.h"
#include "hbase64.h"
#include "hlist.h"

#include <stack>
#include <vector>
#include <map>
#include <string>



namespace HCPP {
    
    IMP_VALUETYPE(String,const char *)
    IMP_VALUETYPE(Integer,int)
    IMP_VALUETYPE(Int64,long long)
    IMP_VALUETYPE(Float,float)
    IMP_VALUETYPE(Double,double)
    IMP_VALUETYPE(Boolean,bool)
    IMP_VALUETYPE(Bytes,char *)
    IMP_VALUETYPE(Object,Object *)
    IMP_VALUETYPE(Ptr,void *)
    IMP_VALUETYPE_LENGTH(Void,void,0)
    
    struct _ObjectAfterCallerPoolInstall{
        void (* callback)(Object * target,Object::FUN_T selector,Object * userInfo,void * context);
        void * context;
    };
    
    
    typedef std::vector<Object *> ObjectAutoreleasePoolVector;
    
    typedef std::stack<ObjectAutoreleasePoolVector * > ObjectAutoreleasePool;
    
    static void ObjectAutoreleasePoolRelease(void * pool){
        ObjectAutoreleasePool * p = (ObjectAutoreleasePool *) pool;
        delete p;
    }
    
    static void ObjectAfterCallerPoolRelease(void * pool){
        _ObjectAfterCallerPoolInstall * p = (_ObjectAfterCallerPoolInstall *) pool;
        delete p;
    }
    
    
    static hthread_key_t gObjectAutoreleasePoolKey = NULL;
    static hthread_key_t gObjectAfterCallerObjectKey = NULL;
    
    static std::map<std::string,Class *> gClasss;

    static Object * Object_alloc(){
        return new Object();
    }
    
    Class Object::oClass = {NULL,"Object",Object_alloc,NULL,0,NULL,0};
    
    bool Object::_initialized = false;
    
    void Object::initialize(){
        if(!_initialized){ RegisterClass(&Object::oClass); _initialized = true; } 
    }
    
    Class * Object::clazz(){
        return &Object::oClass;
    }
    
    Object::Object(){
        _retainCount = 1;
    }
    
    Object::~Object(){
        
    }
    
    Object * Object::retain(){
        _retainCount ++;
        return this;
    }
    
    int Object::retainCount(){
        return _retainCount;
    }
    
    void Object::release(){
        assert(_retainCount >0);
        if(-- _retainCount == 0){
            delete this;
        }
    }
    
    Object * Object::autorelease(){
        ObjectAutoreleasePoolAddObject(this);
        return this;
    }
    
    bool Object::isKindOfClass(Class * clazz){
        Class * c = this->clazz();
        while(c != NULL){
            if(c == clazz){
                return true;
            }
            c = c->superClass;
        }
        return false;
    }
    
    bool Object::hasProperty(const char * property){
        Class * c = this->clazz();
        while(c != NULL){
            if(c->propertys){
                Property * p = c->propertys;
                int pc = c->propertysCount;
                
                while(pc >0){
                    
                    if(strcmp(p->name, property) ==0){
                        return true;
                    }
                    
                    pc --;
                    p ++;
                }

            }
            c = c->superClass;
        }
        return false;
    }
    
    Property * Object::getProperty(const char * property){
        Class * c = this->clazz();
        while(c != NULL){
            if(c->propertys){
                Property * p = c->propertys;
                int pc = c->propertysCount;
                
                while(pc >0){
                    
                    if(strcmp(p->name, property) ==0){
                        return p;
                    }
                    
                    pc --;
                    p ++;
                }
                
            }
            c = c->superClass;
        }
        return NULL;
    }
    
    Property * Object::getPropertyForKeyPath(const char * keyPath,Object ** atObject){
        
        char * p = (char *)keyPath;
        int l =0;
        while( *p != '\0' ){
            if(*p == '.'){
                break;
            }
            p ++;
            l ++;
        }
        
        Property * prop = getProperty(std::string(keyPath,0,l).c_str());
        
        if(prop){
            
            if(*p == '\0'){
                if(atObject){
                    * atObject = this;
                }
                return prop;
            }
            else{
                Object * v = getPropertyValue(prop);
                if(v){
                    return v->getPropertyForKeyPath(p +1, atObject);
                }
            }
        }

        return NULL;
    }
    
    Object * Object::getPropertyValue(Property * property){
        if(property && property->getter){
            if(property->valueType == ValueTypeObject){
                return PropertyValueGet(this,property,Object *);
            }
            if(property->valueType == ValueTypeInteger){
                Value * v = new Value(PropertyValueGet(this,property,int));
                return v->autorelease();
            }
            if(property->valueType == ValueTypeInt64){
                Value * v = new Value(PropertyValueGet(this,property,long long));
                return v->autorelease();
            }
            if(property->valueType == ValueTypeFloat){
                Value * v = new Value(PropertyValueGet(this,property,float));
                return v->autorelease();
            }
            if(property->valueType == ValueTypeDouble){
                Value * v = new Value(PropertyValueGet(this,property,double));
                return v->autorelease();
            }
            if(property->valueType == ValueTypeBoolean){
                Value * v = new Value(PropertyValueGet(this,property,bool));
                return v->autorelease();
            }
            if(property->valueType == ValueTypeString){
                Value * v = new Value(PropertyValueGet(this, property, const char *));
                return v->autorelease();
            }
            if(property->valueType == ValueTypePtr){
                Value * v = new Value(PropertyValueGet(this, property, void *));
                return v->autorelease();
            }
        }
        return NULL;
    }
    
    void Object::setPropertyValue(Property * property,Object * value){
        if(property && property->setter){
            if(property->valueType == ValueTypeObject){
                PropertyValueSet(this,property,Object *,value);
            }
            else if(property->valueType == ValueTypeInteger){
                Value * v = (Value *) value;
                PropertyValueSet(this,property,int,v ? v->intValue() : 0);
            }
            else if(property->valueType == ValueTypeInt64){
                Value * v = (Value *) value;
                PropertyValueSet(this,property,long long,v ? v->int64Value() : 0);
            }
            else if(property->valueType == ValueTypeFloat){
                Value * v = (Value *) value;
                PropertyValueSet(this,property,float,v ? v->floatValue() : 0.0f);
            }
            else if(property->valueType == ValueTypeDouble){
                Value * v = (Value *) value;
                PropertyValueSet(this,property,double,v ? v->doubleValue(): 0.0);
            }
            else if(property->valueType == ValueTypeBoolean){
                Value * v = (Value *) value;
                PropertyValueSet(this,property,bool,v ? v->booleanValue() : false);
            }
            else if(property->valueType == ValueTypeString){
                Value * v = (Value *) value;
                PropertyValueSet(this, property, const char *, v->stringValue());
            }
            else if(property->valueType == ValueTypePtr){
                Value * v = (Value *) value;
                PropertyValueSet(this, property, void *, v->ptrValue());
            }
        }
    }
    
    Object * Object::objectForKey(const char * key){
        Property * prop = getProperty(key);
        if(prop){
            return getPropertyValue(prop);
        }
        return NULL;
    }
    
    void Object::setObjectForKey(const char * key,Object * value){
        Property * prop = getProperty(key);
        if(prop){
            setPropertyValue(prop, value);
        }
    }
    
    Object * Object::objectForKeyPath(const char * keyPath){
        char * p = (char *)keyPath;
        int l =0;
        while( *p != '\0' ){
            if(*p == '.'){
                break;
            }
            p ++;
            l ++;
        }
        
        Object * v = objectForKey(std::string(keyPath,0,l).c_str());
        
        if(*p =='\0'){
            return v;
        }
        if(v){
            return v->objectForKeyPath(p +1);
        }
        
        return NULL;
    }
    
    Invoke * Object::getInvoke(const char * invoke){
        Class * c = this->clazz();
        while(c != NULL){
            if(c->invokes){
                Invoke * i = c->invokes;
                int ic = c->invokesCount;
                
                while(ic >0){
                    
                    if(strcmp(i->name, invoke) ==0){
                        return i;
                    }
                    
                    ic --;
                    i ++;
                }
                
            }
            c = c->superClass;
        }
        return NULL;
    }
    
    Object * Object::invoke(Invoke * invoke){
        if(invoke && invoke->invoke){
            if(invoke->returnType == ValueTypeObject){
                return InvokeCall(this,invoke,Object *);
            }
            if(invoke->returnType == ValueTypeInteger){
                Value * v = new Value(InvokeCall(this,invoke,int));
                return v->autorelease();
            }
            if(invoke->returnType == ValueTypeFloat){
                Value * v = new Value(InvokeCall(this,invoke,float));
                return v->autorelease();
            }
            if(invoke->returnType == ValueTypeDouble){
                Value * v = new Value(InvokeCall(this,invoke,double));
                return v->autorelease();
            }
            if(invoke->returnType == ValueTypeBoolean){
                Value * v = new Value(InvokeCall(this,invoke,bool));
                return v->autorelease();
            }
            if(invoke->returnType == ValueTypeString){
                Value * v = new Value(InvokeCall(this,invoke,const char *));
                return v->autorelease();
            }
            if(invoke->returnType == ValueTypeInt64){
                Value * v = new Value(InvokeCall(this,invoke,long long));
                return v->autorelease();
            }
            if(invoke->returnType == ValueTypeVoid){
                InvokeCall(this, invoke, void);
                return NULL;
            }
        }
        return NULL;
    }
    
    Object * Object::invoke(const char * invoke){
        Invoke * i = getInvoke(invoke);
        if(i){
            return Object::invoke(i);
        }
        return NULL;
    }
    
    void Object::setObjectForKeyPath(const char * keyPath,Object * value){
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
            setObjectForKey(keyPath, value);
        }
        else{
            Object * v = objectForKey(std::string(keyPath,0,l).c_str());
            if(v){
                v->setObjectForKeyPath(p +1, value);
            }
        }

    }
    
    bool Object::keyPathHasPrefix(const char * keyPath,const char * key,...){
        int i = 0;
        va_list arg;
        va_start(arg, key);
        
        while(key){
            
            i = 0;
            
            while(keyPath[i] != '\0' && key[i] != '\0' && keyPath[i] != '.' && keyPath[i] == key[i]) i++;
            
            if(key[i] == '\0' && (keyPath[i] == '\0' || keyPath[i] == '.')){
                return true;
            }
            
            key = va_arg(arg, const char *);
        }
        
        return false;
    }

    Value * Object::toStringValue(){
        return Value::newValue(clazz()->name);
    }
    
    void Object::afterCaller(Object::FUN_T selector,Object * userInfo){
        ObjectAfterCallerPoolAdd(this, selector, userInfo);
    }
    
    void Object::afterCaller(Invoke * invoke,Object * userInfo){
        ObjectAfterCallerPoolAdd(this, invoke->invoke, userInfo);
    }
    
    void Object::afterCaller(const char * invoke,Object * userInfo){
        Invoke * i = getInvoke(invoke);
        if(i){
            ObjectAfterCallerPoolAdd(this, i->invoke, userInfo);
        }
    }
    
    static void ObjectCopyFill(Dictionary * data, Object * obj,Class * clazz){
        
        if(clazz->superClass){
            ObjectCopyFill(data,obj,clazz->superClass);
        }
        
        Property * prop = clazz->propertys;
        int count = clazz->propertysCount;
        while(count >0){
            
            if(prop->coder){
                Object * v = obj->getPropertyValue(prop);
                if(v){
                    data->setObjectForKey(prop->name, v);
                }
            }
            prop ++;
            count --;
        }
    }
    
    Object * Object::copy(){
        
        Dictionary * data = Dictionary::newDictionary();
        
        ObjectCopyFill(data,this,clazz());
        
        return data;
    }
    
    void ObjectAutoreleasePoolBegin(void){
        
        if(gObjectAutoreleasePoolKey == NULL){
             gObjectAutoreleasePoolKey = hthread_key_create(ObjectAutoreleasePoolRelease);
        }
        
        ObjectAutoreleasePool * pool = (ObjectAutoreleasePool *)hthread_key_value(gObjectAutoreleasePoolKey);
        if(pool == NULL){
            pool = new ObjectAutoreleasePool();
            hthread_key_value_set(gObjectAutoreleasePoolKey, pool);
        }
        ObjectAutoreleasePoolVector * poolVector = new ObjectAutoreleasePoolVector();
        //hlog("ObjectAutoreleasePoolBegin 0x%lx\n",(unsigned long)poolVector);
        pool->push(poolVector);
    }
    
    void ObjectAutoreleasePoolEnd(void){
        ObjectAutoreleasePool * pool = (ObjectAutoreleasePool *)hthread_key_value(gObjectAutoreleasePoolKey);
        if(pool && pool->size() >0 ){
            ObjectAutoreleasePoolVector * t = pool->top();
            ObjectAutoreleasePoolVector::iterator begin = t->begin();
            while(begin != t->end()){
                (* begin)->release();
                begin ++;
            }
            pool->pop();
            //hlog("ObjectAutoreleasePoolEnd 0x%lx\n",(unsigned long)t);
            delete t;
        }
    }
    
    void ObjectAutoreleasePoolAddObject(Object * obj){
        ObjectAutoreleasePool * pool = (ObjectAutoreleasePool *)hthread_key_value(gObjectAutoreleasePoolKey);
        if(pool && pool->size() >0 ){
            ObjectAutoreleasePoolVector * t = pool->top();
            t->insert(t->end(), obj);
        }
        else{
            hlog("not found ObjectAutoreleasePool \n");
        }
    }
    
        
    void RegisterClass(Class * clazz){
        gClasss[std::string(clazz->name)] = clazz;
    }
    
    Class * GetClass(const char * className){
        return gClasss[std::string(className)];
    }
    
    bool ClassIsInherit(Class * clazz,Class * ofClass){
        Class * pClass = clazz;
        
        if(!clazz){
            return false;
        }
        if(!ofClass){
            return false;
        }
        
        while(pClass){
            if(pClass == ofClass){
                return true;
            }
            pClass = pClass->superClass;
        }
        return false;
    }
    
    Property * GetProperty(Class * clazz,const char * property){
        Class * pClass = clazz;
        Property * prop;
        int i;
        
        while(pClass){
            
            for(i=0;i<pClass->propertysCount;i++){
                prop = pClass->propertys + i;
                if(strcmp(prop->name, property) ==0){
                    return prop;
                }
            }
            
            pClass = pClass->superClass;
        }
        
        return NULL;
    }
    
    Invoke * GetInvoke(Class * clazz,const char * invoke){
        Class * pClass = clazz;
        Invoke * inv;
        int i;
        
        while(pClass){
            
            for(i=0;i<pClass->invokesCount;i++){
                inv = pClass->invokes + i;
                if(strcmp(inv->name, invoke) ==0){
                    return inv;
                }
            }
            
            pClass = pClass->superClass;
        }
        
        return NULL;
    }
    
    
    static void ObjectAfterCallerPoolInstallCallback(Object * target,Object::FUN_T selector,Object * userInfo,void * context){
        ((target)->*((void (Object::*)(Object *))selector))(userInfo);
    }
    
    void ObjectAfterCallerPoolInstall(void){
        
        if(gObjectAfterCallerObjectKey == NULL){
            gObjectAfterCallerObjectKey = hthread_key_create(ObjectAfterCallerPoolRelease);
        }
        
        _ObjectAfterCallerPoolInstall * pool = (_ObjectAfterCallerPoolInstall *)hthread_key_value(gObjectAfterCallerObjectKey);
        if(pool == NULL){
            pool = new _ObjectAfterCallerPoolInstall();
            hthread_key_value_set(gObjectAfterCallerObjectKey, pool);
        }
        memset(pool, 0, sizeof(_ObjectAfterCallerPoolInstall));
        pool->callback = ObjectAfterCallerPoolInstallCallback;
    }
    
    void ObjectAfterCallerPoolInstall(void (*callback)(Object * target,Object::FUN_T selector,Object * userInfo,void * context), void * context){
        
        if(gObjectAfterCallerObjectKey == NULL){
            gObjectAfterCallerObjectKey = hthread_key_create(ObjectAfterCallerPoolRelease);
        }
        
        _ObjectAfterCallerPoolInstall * pool = (_ObjectAfterCallerPoolInstall *)hthread_key_value(gObjectAfterCallerObjectKey);
        if(pool == NULL){
            pool = new _ObjectAfterCallerPoolInstall();
            hthread_key_value_set(gObjectAfterCallerObjectKey, pool);
        }
        memset(pool, 0, sizeof(_ObjectAfterCallerPoolInstall));
        pool->callback = callback;
        pool->context = context;
    }
    
    void ObjectAfterCallerPoolAdd(Object * target,Object::FUN_T selector,Object * userInfo){
        _ObjectAfterCallerPoolInstall * pool = (_ObjectAfterCallerPoolInstall *)hthread_key_value(gObjectAfterCallerObjectKey);
        if(pool){
            (* pool->callback)(target,selector,userInfo,pool->context);
        }
        else{
            hlog("not found ObjectAfterCallerPool \n");
        }
    }
    
    
}
