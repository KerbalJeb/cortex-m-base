/** @file timer_config.c
*   @brief Created on 2021-03-20 by Ben
*/
/**********************************************************************
* Includes
**********************************************************************/
#include "timer_config.h"

/**********************************************************************
* Module Preprocessor Constants
**********************************************************************/

/**********************************************************************
* Module Preprocessor Macros
**********************************************************************/

/**********************************************************************
* Module Typedefs
**********************************************************************/

/*********************************************************************
* Module Variable Definitions
**********************************************************************/

static const TimerCompareCaptureConfig Timer3ChannelConfigTable[] =
{
    {CC_CHANNEL_3, 500, CC_MODE_PWM, true},
    {CC_CHANNEL_END},
};

static const TimerConfig ConfigTable[] =
{
        {TIMER3_CHANNEL, 48000, 1000, TIM_COUNTER_UP, true, Timer3ChannelConfigTable},
        {TIMER_CHANNEL_END}
};

/**********************************************************************
* Function Prototypes
**********************************************************************/

/**********************************************************************
* Function Definitions
**********************************************************************/
const TimerConfig *timer_get_config(void)
{
    return ConfigTable;
}
