#include <stdint.h>
#include "io.hpp"
#include "periodic_callback.h"

#include "_can_dbc/generated_can.h"
#include "can.h"
#include "stdio.h"


const uint32_t                             TESTING_CAN__MIA_MS = 3000;
const TESTING_CAN_t                        TESTING_CAN__MIA_MSG = {.TESTING_CAN_signal = 50};

TESTING_CAN_t testing_msg = { 0 };


/// Called once before the RTOS is started, this is a good place to initialize things once
bool period_init(void)
{
    CAN_init(can1, 100, 5, 5, NULL, NULL);
    CAN_reset_bus(can1);
    CAN_bypass_filter_accept_all_msgs();
    testing_msg.mia_info.mia_counter_ms = 0;
    return true; // Must return true upon success
}

void period_1Hz(uint32_t count)
{
    if(CAN_is_bus_off(can1)){
        CAN_reset_bus(can1);
    }
}

void period_10Hz(uint32_t count)
{
    can_msg_t can_msg;
    
    // Empty all of the queued, and received messages within the last 10ms (100Hz callback frequency)
    while (CAN_rx(can1, &can_msg, 0))
    {
        // Form the message header from the metadata of the arriving message
        dbc_msg_hdr_t can_msg_hdr;
        can_msg_hdr.dlc = can_msg.frame_fields.data_len;
        can_msg_hdr.mid = can_msg.msg_id;
        
        // Attempt to decode the message (brute force, but should use switch/case with MID)
        dbc_decode_TESTING_CAN(&testing_msg, can_msg.data.bytes, &can_msg_hdr);
        LD.setNumber(testing_msg.TESTING_CAN_signal);
    }
    
    // Service the MIA counter of a regular (non MUX'd) message
    if(dbc_handle_mia_TESTING_CAN(&testing_msg, 100))
        LD.setNumber(testing_msg.TESTING_CAN_signal);
}
