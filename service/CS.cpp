//
//  CS.cpp
//  hcppservice
//
//  Created by zhang hailong on 12-12-20.
//  Copyright (c) 2012年 9vteam. All rights reserved.
//

#include "hconfig.h"
#include "CS.h"

#include "CSAPITask.h"
#include "CSHttpTask.h"
#include "CSResourceTask.h"
#include "CSDownlinkTask.h"
#include "CSDownlinkPageTask.h"
#include "CSDownlinkService.h"
#include "CSUplinkService.h"
#include "CSSyncTask.h"
#include "CSSyncRequestTask.h"
#include "CSSyncResponseTask.h"

#include "CSSyncService.h"
#include "CSSDeviceService.h"

#include "CSMessageTask.h"
#include "CSMessageListenerTask.h"
#include "CSHttpStateMessageTask.h"
#include "CSMessageService.h"

#include "CSSystemAudioTask.h"

namespace CS {
    
    void CSInitialize(void){
        CSHttpTask::initialize();
        CSAPITask::initialize();
        CSResourceTask::initialize();
        CSDownlinkTask::initialize();
        CSDownlinkPageTask::initialize();
        CSDownlinkService::initialize();
        CSUplinkService::initialize();
        
        CSSyncTask::initialize();
        CSSyncRequestTask::initialize();
        CSSyncResponseTask::initialize();
        
        CSSyncService::initialize();
        CSSDeviceService::initialize();
        
        CSMessageTask::initialize();
        CSMessageListenerTask::initialize();
        CSHttpStateMessageTask::initialize();
        CSMessageService::initialize();
        
        CSSystemAudioTask::initialize();
    }
    
}