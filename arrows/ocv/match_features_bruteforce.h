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
 * \brief OCV brute-force feature matcher wrapper
 */

#ifndef KWIVER_ARROWS_MATCH_FEATURES_BRUTEFORCE_H_
#define KWIVER_ARROWS_MATCH_FEATURES_BRUTEFORCE_H_

#include <memory>
#include <vector>

#include <arrows/ocv/kwiver_algo_ocv_export.h>
#include <arrows/ocv/match_features.h>

namespace kwiver {
namespace arrows {
namespace ocv {


/// Feature matcher implementation using OpenCV's brute-force feature matcher
class KWIVER_ALGO_OCV_EXPORT match_features_bruteforce
    : public vital::algorithm_impl< match_features_bruteforce,
                                    match_features,
                                    vital::algo::match_features >
{
public:
  /// Constructor
  match_features_bruteforce();
  /// Copy Constructor
  match_features_bruteforce(match_features_bruteforce const &other);
  /// Destructor
  virtual ~match_features_bruteforce();

  /// Return the name of this implementation
  virtual std::string impl_name() const { return "ocv_brute_force"; }
  /// Returns a descriptive string for this implementation
  virtual std::string description() const {
    return "OpenCV brute-force feature matching algorithm";
  }

  /// Get this algorithm's \link kwiver::vital::config_block configuration block \endlink
  virtual vital::config_block_sptr get_configuration() const;
  /// Set this algorithm's properties via a config block
  virtual void set_configuration(vital::config_block_sptr config);
  /// Check that the algorithm's configuration vital::config_block is valid
  virtual bool check_configuration(vital::config_block_sptr config) const;

protected:
  /// Perform matching based on the underlying OpenCV implementation
  virtual void ocv_match(const cv::Mat& descriptors1,
                         const cv::Mat& descriptors2,
                         std::vector<cv::DMatch>& matches) const;

private:
  class priv;
  std::unique_ptr<priv> const p_;
};


} // end namespace ocv
} // end namespace arrows
} // end namespace kwiver

#endif //KWIVER_ARROWS_MATCH_FEATURES_BRUTEFORCE_H_
