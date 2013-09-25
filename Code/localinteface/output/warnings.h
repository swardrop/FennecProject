#ifndef WARNINGS_H
#define WARNINGS_H

/* Warnings
 *
 * This module defines the behavour executed to indicate a particular warning.
 * These warnings are identified by the defined symbolic constants below.
 * To execute this behaviour, the public function showWarning is executed with
 * the warning code as its argument.
 *
 */

#define WARNING_OVERLOAD    0
#define WARNING_VARIANCE    1
#define WARNING_LARGEERROR  2

/** showWarning
 *  @args warning code
 *  @return status (0 for success)
 */
char showWarning(char warningCode)
{
    return 0;
}
#endif //WARNINGS_H