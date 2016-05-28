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

    BOOST_AUTO_TEST_CASE(Pipe_read_write)
    {
        const char *msg = "Hello Linda!";
        char *rcv = (char*)malloc(sizeof(char) * std::strlen(msg));
        Pipe p;
        p.writePipe(msg, (unsigned)std::strlen(msg));
        p.readPipe(rcv, (unsigned)std::strlen(msg));
        BOOST_CHECK(std::strcmp(msg, rcv));
    }

    BOOST_AUTO_TEST_CASE(Pipe_write_too_much)
    {
        const char *msg = "Hello Linda!";
        char *rcv = (char*)malloc(sizeof(char) * std::strlen(msg));
        Pipe p;
        try
        {
            p.writePipe(msg, PIPE_BUF + 2);
        }
        catch(std::string err)
        {
            BOOST_CHECK(err.compare("Too big message: " + PIPE_BUF + 2));
        }
    }

    BOOST_AUTO_TEST_CASE(Pipe_read_not_enough)
    {
        const char *msg = "Hello Linda!";
        char *expected = "Hello";
        char *rcv = (char*)malloc(sizeof(char) * (std::strlen(msg) - 7));
        Pipe p;
        p.writePipe(msg, (unsigned)std::strlen(msg));
        try
        {
            p.readPipe(rcv, (unsigned)(std::strlen(msg) - 7));
        }
        catch(std::string err)
        {
            BOOST_CHECK(err.compare("Incomplete reading pipe"));
            BOOST_CHECK(std::strcmp(rcv, expected));
        }
    }

BOOST_AUTO_TEST_SUITE_END()



//test_suite* init_unit_test_suite( int argc, char * argv[] )
//{
//
//    return 0;
//}