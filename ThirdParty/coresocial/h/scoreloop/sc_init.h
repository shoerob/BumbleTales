/*-------------------------------------------------------------------------------------*
 * Copyright (C) 2012 Scoreloop AG. All rights reserved.
 *-------------------------------------------------------------------------------------*/

/**
 * @file        sc_init.h
 * @brief       Platform Abstraction Layer - initialization data for Marmalade (aka AirPlay).
 *
 * @addtogroup  SC_Init
 * @{
 */

#ifndef __SC_INIT_H__
#define __SC_INIT_H__

#include <scoreloop/sc_types.h>

#ifdef __cplusplus
extern "C" {
#endif

/*-------------------------------------------------------------------------------------*
 * Defines
 *-------------------------------------------------------------------------------------*/

/** Definition of the 1.0 version */
#define SC_INIT_VERSION_1_0        0x100

/** Constant describing current version of the Scoreloop CoreSocial and the library itself. */
#define SC_INIT_CURRENT_VERSION    SC_INIT_VERSION_1_0

/*-------------------------------------------------------------------------------------*
 * Types
 *-------------------------------------------------------------------------------------*/

/* Marmalade requires no initialization data to be passed to SC constructor */

/** Platform-dependant initialization arguments for the Scoreloop Client SDK */
typedef struct SC_InitData_tag
{
    /** Type of the client's application (optional). NULL for a game. */
    const char *clientType;

} SC_InitData_t;

/*-------------------------------------------------------------------------------------*
 * Function prototypes
 *-------------------------------------------------------------------------------------*/

/**
 * @brief Initializes the SC_InitData_t structure with default values.
 *
 * @param initData  A Pointer to the init data to be initialized
 */
#define SC_InitData_Init(initData) (SC_InitData_InitWithSize(initData, sizeof(SC_InitData_t)))
    
/**
 * @brief Method used by SC_InitData_Init to do the initialization.
 *
 * This method is used internally by the method SC_InitData_Init to do the initialization.
 * It initializes the data size.
 *
 * @param *initData pointer to SC_InitData_t
 * @param size int representing the size of the SC_InitData
 */
SC_PUBLISHED void SC_InitData_InitWithSize(SC_InitData_t* initData, unsigned int size);

#ifdef __cplusplus
}
#endif

#endif /* __SC_INIT_H__ */

/*! @} */
