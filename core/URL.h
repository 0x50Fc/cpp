//
//  URL.h
//  hcpp
//
//  Created by zhang hailong on 12-12-27.
//  Copyright (c) 2012年 hailong.org. All rights reserved.
//

#ifndef __hcpp__URL__
#define __hcpp__URL__

#include "Value.h"

#include <string>
#include <map>

namespace HCPP {
    
    // http://user:pwd@www.9vteam.com/issue?id=123#token
    
    
    std::string URLEncodeValue(const char * value);
    
    std::string URLDecodeValue(const char * value);
    
    class URL : public Object{
    public:
        
        URL(void);
        
        URL(URL * baseURL,const char * format,...);
        
        URL(URL * baseURL,const char * format,va_list va);
        
        virtual ~URL(void);
        
        virtual const char * url();
        
        virtual const char * absoluteUrl();
        
        virtual const char * path();
        
        virtual const char * protocol();
        
        virtual bool hasProtocol();
        
        virtual const char * queryValue(const char * key);
        
        virtual const char * query();
        
        virtual bool hasQuery();
        
        virtual const char * token();
        
        virtual bool hasToken();
        
        virtual const char * domain();
        
        virtual bool hasDomain();
        
        virtual int port();
        
        virtual bool hasPort();
        
        virtual const char * user();
        
        virtual bool hasUser();
        
        virtual const char * password();
        
        virtual bool hasPassword();
        
        virtual URL * baseURL();
        
        static Value * encodeValue(const char * value);
        
        static Value * decodeValue(const char * value);
        
        static URL * newURL(URL * baseURL,const char * format,...);
        
        DEC_CLASS
        
    private:
        std::string _url;
        std::string _absoluteUrl;
        std::string _path;
        std::string _protocol;
        std::string _token;
        std::string _domain;
        std::string _query;
        int _port;
        std::string _user;
        std::string _password;
        std::map<std::string,std::string> _queryValues;
        URL * _baseURL;
        
        void _URL(URL * baseURL,const char * format,va_list va);
    };
}


#endif /* defined(__hcpp__URL__) */
