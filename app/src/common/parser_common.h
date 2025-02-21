/*******************************************************************************
*  (c) 2018 - 2022 Zondax AG
*
*  Licensed under the Apache License, Version 2.0 (the "License");
*  you may not use this file except in compliance with the License.
*  You may obtain a copy of the License at
*
*      http://www.apache.org/licenses/LICENSE-2.0
*
*  Unless required by applicable law or agreed to in writing, software
*  distributed under the License is distributed on an "AS IS" BASIS,
*  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*  See the License for the specific language governing permissions and
*  limitations under the License.
********************************************************************************/
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "parser_txdef.h"
#include <stdint.h>
#include <stddef.h>

#define CHECK_ERROR(__CALL) { \
    parser_error_t __err = __CALL;  \
    CHECK_APP_CANARY()  \
    if (__err!=parser_ok) return __err;}

typedef enum {
    // Generic errors
    parser_ok = 0,
    parser_no_data,
    parser_init_context_empty,
    parser_display_idx_out_of_range,
    parser_display_page_out_of_range,
    parser_unexpected_error,
    parser_blindsign_mode_required,

    // Coin generic
    parser_unexpected_type,
    parser_unexpected_method,
    parser_unexpected_buffer_end,
    parser_unexpected_value,
    parser_unexpected_number_items,
    parser_unexpected_version,
    parser_unexpected_characters,
    parser_unexpected_field,
    parser_duplicated_field,
    parser_value_out_of_range,
    parser_invalid_address,
    parser_unexpected_chain,
    parser_missing_field,
    parser_query_no_results,
    parser_program_fields_too_long,
    parser_too_many_extra_pages,
    parser_buffer_too_small,

    parser_unknown_transaction,
    parser_key_not_found,

    //Msgpack specific
    parser_msgpack_unexpected_type,
    parser_msgpack_unexpected_key,

    parser_msgpack_map_type_expected,
    parser_msgpack_map_type_not_supported,

    parser_msgpack_str_type_expected,
    parser_msgpack_str_type_not_supported,
    parser_msgpack_str_too_big,

    parser_msgpack_bin_type_expected,
    parser_msgpack_bin_type_not_supported,
    parser_msgpack_bin_unexpected_size,

    parser_msgpack_int_type_expected,

    parser_msgpack_bool_type_expected,

    parser_msgpack_array_unexpected_size,
    parser_msgpack_array_too_big,
    parser_msgpack_array_type_expected,

} parser_error_t;

typedef struct {
    const uint8_t *buffer;
    uint16_t bufferLen;
    uint16_t offset;
    parser_tx_t *parser_tx_obj;
} parser_context_t;

#ifdef __cplusplus
}
#endif
