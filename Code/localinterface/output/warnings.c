#include "../../spi.h"
#include "../../remoteinterface/rs232.h"
#include "../../../GUI/commscodes.h"
#include "warnings.h"

char showWarning(char warningCode)
{
    if (warningCode == WARNING_VARIANCE)
        RS232writeByte(COMM_WARN_VARIANCE);
    if (warningCode == WARNING_OVERLOAD)
        RS232writeByte(COMM_WARN_OVERLOAD);
    return 0;
}