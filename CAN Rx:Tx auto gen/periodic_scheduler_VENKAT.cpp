#include <stdint.h>
#include "io.hpp"
#include "periodic_callback.h"
#include "can.h"
#include "io.hpp"
#include <stdio.h>
#include "_can_dbc/generated_can.h"

can_msg_t msg;

int sensors()
{
    return LS.getPercentValue();
}

bool period_init(void)
{
    CAN_init(can1, 100, 5, 5, NULL, NULL);
    CAN_reset_bus(can1);
    CAN_bypass_filter_accept_all_msgs();
    return true; // Must return true upon success
}

void period_1Hz(uint32_t count)
{
    if(CAN_is_bus_off(can1))
        CAN_reset_bus(can1);
}

void period_10Hz(uint32_t count)
{
    TESTING_CAN_t testing_cmd = { 0 };
    testing_cmd.TESTING_CAN_signal = sensors();
    printf("%d", &testing_cmd.TESTING_CAN_signal);

    can_msg_t can_msg = { 0 };
    dbc_msg_hdr_t msg_hdr = dbc_encode_TESTING_CAN(can_msg.data.bytes, &testing_cmd);
    can_msg.msg_id = msg_hdr.mid;
    can_msg.frame_fields.data_len = msg_hdr.dlc;
    CAN_tx(can1, &can_msg, 0);
}

