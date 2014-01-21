//
//  Bundle.h
//  hcpp
//
//  Created by Zhang Hailong on 13-1-17.
//  Copyright (c) 2013年 hailong.org. All rights reserved.
//

#ifndef __hcpp__Bundle__
#define __hcpp__Bundle__

#include "Object.h"
#include "Value.h"

#include <string>


namespace HCPP {
    
    class Bundle : public Object{
    public:
        
        Bundle(void);
        
        Bundle(Bundle * parent,const char * bundlePath,const char * info);
        
        Bundle(Bundle * parent,const char * bundlePath);
        
        virtual ~Bundle(void);
        
        virtual const char * bundlePath();
        
        virtual Bundle * parent();
        
        virtual Object * infoObject();
        
        virtual Value * getStringContent(const char * format,...);
        
        virtual Value * getStringContentV(const char * format,va_list va);
        
        virtual Value * getBytesContent(const char * format,...);
        
        virtual Value * getBytesContentV(const char * format,va_list va);
        
        virtual Value * getFilePath(const char * format,...);
        
        virtual Value * getFilePathV(const char * format,va_list va);
        
        virtual const char * version();
        
        virtual bool isExists();
        
        static Bundle * newBundle(Bundle * parent,const char * bundlePath,const char * info);
        
        static Bundle * newBundle(Bundle * parent,const char * bundlePath);
        
        DEC_CLASS
    protected:
        void _Bundle(Bundle * bundle,const char * bundlePath,const char * info);
    private:
        Bundle * _parent;
        std::string _bundlePath;
        Object * _infoObject;
    };
}

#endif /* defined(__hcpp__Bundle__) */
