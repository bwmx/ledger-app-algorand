/*******************************************************************************
*   (c) 2018 - 2022 Zondax AG
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

#include <stdio.h>
#include <zxmacros.h>
#include <zxformat.h>
#include <zxtypes.h>

#include "app_mode.h"
#include "tx.h"
#include "coin.h"
#include "parser_common.h"
#include "parser_impl.h"
#include "common/parser.h"
#include "parser_encoding.h"

#include "base64.h"
#include "algo_asa.h"

#include "crypto.h"


parser_error_t parser_parse(parser_context_t *ctx,
                            const uint8_t *data,
                            size_t dataLen,
                            parser_tx_t *tx_obj) {
    CHECK_ERROR(parser_init(ctx, data, dataLen))
    ctx->parser_tx_obj = tx_obj;
    return _read(ctx, tx_obj);
}

parser_error_t parser_validate(parser_context_t *ctx) {
    // Iterate through all items to check that all can be shown and are valid
    uint8_t numItems = 0;
    CHECK_ERROR(parser_getNumItems(&numItems))

    char tmpKey[40];
    char tmpVal[40];

    for (uint8_t idx = 0; idx < numItems; idx++) {
        uint8_t pageCount = 0;
        CHECK_ERROR(parser_getItem(ctx, idx, tmpKey, sizeof(tmpKey), tmpVal, sizeof(tmpVal), 0, &pageCount))
    }
    return parser_ok;
}

parser_error_t parser_getNumItems(uint8_t *num_items) {
    *num_items = _getNumItems();
    if (tx_group_is_initialized() && app_mode_blindsign_required()) {
        // Add Group Txn Hash, Max Fees
        *num_items += 2;
    }
    if(*num_items == 0) {
        return parser_unexpected_number_items;
    }
    return parser_ok;
}

static parser_error_t parser_getCommonNumItems(uint8_t *common_num_items) {
    *common_num_items = _getCommonNumItems();
    if(*common_num_items == 0) {
        return parser_unexpected_number_items;
    }
    return parser_ok;
}

static parser_error_t parser_getTxNumItems(uint8_t *tx_num_items) {
    *tx_num_items = _getTxNumItems();
    return parser_ok;
}

static void cleanOutput(char *outKey, uint16_t outKeyLen,
                        char *outVal, uint16_t outValLen)
{
    MEMZERO(outKey, outKeyLen);
    MEMZERO(outVal, outValLen);
    snprintf(outKey, outKeyLen, "?");
    snprintf(outVal, outValLen, " ");
}

static parser_error_t checkSanity(uint8_t numItems, uint8_t displayIdx)
{
    if ( displayIdx >= numItems) {
        return parser_display_idx_out_of_range;
    }
    return parser_ok;
}

static parser_error_t parser_printTxType(const parser_context_t *ctx, char *outKey, uint16_t outKeyLen, char *outVal, uint16_t outValLen, uint8_t *pageCount)
{
    *pageCount = 1;
    snprintf(outKey, outKeyLen, "Txn type");

    switch (ctx->parser_tx_obj->type) {
        case TX_PAYMENT:
            snprintf(outVal, outValLen, "Payment");
            break;
        case TX_KEYREG:
            snprintf(outVal, outValLen, "Key reg");
            break;
        case TX_ASSET_XFER:
            snprintf(outVal, outValLen, "Asset xfer");
            break;
        case TX_ASSET_FREEZE:
            snprintf(outVal, outValLen, "Asset Freeze");
            break;
        case TX_ASSET_CONFIG:
            snprintf(outVal, outValLen, "Asset config");
            break;
        case TX_APPLICATION:
            snprintf(outVal, outValLen, "Application");
            break;
        default:
            return parser_unexpected_error;
    }
    return parser_ok;
}

static parser_error_t parser_printBoxes(char *outKey, uint16_t outKeyLen, char *outVal, uint16_t outValLen, uint8_t displayIdx,
                                        uint8_t pageIdx, uint8_t *pageCount, txn_application *application) {
    if (outKey == NULL || outVal == NULL || application ==NULL) {
        return parser_unexpected_error;
    }

    const uint8_t tmpIdx = displayIdx -  IDX_BOXES;
    if (tmpIdx >= MAX_FOREIGN_APPS) return parser_unexpected_value;

    snprintf(outKey, outKeyLen, "Box %d", application->boxes[tmpIdx].i);

    if (application->boxes[tmpIdx].n != NULL && application->boxes[tmpIdx].n_len > 0) {

        bool printable = true;
        for (uint16_t j = 0; j < application->boxes[tmpIdx].n_len; j++) {
            printable &= IS_PRINTABLE(*(application->boxes[tmpIdx].n + j));
        }

        if (printable) {
            pageStringExt(outVal, outValLen, (const char*) application->boxes[tmpIdx].n,
                        application->boxes[tmpIdx].n_len, pageIdx, pageCount);
        } else {
            base64_encode(outVal, outValLen, (const uint8_t*) application->boxes[tmpIdx].n, application->boxes[tmpIdx].n_len);
        }
    } else {
        char null_box[8] = {0};
        base64_encode(outVal, outValLen, (const uint8_t*) null_box, sizeof(null_box));
    }

    return parser_ok;
}

static parser_error_t parser_printCommonParams(const parser_tx_t *parser_tx_obj,
                                               uint8_t displayIdx,
                                               char *outKey, uint16_t outKeyLen,
                                               char *outVal, uint16_t outValLen,
                                               uint8_t pageIdx, uint8_t *pageCount)
{
    *pageCount = 1;
    char buff[80] = {0};
    switch (displayIdx) {
        case IDX_COMMON_SENDER:
            snprintf(outKey, outKeyLen, "Sender");
            if (encodePubKey((uint8_t*) buff, sizeof(buff), parser_tx_obj->sender) == 0) {
                return parser_unexpected_buffer_end;
            }
            pageString(outVal, outValLen, buff, pageIdx, pageCount);
            return parser_ok;

        case IDX_COMMON_REKEY_TO: {
            snprintf(outKey, outKeyLen, "Rekey to");
            const char warning[9] = "WARNING: ";
            const uint8_t warning_size = strnlen(warning, 9);
            MEMCPY(buff, warning, warning_size);
            if (encodePubKey((uint8_t*) (buff + warning_size), sizeof(buff) - warning_size, parser_tx_obj->rekey) == 0) {
                 return parser_unexpected_buffer_end;
            }
            pageString(outVal, outValLen, buff, pageIdx, pageCount);
            return parser_ok;
        }

        case IDX_COMMON_FEE:
            snprintf(outKey, outKeyLen, "Fee");
            return _toStringBalance((uint64_t*) &parser_tx_obj->fee, COIN_AMOUNT_DECIMAL_PLACES, "", COIN_TICKER,
                                    outVal, outValLen, pageIdx, pageCount);

        case IDX_COMMON_GEN_ID:
            snprintf(outKey, outKeyLen, "Genesis ID");
            pageString(outVal, outValLen, parser_tx_obj->genesisID, pageIdx, pageCount);
            return parser_ok;

        case IDX_COMMON_LEASE:
            snprintf(outKey, outKeyLen, "Lease");
            base64_encode(buff, sizeof(buff), (const uint8_t*) parser_tx_obj->lease, sizeof(parser_tx_obj->lease));
            pageString(outVal, outValLen, buff, pageIdx, pageCount);
            return parser_ok;

        case IDX_COMMON_GEN_HASH:
            snprintf(outKey, outKeyLen, "Genesis hash");
            base64_encode(buff, sizeof(buff), (const uint8_t*) parser_tx_obj->genesisHash, sizeof(parser_tx_obj->genesisHash));
            pageString(outVal, outValLen, buff, pageIdx, pageCount);
            return parser_ok;

        case IDX_COMMON_GROUP_ID:
            snprintf(outKey, outKeyLen, "Group ID");
            base64_encode(buff, sizeof(buff), (const uint8_t*) parser_tx_obj->groupID, sizeof(parser_tx_obj->groupID));
            pageString(outVal, outValLen, buff, pageIdx, pageCount);
            return parser_ok;

        case IDX_COMMON_NOTE:
            snprintf(outKey, outKeyLen, "Note");
            snprintf(outVal, outValLen, "%d bytes", parser_tx_obj->note_len);
            return parser_ok;

#if 0
        case IDX_COMMON_FIRST_VALID:
            snprintf(outKey, outKeyLen, "First valid");
            if (int64_to_str(outVal, outValLen, parser_tx_obj->firstValid) != NULL) {
                return parser_unexpected_error;
            }
            return parser_ok;

        case IDX_COMMON_LAST_VALID:
            snprintf(outKey, outKeyLen, "Last valid");
            if (int64_to_str(outVal, outValLen, parser_tx_obj->lastValid) != NULL) {
                return parser_unexpected_error;
            }
            return parser_ok;
#endif
        default:
            break;
    }

    return parser_display_idx_out_of_range;
}

static parser_error_t parser_printTxPayment(const txn_payment *payment,
                                                   uint8_t displayIdx,
                                                   char *outKey, uint16_t outKeyLen,
                                                   char *outVal, uint16_t outValLen,
                                                   uint8_t pageIdx, uint8_t *pageCount)
{
    *pageCount = 1;
    char buff[65] = {0};
    switch (displayIdx) {
        case IDX_PAYMENT_RECEIVER:
            snprintf(outKey, outKeyLen, "Receiver");
            if (encodePubKey((uint8_t*) buff, sizeof(buff), payment->receiver) == 0) {
                return parser_unexpected_buffer_end;
            }
            pageString(outVal, outValLen, buff, pageIdx, pageCount);
            return parser_ok;

        case IDX_PAYMENT_AMOUNT:
            snprintf(outKey, outKeyLen, "Amount");
            return _toStringBalance((uint64_t*) &payment->amount, COIN_AMOUNT_DECIMAL_PLACES, "", COIN_TICKER,
                                    outVal, outValLen, pageIdx, pageCount);
            break;

        case IDX_PAYMENT_CLOSE_TO:
            snprintf(outKey, outKeyLen, "Close to");
            if (encodePubKey((uint8_t*) buff, sizeof(buff), payment->close) == 0) {
                return parser_unexpected_buffer_end;
            }
            pageString(outVal, outValLen, buff, pageIdx, pageCount);
            return parser_ok;
            break;

        default:
            break;
    }

    return parser_display_idx_out_of_range;
}

static parser_error_t parser_printTxKeyreg(const txn_keyreg *keyreg,
                                                   uint8_t displayIdx,
                                                   char *outKey, uint16_t outKeyLen,
                                                   char *outVal, uint16_t outValLen,
                                                   uint8_t pageIdx, uint8_t *pageCount)
{
    *pageCount = 1;
    char buff[45];
    switch (displayIdx) {
        case IDX_KEYREG_VOTE_PK:
            snprintf(outKey, outKeyLen, "Vote PK");
            base64_encode(buff, sizeof(buff), (const uint8_t*) keyreg->votepk, sizeof(keyreg->votepk));
            pageString(outVal, outValLen, buff, pageIdx, pageCount);
            return parser_ok;

        case IDX_KEYREG_VRF_PK:
            snprintf(outKey, outKeyLen, "VRF PK");
            base64_encode(buff, sizeof(buff), (const uint8_t*) keyreg->vrfpk, sizeof(keyreg->vrfpk));
            pageString(outVal, outValLen, buff, pageIdx, pageCount);
            return parser_ok;

        case IDX_KEYREG_SPRF_PK: {
            snprintf(outKey, outKeyLen, "SPRF PK");
            char tmpBuff[90];
            base64_encode(tmpBuff, sizeof(tmpBuff), (const uint8_t*) keyreg->sprfkey, sizeof(keyreg->sprfkey));
            pageString(outVal, outValLen, tmpBuff, pageIdx, pageCount);
            return parser_ok;
        }

        case IDX_KEYREG_VOTE_FIRST:
            snprintf(outKey, outKeyLen, "Vote first");
            if (int64_to_str(outVal, outValLen, keyreg->voteFirst) != NULL) {
                return parser_unexpected_error;
            }
            return parser_ok;

        case IDX_KEYREG_VOTE_LAST:
            snprintf(outKey, outKeyLen, "Vote last");
            if (int64_to_str(outVal, outValLen, keyreg->voteLast) != NULL) {
                return parser_unexpected_error;
            }
            return parser_ok;

        case IDX_KEYREG_KEY_DILUTION:
            snprintf(outKey, outKeyLen, "Key dilution");
            if (int64_to_str(outVal, outValLen, keyreg->keyDilution) != NULL) {
                return parser_unexpected_error;
            }
            return parser_ok;

        case IDX_KEYREG_PARTICIPATION:
            snprintf(outKey, outKeyLen, "Participating");
            if (keyreg->nonpartFlag) {
                snprintf(outVal, outValLen, "No");
            } else {
                snprintf(outVal, outValLen, "Yes");
            }
            return parser_ok;

        default:
            break;
    }

    return parser_display_idx_out_of_range;
}

static parser_error_t parser_printTxAssetXfer(const txn_asset_xfer *asset_xfer,
                                                   uint8_t displayIdx,
                                                   char *outKey, uint16_t outKeyLen,
                                                   char *outVal, uint16_t outValLen,
                                                   uint8_t pageIdx, uint8_t *pageCount)
{
    *pageCount = 1;
    union {
        char bufferUI[200];
        char buff[65];
    } tmpBuff;

    switch (displayIdx) {
        case IDX_XFER_ASSET_ID: {
            snprintf(outKey, outKeyLen, "Asset ID");
            const algo_asset_info_t *asa = algo_asa_get(asset_xfer->id);
            if (uint64_to_str(tmpBuff.bufferUI, sizeof(tmpBuff.bufferUI), asset_xfer->id) != NULL) {
                return parser_unexpected_value;
            }
            if (asa == NULL) {
                snprintf(outVal, outValLen, "#%s", tmpBuff.bufferUI);
            } else {
                snprintf(outVal, outValLen, "%s (#%s)", asa->name, tmpBuff.bufferUI);
            }
            return parser_ok;
        }

        case IDX_XFER_AMOUNT: {
            const algo_asset_info_t *asa = algo_asa_get(asset_xfer->id);
            if (asa == NULL) {
                snprintf(outKey, outKeyLen, "Amount");
                return _toStringBalance((uint64_t*) &asset_xfer->amount, 0, "", "Base unit ",
                                        outVal, outValLen, pageIdx, pageCount);
            } else {
                snprintf(outKey, outKeyLen, "Amount");
                return _toStringBalance((uint64_t*) &asset_xfer->amount, asa->decimals, "", (char*)asa->unit,
                                        outVal, outValLen, pageIdx, pageCount);
            }
        }

        case IDX_XFER_SOURCE:
            snprintf(outKey, outKeyLen, "Asset src");
            if (encodePubKey((uint8_t*) tmpBuff.buff, sizeof(tmpBuff.buff), asset_xfer->sender) == 0) {
                return parser_unexpected_buffer_end;
            }
            pageString(outVal, outValLen, tmpBuff.buff, pageIdx, pageCount);
            return parser_ok;

        case IDX_XFER_DESTINATION:
            snprintf(outKey, outKeyLen, "Asset dst");
            if (encodePubKey((uint8_t*) tmpBuff.buff, sizeof(tmpBuff.buff), asset_xfer->receiver) == 0) {
                return parser_unexpected_buffer_end;
            }
            pageString(outVal, outValLen, tmpBuff.buff, pageIdx, pageCount);
            return parser_ok;

        case IDX_XFER_CLOSE:
            snprintf(outKey, outKeyLen, "Asset close");
            if (encodePubKey((uint8_t*) tmpBuff.buff, sizeof(tmpBuff.buff), asset_xfer->close) == 0) {
                return parser_unexpected_buffer_end;
            }
            pageString(outVal, outValLen, tmpBuff.buff, pageIdx, pageCount);
            return parser_ok;

        default:
            break;
    }

    return parser_display_idx_out_of_range;
}

static parser_error_t parser_printTxAssetFreeze(const txn_asset_freeze *asset_freeze,
                                                   uint8_t displayIdx,
                                                   char *outKey, uint16_t outKeyLen,
                                                   char *outVal, uint16_t outValLen,
                                                   uint8_t pageIdx, uint8_t *pageCount)
{
    *pageCount = 1;
    char buff[65] = {0};
    switch (displayIdx) {
        case IDX_FREEZE_ASSET_ID:
            snprintf(outKey, outKeyLen, "Asset ID");
            if (uint64_to_str(outVal, outValLen, asset_freeze->id) != NULL) {
                return parser_unexpected_error;
            }
            return parser_ok;

        case IDX_FREEZE_ACCOUNT:
            snprintf(outKey, outKeyLen, "Asset account");
            if (encodePubKey((uint8_t*) buff, sizeof(buff), asset_freeze->account) == 0) {
                return parser_unexpected_buffer_end;
            }
            pageString(outVal, outValLen, buff, pageIdx, pageCount);
            return parser_ok;

        case IDX_FREEZE_FLAG:
            snprintf(outKey, outKeyLen, "Freeze flag");
            if (asset_freeze->flag) {
                snprintf(outVal, outValLen, "Frozen");
            } else {
                snprintf(outVal, outValLen, "Unfrozen");
            }
            return parser_ok;
            break;

        default:
            break;
    }

    return parser_display_idx_out_of_range;
}

static parser_error_t parser_printTxAssetConfig(const txn_asset_config *asset_config,
                                                   uint8_t displayIdx,
                                                   char *outKey, uint16_t outKeyLen,
                                                   char *outVal, uint16_t outValLen,
                                                   uint8_t pageIdx, uint8_t *pageCount)
{
    *pageCount = 1;
    char buff[100] = {0};
    switch (displayIdx) {
        case IDX_CONFIG_ASSET_ID:
            snprintf(outKey, outKeyLen, "Asset ID");
            if (asset_config->id == 0) {
                snprintf(outKey, outKeyLen, "Create");
            } else {
                if (uint64_to_str(outVal, outValLen, asset_config->id) != NULL) {
                    return parser_unexpected_error;
                }
            }
            return parser_ok;

        case IDX_CONFIG_TOTAL_UNITS:
            snprintf(outKey, outKeyLen, "Total units");
            if (uint64_to_str(outVal, outValLen, asset_config->params.total) != NULL) {
                return parser_unexpected_error;
            }
            return parser_ok;

        case IDX_CONFIG_FROZEN:
            snprintf(outKey, outKeyLen, "Default frozen");
            if (asset_config->params.default_frozen) {
                snprintf(outVal, outValLen, "Frozen");
            } else {
                snprintf(outVal, outValLen, "Unfrozen");
            }
            return parser_ok;

        case IDX_CONFIG_UNIT_NAME:
            snprintf(outKey, outKeyLen, "Unit name");
            MEMCPY(buff,asset_config->params.unitname, sizeof(asset_config->params.unitname));
            pageString(outVal, outValLen, buff, pageIdx, pageCount);
            return parser_ok;

        case IDX_CONFIG_DECIMALS:
            snprintf(outKey, outKeyLen, "Decimals");
            if (uint64_to_str(outVal, outValLen, asset_config->params.decimals) != NULL) {
                return parser_unexpected_error;
            }
            return parser_ok;

        case IDX_CONFIG_ASSET_NAME:
            snprintf(outKey, outKeyLen, "Asset name");
            MEMCPY(buff,asset_config->params.assetname, sizeof(asset_config->params.assetname));
            pageString(outVal, outValLen, buff, pageIdx, pageCount);
            return parser_ok;

        case IDX_CONFIG_URL:
            snprintf(outKey, outKeyLen, "URL");
            MEMCPY(buff,asset_config->params.url, sizeof(asset_config->params.url));
            pageString(outVal, outValLen, buff, pageIdx, pageCount);
            return parser_ok;

        case IDX_CONFIG_METADATA_HASH:
            snprintf(outKey, outKeyLen, "Metadata hash");
            base64_encode(buff, sizeof(buff), (const uint8_t*) asset_config->params.metadata_hash, sizeof(asset_config->params.metadata_hash));
            pageString(outVal, outValLen, buff, pageIdx, pageCount);
            return parser_ok;

        case IDX_CONFIG_MANAGER:
            snprintf(outKey, outKeyLen, "Manager");
            return _toStringAddress((uint8_t*) asset_config->params.manager, outVal, outValLen, pageIdx, pageCount);

        case IDX_CONFIG_RESERVE:
            snprintf(outKey, outKeyLen, "Reserve");
            return _toStringAddress((uint8_t*) asset_config->params.reserve, outVal, outValLen, pageIdx, pageCount);

        case IDX_CONFIG_FREEZER:
            snprintf(outKey, outKeyLen, "Freezer");
            return _toStringAddress((uint8_t*) asset_config->params.freeze, outVal, outValLen, pageIdx, pageCount);

        case IDX_CONFIG_CLAWBACK:
            snprintf(outKey, outKeyLen, "Clawback");
            return _toStringAddress((uint8_t*) asset_config->params.clawback, outVal, outValLen, pageIdx, pageCount);

        default:
            break;
    }

    return parser_display_idx_out_of_range;
}

static parser_error_t parser_printTxApplication(parser_context_t *ctx,
                                                uint8_t displayIdx,
                                                txn_application_index_e itemType,
                                                char *outKey, uint16_t outKeyLen,
                                                char *outVal, uint16_t outValLen,
                                                uint8_t pageIdx, uint8_t *pageCount)
{
    *pageCount = 1;
    char buff[65] = {0};
    txn_application *application = &ctx->parser_tx_obj->application;

    switch (itemType) {
        case IDX_APP_ID:
            snprintf(outKey, outKeyLen, "App ID");
            if (uint64_to_str(outVal, outValLen, application->id) != NULL) {
                return parser_unexpected_error;
            }
            return parser_ok;

        case IDX_ON_COMPLETION:
            snprintf(outKey, outKeyLen, "On completion");
            switch (application->oncompletion)
            {
            case NOOPOC:
                snprintf(outVal, outValLen, "NoOp");
                break;
            case OPTINOC:
                snprintf(outVal, outValLen, "OptIn");
                break;
            case CLOSEOUTOC:
                snprintf(outVal, outValLen, "CloseOut");
                break;
            case CLEARSTATEOC:
                snprintf(outVal, outValLen, "ClearState");
                break;
            case UPDATEAPPOC:
                snprintf(outVal, outValLen, "UpdateApp");
                break;
            case DELETEAPPOC:
                snprintf(outVal, outValLen, "DeleteApp");
                break;
            default:
                snprintf(outVal, outValLen, "Unknown");
                break;
            }
            return parser_ok;

        case IDX_BOXES: {
            return parser_printBoxes(outKey, outKeyLen, outVal, outValLen, displayIdx, pageIdx, pageCount, application);
        }

        case IDX_FOREIGN_APP: {
            const uint8_t tmpIdx = (displayIdx - (application->num_boxes)) - IDX_BOXES;
            // Check max index
            if (tmpIdx >= MAX_FOREIGN_APPS) return parser_unexpected_value;
            snprintf(outKey, outKeyLen, "Foreign app %d", tmpIdx);
            if (uint64_to_str(outVal, outValLen, application->foreign_apps[tmpIdx]) != NULL) {
                return parser_unexpected_error;
            }
            return parser_ok;
        }

        case IDX_FOREIGN_ASSET: {
            const uint8_t tmpIdx = (displayIdx - application->num_foreign_apps - application->num_boxes) - IDX_BOXES;
            // Check max index
            if (tmpIdx >= MAX_FOREIGN_ASSETS) return parser_unexpected_value;
            snprintf(outKey, outKeyLen, "Foreign asset %d", tmpIdx);
            if (uint64_to_str(outVal, outValLen, application->foreign_assets[tmpIdx]) != NULL) {
                return parser_unexpected_error;
            }
            return parser_ok;
        }

        case IDX_ACCOUNTS: {
            const uint8_t tmpIdx = (displayIdx - application->num_foreign_apps - application->num_foreign_assets - application->num_boxes) - IDX_BOXES;
            uint8_t account[ACCT_SIZE] = {0};
            snprintf(outKey, outKeyLen, "Account %d", tmpIdx);
            CHECK_ERROR(_getAccount(ctx, account, tmpIdx, application->num_accounts))
            if (encodePubKey((uint8_t*) buff, sizeof(buff), account) == 0) {
                return parser_unexpected_buffer_end;
            }
            pageString(outVal, outValLen, buff, pageIdx, pageCount);
            return parser_ok;
        }

        case IDX_APP_ARGS: {
            const uint8_t tmpIdx = (displayIdx - application->num_foreign_apps - application->num_foreign_assets - application->num_accounts - application->num_boxes) - IDX_BOXES;
            // Check max index
            if (tmpIdx >= MAX_ARG) return parser_unexpected_value;
            snprintf(outKey, outKeyLen, "App arg %d", tmpIdx);
            uint8_t* app_args_ptr = NULL;
            CHECK_ERROR(_getAppArg(ctx, &app_args_ptr, &application->app_args_len[tmpIdx], tmpIdx, MAX_ARGLEN, MAX_ARG))
            b64hash_data((unsigned char*)app_args_ptr, application->app_args_len[tmpIdx], buff, sizeof(buff));
            pageString(outVal, outValLen, buff, pageIdx, pageCount);
            return parser_ok;
        }

        case IDX_GLOBAL_SCHEMA:
            snprintf(outKey, outKeyLen, "Global schema");
            return _toStringSchema(&application->global_schema, outVal, outValLen, pageIdx, pageCount);

        case IDX_LOCAL_SCHEMA:
            snprintf(outKey, outKeyLen, "Local schema");
            return _toStringSchema(&application->local_schema, outVal, outValLen, pageIdx, pageCount);

        case IDX_EXTRA_PAGES:
            snprintf(outKey, outKeyLen, "Extra pages");
            snprintf(outVal, outValLen, "%d", application->extra_pages);
            return parser_ok;

        case IDX_APPROVE:
            snprintf(outKey, outKeyLen, "Apprv");
            b64hash_data((unsigned char*) application->aprog, application->aprog_len, buff, sizeof(buff));
            pageString(outVal, outValLen, buff, pageIdx, pageCount);
            return parser_ok;

        case IDX_CLEAR:
            snprintf(outKey, outKeyLen, "Clear");
            b64hash_data((unsigned char*) application->cprog, application->cprog_len, buff, sizeof(buff));
            pageString(outVal, outValLen, buff, pageIdx, pageCount);
            return parser_ok;

        default:
            break;
    }

    return parser_display_idx_out_of_range;
}


parser_error_t parser_getItem(parser_context_t *ctx,
                              uint8_t displayIdx,
                              char *outKey, uint16_t outKeyLen,
                              char *outVal, uint16_t outValLen,
                              uint8_t pageIdx, uint8_t *pageCount) {
    if (ctx == NULL || outKey == NULL || outVal == NULL || pageCount == NULL) {
        return parser_unexpected_value;
    }

    cleanOutput(outKey, outKeyLen, outVal, outValLen);
    *pageCount = 0;

    uint8_t numItems = 0;
    CHECK_ERROR(parser_getNumItems(&numItems))
    CHECK_APP_CANARY()

    if (tx_group_is_initialized()) {
        if (app_mode_blindsign_required()) {
            switch (displayIdx) {
                case 0xFF: {
                    #if defined(TARGET_STAX) || defined(TARGET_FLEX)
                    snprintf(outKey, outKeyLen, "Review Group Transaction");
                    snprintf(outVal, outValLen, "Total Transactions: %d", tx_group_get_num_of_txns());
                    #else
                    snprintf(outKey, outKeyLen, "Review Group Tx");
                    snprintf(outVal, outValLen, "Total Txs: %d", tx_group_get_num_of_txns());
                    #endif
                    return parser_ok;
                }
                case 0: {
                    snprintf(outKey, outKeyLen, "Group ID");
                    char buff[80] = {0};
                    base64_encode(buff, sizeof(buff), (const uint8_t*) ctx->parser_tx_obj->groupID, sizeof(ctx->parser_tx_obj->groupID));
                    pageString(outVal, outValLen, buff, pageIdx, pageCount);
                    return parser_ok;
                }
                case 1: {
                    snprintf(outKey, outKeyLen, "Sender");
                    char buff[80] = {0};
                    if (encodePubKey((uint8_t*) buff, sizeof(buff), ctx->parser_tx_obj->sender) == 0) {
                        return parser_unexpected_buffer_end;
                    }
                    pageString(outVal, outValLen, buff, pageIdx, pageCount);
                    return parser_ok;
                }
                case 2: {
                    snprintf(outKey, outKeyLen, "Max Fees");
                    return _toStringBalance((uint64_t*) &group_max_fees, COIN_AMOUNT_DECIMAL_PLACES, "", COIN_TICKER,
                                            outVal, outValLen, pageIdx, pageCount);
                }
            }
        } else {
            if (displayIdx == 0xFF) {
                #if defined(TARGET_STAX) || defined(TARGET_FLEX)
                snprintf(outKey, outKeyLen, "Review Group Transaction");
                snprintf(outVal, outValLen, "Transactions to review: %d", tx_group_get_num_of_txns() - tx_group_get_num_of_txns_reviewed());
                #else
                snprintf(outKey, outKeyLen, "Review Group Tx");
                snprintf(outVal, outValLen, "Txs to review: %d", tx_group_get_num_of_txns() - tx_group_get_num_of_txns_reviewed());
                #endif
                return parser_ok;
            }
        }
    }

    uint8_t commonItems = 0;
    CHECK_ERROR(parser_getCommonNumItems(&commonItems))

    uint8_t txItems = 0;
    CHECK_ERROR(parser_getTxNumItems(&txItems))

    CHECK_ERROR(checkSanity(numItems, displayIdx))

    if (displayIdx == 0) {
        return parser_printTxType(ctx, outKey, outKeyLen, outVal, outValLen, pageCount);
    }

    if (displayIdx <= commonItems) {
        uint8_t commonDisplayIdx = 0;
        CHECK_ERROR(getItem(displayIdx - 1, &commonDisplayIdx))
        return parser_printCommonParams(ctx->parser_tx_obj, commonDisplayIdx, outKey, outKeyLen,
                                        outVal, outValLen, pageIdx, pageCount);
    }

    uint8_t txDisplayIdx = 0;
    CHECK_ERROR(getItem(displayIdx - 1, &txDisplayIdx))
    displayIdx = displayIdx - commonItems -1;

    if (displayIdx < txItems) {
        switch (ctx->parser_tx_obj->type) {
            case TX_PAYMENT:
                return parser_printTxPayment(&ctx->parser_tx_obj->payment,
                                             txDisplayIdx, outKey, outKeyLen,
                                             outVal, outValLen, pageIdx, pageCount);
                break;
            case TX_KEYREG:
                return parser_printTxKeyreg(&ctx->parser_tx_obj->keyreg,
                                            txDisplayIdx, outKey, outKeyLen,
                                            outVal, outValLen, pageIdx, pageCount);
                break;
            case TX_ASSET_XFER:
                return parser_printTxAssetXfer(&ctx->parser_tx_obj->asset_xfer,
                                               txDisplayIdx, outKey, outKeyLen,
                                               outVal, outValLen, pageIdx, pageCount);
                break;
            case TX_ASSET_FREEZE:
                return parser_printTxAssetFreeze(&ctx->parser_tx_obj->asset_freeze,
                                                 txDisplayIdx, outKey, outKeyLen,
                                                 outVal, outValLen, pageIdx, pageCount);
                break;
            case TX_ASSET_CONFIG:
                return parser_printTxAssetConfig(&ctx->parser_tx_obj->asset_config,
                                                 txDisplayIdx, outKey, outKeyLen,
                                                 outVal, outValLen, pageIdx, pageCount);
                break;
            case TX_APPLICATION:
                return parser_printTxApplication(ctx,displayIdx, txDisplayIdx, outKey, outKeyLen,
                                                 outVal, outValLen, pageIdx, pageCount);
                break;
            default:
                return parser_unexpected_error;
        }
        return parser_display_idx_out_of_range;
    }

    return parser_display_idx_out_of_range;
}

parser_error_t parser_getTxnText(parser_context_t *ctx,
                                 char *outVal, uint16_t outValLen) {
    if (ctx == NULL || outVal == NULL) {
        return parser_unexpected_error;
    }

    switch (ctx->parser_tx_obj->type) {
        case TX_PAYMENT:
            snprintf(outVal, outValLen, "Review payment");
            break;
        case TX_KEYREG:
            snprintf(outVal, outValLen, "Review account\nregistration");
            break;
        case TX_ASSET_XFER:
            snprintf(outVal, outValLen, "Review ASA transfer");
            break;
        case TX_ASSET_FREEZE:
            snprintf(outVal, outValLen, "Review asset freeze");
            break;
        case TX_ASSET_CONFIG:
            snprintf(outVal, outValLen, "Review asset\nconfiguration");
            break;
        case TX_APPLICATION:
            snprintf(outVal, outValLen, "Review application\ncall");
            break;
        default:
            return parser_unknown_transaction;
    }

    return parser_ok;
}
