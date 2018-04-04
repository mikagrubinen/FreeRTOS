/// DBC file: ../_can_dbc/243.dbc    Self node: 'VENKAT'  (ALL = 0)
/// This file can be included by a source file, for example: #include "generated.h"
#ifndef __GENEARTED_DBC_PARSER
#define __GENERATED_DBC_PARSER
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>



/// Extern function needed for dbc_encode_and_send()
extern bool dbc_app_send_can_msg(uint32_t mid, uint8_t dlc, uint8_t bytes[8]);

/// Missing in Action structure
typedef struct {
    uint32_t is_mia : 1;          ///< Missing in action flag
    uint32_t mia_counter_ms : 31; ///< Missing in action counter
} dbc_mia_info_t;

/// CAN message header structure
typedef struct { 
    uint32_t mid; ///< Message ID of the message
    uint8_t  dlc; ///< Data length of the message
} dbc_msg_hdr_t; 

static const dbc_msg_hdr_t TESTING_CAN_HDR =                      {  150, 1 };




/// Message: TESTING_CAN from 'VENKAT', DLC: 1 byte(s), MID: 150
typedef struct {
    uint8_t TESTING_CAN_signal;               ///< B7:0   Destination: MIRO

    // No dbc_mia_info_t for a message that we will send
} TESTING_CAN_t;


/// @{ These 'externs' need to be defined in a source file of your project
/// @}


/// Encode VENKAT's 'TESTING_CAN' message
/// @returns the message header of this message
static inline dbc_msg_hdr_t dbc_encode_TESTING_CAN(uint8_t bytes[8], TESTING_CAN_t *from)
{
    uint32_t raw;
    bytes[0]=bytes[1]=bytes[2]=bytes[3]=bytes[4]=bytes[5]=bytes[6]=bytes[7]=0;

    raw = ((uint32_t)(((from->TESTING_CAN_signal)))) & 0xff;
    bytes[0] |= (((uint8_t)(raw) & 0xff)); ///< 8 bit(s) starting from B0

    return TESTING_CAN_HDR;
}

/// Encode and send for dbc_encode_TESTING_CAN() message
static inline bool dbc_encode_and_send_TESTING_CAN(TESTING_CAN_t *from)
{
    uint8_t bytes[8];
    const dbc_msg_hdr_t hdr = dbc_encode_TESTING_CAN(bytes, from);
    return dbc_app_send_can_msg(hdr.mid, hdr.dlc, bytes);
}



/// Not generating code for dbc_decode_TESTING_CAN() since 'VENKAT' is not the recipient of any of the signals

#endif
