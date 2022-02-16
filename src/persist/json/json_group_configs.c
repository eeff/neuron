/**
 * NEURON IIoT System for Industry 4.0
 * Copyright (C) 2020-2021 EMQ Technologies Co., Ltd All rights reserved.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 **/

/*
 * DO NOT EDIT THIS FILE MANUALLY!
 * It was automatically generated by `json-autotype`.
 */

#include <stdlib.h>
#include <string.h>

#include "json/json.h"

#include "persist/json/json_group_configs.h"

int neu_json_decode_group_configs_req(char *                         buf,
                                      neu_json_group_configs_req_t **result)
{
    int                           ret = 0;
    neu_json_group_configs_req_t *req =
        calloc(1, sizeof(neu_json_group_configs_req_t));

    neu_json_elem_t req_elems[] = { {
                                        .name = "read_interval",
                                        .t    = NEU_JSON_INT,
                                    },
                                    {
                                        .name = "group_config_name",
                                        .t    = NEU_JSON_STR,
                                    },
                                    {
                                        .name = "adapter_name",
                                        .t    = NEU_JSON_STR,
                                    } };
    ret = neu_json_decode(buf, NEU_JSON_ELEM_SIZE(req_elems), req_elems);
    if (ret != 0) {
        goto decode_fail;
    }

    req->read_interval     = req_elems[0].v.val_int;
    req->group_config_name = req_elems[1].v.val_str;
    req->adapter_name      = req_elems[2].v.val_str;

    *result = req;
    return ret;

decode_fail:
    if (req != NULL) {
        free(req);
    }
    return -1;
}

void neu_json_decode_group_configs_req_free(neu_json_group_configs_req_t *req)
{

    free(req->group_config_name);
    free(req->adapter_name);

    free(req);
}

int neu_json_encode_group_configs_resp(void *json_object, void *param)
{
    int                            ret = 0;
    neu_json_group_configs_resp_t *resp =
        (neu_json_group_configs_resp_t *) param;

    neu_json_elem_t resp_elems[] = { {
                                         .name      = "read_interval",
                                         .t         = NEU_JSON_INT,
                                         .v.val_int = resp->read_interval,
                                     },
                                     {
                                         .name      = "group_config_name",
                                         .t         = NEU_JSON_STR,
                                         .v.val_str = resp->group_config_name,
                                     },
                                     {
                                         .name      = "adapter_name",
                                         .t         = NEU_JSON_STR,
                                         .v.val_str = resp->adapter_name,
                                     } };
    ret = neu_json_encode_field(json_object, resp_elems,
                                NEU_JSON_ELEM_SIZE(resp_elems));

    return ret;
}