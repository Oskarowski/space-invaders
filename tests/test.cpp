#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(TestTestSuite, *boost::unit_test::label("exampleTests"))

BOOST_AUTO_TEST_CASE(JustTestIfTestWorks)
{
    BOOST_REQUIRE_EQUAL(1, 1);
}

BOOST_AUTO_TEST_CASE(JustTestIfTestFailsWorks)
{
    BOOST_REQUIRE_EQUAL(1, 1);
}
BOOST_AUTO_TEST_SUITE_END()