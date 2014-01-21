//
//  URL.cpp
//  hcpp
//
//  Created by zhang hailong on 12-12-27.
//  Copyright (c) 2012年 hailong.org. All rights reserved.
//
#include "hconfig.h"
#include "URL.h"
#include "hbuffer.h"

namespace HCPP {
    
    
    std::string URLEncodeValue(const char * value){
        std::string s;
        unsigned char * p = (unsigned char *) value;
        char sx[4];
        while(p && *p != '\0'){
            
            if(*p == ' '){
                s += '+';
            }
            else if((*p >='0' && *p <='9') || (*p >= 'a' && *p <='z') || (*p >= 'A' && *p <='Z')){
                s += *p;
            }
            else{
                sprintf(sx, "%%%02X",*p);
                s += sx;
            }
            
            p++;
        }
        return s;
    }
    
    std::string URLDecodeValue(const char * value){
        std::string s;
        unsigned char * p = (unsigned char *) value;
        unsigned int c;
        char sx[4];
        while(p && *p != '\0'){
            
            if(*p == '+'){
                s += ' ';
            }
            else if(*p == '%'){
                c = 0;
                sx[0] = p[1];
                sx[1] = p[2];
                sx[2] = 0;
                
                sscanf(sx, "%02x",&c);
                
                if(c){
                    s += (unsigned char) c;
                }
                
                p += 2;
            }
            else{
                s += *p;
            }
            
            p++;
        }
        return s;
    }
    
    IMP_CLASS(URL, Object)
    
    URL::URL(void){
        _port = 0;
        _baseURL = NULL;
    }
    
    void URL::_URL(URL * baseURL,const char * format,va_list va){
        InvokeTickBegin
        hbuffer_t buf = buffer_alloc(MAX_PATH, 128);
        
        buffer_append_format_va_list(buf, format, va);
        
        const char * url = buffer_to_str(buf);
        
        if(baseURL){
            baseURL->retain();
        }
        
        _baseURL = baseURL;
        _url = url;
        _port = 0;
        
        if(baseURL){
            if(baseURL->hasProtocol()){
                _absoluteUrl += baseURL->protocol();
                _absoluteUrl += "://";
            }
            if(baseURL->hasUser()){
                _absoluteUrl += baseURL->user();
                if(baseURL->hasPassword()){
                    _absoluteUrl += ":";
                    _absoluteUrl += baseURL->password();
                }
                _absoluteUrl += "@";
            }
            if(baseURL->hasDomain()){
                _absoluteUrl += baseURL->domain();
                if(baseURL->hasPort()){
                    _absoluteUrl += ":";
                    _absoluteUrl += baseURL->port();
                }
            }
            
            if(baseURL->path()){
                _absoluteUrl += baseURL->path();
            }
            
            char * p = (char *) url;
            if(p && *p =='/'){
                _absoluteUrl += url;
            }
            else if(p && *p == '?'){
                _absoluteUrl += url;
            }
            else if(p && *p == '#'){
                if(baseURL->query()){
                    _absoluteUrl += baseURL->query();
                }
                _absoluteUrl += url;
            }
            else {
                
                while(p && *p != '\0'){
                    if(p[0] == '.' && p[1] == '.'){
                        
                        p += 2;
                        
                        while(*p == '/'){
                            p++;
                        }
                        
                        int i = _absoluteUrl.find_last_of('/');
                        
                        if(i>=0 && i < _absoluteUrl.length()){
                            _absoluteUrl.erase(_absoluteUrl.begin() + (i + 1),_absoluteUrl.end());
                        }
                        else{
                            break;
                        }
                    }
                    else{
                        break;
                    }
                }
                
                if(p && *p !='\0'){
                    std::string::iterator i =  _absoluteUrl.end();
                    i--;
                    if( * i == '/'){
                        _absoluteUrl += p;
                    }
                    else{
                        int i = _absoluteUrl.find_last_of('/');
                        if(i>=0 && i < _absoluteUrl.length()){
                            _absoluteUrl.erase(_absoluteUrl.begin() + (i + 1),_absoluteUrl.end());
                        }
                        _absoluteUrl += p;
                    }
                }
                
            }
        }
        else{
            _absoluteUrl = url;
        }
        
        int index = 0;
        
        int i = _absoluteUrl.find("://",index);
        if(i >=0 && i < _absoluteUrl.length()){
            _protocol = _absoluteUrl.substr(index,i - index);
            index = i + 3;
        }
        
        
        i = _absoluteUrl.find("@",index);
        
        if(i >=0 && i < _absoluteUrl.length()){
            _user = _absoluteUrl.substr(index,i - index);
            i = _user.find(":");
            if(i >=0 && i< _user.length()){
                _password = _user.substr(i +1);
                _user = _user.substr(0,i);
            }
            index = i + 1;
        }
        
        i = _absoluteUrl.find("/",index);
        
        if(i >=0 && i < _absoluteUrl.length()){
            if(i - index !=0){
                _domain = _absoluteUrl.substr(index,i - index);
                index = i;
                
                i = _domain.find(":");
                if(i >=0 && i< _domain.length()){
                    _port = atoi(_domain.substr(i +1).c_str());
                    _domain = _domain.substr(0,i);
                }
            }
            
            i = _absoluteUrl.find("?",index);
            if(i >=0 && i < _absoluteUrl.length()){
                _path = _absoluteUrl.substr(index,i - index);
                index = i +1;
                i = _absoluteUrl.find("#",index);
                if(i >=0 && i<_absoluteUrl.length()){
                    _query = _absoluteUrl.substr(index,i - index);
                    _token = _absoluteUrl.substr(i +1);
                }
                else{
                    _query = _absoluteUrl.substr(index);
                }
                if(_query.length()){
                    std::string key;
                    std::string value;
                    std::string::iterator i = _query.begin();
                    int s = 0;
                    while(i != _query.end()){
                        
                        if(s == 0){
                            if(*i == '='){
                                s = 1;
                            }
                            else if(*i == '&'){
                                if(key.length()){
                                    _queryValues[key] = URLDecodeValue(value.c_str());
                                }
                                key.clear();
                                value.clear();
                            }
                            else{
                                key += *i;
                            }
                        }
                        else if(s ==1){
                            if(* i == '&'){
                                if(key.length()){
                                    _queryValues[key] = URLDecodeValue(value.c_str());
                                }
                                key.clear();
                                value.clear();
                                s = 0;
                            }
                            else{
                                value += *i;
                            }
                        }
                        i++;
                    }
                    if(key.length()){
                        _queryValues[key] = URLDecodeValue(value.c_str());
                    }
                }
            }
            else{
                i = _absoluteUrl.find("#",index);
                if(i >=0 && i<_absoluteUrl.length()){
                    _path = _absoluteUrl.substr(index,i - index);
                    _token = _absoluteUrl.substr(i +1);
                }
                else{
                    _path = _absoluteUrl.substr(index);
                }
            }
            
        }
        else{
            _domain = _absoluteUrl.substr(index);
            _path = "/";
        }
        
        buffer_dealloc(buf);
    }
    
    URL::URL(URL * baseURL,const char * format,...){
        va_list va;
        
        va_start(va, format);
        
        _URL(baseURL, format,va);
    
        va_end(va);
    }
    
    URL::URL(URL * baseURL,const char * format,va_list va){
        _URL( baseURL,format, va);
    }
    
    URL::~URL(void){
        if(_baseURL){
            _baseURL->release();
        }
    }
    
    const char * URL::url(){
        return _url.c_str();
    }
    
    const char * URL::absoluteUrl(){
        return _absoluteUrl.c_str();
    }
    
    const char * URL::path(){
        return _path.c_str();
    }
    
    
    const char * URL::protocol(){
        return _protocol.c_str();
    }
    
    bool URL::hasProtocol(){
        return _protocol.length() >0;
    }
    
    const char * URL::queryValue(const char * key){
        std::map<std::string, std::string>::iterator i = _queryValues.find(key);
        if(i != _queryValues.end()){
            return i->second.c_str();
        }
        return NULL;
    }
    
    const char * URL::token(){
        return _token.c_str();
    }
    
    bool URL::hasToken(){
        return _token.length() >0;
    }
    
    const char * URL::domain(){
        return _domain.c_str();
    }
    
    bool URL::hasDomain(){
        return _domain.length() >0;
    }
    
    int URL::port(){
        return _port;
    }
    
    bool URL::hasPort(){
        return _port != 0;
    }
    
    const char * URL::user(){
        return _user.c_str();
    }
    
    bool URL::hasUser(){
        return _user.length() >0;
    }
    
    const char * URL::password(){
        return _password.c_str();
    }
    
    bool URL::hasPassword(){
        return _password.length() >0;
    }
    
    URL * URL::baseURL(){
        return _baseURL;
    }
    
    const char * URL::query(){
        return _query.c_str();
    }
    
    bool URL::hasQuery(){
        return _query.length() >0;
    }

    Value * URL::encodeValue(const char * value){
        
        std::string s =  URLEncodeValue(value);
        
        return (Value *)(new Value(s.c_str()))->autorelease();
    }
    
    Value * URL::decodeValue(const char * value){
        
        std::string s =  URLDecodeValue(value);
        
        return (Value *)(new Value(s.c_str()))->autorelease();
    }
    
    URL * URL::newURL(URL * baseUrl,const char * format,...){
        va_list va;
        va_start(va, format);
        URL * u = new URL(baseUrl,format,va);
        va_end(va);
        return (URL *) u->autorelease();
    }
}