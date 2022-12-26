/**
 * NEURON IIoT System for Industry 4.0
 * Copyright (C) 2020-2022 EMQ Technologies Co., Ltd All rights reserved.
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

#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

#include "file_req.h"

struct file_group_data {
    UT_array *tags;
    char *    group;
};

static void plugin_group_free(neu_plugin_group_t *pgp);

int file_group_timer(neu_plugin_t *plugin, neu_plugin_group_t *group)
{
    struct file_group_data *gd     = NULL;
    int                     length = plugin->file_length;

    if (group->user_data == NULL) {
        gd                = calloc(1, sizeof(struct file_group_data));
        group->user_data  = gd;
        group->group_free = plugin_group_free;
        utarray_new(gd->tags, &ut_ptr_icd);

        gd->group = strdup(group->group_name);
    }

    utarray_foreach(group->tags, neu_datatag_t *, tag)
    {
        FILE *       f      = NULL;
        struct stat  st     = { 0 };
        char *       buf    = calloc(1, length);
        neu_dvalue_t dvalue = { 0 };

        if ((tag->attribute & NEU_ATTRIBUTE_WRITE) == NEU_ATTRIBUTE_WRITE) {
            dvalue.type      = NEU_TYPE_ERROR;
            dvalue.value.i32 = NEU_ERR_TAG_ATTRIBUTE_NOT_SUPPORT;
            goto dvalue_result;
        }

        if (stat(tag->address, &st) != 0) {
            dvalue.type      = NEU_TYPE_ERROR;
            dvalue.value.i32 = NEU_ERR_FILE_NOT_EXIST;
            goto dvalue_result;
        }
        if ((f = fopen(tag->address, "rb+")) == NULL) {
            nlog_error("open file:%s", tag->address);
            dvalue.type      = NEU_TYPE_ERROR;
            dvalue.value.i32 = NEU_ERR_FILE_OPEN_FAILURE;
            goto dvalue_result;
        }

        int ret = fread(buf, sizeof(char), length, f);
        if (ret == 0) {
            nlog_error("read file failed:%s", tag->address);
            dvalue.type      = NEU_TYPE_ERROR;
            dvalue.value.i32 = NEU_ERR_FILE_READ_FAILURE;
            goto dvalue_result;
        }

        fseek(f, 0, SEEK_END);
        int size = ftell(f);
        if (size > length) {
            dvalue.type      = NEU_TYPE_ERROR;
            dvalue.value.i32 = NEU_ERR_FILE_TOO_LONG;
            goto dvalue_result;
        }

        dvalue.type = NEU_TYPE_STRING;
        strncpy(dvalue.value.str, buf, strlen(buf));
        fclose(f);

    dvalue_result:
        plugin->common.adapter_callbacks->driver.update(
            plugin->common.adapter, group->group_name, tag->name, dvalue);

        free(buf);
    }

    return 0;
}

static void plugin_group_free(neu_plugin_group_t *pgp)
{
    struct file_group_data *gd = (struct file_group_data *) pgp->user_data;

    utarray_foreach(gd->tags, neu_datatag_t **, tag) { free(*tag); }

    utarray_free(gd->tags);
    free(gd->group);

    free(gd);
}