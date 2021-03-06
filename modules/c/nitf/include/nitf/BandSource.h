/* =========================================================================
 * This file is part of NITRO
 * =========================================================================
 * 
 * (C) Copyright 2004 - 2014, MDA Information Systems LLC
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

#ifndef __NITF_BAND_SOURCE_H__
#define __NITF_BAND_SOURCE_H__

#include "nitf/System.h"
#include "nitf/DataSource.h"
#include "nitf/ImageReader.h"

NITF_CXX_GUARD
/*!
 *  TODO: We should offer an IOInterface source
 *
 */

/*!
 * Typedef nitf_BandSource
 */
typedef nitf_DataSource    nitf_BandSource;

/*!
 * Define nitf_BandSource_destruct which is just
 * nitf_DataSource_destruct
 */
#define nitf_BandSource_destruct nitf_DataSource_destruct



/*!
 *  \fn nitf_MemorySource_construct
 *  \brief A class for reading one band from memory (or VM)
 *
 *  The memory source class allows us to read directly from
 *  a data buffer.  In the event that this is a memory-mapped file,
 *  we will likely get a performance gain over the direct fd approach.
 *
 *  The constructor takes in a buffer, a size, and optionally
 *  a sampling factor (Typically, the factor will be applied most
 *  times during the case of memory mapping, although it may
 *  be used to sample down or cut the image into pieces).
 *
 *  Contains a static declaration of the specific implementation.
 *
 *  \param data The data
 *  \param size The size
 *  \param start The start offset
 *  \param numBytesPerPixel the number of bytes per pixel
 *         (if pixelSkip is equal to 0, then numBytesPerPixel is ignored)
 *  \param pixelSkip The amount of pixels to skip (0 signifies contiguous read)
 *         (this will get multipled by numBytesPerPixel to figure
 *          out how many actual bytes to skip)
 */
NITFAPI(nitf_BandSource *) nitf_MemorySource_construct(const void* data,
        nitf_Off size,
        nitf_Off start,
        int numBytesPerPixel,
        int pixelSkip,
        nitf_Error * error);

/*!
 *  \fn nitf_FileSource_construct
 *  \brief Provides impl for reading one band from an FD or HANDLE
 *
 *  The FileSource class is a BandSource that comes from an open
 *  file descriptor or handle.  Due to any number of constraints,
 *  not the least of which is the band interleaved by pixel case,
 *  we allow the creator to specify a start point, and a pixel skip
 *  (this would help you create a thumbnail as well).
 *
 *  Construct a file source from a handle, a start point, and
 *  a pixel skip.
 *
 *  \param fname The file to use
 *  \param start The location to seek to (as the beginning)
 *  \param numBytesPerPixel the number of bytes per pixel
 *         (if pixelSkip is equal to 0, then numBytesPerPixel is ignored)
 *  \param pixelSkip The amount of pixels to skip (0 signifies contiguous read)
 *        (this will get multipled by numBytesPerPixel to figure
 *         out how many actual bytes to skip)
 */
NITFAPI(nitf_BandSource *) nitf_FileSource_construct(nitf_IOHandle,
                                                     nitf_Off start,
                                                     int numBytesPerPixel,
                                                     int pixelSkip,
                                                     nitf_Error * error);

NITFAPI(nitf_BandSource *) nitf_FileSource_constructFile(const char* fname,
                                                         nitf_Off start,
                                                         int numBytesPerPixel,
                                                         int pixelSkip,
                                                         nitf_Error* error);

NITFAPI(nitf_BandSource *) nitf_IOSource_construct(nitf_IOInterface *io,
                                                   nitf_Off start,
                                                   int numBytesPerPixel,
                                                   int pixelSkip,
                                                   nitf_Error * error);

NITF_CXX_ENDGUARD

#endif
