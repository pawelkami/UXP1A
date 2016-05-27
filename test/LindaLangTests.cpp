#define BOOST_TEST_MODULE LindaLangModule

#include <boost/test/included/unit_test.hpp>
#include "Linda.h"
#include "TupleValue.h"

#include "Enums.h"

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

    BOOST_AUTO_TEST_CASE(Conditions_fulfilled)
    {
        BOOST_CHECK(ConditionTraits<Condition::EQ>::fulfilled(4, 4));
        BOOST_CHECK(ConditionTraits<Condition::EQ>::fulfilled(12.34, 12.34));
        BOOST_CHECK(ConditionTraits<Condition::EQ>::fulfilled(std::string("rowny"), std::string("rowny")));

        BOOST_CHECK(ConditionTraits<Condition::GE>::fulfilled(4, 4));
        BOOST_CHECK(ConditionTraits<Condition::GE>::fulfilled(17.9, 12.34));
        BOOST_CHECK(ConditionTraits<Condition::GE>::fulfilled(std::string("arbuz"), std::string("banan")));
    }



BOOST_AUTO_TEST_SUITE_END()



//test_suite* init_unit_test_suite( int argc, char * argv[] )
//{
//
//    return 0;
//}