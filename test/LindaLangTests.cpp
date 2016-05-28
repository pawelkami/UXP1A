#define BOOST_TEST_MODULE LindaLangModule

#include <boost/test/included/unit_test.hpp>
#include "Linda.h"
#include "TupleValue.h"
#include "Tuple.h"
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <sys/param.h>

#include "ConditionVis.h"

#include "Enums.h"

using namespace boost::unit_test;

BOOST_AUTO_TEST_SUITE( LindaLangSuite )

    BOOST_AUTO_TEST_CASE(TupleValue_getTypeName)
    {
        TupleValue intValue(1);

        TupleValue floatValue((float)1.2);

        TupleValue strValue("Tuple");


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
            BOOST_CHECK(err.compare("Too big message: " + std::to_string(PIPE_BUF + 2)));
        }
    }

    BOOST_AUTO_TEST_CASE(Pipe_read_not_enough)
    {
        const char *msg = "Hello Linda!";
        char *expected = (char*)"Hello";
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


    BOOST_AUTO_TEST_CASE(Tuple_value)
    {
        TupleValue stringTuple("Hello!");
        BOOST_CHECK(stringTuple.getTypeName() == "string");
        BOOST_CHECK(stringTuple.value.type() == typeid(std::string));
        BOOST_CHECK(boost::get<std::string>(stringTuple.value) == "Hello!");



    }

    BOOST_AUTO_TEST_CASE(Conditions_fulfilled_TupleValue)
    {

        TupleValue intValue1(1);
        TupleValue intValue2(2);
        TupleValue floatValue1((float)5.2);
        TupleValue floatValue2(3.2f);
        TupleValue strValue("Tuple");
        TupleValue floatValue3(1.0f);

        BOOST_CHECK(boost::apply_visitor(ConditionVis<Condition::EQ>(), intValue1.value, intValue1.value));
        BOOST_CHECK(boost::apply_visitor(ConditionVis<Condition::LS>(), floatValue2.value, floatValue1.value));
        BOOST_CHECK(!boost::apply_visitor(ConditionVis<Condition::EQ>(), floatValue3.value, intValue1.value));


        //BOOST_CHECK(ConditionTraits<Condition::EQ>::fulfilled(intValue1.value, intValue1.value));
        //BOOST_CHECK(ConditionTraits<Condition::LS>::fulfilled(intValue1.value, intValue2.value));

        //BOOST_CHECK(ConditionTraits<Condition::GR>::fulfilled(floatValue1.value, floatValue2.value));


//        BOOST_CHECK(ConditionTraits<Condition::EQ>::fulfilled(12.34f, 12.34f));
//        BOOST_CHECK(ConditionTraits<Condition::EQ>::fulfilled(std::string("rowny"), std::string("rowny")));
//
//        BOOST_CHECK(ConditionTraits<Condition::GE>::fulfilled(4, 4));
//        BOOST_CHECK(ConditionTraits<Condition::GE>::fulfilled(17.9f, 12.34f));
//        BOOST_CHECK(ConditionTraits<Condition::LE>::fulfilled(std::string("arbuz"), std::string("banan")));
    }

BOOST_AUTO_TEST_SUITE_END()



//test_suite* init_unit_test_suite( int argc, char * argv[] )
//{
//
//    return 0;
//}