#include "ismrmrd/xml.h"
#include "ismrmrd/version.h"
#include "embedded_xml.h"
#include <boost/test/unit_test.hpp>
#include <sstream>

using namespace ISMRMRD;

BOOST_AUTO_TEST_SUITE(HeaderTest)

BOOST_AUTO_TEST_CASE(test_basic_xml_header)
{

    IsmrmrdHeader header;
    deserialize(basic_xml.c_str(),header);
    std::stringstream stream;
    serialize(header,stream);

    IsmrmrdHeader header2;
    deserialize(stream.str().c_str(),header2);

    BOOST_CHECK_EQUAL(header,header2);
}

BOOST_AUTO_TEST_CASE(test_extended_xml_header)
{

    IsmrmrdHeader header;
    deserialize(extended_xml.c_str(),header);
    std::stringstream stream;
    serialize(header,stream);

    BOOST_CHECK(header.encoding.at(1).parallelImaging);
    BOOST_CHECK(header.encoding.at(1).parallelImaging->multiband);
    BOOST_CHECK_EQUAL(header.encoding.at(1).parallelImaging.get().multiband.get().deltaKz,1.0f);
    BOOST_CHECK_EQUAL(header.encoding.at(1).parallelImaging.get().multiband.get().multiband_factor,2);
    BOOST_CHECK(header.sequenceParameters.get().diffusion);
    BOOST_CHECK_EQUAL(header.sequenceParameters.get().diffusion.get().size(),3 );

    IsmrmrdHeader header2;
    deserialize(stream.str().c_str(),header2);

    BOOST_CHECK_EQUAL(header,header2);
}

BOOST_AUTO_TEST_CASE(test_xml_header_locale)
{
    IsmrmrdHeader header;
    deserialize(basic_xml.c_str(), header);

    std::stringstream stream1;
    std::locale original_locale = std::locale::global(std::locale("C"));
    serialize(header, stream1);

    std::stringstream stream2;
    std::locale::global(std::locale("en_US.UTF-8"));
    serialize(header, stream2);

    std::locale::global(original_locale);

    BOOST_CHECK_EQUAL(stream1.str(), stream2.str());
}

BOOST_AUTO_TEST_SUITE_END()
