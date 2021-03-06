/*ckwg +29
 * Copyright 2011-2013 by Kitware, Inc.
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

#ifndef SPROKIT_PIPELINE_UTIL_LOAD_PIPE_EXCEPTION_H
#define SPROKIT_PIPELINE_UTIL_LOAD_PIPE_EXCEPTION_H

#include "pipeline_util-config.h"

#include "path.h"

#include <sprokit/pipeline/types.h>

#include <string>

#include <cstddef>

/**
 * \file load_pipe_exception.h
 *
 * \brief Header for exceptions used when loading a pipe declaration.
 */

namespace sprokit
{

/**
 * \class load_pipe_exception load_pipe_exception.h <sprokit/pipeline_util/load_pipe_exception.h>
 *
 * \brief The base class for all exceptions thrown when loading a pipe declaration.
 *
 * \ingroup exceptions
 */
class SPROKIT_PIPELINE_UTIL_EXPORT load_pipe_exception
  : public pipeline_exception
{
  public:
    /**
     * \brief Constructor.
     */
    load_pipe_exception() throw();
    /**
     * \brief Destructor.
     */
    virtual ~load_pipe_exception() throw();
};

/**
 * \class file_no_exist_exception load_pipe_exception.h <sprokit/pipeline_util/load_pipe_exception.h>
 *
 * \brief The exception thrown when a file does not exist.
 *
 * \ingroup exceptions
 */
class SPROKIT_PIPELINE_UTIL_EXPORT file_no_exist_exception
  : public load_pipe_exception
{
  public:
    /**
     * \brief Constructor.
     *
     * \param fname The path that does not exist.
     */
    file_no_exist_exception(path_t const& fname) throw();
    /**
     * \brief Destructor.
     */
    ~file_no_exist_exception() throw();

    /// The path that does not exist.
    path_t const m_fname;
};

/**
 * \class not_a_file_exception load_pipe_exception.h <sprokit/pipeline_util/load_pipe_exception.h>
 *
 * \brief The exception thrown when a path is not a file.
 *
 * \ingroup exceptions
 */
class SPROKIT_PIPELINE_UTIL_EXPORT not_a_file_exception
  : public load_pipe_exception
{
  public:
    /**
     * \brief Constructor.
     *
     * \param path The path that is not a file.
     */
    not_a_file_exception(path_t const& path) throw();
    /**
     * \brief Destructor.
     */
    ~not_a_file_exception() throw();

    /// The path is not a file.
    path_t const m_path;
};

/**
 * \class file_open_exception load_pipe_exception.h <sprokit/pipeline_util/load_pipe_exception.h>
 *
 * \brief The exception thrown when a file could not be opened.
 *
 * \ingroup exceptions
 */
class SPROKIT_PIPELINE_UTIL_EXPORT file_open_exception
  : public load_pipe_exception
{
  public:
    /**
     * \brief Constructor.
     *
     * \param fname The path that was unable to be loaded.
     */
    file_open_exception(path_t const& fname) throw();
    /**
     * \brief Destructor.
     */
    ~file_open_exception() throw();

    /// The path that was unable to be loaded.
    path_t const m_fname;
};

/**
 * \class stream_failure_exception load_pipe_exception.h <sprokit/pipeline_util/load_pipe_exception.h>
 *
 * \brief The exception thrown when a stream has an error.
 *
 * \ingroup exceptions
 */
class SPROKIT_PIPELINE_UTIL_EXPORT stream_failure_exception
  : public load_pipe_exception
{
  public:
    /**
     * \brief Constructor.
     *
     * \param msg The message given for the stream failure.
     */
    stream_failure_exception(std::string const& msg) throw();
    /**
     * \brief Destructor.
     */
    ~stream_failure_exception() throw();

    /// The message given for the stream failure.
    std::string const m_msg;
};

/**
 * \class failed_to_parse load_pipe_exception.h <sprokit/pipeline_util/load_pipe_exception.h>
 *
 * \brief The exception thrown when a parse error occurred.
 *
 * \ingroup exceptions
 */
class SPROKIT_PIPELINE_UTIL_EXPORT failed_to_parse
  : public load_pipe_exception
{
  public:
    /**
     * \brief Constructor.
     *
     * \param reason A reason for the failure
     * \param where Where the error occurred.
     */
    failed_to_parse(std::string const& reason, std::string const& where) throw();
    /**
     * \brief Destructor.
     */
    ~failed_to_parse() throw();

    /// The reason for the failure to parse.
    std::string const m_reason;
    /// Where the error occurred.
    std::string const m_where_full;
    /// Where the error occurred, abbreviated to 64 bytes.
    std::string const m_where_brief;
  private:
    static size_t const max_size;
};

}

#endif // SPROKIT_PIPELINE_UTIL_LOAD_PIPE_EXCEPTION_H
