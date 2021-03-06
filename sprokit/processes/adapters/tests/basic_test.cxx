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

#include <test_common.h>

#include <vital/config/config_block.h>
#include <vital/vital_foreach.h>

#include <sprokit/tools/pipeline_builder.h>
#include <sprokit/tools/literal_pipeline.h>
#include <sprokit/pipeline/modules.h>
#include <sprokit/pipeline/pipeline.h>
#include <sprokit/pipeline/datum.h>
#include <sprokit/pipeline/scheduler.h>
#include <sprokit/pipeline/scheduler_registry.h>

#include <sprokit/processes/adapters/input_adapter.h>
#include <sprokit/processes/adapters/input_adapter_process.h>

#include <sprokit/processes/adapters/output_adapter.h>
#include <sprokit/processes/adapters/output_adapter_process.h>

#include <sprokit/processes/adapters/embedded_pipeline.h>

#include <sstream>


static kwiver::vital::config_block_key_t const scheduler_block = kwiver::vital::config_block_key_t("_scheduler");

#define TEST_ARGS ()

DECLARE_TEST_MAP();

int
main(int argc, char* argv[])
{
  CHECK_ARGS(1);

  testname_t const testname = argv[1];

  RUN_TEST(testname);
}

IMPLEMENT_TEST( basic_pipeline )
{
  kwiver::input_adapter input_ad;
  kwiver::output_adapter output_ad;

  // load processes
  sprokit::load_known_modules();

  // Use SPROKIT macros to create pipeline description
  std::stringstream pipeline_desc;
  pipeline_desc << SPROKIT_PROCESS( "input_adapter",  "ia" )
                << SPROKIT_PROCESS( "output_adapter", "oa" )

                << SPROKIT_CONNECT( "ia", "port1",    "oa", "port1" )
                << SPROKIT_CONNECT( "ia", "port2",    "oa", "port3" ) // yeah, i know
                << SPROKIT_CONNECT( "ia", "port3",    "oa", "port2" )
    ;

    // create a pipeline
  sprokit::pipeline_builder builder;
  builder.load_pipeline( pipeline_desc );

  // build pipeline
  sprokit::pipeline_t const pipe = builder.pipeline();
  kwiver::vital::config_block_sptr const conf = builder.config();

  if (!pipe)
  {
    TEST_EQUAL( "Baking pipeline", true, false);
    return;
  }

  // perform setup operation on pipeline and get it ready to run
  // This throws many exceptions
  try
  {
    pipe->setup_pipeline();
  }
  catch( sprokit::pipeline_exception const& e)
  {
    std::cerr << "Error setting up pipeline: " << e.what() << std::endl;
    TEST_EQUAL( "Setting up pipeline", true, false );
    return;
  }

  // Connect adapters to their processes.
  input_ad.connect( "ia", pipe );
  output_ad.connect( "oa", pipe );

  // Query adapters for ports
  auto input_list = input_ad.port_list();
  TEST_EQUAL( "Number of input ports", input_list.size(), 3 );
  std::cout << "Input adapter ports:\n";
  VITAL_FOREACH( auto port, input_list )
  {
    std::cout << "    " << port << "\n";
  }

  auto output_list = output_ad.port_list();
  TEST_EQUAL( "Number of output ports", output_list.size(), 3 );
  std::cout << "\nOutput adapter ports:\n";
  VITAL_FOREACH( auto port, output_list )
  {
    std::cout << "    " << port << "\n";
  }

  sprokit::scheduler_registry::type_t scheduler_type = sprokit::scheduler_registry::default_type;
  kwiver::vital::config_block_sptr const scheduler_config = conf->subblock(scheduler_block +
                                              kwiver::vital::config_block::block_sep + scheduler_type);

  sprokit::scheduler_registry_t reg = sprokit::scheduler_registry::self();
  sprokit::scheduler_t scheduler = reg->create_scheduler(scheduler_type, pipe, scheduler_config);

  if (!scheduler)
  {
    TEST_EQUAL( "Unable to create scheduler", true, false );
    return;
  }

  scheduler->start();

  // Feed data to input adapter
  for ( int i = 0; i < 10; ++i)
  {
    auto ds = kwiver::adapter::adapter_data_set::create();
    int val = i;

    VITAL_FOREACH( auto port, input_list )
    {
      ds->add_value( port, (val++) );
    }
    std::cout << "sending set: " << i << "\n";
    input_ad.send( ds );
  }

  std::cout << "Sending end of input element\n";
  auto ds = kwiver::adapter::adapter_data_set::create( kwiver::adapter::adapter_data_set::end_of_input );
  input_ad.send( ds );

  while( true )
  {
    auto ods = output_ad.receive(); // blocks

    // check for end of data marker
    if ( ods->is_end_of_data() )
    {
      std::cout << "End of data detected\n";
      break;
    }

    auto ix = ods->begin();
    auto eix = ods->end();

    std::cout << "\nData from pipeline\n";

    for ( ; ix != eix; ++ix )
    {
      std::cout << "   port: " << ix->first << "  value: " << ix->second->get_datum<int>() << "\n";
    }
  } // end while

  scheduler->wait();
}

// ------------------------------------------------------------------
IMPLEMENT_TEST( embedded_pipeline )
{
  // Use SPROKIT macros to create pipeline description
  std::stringstream pipeline_desc;
  pipeline_desc << SPROKIT_PROCESS( "input_adapter",  "ia" )
                << SPROKIT_PROCESS( "output_adapter", "oa" )

                << SPROKIT_CONNECT( "ia", "port1",    "oa", "port1" )
                << SPROKIT_CONNECT( "ia", "port2",    "oa", "port3" ) // yeah, i know
                << SPROKIT_CONNECT( "ia", "port3",    "oa", "port2" )
    ;

  // create embedded pipeline
  kwiver::embedded_pipeline ep( pipeline_desc );

  // Query adapters for ports
  auto input_list = ep.input_port_names();
  TEST_EQUAL( "Number of input ports", input_list.size(), 3 );

  std::cout << "Input adapter ports:\n";
  VITAL_FOREACH( auto port, input_list )
  {
    std::cout << "    " << port << "\n";
  }

  auto output_list = ep.output_port_names();
  TEST_EQUAL( "Number of output ports", output_list.size(), 3 );

  std::cout << "\nOutput adapter ports:\n";
  VITAL_FOREACH( auto port, output_list )
  {
    std::cout << "    " << port << "\n";
  }

  // Start pipeline
  ep.start();

    // Feed data to input adapter
  for ( int i = 0; i < 10; ++i)
  {
    auto ds = kwiver::adapter::adapter_data_set::create();
    int val = i;

    VITAL_FOREACH( auto port, input_list )
    {
      ds->add_value( port, (val++) );
    }
    std::cout << "sending set: " << i << "\n";
    ep.send( ds );
  }

  std::cout << "Sending end of input element\n";
  ep.send_end_of_input();

  while( true )
  {
    auto ods = ep.receive(); // blocks

    // check for end of data marker
    if ( ods->is_end_of_data() )
    {
      TEST_EQUAL( "at_end() set correctly", ep.at_end(), true );
      break;
    }

    auto ix = ods->begin();
    auto eix = ods->end();

    std::cout << "\nData from pipeline\n";

    for ( ; ix != eix; ++ix )
    {
      std::cout << "   port: " << ix->first << "  value: " << ix->second->get_datum<int>() << "\n";
    }
  } // end while

}
