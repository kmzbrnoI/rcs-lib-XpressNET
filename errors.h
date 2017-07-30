////////////////////////////////////////////////////////////////////////////////
// Errors.pas
//  MTB simulator library
//  Error codes definiton
//   (c) Jan Horacek (jan.horacek@kmz-brno.cz),
////////////////////////////////////////////////////////////////////////////////

/*
   LICENSE:
   Copyright 2016-2017 Jan Horacek
   Licensed under the Apache License, Version 2.0 (the "License")
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at
       http://www.apache.org/licenses/LICENSE-2.0
   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
  limitations under the License.
*/

/*
  DESCRIPTION:
  This file defines library error codes.
*/
#ifndef ERRORS_H
#define ERRORS_H

#define MTB_GENERAL_EXCEPTION (1000)
// device is always closed when this exception happens
#define MTB_FT_EXCEPTION 1001       
#define MTB_FILE_CANNOT_ACCESS (1010)
#define MTB_FILE_DEVICE_OPENED (1011)
#define MTB_MODULE_INVALID_ADDR (1100)
#define MTB_MODULE_FAILED (1102)
#define MTB_PORT_INVALID_NUMBER (1103)
#define MTB_MODULE_UNKNOWN_TYPE (1104)
#define MTB_INVALID_SPEED (1105)
#define MTB_INVALID_SCOM_CODE (1106)
#define MTB_INVALID_MODULES_COUNT (1107)
#define MTB_INPUT_NOT_YET_SCANNED (1108)

#define MTB_ALREADY_OPENNED (2001)
#define MTB_CANNOT_OPEN_PORT (2002)
#define MTB_FIRMWARE_TOO_LOW (2003)
#define MTB_DEVICE_DISCONNECTED (2004)
#define MTB_SCANNING_NOT_FINISHED (2010)
#define MTB_NOT_OPENED (2011)
#define MTB_ALREADY_STARTED (2012)
#define MTB_OPENING_NOT_FINISHED (2021)
#define MTB_NO_MODULES (2025)
#define MTB_NOT_STARTED (2031)

#define MTB_INVALID_PACKET (3100)
#define MTB_MODULE_NOT_ANSWERED_CMD (3101)
#define MTB_MODULE_NOT_ANSWERED_CMD_GIVING_UP (3102)
#define MTB_MODULE_OUT_SUM_ERROR (3106)
#define MTB_MODULE_OUT_SUM_ERROR_GIVING_UP (3107)
#define MTB_MODULE_IN_SUM_ERROR (3108)
#define MTB_MODULE_IN_SUM_ERROR_GIVING_UP (3109)

#define MTB_MODULE_NOT_RESPONDED_FB (3121)
#define MTB_MODULE_NOT_RESPONDED_FB_GIVING_UP (3122)
#define MTB_MODULE_IN_FB_SUM_ERROR (3126)
#define MTB_MODULE_IN_FB_SUM_ERROR_GIVING_UP (3127)
#define MTB_MODULE_OUT_FB_SUM_ERROR (3128)
#define MTB_MODULE_OUT_FB_SUM_ERROR_GIVING_UP (3129)
#define MTB_MODULE_INVALID_FB_SUM (3125)
#define MTB_MODULE_NOT_RESPONDING_PWR_ON (3131)

#define MTB_MODULE_PWR_ON_IN_SUM_ERROR (3136)
#define MTB_MODULE_PWR_ON_IN_SUM_ERROR_GIVING_UP (3137)
#define MTB_MODULE_PWR_ON_OUT_SUM_ERROR (3138)
#define MTB_MODULE_PWR_ON_OUT_SUM_ERROR_GIVING_UP (3139)

#define MTB_MODULE_FAIL (3141)
#define MTB_MODULE_RESTORED (3142)
#define MTB_MODULE_INVALID_DATA (3145)

#define MTB_MODULE_REWIND_IN_SUM_ERROR (3162)
#define MTB_MODULE_REWIND_OUT_SUM_ERROR (3163)

#define MTB_MODULE_SCAN_IN_SUM_ERROR (3166)
#define MTB_MODULE_SCAN_IN_SUM_ERROR_GIVING_UP (3167)
#define MTB_MODULE_SCAN_OUT_SUM_ERROR (3168)
#define MTB_MODULE_SCAN_OUT_SUM_ERROR_GIVING_UP (3169)

#define MTB_MODULE_SC_IN_SUM_ERROR (3176)
#define MTB_MODULE_SC_IN_SUM_ERROR_GIVING_UP (3177)
#define MTB_MODULE_SC_OUT_SUM_ERROR (3178)
#define MTB_MODULE_SC_OUT_SUM_ERROR_GIVING_UP (3179)

#endif