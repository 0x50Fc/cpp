//
//  Coder.cpp
//  hcpp
//
//  Created by zhang hailong on 12-12-11.
//  Copyright (c) 2012年 hailong.org. All rights reserved.
//

#include "Coder.h"

#include "hconfig.h"
#include "hlog.h"
#include "hstr.h"
#include "hbase64.h"
#include "hlist.h"
#include "hbuffer.h"
#include "md5.h"
#include <stack>
#include <vector>
#include <map>
#include <string>

#include "Array.h"
#include "Dictionary.h"
#include "Value.h"

#include "hjson.h"

#include "hlog.h"


namespace HCPP {
    
    static hany JSONCoderObjectNew(struct _hjson_t * json,InvokeTickDeclare){
        return Dictionary::newDictionary();
    }
    
    static void JSONCoderObjectPut(struct _hjson_t * json,hany object,hcchar * key,hany value,InvokeTickDeclare){
        ((Dictionary *) object)->setObjectForKey(key, (Object *) value);
    }
    
    static hany JSONCoderArrayNew(struct _hjson_t * json,InvokeTickDeclare){
        return Array::newArray();
    }
    
    static void JSONCoderArrayAdd(struct _hjson_t * json,hany array,hany value,InvokeTickDeclare){
        ((Array *) array)->addObject((Object *) value);
    }
    
    static hany JSONCoderNumber(struct _hjson_t * json,hcchar * value,InvokeTickDeclare){
        hint64 int64_value = 0;
        hdouble double_value = 0;
        if(str_exist(value, ".") || str_exist(value, "e")){
            sscanf(value, "%lf",&double_value);
            if((hint32)double_value == double_value){
                return (Value *)(new Value((hint32)double_value))->autorelease();
            }
            else{
                return (Value *)(new Value(double_value))->autorelease();
            }
        }
        else{
            sscanf(value, "%lld",&int64_value);
            if((hint32)int64_value == int64_value){
                return (Value *)(new Value((int)int64_value))->autorelease();
            }
            else {
                return (Value *)(new Value((long long)int64_value))->autorelease();
            }
        }
    }
    
    static hany JSONCoderString(struct _hjson_t * json,hcchar * value,struct _buffer_t * base64_buffer,InvokeTickDeclare){
        if(str_has_prefix(value, "#bit64__")){
            buffer_clear(base64_buffer);
            if(hbase64_decode(value + 8,base64_buffer)){
                return (Value *)(new Value(buffer_data(base64_buffer),buffer_length(base64_buffer),ValueTypeBytes))->autorelease();
            }
        }
        return Value::newValue(value);
    }
    
    static hany JSONCoderBoolean(struct _hjson_t * json,hbool value,InvokeTickDeclare){
        return Value::newValue((int)value);
    }
    
    static hany JSONCoderNull(struct _hjson_t * json,InvokeTickDeclare){
        Value * v = new Value();
        return v->autorelease();
    }
    
    static void JSONCoderObjectDealloc(struct _hjson_t * json,hany object,InvokeTickDeclare){
        
    }
    
    
    static hjson_t JSONCoderJSON = {
        JSONCoderObjectNew,JSONCoderObjectPut,JSONCoderArrayNew,JSONCoderArrayAdd
        ,JSONCoderNumber,JSONCoderString,JSONCoderBoolean,JSONCoderNull,JSONCoderObjectDealloc
    };

    
    static void ObjectEncodeLevel(hbuffer_t out,int level,InvokeTickDeclare){
        while(level >0){
            buffer_append_str(out, "\t");
            level --;
        }
    }

    static void ObjectEncode(hbuffer_t out,Object * obj,int level,InvokeTickDeclare){
        if(!obj){
            buffer_append_str(out, "null");
            return;
        }
        if(obj->isKindOfClass(&Array::oClass)){
            
            buffer_append_str(out, "[\n");
            
            Array * a = (Array *) obj;
            ArrayIterator i = a->begin();
            
            while(i != a->end()){
                ObjectEncodeLevel(out,level +1,InvokeTickArg);
                if(i != a->begin()){
                    buffer_append_str(out, ",");
                }
                ObjectEncode(out, * i, level +1,InvokeTickArg);
                buffer_append_str(out, "\n");
                i ++;
            }
            ObjectEncodeLevel(out,level,InvokeTickArg);
            buffer_append_str(out, "]");
        }
        else if(obj->isKindOfClass(&Dictionary::oClass)){
            buffer_append_str(out, "{\n");
            
            Dictionary * a = (Dictionary *) obj;
            DictionaryIterator i = a->begin();
            
            while(i != a->end()){
                ObjectEncodeLevel(out,level +1,InvokeTickArg);
                if(i != a->begin()){
                    buffer_append_str(out, ",");
                }
                buffer_append_str(out, "\"");
                buffer_append_str(out, i->first.c_str());
                buffer_append_str(out, "\":");

                ObjectEncode(out, i->second, level +1,InvokeTickArg);
                buffer_append_str(out, "\n");
                
                i ++;
            }
            ObjectEncodeLevel(out,level,InvokeTickArg);
            buffer_append_str(out, "}");
            
        }
        else if(obj->isKindOfClass(&Value::oClass)){
  
            Value * a = (Value *) obj;
            ValueType type = a->valueType();
            
            if(type == ValueTypeString){
                char * p = (char *)a->stringValue();
                buffer_append_str(out, "\"");
                
                while( *p != '\0'){
                    if(*p == '"'){
                        buffer_append_str(out, "\\\"");
                    }
                    else if(*p == '\t'){
                        buffer_append_str(out, "\\t");
                    }
                    else if(*p == '\r'){
                        buffer_append_str(out, "\\r");
                    }
                    else if(*p == '\n'){
                        buffer_append_str(out, "\\n");
                    }
                    else{
                        buffer_append(out, p,1);
                    }
                    p ++;
                }
                
                buffer_append_str(out, "\"");
            }
            else if(type == ValueTypeInteger){
                buffer_append_format(out, "%d", InvokeTickArg,a->intValue());
            }
            else if(type == ValueTypeInt64){
                buffer_append_format(out, "%lld", InvokeTickArg,a->int64Value());
            }
            else if(type == ValueTypeDouble){
                buffer_append_format(out, "%f", InvokeTickArg,a->doubleValue());
            }
            else if(type == ValueTypeFloat){
                buffer_append_format(out, "%f", InvokeTickArg,a->floatValue());
            }
            else if(type == ValueTypeBoolean){
                buffer_append_str(out, (a->booleanValue() ? "true":"false"));
            }
        }
        else{
            Class * clazz = obj->clazz();
            Value className(clazz->name);
            Dictionary * d = new Dictionary("__class",(Object *)&className,NULL);
            
            while(clazz){
                
                Property * p = clazz->propertys;
                int pc = clazz->propertysCount;
                
                while(pc >0){
                    if(p->coder && d->objectForKey(p->name) == NULL){
                        Object * v = obj->getPropertyValue(p);
                        if(v){
                            d->setObjectForKey(p->name, v);
                        }
                    }
                    p ++;
                    pc --;
                }
                
                clazz = clazz->superClass;
            }
            
            ObjectEncode(out,d,level,InvokeTickArg);
            
            d->release();
            
        }
    }
    
    JSONCoder::JSONCoder(void){
        InvokeTickBegin
        _JSONString = buffer_alloc(1024, 1024);
        strcpy(_signature, "");
    }
    
    JSONCoder::~JSONCoder(void){
        InvokeTickBegin
        buffer_dealloc(_JSONString);
    }
    
    Object * JSONCoder::decode(){
        InvokeTickBegin
        return (Object *) hjson_decode(&JSONCoderJSON, buffer_to_str(_JSONString), InvokeTickArg);
    }
    
    void JSONCoder::encode(Object * object) {
        InvokeTickBegin
        buffer_clear(_JSONString);
        ObjectEncode(_JSONString,object,0,InvokeTickArg);
    }
    
    const char * JSONCoder::JSONString(){
        InvokeTickBegin
        return buffer_to_str(_JSONString);
    }
    
    void JSONCoder::setJSONString(const char * string){
        InvokeTickBegin
        buffer_clear(_JSONString);
        buffer_append_str(_JSONString, string);
    }
    
    void JSONCoder::setJSONFile(const char * filePath){
        InvokeTickBegin
        buffer_clear(_JSONString);
        FILE * f = fopen(filePath, "r");
        char buffer[1024];
        int len;
        if(f){
            
            while((len = fread(buffer, 1, sizeof(buffer), f)) >0){
                buffer_append(_JSONString, buffer, len);
            }
            fclose(f);
        }
    }
    
    static void JSONCoderSignature(md5_state_t * md5,Object * obj,InvokeTickDeclare){
       
        if(obj == NULL){
            md5_append(md5, (md5_byte_t *)"null", 4);
        }
        
        if(obj->isKindOfClass(&Array::oClass)){
            
            md5_append(md5, (md5_byte_t *)"[", 1);
            
            Array * a = (Array *) obj;
            ArrayIterator i = a->begin();
            
            while(i != a->end()){
                md5_append(md5, (md5_byte_t *)",", 1);
                JSONCoderSignature(md5, * i,InvokeTickArg);
                i ++;
            }
            md5_append(md5, (md5_byte_t *)"]", 1);
        }
        else if(obj->isKindOfClass(&Dictionary::oClass)){
           
            md5_append(md5, (md5_byte_t *)"{", 1);
            
            Dictionary * a = (Dictionary *) obj;
            DictionaryIterator i = a->begin();
            
            while(i != a->end()){
                md5_append(md5, (md5_byte_t *)",", 1);
                md5_append(md5, (md5_byte_t *)i->first.c_str(), i->first.length());
                md5_append(md5, (md5_byte_t *)":", 1);
                JSONCoderSignature(md5, i->second, InvokeTickArg);
                i ++;
            }

            md5_append(md5, (md5_byte_t *)"}", 1);
            
        }
        else if(obj->isKindOfClass(&Value::oClass)){
            Value * a = (Value *) obj;
            md5_append(md5, (md5_byte_t *)a->value(), a->length());
        }
        else{
            Class * clazz = obj->clazz();
            
            md5_append(md5, (md5_byte_t *)clazz->name, strlen(clazz->name));
            
            while(clazz){
                
                Property * p = clazz->propertys;
                int pc = clazz->propertysCount;
                
                while(pc >0){
                    if(p->coder){
                        Object * v = obj->getPropertyValue(p);
                        if(v){
                            md5_append(md5, (md5_byte_t *)",", 1);
                            md5_append(md5, (md5_byte_t *)p->name, strlen(p->name));
                            md5_append(md5, (md5_byte_t *)":", 1);
                            JSONCoderSignature(md5,v,InvokeTickArg);
                        }
                    }
                    p ++;
                    pc --;
                }
                
                clazz = clazz->superClass;
            }
            
        }
        
    }
    
    const char * JSONCoder::signature(Object * object){
        md5_state_t md5;
        md5_byte_t digest[16];
        
        strcpy(_signature, "");
        
        md5_init(&md5);
        
        JSONCoderSignature(&md5,object,InvokeTickRoot);
        
        md5_finish(&md5, digest);
        
        sprintf(_signature, "%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x"
                ,digest[0],digest[1],digest[2],digest[3]
                ,digest[4],digest[5],digest[6],digest[7]
                ,digest[8],digest[9],digest[10],digest[11]
                ,digest[12],digest[13],digest[14],digest[15]);
        
        return _signature;
    }

    Coder::~Coder(void){

    }
}
