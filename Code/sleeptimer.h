#ifndef SLEEPTIMER_H
#define SLEEPTIMER_H

/**
 * Sleep timer module.
 * When the timer reaches 2 minutes since the last user input, it calls this
 * module, which initialises shutdown.
 *
 * Inputs:  None
 *
 * Outputs: Power down state change.
 */
extern int sleepTimerCounts;

void initialiseSleepTimer(void);

/**
 * resetSleepTimer
 * Upon user input reset counts value to 2 minutes.
 */
void resetSleepTimer(void);

/**
 * sleepTimerExpire
 * upon expiration of the two minutes, change required state to POWER_OFF
 */
void sleepTimerExpire(void);

#endif //SLEEPTIMER_H
