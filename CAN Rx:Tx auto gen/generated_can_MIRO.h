/// DBC file: ../_can_dbc/243.dbc    Self node: 'MIRO'  (ALL = 0)
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
    
    dbc_mia_info_t mia_info;
} TESTING_CAN_t;


/// @{ These 'externs' need to be defined in a source file of your project
extern const uint32_t                             TESTING_CAN__MIA_MS;
extern const TESTING_CAN_t                        TESTING_CAN__MIA_MSG;
/// @}


/// Not generating code for dbc_encode_TESTING_CAN() since the sender is VENKAT and we are MIRO

/// Decode VENKAT's 'TESTING_CAN' message
/// @param hdr  The header of the message to validate its DLC and MID; this can be NULL to skip this check
static inline bool dbc_decode_TESTING_CAN(TESTING_CAN_t *to, const uint8_t bytes[8], const dbc_msg_hdr_t *hdr)
{
    const bool success = true;
    // If msg header is provided, check if the DLC and the MID match
    if (NULL != hdr && (hdr->dlc != TESTING_CAN_HDR.dlc || hdr->mid != TESTING_CAN_HDR.mid)) {
        return !success;
    }
    
    uint32_t raw;
    raw  = ((uint32_t)((bytes[0]))); ///< 8 bit(s) from B0
    to->TESTING_CAN_signal = ((raw));
    
    to->mia_info.mia_counter_ms = 0; ///< Reset the MIA counter
    
    return success;
}


/// Handle the MIA for VENKAT's TESTING_CAN message
/// @param   time_incr_ms  The time to increment the MIA counter with
/// @returns true if the MIA just occurred
/// @post    If the MIA counter reaches the MIA threshold, MIA struct will be copied to *msg
static inline bool dbc_handle_mia_TESTING_CAN(TESTING_CAN_t *msg, uint32_t time_incr_ms)
{
    bool mia_occurred = false;
    const dbc_mia_info_t old_mia = msg->mia_info;
    msg->mia_info.is_mia = (msg->mia_info.mia_counter_ms >= TESTING_CAN__MIA_MS);
    
    if (!msg->mia_info.is_mia) { // Not MIA yet, so keep incrementing the MIA counter
        msg->mia_info.mia_counter_ms += time_incr_ms;
    }
    else if(!old_mia.is_mia)   { // Previously not MIA, but it is MIA now
        // Copy MIA struct, then re-write the MIA counter and is_mia that is overwriten
        *msg = TESTING_CAN__MIA_MSG;
        msg->mia_info.mia_counter_ms = TESTING_CAN__MIA_MS;
        msg->mia_info.is_mia = true;
        mia_occurred = true;
    }
    
    return mia_occurred;
}

#endif

