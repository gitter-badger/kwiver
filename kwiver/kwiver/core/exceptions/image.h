/*ckwg +29
 * Copyright 2014 by Kitware, Inc.
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
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS IS''
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
 * \brief KWIVER Exceptions pertaining to image operations and manipulation
 */

#ifndef KWIVER_CORE_EXCEPTIONS_IMAGE_H
#define KWIVER_CORE_EXCEPTIONS_IMAGE_H

#include <string>

#include <kwiver/core/core-config.h>
#include <kwiver/core/exceptions/base.h>


namespace kwiver
{


/// Generic image exception
class KWIVER_CORE_EXPORT image_exception
  : public kwiver_core_base_exception
{
public:
  /// Constructor
  image_exception() KWIVER_NOTHROW;
  /// Destructor
  virtual ~image_exception() KWIVER_NOTHROW;
};


/// Exception for image sizing mismatch
/**
 * For when image shape/size equality must be asserted.
 */
class KWIVER_CORE_EXPORT image_size_mismatch_exception
  : public image_exception
{
public:
  /// Constructor
  image_size_mismatch_exception(std::string message,
                                size_t correct_w, size_t correct_h,
                                size_t given_w, size_t given_h) KWIVER_NOTHROW;
  /// Destructor
  virtual ~image_size_mismatch_exception() KWIVER_NOTHROW;

  /// Given error message string
  std::string m_message;
  /// The correct pixel width and height
  size_t m_correct_w,
         m_correct_h;
  /// The incorrect, given pixel width and height
  size_t m_given_w,
         m_given_h;
};

}

#endif // KWIVER_CORE_EXCEPTIONS_IMAGE_H