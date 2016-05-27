#define BOOST_TEST_MODULE LindaLangModule

#include <boost/test/included/unit_test.hpp>
#include "Linda.h"
#include "TupleValue.h"

using namespace boost::unit_test;

BOOST_AUTO_TEST_SUITE( LindaLangSuite )
    BOOST_AUTO_TEST_CASE(output)
    {
        Linda linda;
        Tuple tuple;
        BOOST_CHECK( linda.output(tuple) == false );
    }

    BOOST_AUTO_TEST_CASE(TupleValue_getTypeName)
    {
        TupleValue<float> floatValue;
        TupleValue<int> intValue;
        TupleValue<std::string> strValue;


        BOOST_CHECK_EQUAL("float", floatValue.getTypeName());
        BOOST_CHECK_EQUAL("integer", intValue.getTypeName());
        BOOST_CHECK_EQUAL("string", strValue.getTypeName());
    }



BOOST_AUTO_TEST_SUITE_END()



//test_suite* init_unit_test_suite( int argc, char * argv[] )
//{
//
//    return 0;
//}