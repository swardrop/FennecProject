#ifndef SLEEPTIMER_H
#define SLEEPTIMER_H
/* This is the sleep timer module.
 * When the timer reaches 2 minutes since the last user input, it calls this
 * module, which initialises shutdown.
 *
 * Inputs:  None
 *
 * Outputs: Power down state change.
 */
extern int sleepTimerCounts;

void initialiseSleepTimer(void);
void resetSleepTimer(void);
void sleepTimerExpire(void);

#endif //SLEEPTIMER_H
