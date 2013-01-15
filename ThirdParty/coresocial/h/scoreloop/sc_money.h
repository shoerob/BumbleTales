/*-------------------------------------------------------------------------------------*
 * Copyright (C) 2012 Scoreloop AG. All rights reserved.
 *-------------------------------------------------------------------------------------*/

/**
 * @file        sc_money.h
 * @brief       Structure that represents an amount of game-specific currency.
 *
 * @addtogroup  SC_Money
 * @{
 *
 * Instances of \ref SC_Money are used to represent an amount of
 * game-specific currency.
 *
 * Game-specific currencies are represented using a 3-character code.
 * The code is generated by Scoreloop when the game is registered
 * at https://developer.scoreloop.com along with the game ID and game secret.
 *
 * The amount of currency represented by the \ref SC_Money instance
 * must be given in cents.
 *
 * Basic Use:
 * -# Optional: Use the session object's SC_Session_GetBalance() to check if the user has enough balance to create a challenge.
 * -# Use the \ref SC_Client instance to create an \ref SC_Money object by calling SC_Client_CreateMoney().
 * -# Use this \ref SC_Money object as the stake to create a challenge by calling SC_Client_CreateChallenge()
 */

#ifndef __SC_MONEY_H__
#define __SC_MONEY_H__

/*-------------------------------------------------------------------------------------*
 * Includes
 *-------------------------------------------------------------------------------------*/

#include <scoreloop/sc_object.h>
#include <scoreloop/sc_errors.h>
#include <scoreloop/sc_string.h>

#ifdef __cplusplus
extern "C" {
#endif

/*-------------------------------------------------------------------------------------*
 * Types
 *-------------------------------------------------------------------------------------*/

/** Opaque Money object handle */
typedef struct SC_Money_tag* SC_Money_h;

/** Type descriptors for SC_Money. */
SC_TYPEINFO(SC_Money);

/*-------------------------------------------------------------------------------------*
 * Methods
 *-------------------------------------------------------------------------------------*/

/**
 * @brief Increments the object's reference count
 *
 * This method increments the reference count of the SC_Money
 * instance.
 *
 * @param self An opaque handle for the SC_Money instance.
 */
SC_PUBLISHED void SC_Money_Retain(SC_Money_h self);

/**
 * @brief Decrements the object's reference count, and deletes the object if the counter reaches 0.
 *
 * This method decrements the reference count of the SC_Money instance.
 * The instance will be automatically deleted when the reference count
 * reaches 0.
 *
 * Please note that this method is NULL pointer safe. That is, NULL as an argument will
 * not cause an exception.
 *
 * @param self An opaque handle for the SC_Money instance.
 */
SC_PUBLISHED void SC_Money_Release(SC_Money_h self);

/**
 * @brief Returns the amount of game-specific currency represented by the money object.
 *
 * This method returns the amount of currency represented by the
 * instance of SC_Money.
 *
 * @param self An opaque handle for the SC_Money instance.
 * @return unsigned int The amount of currency.
 */
SC_PUBLISHED unsigned int SC_Money_GetAmount(SC_Money_h self);

#ifdef __cplusplus
}
#endif

#endif /* __SC_MONEY_H__ */

/*! @} */