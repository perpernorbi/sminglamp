#ifndef __USER_CONFIG_H__
#define __USER_CONFIG_H__

#ifdef __cplusplus
extern "C" {
#endif

// UART config
#define SERIAL_BAUD_RATE COM_SPEED_SERIAL

// ESP SDK config
#define LWIP_OPEN_SRC
//#define USE_US_TIMER

// Default types
#define __CORRECT_ISO_CPP_STDLIB_H_PROTO
#include <limits.h>
#include <stdint.h>

// Override c_types.h include and remove buggy espconn
//#define _C_TYPES_H_
//#define _NO_ESPCON_

#include <c_types.h>

// System API declarations
#include <esp_systemapi.h>

// C++ Support
#include <esp_cplusplus.h>
// Extended string conversion for compatibility
#include <stringconversion.h>
// Network base API
#include <espinc/lwip_includes.h>

#ifdef __cplusplus
}
#endif

#endif
