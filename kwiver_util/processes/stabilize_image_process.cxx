/*ckwg +29
 * Copyright 2015 by Kitware, Inc.
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
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS [yas] elisp error!AS IS''
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

#include "stabilize_image_process.h"

#include <kwiver/pipeline_types/kwiver.h>
#include <kwiver/timestamp.h>

#include <sprokit/pipeline/process_exception.h>

#include <maptk/modules.h>
#include <maptk/algo/track_features.h>
#include <maptk/algo/compute_ref_homography.h>

#include <kwiver/image_container.h>
#include <maptk/track_set.h>
#include <kwiver/homography.h>

#include <boost/make_shared.hpp>

// -- DEBUG
#if defined DEBUG
#include <maptk/ocv/image_container.h>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;
#endif

namespace kwiver
{

//----------------------------------------------------------------
// Private implementation class
class stabilize_image_process::priv
{
public:
  priv();
  ~priv();


  // Configuration values

  // There are many config items for the tracking and stabilization that go directly to
  // the maptk algo.

  // feature tracker algorithm - homography source
  maptk::algo::track_features_sptr         m_feature_tracker;
  maptk::algo::compute_ref_homography_sptr m_compute_homog;

  maptk::track_set_sptr m_tracks; // last set of tracks

}; // end priv class

// ================================================================

stabilize_image_process
::stabilize_image_process( sprokit::config_t const& config )
  : process( config ),
    d( new stabilize_image_process::priv )
{
  make_ports();
  make_config();
}


stabilize_image_process
::~stabilize_image_process()
{
}


// ----------------------------------------------------------------
void stabilize_image_process
::_configure()
{
  // Convert sprokit config to maptk config for algorithms
  sprokit::config_t proc_config = get_config(); // config for process
  maptk::config_block_sptr algo_config = maptk::config_block::empty_config();

  //+ convert_config( proc_config, algo_config );

  // Maybe should call check_nested_algo_configuration( "feature_tracker", algo_config );
  // Maybe should call check_nested_algo_configuration( "homography_generator", algo_config );

  maptk::algo::track_features::set_nested_algo_configuration( "feature_tracker",
                                              algo_config, d->m_feature_tracker );
  if ( ! d->m_feature_tracker )
  {
    throw sprokit::invalid_configuration_exception( name(), "Error configuring \"feature_tracker\"" );
  }

  maptk::algo::compute_ref_homography::set_nested_algo_configuration( "homography_generator",
                                                              algo_config, d->m_compute_homog );
  if ( ! d->m_compute_homog )
  {
    throw sprokit::invalid_configuration_exception( name(), "Error configuring \"homography_generator\"" );
  }

  sprokit::process::_configure();
}


// ----------------------------------------------------------------
void
stabilize_image_process
::_step()
{
  kwiver::f2f_homography_sptr src_to_ref_homography;

  // timestamp
  kwiver::timestamp frame_time = grab_input_using_trait( timestamp );

  // image
  //+ kwiver::image_container_sptr img = grab_input_using_trait( image );
  kwiver::image_container_sptr img = grab_from_port_using_trait( image );

  // LOG_DEBUG - this is a good thing to have in all processes that handle frames.
  std::cerr << "DEBUG - (stab image) Processing frame " << frame_time
            << std::endl;

  // --- debug
#if defined DEBUG
  cv::Mat image = maptk::ocv::image_container::maptk_to_ocv( img->get_image() );
  namedWindow( "Display window", cv::WINDOW_NORMAL ); // Create a window for display.
  imshow( "Display window", image );                   // Show our image inside it.

  waitKey( 0 );
#endif                                        // Wait for a keystroke in the window
  // -- end debug
  // Get feature tracks
  //+ type error --] d->m_tracks = d->m_feature_tracker->track( d->m_tracks, frame_time.get_frame(), img );

  // Get stabilization homography
  src_to_ref_homography = d->m_compute_homog->estimate( frame_time.get_frame(), d->m_tracks );

  // return by value
  push_to_port_using_trait( src_to_ref_homography, *src_to_ref_homography );

  sprokit::process::_step();
}


// ----------------------------------------------------------------
void stabilize_image_process
::make_ports()
{
  // Set up for required ports
  sprokit::process::port_flags_t required;
  required.insert( flag_required );

  // -- input --
  declare_input_port_using_trait( timestamp, required );
  declare_input_port_using_trait( image, required );

  declare_output_port_using_trait( src_to_ref_homography, required );
}


// ----------------------------------------------------------------
void stabilize_image_process
::make_config()
{

}


// ================================================================
stabilize_image_process::priv
::priv()
{
}


stabilize_image_process::priv
::~priv()
{
}

} // end namespace