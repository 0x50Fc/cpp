//
//  Value.h
//  hcpp
//
//  Created by zhang hailong on 12-12-7.
//  Copyright (c) 2012年 hailong.org. All rights reserved.
//

#ifndef HCPP__Value__
#define HCPP__Value__

#include "Object.h"

namespace HCPP {
    
    class Value : public Object{
        
    protected:
        void _Value(void * v,int length,ValueType valueType);
        
    public :
        
        Value(void);
        
        Value(void * v,int length,ValueType valueType);
        
        Value(void * v,ValueType valueType);
        
        Value(const char * value);
        
        Value(int value);
        
        Value(long long value);
        
        Value(float value);
        
        Value(double value);
        
        Value(bool value);
        
        Value(void * ptr);
        
        virtual ~Value(void);
        
        void * value();
        
        const char * stringValue();
        
        int intValue();
        
        long long int64Value();
        
        float floatValue();
        
        double doubleValue();
        
        bool booleanValue();
        
        void * ptrValue();
        
        void getValue(void * p);
        
        ValueType valueType();
        
        int length();
        
        virtual Value * toStringValue();
        
        virtual double compare(Value * value);
        
        virtual Object * copy();
        
        /*
         
         转换控制符	说明
         %a	星期几的简写形式
         %A	星期几的全称
         %b	月份的简写形式
         %B	月份的全称
         %c	日期和时间
         %d	月份中的日期,0-31
         %H	小时,00-23
         %I	12进制小时钟点,01-12
         %j	年份中的日期,001-366
         %m	年份中的月份,01-12
         %M	分,00-59
         %p	上午或下午
         %s	秒,00-60
         %u	星期几,1-7
         %w	星期几,0-6
         %x	当地格式的日期
         %X	当地格式的时间
         %y	年份中的最后两位数,00-99
         %Y	年
         %Z	地理时区名称
         */
        
        virtual Value * toDateFormat(const char * format);
        
        static Value * newValue(int value);
        
        static Value * newValue(long long value);
        
        static Value * newValue(float value);
        
        static Value * newValue(double value);
        
        static Value * newValue(bool value);
        
        static Value * newValue(void * v,ValueType valueType);
        
        static Value * newValue(void * ptr);
        
        static Value * newValue(void * v,int length);
        
        static Value * newDateValue();
        
        static Value * newFormat(const char * format,...);
        
        static Value * newValue(const char * value);
        
        DEC_CLASS
        
    private:
        ValueType _valueType;
        char * _value;
        int _length;
    };
    
}
#endif /* defined(__hcpp__Value__) */
