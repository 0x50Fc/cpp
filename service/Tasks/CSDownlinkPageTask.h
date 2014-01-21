//
//  CSDownlinkPageTask.h
//  hcppservice
//
//  Created by zhang hailong on 12-12-26.
//  Copyright (c) 2012年 9vteam. All rights reserved.
//

#ifndef __hcppservice__CSDownlinkPageTask__
#define __hcppservice__CSDownlinkPageTask__

#include "CSDownlinkTask.h"
#include "CSContext.h"

namespace CS {
    
    
    class CSDownlinkPageTask : public CSDownlinkTask{
        
    public:
        
        CSDownlinkPageTask(void);
        
        virtual ~CSDownlinkPageTask(void);
        
        virtual int pageSize();
        
        virtual void setPageSize(int pageSize);
        
        virtual int pageIndex();
        
        virtual void setPageIndex(int pageIndex);
        
        virtual long long maxId();
        
        virtual void setMaxId(long long maxId);
        
        virtual long long minId();
        
        virtual void setMinId(long long minId);
        
        DEC_CLASS
        
    private:
        int _pageSize;
        int _pageIndex;
        long long _maxId;
        long long _minId;
    };
    
}

#endif /* defined(__hcppservice__CSDownlinkPageTask__) */
