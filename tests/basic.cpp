#include "init.hpp"

#include "Bootstrapper.hpp"

BOOST_AUTO_TEST_CASE(checkSanity)
{
    // Check will fail, but continue
    BOOST_CHECK_EQUAL(4, 2 + 2);

    // Require fails immediately
    BOOST_REQUIRE_EQUAL(5, 2 + 3);

    Bootstrapper bs;
    BOOST_CHECK(&bs.mainWidget());
}

// vim: set ts=4 sw=4 :
