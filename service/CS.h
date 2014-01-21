//
//  CS.h
//  hcppservice
//
//  Created by zhang hailong on 12-12-20.
//  Copyright (c) 2012年 9vteam. All rights reserved.
//

#ifndef __hcppservice__CS__
#define __hcppservice__CS__

#include "Object.h"

namespace CS {
    
#define BS_NOT_FOUND_DEVICE_ERROR 0x0B01
#define BS_USER_AUTH_TOKEN_FAIL 0x0102
#define BS_USER_AUTH_LOGINNAME_OR_PASSWORD 0x0103
#define BS_USER_AUTH_VERIFY_CODE 0x0104
#define BS_APP_AUTH_TOKEN   0x0203
    
    void CSInitialize(void);
    
}

#endif /* defined(__hcppservice__CS__) */
