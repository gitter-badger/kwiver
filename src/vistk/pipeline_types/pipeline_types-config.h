/*ckwg +5
 * Copyright 2011 by Kitware, Inc. All Rights Reserved. Please refer to
 * KITWARE_LICENSE.TXT for licensing information, or contact General Counsel,
 * Kitware, Inc., 28 Corporate Drive, Clifton Park, NY 12065.
 */

#ifndef VISTK_PIPELINE_TYPES_CONFIG_H_
#define VISTK_PIPELINE_TYPES_CONFIG_H_

#include <vistk/config.h>

/**
 * \file pipeline_types-config.h
 *
 * \brief Defines for symbol visibility in pipeline_types.
 */

#ifndef VISTK_PIPELINE_TYPES_EXPORT
#ifdef MAKE_VISTK_PIPELINE_TYPES_LIB
/// Export the symbol if building the library.
#define VISTK_PIPELINE_TYPES_EXPORT VISTK_EXPORT
#else
/// Import the symbol if including the library.
#define VISTK_PIPELINE_TYPES_EXPORT VISTK_IMPORT
#endif // MAKE_VISTK_PIPELINE_TYPES_LIB
/// Hide the symbol from the library interface.
#define VISTK_PIPELINE_TYPES_NO_EXPORT VISTK_NO_EXPORT
#endif // VISTK_PIPELINE_TYPES_EXPORT

#ifndef VISTK_PIPELINE_TYPES_EXPORT_DEPRECATED
/// Mark as deprecated.
#define VISTK_PIPELINE_TYPES_EXPORT_DEPRECATED VISTK_DEPRECATED VISTK_PIPELINE_TYPES_EXPORT
#endif // VISTK_PIPELINE_EXPORT_DEPRECATED

#endif // VISTK_PIPELINE_TYPES_CONFIG_H_
