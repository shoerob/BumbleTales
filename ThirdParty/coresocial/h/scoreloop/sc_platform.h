/*-------------------------------------------------------------------------------------*
 * Copyright (C) 2012 Scoreloop AG. All rights reserved.
 *-------------------------------------------------------------------------------------*/

/**
 * @brief       Platform-specific definitions for Marmalade (aka AirPlay).
 *
 * @file        sc_platform.h
 * @addtogroup  SC_Client
 * @{
 */

#ifndef __SC_PLATFORM_H__
#define __SC_PLATFORM_H__


#ifdef __cplusplus
extern "C" {
#endif

/*-------------------------------------------------------------------------------------*
 * Macros
 *-------------------------------------------------------------------------------------*/

#ifndef SC_PLATFORM_MARMALADE
    /** Type of the platform */
    #define SC_PLATFORM_MARMALADE   (1)
#endif

/** Social providers implementation available */
#define SC_HAS_SOCIAL_PROVIDERS     (1)

/** SC_PUBLISHED not needed on this platform */
#define SC_PUBLISHED

#ifdef __cplusplus
}
#endif

#endif /* __SC_PLATFORM_H__ */

/*! @} */
