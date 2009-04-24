/* =========================================================================
 * This file is part of NITRO
 * =========================================================================
 *
 * (C) Copyright 2004 - 2008, General Dynamics - Advanced Information Systems
 *
 * NITRO is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this program; if not,
 * see <http://www.gnu.org/licenses/>.
 *
 */

#include "nitf/Utils.h"

NITFAPI(nitf_List*) nitf_Utils_splitString(
        char *str, unsigned int max, nitf_Error* error)
{
    unsigned int count = 0;
    nitf_List *parts;
    char *op, *cur, *end;
    size_t strLen;

    parts = nitf_List_construct(error);
    if (!parts)
        return NULL;

    strLen = strlen(str);
    end = str + strLen;

    op = str;

    if (max == 1)
    {
        char *val = NITF_MALLOC(strLen + 1);
        if (!val)
        {
            nitf_Error_init(error, NITF_STRERROR(NITF_ERRNO),
                    NITF_CTXT, NITF_ERR_MEMORY);
            return NULL;
        }
        memset(val, 0, strLen + 1);
        memcpy(val, str, strLen);
        nitf_List_pushBack(parts, val, error);
    }
    else
    {
        /* strtok is not thread safe */
        while(op < end)
        {
            char *val = NULL;
            int sz;
            /* skip past white space */
            while (isspace(*op) && op < end)
                ++op;
            cur = op;

            while(!isspace(*op) && op < end)
                ++op;

            if (cur == op)
                break;

            sz = op - cur;
            val = NITF_MALLOC(sz + 1);
            if (!val)
            {
                nitf_Error_init(error, NITF_STRERROR(NITF_ERRNO),
                        NITF_CTXT, NITF_ERR_MEMORY);
                return NULL;
            }
            memset(val, 0, sz + 1);
            memcpy(val, cur, sz);
            nitf_List_pushBack(parts, val, error);
            count++;

            /* check the count limit */
            if (max != 0 && count == (max - 1) && op < end)
            {
                /* push on the rest of the string - skip spaces first */
                while (isspace(*op) && op < end)
                    ++op;

                if (op < end)
                {
                    sz = end - op;
                    val = NITF_MALLOC(sz + 1);
                    if (!val)
                    {
                        nitf_Error_init(error, NITF_STRERROR(NITF_ERRNO),
                                NITF_CTXT, NITF_ERR_MEMORY);
                        return NULL;
                    }
                    memset(val, 0, sz + 1);
                    memcpy(val, op, sz);
                    nitf_List_pushBack(parts, val, error);
                }
                break;
            }
        }
    }

    return parts;
}

NITFAPI(NITF_BOOL) nitf_Utils_isNumeric(char *str)
{
    char *sp = NULL;
    if (!str)
        return 0;
    sp = str + strlen(str);
    if (sp <= str)
        return 0;

    do
    {
        if (!isdigit(*(--sp)))
            return 0;
    }
    while(sp > str);
    return 1;
}

NITFAPI(NITF_BOOL) nitf_Utils_isAlpha(char *str)
{
    char *sp = NULL;
    if (!str)
        return 0;
    sp = str + strlen(str);
    if (sp <= str)
        return 0;

    do
    {
        if (!isalpha(*(--sp)))
            return 0;
    }
    while(sp > str);
    return 1;
}

NITFPROT(void) nitf_Utils_trimString(char *str)
{
    nitf_Uint32 len;            /* Length of the string */
    char *strp;                 /* Pointer into the string */
    nitf_Uint32 i;

    /* strip the end */
    strp = (char *) (str + strlen(str) - 1);
    while (isspace(*strp) && strp != str)
        *(strp--) = 0;

    /* strip the front */
    len = strlen(str);
    strp = str;
    for (i = 0; i < len && isspace(*strp); ++i)
        strp++;
    if (strp != str)
    {
        len = str + len - strp;
        memmove(str, strp, len);
        str[len] = 0;
    }
    return;
}

NITFPROT(void) nitf_Utils_replace(char* str, char oldValue, char newValue)
{
    char *p;
    while( (p = strchr(str, oldValue)) != NULL)
    {
        *p = newValue;
    }

}

NITFPROT(void) nitf_Utils_baseName(char *base,
                                   const char* fullName,
                                   const char* extension)
{
    int i, begin = 0;
    int end = strlen(fullName);
    char *p = strstr(fullName, extension);
    for (i = 0; i < strlen(fullName); i++)
    {
        if ( *(fullName + i) == '/' || *(fullName + i) == '\\')
            begin = i + 1;
        
        if ( fullName + i == p)
            end = i - 1;
    }
    memcpy(base, &fullName[begin], end - begin + 1);
    base[ end - begin + 1] = 0;
}