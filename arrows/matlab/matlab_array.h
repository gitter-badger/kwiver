/*ckwg +29
 * Copyright 2016 by Kitware, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *  * Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 *  * Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 *  * Neither name of Kitware, Inc. nor the names of any contributors may be used
 *    to endorse or promote products derived from this software without specific
 *    prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHORS OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * \file
 * \brief Interface of matlab image object detector
 */

#ifndef VITAL_BINDINGS_MATLAB_ARRAY_H
#define VITAL_BINDINGS_MATLAB_ARRAY_H

#include <arrows/matlab/kwiver_algo_matlab_export.h>

#include <matrix.h>  // matlab include

#include <memory>

namespace kwiver {
namespace arrows {
namespace matlab {

typedef std::shared_ptr<mxArray> mxArraySptr;

/** \defgroup create_matlab_array Create Matlab Array
 * Factory functions to create managed Matlab arrays.
 * @{
 */

/**
 * @brief Create empty Matlab managed array.
 *
 * This function is a factory for managed Matlab arrays.
 *
 * @param r - number of rows in the array
 * @param c - number of columns in the array
 *
 * @return Managed pointer to the newly allocated array.
 */
KWIVER_ALGO_MATLAB_EXPORT mxArraySptr create_mxByteArray( size_t r, size_t c );

/**
 * @brief Create empty Matlab managed array.
 *
 * This function is a factory for managed Matlab arrays.
 *
 * @param r - number of rows in the array
 * @param c - number of columns in the array
 *
 * @return Managed pointer to the newly allocated array.
 */
KWIVER_ALGO_MATLAB_EXPORT mxArraySptr create_mxIntArray( size_t r, size_t c );

/**
 * @brief Create empty Matlab managed array.
 *
 * This function is a factory for managed Matlab arrays.
 *
 * @param r - number of rows in the array
 * @param c - number of columns in the array
 *
 * @return Managed pointer to the newly allocated array.
 */
KWIVER_ALGO_MATLAB_EXPORT mxArraySptr create_mxDoubleArray( size_t r, size_t c );
//@}

} } } // end namespace

#endif /* VITAL_BINDINGS_MATLAB_ARRAY_H */