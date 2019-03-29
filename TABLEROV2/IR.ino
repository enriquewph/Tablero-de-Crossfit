#include "header.h"

CNec IRLremote;

void IR_init()
{
    IRLremote.begin(IR_RECEIVER_DATA_PIN);
}

bool IR_NewCommand()
{
    if (IRLremote.available())
    {
        // Get the new data from the remote
        auto data = IRLremote.read();

        if (data.address == IR_REMOTE_ADDRESS)
        {
            lastIRCommand = data.command;
            return true;
        }
    }
    else
        return false;
}
