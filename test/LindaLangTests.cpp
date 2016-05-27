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

using namespace boost::unit_test;

BOOST_AUTO_TEST_SUITE( LindaLangSuite )
    BOOST_AUTO_TEST_CASE(output)
    {
        Linda linda;
        Tuple tuple;
        BOOST_CHECK(!linda.output(tuple));
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

    BOOST_AUTO_TEST_CASE(Tuple_serialization)
    {
        Tuple tuple;
        std::stringstream ss;
        PValue pval = boost::make_shared<TupleValue<int>>();

        TupleValue<int> p = static_cast< TupleValue<int>& >(*pval);
        p.setValue(5);

        boost::archive::text_oarchive oa(ss);

        oa << p;

        boost::archive::text_iarchive ia(ss);

        TupleValue<int> a;

        ia >> a;

        BOOST_CHECK_EQUAL(a.getValue(), p.getValue());


    }



BOOST_AUTO_TEST_SUITE_END()



//test_suite* init_unit_test_suite( int argc, char * argv[] )
//{
//
//    return 0;
//}