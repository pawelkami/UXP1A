#define BOOST_TEST_MODULE LindaLangModule

#include <boost/test/included/unit_test.hpp>
#include "Linda.h"
#include "TupleValue.h"
#include "Tuple.h"
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

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

//    BOOST_AUTO_TEST_CASE(Pipe_read_write)
//    {
//        const char *msg = "Hello Linda!";
//        char *rcv = (char*)malloc(sizeof(char) * std::strlen(msg));
//        Pipe p;
//        p.writePipe(msg, (unsigned)std::strlen(msg));
//        p.readPipe(rcv, (unsigned)std::strlen(msg));
//        BOOST_CHECK(std::strcmp(msg, rcv));
//        free(rcv);
//    }
//
//    BOOST_AUTO_TEST_CASE(Pipe_write_too_much)
//    {
//        const char *msg = "Hello Linda!";
//        char *rcv = (char*)malloc(sizeof(char) * std::strlen(msg));
//        Pipe p;
//        try
//        {
//            p.writePipe(msg, PIPE_BUF + 2);
//        }
//        catch(std::string err)
//        {
//            BOOST_CHECK(err.compare("Too big message: " + std::to_string(PIPE_BUF + 2)));
//        }
//        free(rcv);
//    }
//
//    BOOST_AUTO_TEST_CASE(Pipe_read_not_enough)
//    {
//        const char *msg = "Hello Linda!";
//        char *expected = (char*)"Hello";
//        char *rcv = (char*)malloc(sizeof(char) * (std::strlen(msg) - 7));
//        Pipe p;
//        p.writePipe(msg, (unsigned)std::strlen(msg));
//        try
//        {
//            p.readPipe(rcv, (unsigned)(std::strlen(msg) - 7));
//        }
//        catch(std::string err)
//        {
//            BOOST_CHECK(err.compare("Incomplete reading pipe"));
//            BOOST_CHECK(std::strcmp(rcv, expected));
//        }
//        free(rcv);
//    }

    BOOST_AUTO_TEST_CASE(Tupl_Value_get_value)
    {
        std::string val1 = "testowyNapis";
        TupleValue tv1(val1);
        boost::any check1 = tv1.getValue(tv1.getTypeName());
        BOOST_CHECK(val1.compare(boost::any_cast<std::string>(check1)) == 0);
        int val2 = 10;
        TupleValue tv2(val2);
        boost::any check2 = tv2.getValue(tv2.getTypeName());
        BOOST_CHECK(val2 == boost::any_cast<int>(check2));
        float val3 = 3.1415;
        TupleValue tv3(val3);
        boost::any check3 = tv3.getValue(tv3.getTypeName());
        BOOST_CHECK(val3 == boost::any_cast<float>(check3));
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
    }


    BOOST_AUTO_TEST_CASE(Conditions_fulfilled_TupleValue_EQ)
    {
        TupleValue intV1((int)1);
        TupleValue intV2((int)1);

        TupleValue floatV1((float)5.5);
        TupleValue floatV2((float)5.5);

        TupleValue stringV1("Tuple");
        TupleValue stringV2("Tuple");

        BOOST_CHECK(boost::apply_visitor(ConditionVis<Condition::EQ>(), intV1.value, intV2.value));
        BOOST_CHECK(boost::apply_visitor(ConditionVis<Condition::EQ>(), floatV1.value, floatV2.value));
        BOOST_CHECK(boost::apply_visitor(ConditionVis<Condition::EQ>(), stringV1.value, stringV2.value));
    }
    BOOST_AUTO_TEST_CASE(Conditions_fulfilled_TupleValue_LS)
    {
        TupleValue intV1((int)1);
        TupleValue intV2((int)2);

        TupleValue floatV1((float)5.5);
        TupleValue floatV2((float)6.5);

        TupleValue stringV1("Tuple1");
        TupleValue stringV2("Tuple2");

        BOOST_CHECK(boost::apply_visitor(ConditionVis<Condition::LS>(), intV1.value, intV2.value));
        BOOST_CHECK(boost::apply_visitor(ConditionVis<Condition::LS>(), floatV1.value, floatV2.value));
        BOOST_CHECK(boost::apply_visitor(ConditionVis<Condition::LS>(), stringV1.value, stringV2.value));
    }
    BOOST_AUTO_TEST_CASE(Conditions_fulfilled_TupleValue_LE)
    {
        TupleValue intV1((int)1);
        TupleValue intV2((int)2);

        TupleValue floatV1((float)5.5);
        TupleValue floatV2((float)6.5);

        TupleValue stringV1("Tuple1");
        TupleValue stringV2("Tuple2");

        TupleValue intV3((int)1);
        TupleValue intV4((int)1);

        TupleValue floatV3((float)5.5);
        TupleValue floatV4((float)5.5);

        TupleValue stringV3("Tuple");
        TupleValue stringV4("Tuple");


        BOOST_CHECK(boost::apply_visitor(ConditionVis<Condition::LE>(), intV1.value, intV2.value));
        BOOST_CHECK(boost::apply_visitor(ConditionVis<Condition::LE>(), floatV1.value, floatV2.value));
        BOOST_CHECK(boost::apply_visitor(ConditionVis<Condition::LE>(), stringV1.value, stringV2.value));

        BOOST_CHECK(boost::apply_visitor(ConditionVis<Condition::LE>(), intV3.value, intV4.value));
        BOOST_CHECK(boost::apply_visitor(ConditionVis<Condition::LE>(), floatV3.value, floatV4.value));
        BOOST_CHECK(boost::apply_visitor(ConditionVis<Condition::LE>(), stringV3.value, stringV4.value));
    }
    BOOST_AUTO_TEST_CASE(Conditions_fulfilled_TupleValue_GR)
    {
        TupleValue intV1((int)3);
        TupleValue intV2((int)2);

        TupleValue floatV1((float)7.5);
        TupleValue floatV2((float)6.5);

        TupleValue stringV1("Tuple3");
        TupleValue stringV2("Tuple2");


        BOOST_CHECK(boost::apply_visitor(ConditionVis<Condition::GR>(), intV1.value, intV2.value));
        BOOST_CHECK(boost::apply_visitor(ConditionVis<Condition::GR>(), floatV1.value, floatV2.value));
        BOOST_CHECK(boost::apply_visitor(ConditionVis<Condition::GR>(), stringV1.value, stringV2.value));
    }
    BOOST_AUTO_TEST_CASE(Conditions_fulfilled_TupleValue_GE)
    {
        TupleValue intV1((int)4);
        TupleValue intV2((int)2);

        TupleValue floatV1((float)7.5);
        TupleValue floatV2((float)6.5);

        TupleValue stringV1("Tuple3");
        TupleValue stringV2("Tuple2");

        TupleValue intV3((int)1);
        TupleValue intV4((int)1);

        TupleValue floatV3((float)5.5);
        TupleValue floatV4((float)5.5);

        TupleValue stringV3("Tuple");
        TupleValue stringV4("Tuple");


        BOOST_CHECK(boost::apply_visitor(ConditionVis<Condition::GE>(), intV1.value, intV2.value));
        BOOST_CHECK(boost::apply_visitor(ConditionVis<Condition::GE>(), floatV1.value, floatV2.value));
        BOOST_CHECK(boost::apply_visitor(ConditionVis<Condition::GE>(), stringV1.value, stringV2.value));

        BOOST_CHECK(boost::apply_visitor(ConditionVis<Condition::GE>(), intV3.value, intV4.value));
        BOOST_CHECK(boost::apply_visitor(ConditionVis<Condition::GE>(), floatV3.value, floatV4.value));
        BOOST_CHECK(boost::apply_visitor(ConditionVis<Condition::GE>(), stringV3.value, stringV4.value));
    }
    BOOST_AUTO_TEST_CASE(Conditions_fulfilled_TupleValue_ANY)
    {
        TupleValue intV1((int)4);
        TupleValue intV2((int)2);

        TupleValue floatV1((float)7.5);
        TupleValue floatV2((float)1.1);

        TupleValue stringV1("Tuple");
        TupleValue stringV2("ANYTHING");


        TupleValue intV3((int)4);
        TupleValue intV4((int)4);

        TupleValue floatV3((float)1.1);
        TupleValue floatV4((float)1.1);

        TupleValue stringV3("Tuple");
        TupleValue stringV4("Tuple");


        TupleValue intV5((int)4);
        TupleValue intV6((int)6);

        TupleValue floatV5((float)7.5);
        TupleValue floatV6((float)11.1);

        TupleValue stringV5("ANYTHING");
        TupleValue stringV6("Tuple");



        BOOST_CHECK(boost::apply_visitor(ConditionVis<Condition::ANY>(), intV1.value, intV2.value));
        BOOST_CHECK(boost::apply_visitor(ConditionVis<Condition::ANY>(), floatV1.value, floatV2.value));
        BOOST_CHECK(boost::apply_visitor(ConditionVis<Condition::ANY>(), stringV1.value, stringV2.value));

        BOOST_CHECK(boost::apply_visitor(ConditionVis<Condition::ANY>(), intV3.value, intV4.value));
        BOOST_CHECK(boost::apply_visitor(ConditionVis<Condition::ANY>(), floatV3.value, floatV4.value));
        BOOST_CHECK(boost::apply_visitor(ConditionVis<Condition::ANY>(), stringV3.value, stringV4.value));

        BOOST_CHECK(boost::apply_visitor(ConditionVis<Condition::ANY>(), intV5.value, intV6.value));
        BOOST_CHECK(boost::apply_visitor(ConditionVis<Condition::ANY>(), floatV5.value, floatV6.value));
        BOOST_CHECK(boost::apply_visitor(ConditionVis<Condition::ANY>(), stringV5.value, stringV6.value));

    }


BOOST_AUTO_TEST_SUITE_END()



//test_suite* init_unit_test_suite( int argc, char * argv[] )
//{
//
//    return 0;
//}