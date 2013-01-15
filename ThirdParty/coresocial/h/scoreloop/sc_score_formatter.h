/*-------------------------------------------------------------------------------------*
 * Copyright (C) 2012 Scoreloop AG. All rights reserved.
 *-------------------------------------------------------------------------------------*/

/**
 * @file        sc_score_formatter.h
 * @brief       Utility class for formatting the game's score.
 *
 * @addtogroup  SC_ScoreFormatter
 * @{
 *
 * The \ref SC_ScoreFormatter class allows you to configure how the score object should be displayed.
 *
 * Basic use:
 * -# Create an SLScoreFormatter.strings file.
 * A Score formatter for your game is available in the Score Definition section of your game page at
 * <a href="https://developer.scoreloop.com" target="_blank">https://developer.scoreloop.com</a>.
 * You can copy this and save it in a file named SLScoreFormatter.strings. You can configure the Score
 * Formatter at <a href="https://developer.scoreloop.com" target="_blank">https://developer.scoreloop.com</a>
 * to meet your specific score formatting needs.
 *
 * You can also view how the formatted scores will look by clicking on the Get Leaderboard Widget link below
 * the Score Formatter. It is important that the SLScoreFormatter.strings file contains the modified configuration.
 *
 * -# Add SLScoreFormatter.strings to your assets.
 * Add SLScoreFormatter.strings to the native/scoreloop directory of your game project, where native is the root
 * of your standard assets folder. You must create the scoreloop subdirectory.
 * -# Use the client instance to get the score formatter by calling SC_Client_GetScoreFormatter().
 * -# For each score in the score list returned, call SC_ScoreFormatter_FormatScore(). Remember to release the string used.
 *
 * Repeat the last two steps in the load Leaderboard Completion Callback, or where you want to display scores, for example, during score submission.
 *
 * Please take a look at @link integration-guide-scores Integrating Leaderboards @endlink for sample code for integrating the score formatter.
 */

#ifndef __SC_SCORE_FORMATTER_H__
#define __SC_SCORE_FORMATTER_H__

/*-------------------------------------------------------------------------------------*
 * Includes
 *-------------------------------------------------------------------------------------*/

#include <scoreloop/sc_errors.h>
#include <scoreloop/sc_score.h>
#include <scoreloop/sc_string.h>

#ifdef __cplusplus
extern "C" {
#endif

/*-------------------------------------------------------------------------------------*
 * Types
 *-------------------------------------------------------------------------------------*/

/** Opaque SC_ScoreFormatter object handle. */
typedef struct SC_ScoreFormatter_tag* SC_ScoreFormatter_h;

/** Type descriptors for SC_ScoreFormatter. */
SC_TYPEINFO(SC_ScoreFormatter);

/** Supported score formats */
typedef enum SC_ScoreFormat_tag {
    SC_SCORE_FORMAT_DEFAULT = 0, 
    SC_SCORE_FORMAT_SCORES_ONLY,
    SC_SCORE_FORMAT_LEVEL_AND_MODE,
    SC_SCORE_FORMAT_LEVEL_ONLY,
    SC_SCORE_FORMAT_MODE_ONLY,
    SC_SCORE_FORMAT_NO_LEVEL,
    SC_SCORE_FORMAT_SCORES_AND_LEVEL,

    SC_SCORE_FORMATS_COUNT
} SC_ScoreFormat_t;

/*-------------------------------------------------------------------------------------*
 * Methods
 *-------------------------------------------------------------------------------------*/

/**
 * @brief Formats the given SC_Score object into a string using a given format.
 *
 * This method creates a new instance of SC_String, with a reference count
 * equal to 1. It must be released by the caller.
 *
 * @param self      An opaque handle of the SC_ScoreFormatter instance.
 * @param score    A score to format.
 * @param format   A format string to use to format the score, @see SC_ScoreFormat_t.
 * @param pString   Out: pointer to the handle of the SC_String instance created.
 * @return SC_Error_t   An error code (a value of SC_OK indicates success,
 *                      any other value indicates an error).
 */
SC_PUBLISHED SC_Error_t SC_ScoreFormatter_FormatScore(SC_ScoreFormatter_h self,
        SC_Score_h score, SC_ScoreFormat_t format, SC_String_h* pString);

#ifdef __cplusplus
}
#endif

#endif /* __SC_SCORE_FORMATTER_H__ */

/*! @} */
