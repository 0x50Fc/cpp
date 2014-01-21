//
//  Object.h
//  hcpp3d
//
//  Created by Zhang Hailong on 12-11-26.
//  Copyright (c) 2012年 9vteam. All rights reserved.
//

#ifndef HCPP_Object__
#define HCPP_Object__

#define DEC_CLASS   public : static HCPP::Class oClass; static void initialize(); virtual HCPP::Class * clazz(); private: static bool _initialized;

#define IMP_CLASS_B(obj,superClass,propertys,propertysCount,invokes,invokesCount)  \
        static HCPP::Object * obj##_alloc(){ return new obj(); };  \
        HCPP::Class obj::oClass = {&superClass::oClass,#obj,obj##_alloc,propertys,propertysCount,invokes,invokesCount}; \
        bool obj::_initialized = false; \
        void obj::initialize() { if(!_initialized){ superClass::initialize(); RegisterClass(&obj::oClass); _initialized = true; } }; \
        HCPP::Class * obj::clazz() {return &obj::oClass;}


#define IMP_PROPERTY_BEGIN(obj) \
        static HCPP::Property obj##_Propertys[]= { 

#define IMP_PROPERTY(name,type,getter,setter)    {(#name),(type),(HCPP::Object::FUN_T)(getter),(HCPP::Object::FUN_T)(setter),0} ,

#define IMP_PROPERTY_CODER(name,type,getter,setter)    {(#name),(type),(HCPP::Object::FUN_T)(getter),(HCPP::Object::FUN_T)(setter),1} ,

#define IMP_PROPERTY_END(obj) \
        };

#define IMP_PROPERTYS(obj) obj##_Propertys
#define IMP_PROPERTYS_COUNT(obj) (sizeof(obj##_Propertys) / sizeof(HCPP::Property))

#define IMP_INVOKE_BEGIN(obj) \
        static HCPP::Invoke obj##_Invokes[] = {

#define IMP_INVOKE(name,returnType,invoke)  {#name,returnType,(Object::FUN_T)(invoke)},

#define IMP_INVOKE_END(obj) \
        };

#define IMP_INVOKES(obj) obj##_Invokes
#define IMP_INVOKES_COUNT(obj) (sizeof(obj##_Invokes) / sizeof(HCPP::Invoke))


#define IMP_CLASS(obj,superClass)  IMP_CLASS_B(obj,superClass,NULL,0,NULL,0)
#define IMP_CLASS_P(obj,superClass) IMP_CLASS_B(obj,superClass,IMP_PROPERTYS(obj),IMP_PROPERTYS_COUNT(obj),NULL,0)
#define IMP_CLASS_I(obj,superClass) IMP_CLASS_B(obj,superClass,NULL,0,IMP_INVOKES(obj),IMP_INVOKES_COUNT(obj))
#define IMP_CLASS_P_I(obj,superClass) IMP_CLASS_B(obj,superClass,IMP_PROPERTYS(obj),IMP_PROPERTYS_COUNT(obj),IMP_INVOKES(obj),IMP_INVOKES_COUNT(obj))

#define OBJ_ALLOC(clazz) (* clazz->alloc)();

#define PropertyValueGet(obj,property,T)  ((obj)->*((T (Object::*)(void))(property)->getter))()
#define PropertyValueSet(obj,property,T,value)  ((obj)->*((void (Object::*)(T))(property)->setter))(value)
#define InvokeCall(obj,invoke,T)    ((obj)->*((T (Object::*)(void))(invoke)->invoke))()


#define DEC_VALUETYPE(T)        		extern HCPP::_ValueType VT_##T;
#define IMP_VALUETYPE(T,type)   		HCPP::_ValueType VT_##T = {#type,sizeof(type)};
#define IMP_VALUETYPE_LENGTH(T,type,length)  HCPP::_ValueType VT_##T = {#type,length};

#define VALUETYPE_NS(T,ns)  (&ns::VT_##T)
#define VALUETYPE(T)        (&VT_##T)
#define VALUETYPELENGTH(T)  (VT_##T.length)
#define VALUETYPENAME(T)    (VT_##T.name)

#define ValueTypeString     VALUETYPE_NS(String,HCPP)
#define ValueTypeInteger    VALUETYPE_NS(Integer,HCPP)
#define ValueTypeInt64      VALUETYPE_NS(Int64,HCPP)
#define ValueTypeFloat      VALUETYPE_NS(Float,HCPP)
#define ValueTypeDouble     VALUETYPE_NS(Double,HCPP)
#define ValueTypeBoolean    VALUETYPE_NS(Boolean,HCPP)
#define ValueTypeObject     VALUETYPE_NS(Object,HCPP)
#define ValueTypeBytes      VALUETYPE_NS(Bytes,HCPP)
#define ValueTypePtr        VALUETYPE_NS(Ptr,HCPP)
#define ValueTypeVoid       VALUETYPE_NS(Void,HCPP)

namespace HCPP {
    
    
    struct _ValueType{
        const char * const name;
        int length;
    };
    
    DEC_VALUETYPE(String)
    DEC_VALUETYPE(Integer)
    DEC_VALUETYPE(Int64)
    DEC_VALUETYPE(Float)
    DEC_VALUETYPE(Double)
    DEC_VALUETYPE(Boolean)
    DEC_VALUETYPE(Object)
    DEC_VALUETYPE(Bytes)
    DEC_VALUETYPE(Ptr)
    DEC_VALUETYPE(Void)
    
    class Object;
    class Value;
    
    struct Property;
    struct Invoke;
    
    struct Class{
        Class * const superClass;
        const char * const name;
        Object * (* const alloc)(void);
        Property * const propertys;
        int const propertysCount;
        Invoke * const invokes;
        int const invokesCount;
    };


    typedef _ValueType * ValueType;
    
    void RegisterClass(Class * clazz);
    
    Class * GetClass(const char * className);
    
    bool ClassIsInherit(Class * clazz,Class * ofClass);
    
    Property * GetProperty(Class * clazz,const char * property);
    
    Invoke * GetInvoke(Class * clazz,const char * invoke);
    
    class Object{
      
    public:
        
        typedef void (Object:: * FUN_T)();

        Object(void);
        virtual ~Object(void);
        
        virtual Object * retain(void);
        virtual void release(void);
        virtual Object * autorelease(void);
        virtual int retainCount(void);
        
        bool isKindOfClass(Class * clazz);
        
        virtual Object * objectForKey(const char * key);
        
        virtual void setObjectForKey(const char * key,Object * value);
        
        virtual Object * objectForKeyPath(const char * keyPath);
        
        virtual void setObjectForKeyPath(const char * keyPath,Object * value);
        
        virtual bool hasProperty(const char * property);

        virtual Property * getProperty(const char * property);
        
        virtual Property * getPropertyForKeyPath(const char * keyPath,Object ** atObject);
        
        virtual Object * getPropertyValue(Property * property);
        
        virtual void setPropertyValue(Property * property,Object * value);
        
        virtual Invoke * getInvoke(const char * invoke);
        
        virtual Object * invoke(Invoke * invoke);
        
        virtual Object * invoke(const char * invoke);
    
        static bool keyPathHasPrefix(const char * keyPath,const char * key,...);
        
        virtual Value * toStringValue();
        
        virtual void afterCaller(Object::FUN_T selector,Object * userInfo);
        
        virtual void afterCaller(Invoke * invoke,Object * userInfo);
        
        virtual void afterCaller(const char * invoke,Object * userInfo);
        
        virtual Object * copy();
        
        DEC_CLASS
        
    private:
        int _retainCount;
    };
    
    
    struct Property{
        const char * const name;
        ValueType const valueType;
        Object::FUN_T const getter;
        Object::FUN_T const setter;
        bool coder;
    };
    
    struct Invoke{
        const char * const name;
        ValueType const returnType;
        Object::FUN_T const invoke;
    };
        
    void ObjectAutoreleasePoolBegin(void);
    
    void ObjectAutoreleasePoolAddObject(Object * obj);
    
    void ObjectAutoreleasePoolEnd(void);
    
    void ObjectAfterCallerPoolInstall(void);
    
    void ObjectAfterCallerPoolInstall(void (*)(Object * target,Object::FUN_T selector,Object * userInfo,void * context), void * context);

    void ObjectAfterCallerPoolAdd(Object * target,Object::FUN_T selector,Object * userInfo);
}



#endif /* defined(__hcpp3d__Object__) */
