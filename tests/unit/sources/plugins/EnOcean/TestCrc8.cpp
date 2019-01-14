#include "stdafx.h"
#include <boost/test/unit_test.hpp>

// Includes needed to compile tested classes
#include "../../../../sources/plugins/EnOcean/message/Crc8.h"


BOOST_AUTO_TEST_SUITE(TestCrc8)


unsigned char computeCrc8OnFullVector(const std::vector<unsigned char>& vector)
{
   return message::computeCrc8(vector.begin(), vector.end());
}

BOOST_AUTO_TEST_CASE(TestCrc8)
{
   BOOST_CHECK(computeCrc8OnFullVector({ 0x00, 0x07, 0x07, 0x01 }) == 0x7a);
   BOOST_CHECK(computeCrc8OnFullVector({ 0xf6, 0x00, 0x00, 0x34, 0xee, 0xf4, 0x20, 0x01, 0xff, 0xff, 0xff, 0xff, 0x4f, 0x00 }) == 0x5d);

   BOOST_CHECK(computeCrc8OnFullVector({ 0xf6, 0xb0, 0x00, 0x34, 0xee, 0x74, 0x31, 0x01, 0xff, 0xff, 0xff, 0xff, 0x31, 0x00 }) == 0x49);
}

BOOST_AUTO_TEST_SUITE_END()
