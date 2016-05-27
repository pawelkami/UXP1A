#define BOOST_TEST_MODULE LindaLangModule

#include <boost/test/included/unit_test.hpp>
#include "Linda.h"
#include "TupleValue.h"
#include "Tuple.h"
#include <boost/shared_ptr.hpp>
#include "Value.h"
#include <boost/make_shared.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include "DetailedValue.h"

#include "Enums.h"

using namespace boost::unit_test;

BOOST_AUTO_TEST_SUITE( LindaLangSuite )

    BOOST_AUTO_TEST_CASE(TupleValue_getTypeName)
    {
        TupleValue<float> floatValue;
        TupleValue<int> intValue;
        TupleValue<std::string> strValue;


        BOOST_CHECK_EQUAL("float", floatValue.getTypeName());
        BOOST_CHECK_EQUAL("integer", intValue.getTypeName());
        BOOST_CHECK_EQUAL("string", strValue.getTypeName());
    }

    BOOST_AUTO_TEST_CASE(Tuple_serialization)
    {
        Tuple tuple;
        std::stringstream ss;
        PValue pval = boost::make_shared<TupleValue<int>>();

        TupleValue<int> p = static_cast< TupleValue<int> & >(*pval);
        p.setValue(5);

        boost::archive::text_oarchive oa(ss);

        oa << p;

        boost::archive::text_iarchive ia(ss);

        TupleValue<int> a;

        ia >> a;

        BOOST_CHECK_EQUAL(a.getValue(), p.getValue());

    }

    BOOST_AUTO_TEST_CASE(Conditions_fulfilled)
    {
        BOOST_CHECK(ConditionTraits<Condition::EQ>::fulfilled(4, 4));
        BOOST_CHECK(ConditionTraits<Condition::EQ>::fulfilled(12.34, 12.34));
        BOOST_CHECK(ConditionTraits<Condition::EQ>::fulfilled(std::string("rowny"), std::string("rowny")));

        BOOST_CHECK(ConditionTraits<Condition::GE>::fulfilled(4, 4));
        BOOST_CHECK(ConditionTraits<Condition::GE>::fulfilled(17.9, 12.34));
        BOOST_CHECK(ConditionTraits<Condition::LE>::fulfilled(std::string("arbuz"), std::string("banan")));
    }



BOOST_AUTO_TEST_SUITE_END()



//test_suite* init_unit_test_suite( int argc, char * argv[] )
//{
//
//    return 0;
//}