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
 * License along with this program; if not, If not, 
 * see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef __NITF_PARSEINFO_H__
#define __NITF_PARSEINFO_H__

#include "nitf/System.h"
#include "nitf/HashTable.h"


/* Choose wisely my son (do this dynamically in the reader)*/
#define NITF_PARSEINFO_NUMHASHBUCKETS 10

/****************************
*** NOTE ABOUT THE MACROS ***
*****************************
All of these macros make the assumption that an instance of a NITF_BOOL
named success is in scope and can be overwritten.  Additionally, a label
called CATCH_ERROR must also exist.  These exist to allow the macors to
simulate throwing as seen in C++.  They do nothing more than reduce the
amount of code needed to perform rigorous error checking.
*/
#define NITF_PARSEINFO_SET(parseInfo_, key_, data_, error_)     \
    success = nitf_ParseInfo_set(parseInfo_,                        \
                                 key_,                              \
                                 data_,                             \
                                 error_);                           \
    if( !success)  goto CATCH_ERROR;

NITF_CXX_GUARD

/*!
 *  \struct nitf_ParseInfo
 *  \brief This object stores information critical to parsing
 *
 *  The ParseInfo object stores information which has been validated and can
 *  safely be used to make decisions while parsing the NITF file or recovering
 *  from errors.  Only validated information should ever be placedin this
 *  object, and all information which is returned can be assumed to be valid.
 */
typedef struct _nitf_ParseInfo
{
    nitf_HashTable *hashTable;  /* Hash table to store all of the parsing info */

}
nitf_ParseInfo;


/*!
 *  Construct a ParseInfo object
 *  This function creates an empty ParseInfo object.
 *  \param error An error object to fill if a problem occurs
 *  \return A ParseInfo object or NULL upon failure
 */
NITFAPI(nitf_ParseInfo *) nitf_ParseInfo_construct(nitf_Error * error);


/*!
 *  Destruct a ParseInfo object
 *  This function destructs a ParseInfo object and NULL sets its pointer
 *  \param parseInfoPtr A pointer to a parseInfo object
 */
NITFAPI(void) nitf_ParseInfo_destruct(nitf_ParseInfo ** parseInfoPtr);


/*!
 *  Get information out of the ParseInfo object
 *  This function returns information in the ParseInfo object.  If the
 *  information does not exist (is not valid) NULL is returned.
 *  \param parseInfo A parseInfo object
 *  \param dataPtr A pointer to the data to be stored
 *  \param fieldName A string describing the field to check
 *  \param error An error object to fill if a problem occurs
 *  \return 1 on success and 0 otherwise
 */
NITFAPI(NITF_BOOL) nitf_ParseInfo_get(nitf_ParseInfo * parseInfo,
                                      NITF_DATA * dataPtr,
                                      const char *fieldName,
                                      nitf_Error * error);

/*!
 *  Set information in the ParseInfo object
 *  This function sets information in the ParseInfo object. This information
 *  is assumed to have already been validated.  Be careful, what is actually
 *  stored is a pointer to the data, so make sure it has been dynamically
 *  allocated.
 *  \param parseInfo A parseInfo object
 *  \param fieldName A string describing the field to assign the data to
 *  \param dataPtr Pointer to the data to associate with the field
 *  \param error An error object to fill if a problem occurs
 *  \return 1 on success and 0 otherwise
 */
NITFPROT(NITF_BOOL) nitf_ParseInfo_set(nitf_ParseInfo * parseInfo,
                                       const char *fieldName,
                                       NITF_DATA * data,
                                       nitf_Error * error);


/*!
 *  Remove information from the ParseInfo object.
 *  NOT DELETE, here is the deal... When an object is removed the ParseInfo
 *  object passes back a handle to it and simply forgets about it.  That
 *  dynamic memory then becomes your responsibility.
 *  \param parseInfo A parseInfo object
 *  \param fieldName A string describing the field to remove
 *  \param error An error object to fill a problem occurs
 *  \return Pointer to the removed data or NULL on failure
 */
NITFPROT(NITF_DATA *) nitf_ParseInfo_remove(nitf_ParseInfo * parseInfo,
        const char *fieldName,
        nitf_Error * error);


NITF_CXX_ENDGUARD

#endif
