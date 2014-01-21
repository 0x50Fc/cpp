//
//  Array.h
//  hcpp3d
//
//  Created by Zhang Hailong on 12-11-26.
//  Copyright (c) 2012年 9vteam. All rights reserved.
//

#ifndef HCPP__Array__
#define HCPP__Array__

#include "Object.h"
#include <vector>

namespace HCPP {
    
    typedef std::vector<Object *>::iterator ArrayIterator;
        
    class Array : public Object{
        
    public :
        Array(void);
        Array(Array & array);
        Array(Object * object,...);
        virtual ~Array(void);
        
        int count();
        
        Object * objectAtIndex(int index);
        Object * lastObject();
        void addObject(Object * object);
        void addArray(Array * array);
        void insertObject(Object * object,int atIndex);
        void removeObject(Object * object);
        void removeObjectAtIndex(int index);
        void removeLastObject();
        void removeAllObjects();
        
        
        ArrayIterator erase(ArrayIterator i);
        ArrayIterator begin();
        ArrayIterator end();
        
        static Array * newArray();
        static Array * newArray(Object * object,...);
        
        virtual Object * copy();
        
        virtual Object * objectForKey(const char * key);

        DEC_CLASS
        
    protected:
        void _Array(Object * object,va_list va);
        
    private:
        std::vector<Object *> _items;
    };
        

    
}


#endif /* defined(HCPP__Array__) */
