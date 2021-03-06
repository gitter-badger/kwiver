/*ckwg +5
 * Copyright 2013-2016 by Kitware, Inc. All Rights Reserved. Please refer to
 * KITWARE_LICENSE.TXT for licensing information, or contact General Counsel,
 * Kitware, Inc., 28 Corporate Drive, Clifton Park, NY 12065.
 */

#ifndef INCL_TRACK_VPD_EVENT_H
#define INCL_TRACK_VPD_EVENT_H

#include <vital/vital_config.h>
#include <track_oracle/track_vpd/track_vpd_export.h>

#include <track_oracle/track_base.h>
#include <track_oracle/track_field.h>
#include <string>
#include <utility>
#include <vgl/vgl_box_2d.h>

namespace kwiver {
namespace track_oracle {

/// This is the track_oracle schema for the VIRAT Public Data 2.0
/// event tracks.

struct TRACK_VPD_EXPORT track_vpd_event_type: public track_base< track_vpd_event_type >
{
  track_field< unsigned >& event_id;
  track_field< unsigned >& event_type;
  track_field< unsigned >& start_frame;
  track_field< unsigned >& end_frame;
  track_field< std::vector< unsigned > >& object_id_list;
  track_field< unsigned >& frame_number;
  track_field< vgl_box_2d<double> >& bounding_box;
  track_vpd_event_type():
    event_id( Track.add_field< unsigned >( "event_id" )),
    event_type( Track.add_field< unsigned >( "vpd_event_type" )),
    start_frame( Track.add_field< unsigned >( "start_frame" )),
    end_frame( Track.add_field< unsigned >( "end_frame" )),
    object_id_list( Track.add_field< std::vector< unsigned > >( "object_id_list" )),
    frame_number( Frame.add_field< unsigned >( "frame_number" )),
    bounding_box( Frame.add_field< vgl_box_2d<double> >( "bounding_box" ))
  {}

  static std::string event_type_to_str( unsigned t );
  static unsigned str_to_event_type( const std::string& s );
};

} // ...track_oracle
} // ...kwiver

#endif
