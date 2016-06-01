#define BOOST_TEST_MODULE LindaLangModule

#include <boost/test/included/unit_test.hpp>
#include "Linda.h"
#include "TupleValue.h"
#include "Tuple.h"
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include "../server/TupleSpace.h"

#include "ConditionVis.h"

#include "Conditions.h"

using namespace boost::unit_test;

BOOST_AUTO_TEST_SUITE( LindaLangSuite )

    BOOST_AUTO_TEST_CASE(TupleValue_getTypeName)
    {
        TupleValue intValue(1);

        TupleValue floatValue(1.2f);

        TupleValue strValue("Tuple");


        BOOST_CHECK_EQUAL("float", floatValue.getTypeName());
        BOOST_CHECK_EQUAL("integer", intValue.getTypeName());
        BOOST_CHECK_EQUAL("string", strValue.getTypeName());
    }

    BOOST_AUTO_TEST_CASE(Tuple_serialization)
    {
        Tuple tuple;
        TupleValue intVal(2);
        TupleValue floatVal(1.0f);
        TupleValue strVal("Tuple");

        tuple.addValue(intVal);
        tuple.addValue(floatVal);
        tuple.addValue(strVal);

        std::stringstream ss;
        boost::archive::text_oarchive oa(ss);

        oa << tuple;

        boost::archive::text_iarchive ia(ss);

        Tuple newTuple;
        ia >> newTuple;

        BOOST_CHECK_EQUAL(tuple.getValues().size(), 3);
        BOOST_CHECK_EQUAL(tuple.getValues().size(), newTuple.getValues().size());
        BOOST_CHECK_EQUAL(tuple.getValues()[0].value, newTuple.getValues()[0].value);

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
        Pipe p(0);
        p.writePipe(msg, (unsigned)std::strlen(msg));
        p.readPipe(rcv, (unsigned)std::strlen(msg));
        BOOST_CHECK(std::strcmp(msg, rcv));
        free(rcv);
        p.closeDescriptors();
    }

    BOOST_AUTO_TEST_CASE(Pipe_write_too_much)
    {
        const char *msg = "Hello Linda!";
        char *rcv = (char*)malloc(sizeof(char) * std::strlen(msg));
        Pipe p(0);
        try
        {
            p.writePipe(msg, PIPE_BUF + 2);
        }
        catch(std::exception& err)
        {
            BOOST_CHECK_EQUAL(std::string(err.what()).compare("Too big message: " + std::to_string(PIPE_BUF + 2)), 0);
        }
        free(rcv);
        p.closeDescriptors();
    }

    BOOST_AUTO_TEST_CASE(Pipe_read_not_enough)
    {
        const char *msg = "Hello Linda!";
        char *expected = (char*)"Hello";
        char *rcv = (char*)malloc(sizeof(char) * (std::strlen(msg) - 7));
        Pipe p(0);
        p.writePipe(msg, (unsigned)std::strlen(msg));
        try
        {
            p.readPipe(rcv, (unsigned)(std::strlen(msg) - 7));
        }
        catch(std::exception& err)
        {
            BOOST_CHECK(std::string(err.what()).compare("Incomplete reading pipe"));
            BOOST_CHECK(std::strcmp(rcv, expected));
        }
        free(rcv);
        p.closeDescriptors();
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
        TupleValue floatValue1(5.2f);
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
        TupleValue intV3((int)2);

        TupleValue floatV1(5.5f);
        TupleValue floatV2(5.5f);
        TupleValue floatV3(6.5f);

        TupleValue stringV1("Tuple");
        TupleValue stringV2("Tuple");
        TupleValue stringV3("Tuple-other");

        BOOST_CHECK(boost::apply_visitor(ConditionVis<Condition::EQ>(), intV1.value, intV2.value));
        BOOST_CHECK(boost::apply_visitor(ConditionVis<Condition::EQ>(), floatV1.value, floatV2.value));
        BOOST_CHECK(boost::apply_visitor(ConditionVis<Condition::EQ>(), stringV1.value, stringV2.value));
        BOOST_CHECK(!boost::apply_visitor(ConditionVis<Condition::EQ>(), intV2.value, intV3.value));
        BOOST_CHECK(!boost::apply_visitor(ConditionVis<Condition::EQ>(), floatV2.value, floatV3.value));
        BOOST_CHECK(!boost::apply_visitor(ConditionVis<Condition::EQ>(), stringV2.value, stringV3.value));

    }
    BOOST_AUTO_TEST_CASE(Conditions_fulfilled_TupleValue_LS)
    {
        TupleValue intV1((int)1);
        TupleValue intV2((int)2);

        TupleValue floatV1(5.5f);
        TupleValue floatV2(6.5f);

        TupleValue stringV1("Tuple1");
        TupleValue stringV2("Tuple2");

        BOOST_CHECK(boost::apply_visitor(ConditionVis<Condition::LS>(), intV1.value, intV2.value));
        BOOST_CHECK(boost::apply_visitor(ConditionVis<Condition::LS>(), floatV1.value, floatV2.value));
        BOOST_CHECK(boost::apply_visitor(ConditionVis<Condition::LS>(), stringV1.value, stringV2.value));
        BOOST_CHECK(!boost::apply_visitor(ConditionVis<Condition::LS>(), intV2.value, intV1.value));
        BOOST_CHECK(!boost::apply_visitor(ConditionVis<Condition::LS>(), floatV2.value, floatV1.value));
        BOOST_CHECK(!boost::apply_visitor(ConditionVis<Condition::LS>(), stringV2.value, stringV1.value));
    }
    BOOST_AUTO_TEST_CASE(Conditions_fulfilled_TupleValue_LE)
    {
        TupleValue intV1((int)1);
        TupleValue intV2((int)2);

        TupleValue floatV1(5.5f);
        TupleValue floatV2(6.5f);

        TupleValue stringV1("Tuple1");
        TupleValue stringV2("Tuple2");

        TupleValue intV3((int)1);
        TupleValue intV4((int)1);

        TupleValue floatV3(5.5f);
        TupleValue floatV4(5.5f);

        TupleValue stringV3("Tuple");
        TupleValue stringV4("Tuple");


        BOOST_CHECK(boost::apply_visitor(ConditionVis<Condition::LE>(), intV1.value, intV2.value));
        BOOST_CHECK(boost::apply_visitor(ConditionVis<Condition::LE>(), floatV1.value, floatV2.value));
        BOOST_CHECK(boost::apply_visitor(ConditionVis<Condition::LE>(), stringV1.value, stringV2.value));

        BOOST_CHECK(boost::apply_visitor(ConditionVis<Condition::LE>(), intV3.value, intV4.value));
        BOOST_CHECK(boost::apply_visitor(ConditionVis<Condition::LE>(), floatV3.value, floatV4.value));
        BOOST_CHECK(boost::apply_visitor(ConditionVis<Condition::LE>(), stringV3.value, stringV4.value));

        BOOST_CHECK(!boost::apply_visitor(ConditionVis<Condition::LE>(), intV2.value, intV1.value));
        BOOST_CHECK(!boost::apply_visitor(ConditionVis<Condition::LE>(), floatV2.value, floatV1.value));
        BOOST_CHECK(!boost::apply_visitor(ConditionVis<Condition::LE>(), stringV2.value, stringV1.value));
    }
    BOOST_AUTO_TEST_CASE(Conditions_fulfilled_TupleValue_GR)
    {
        TupleValue intV1((int)3);
        TupleValue intV2((int)2);

        TupleValue floatV1(7.5f);
        TupleValue floatV2(6.5f);

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

        TupleValue floatV1(7.5f);
        TupleValue floatV2(6.5f);

        TupleValue stringV1("Tuple3");
        TupleValue stringV2("Tuple2");

        TupleValue intV3((int)1);
        TupleValue intV4((int)1);

        TupleValue floatV3(5.5f);
        TupleValue floatV4(5.5f);

        TupleValue stringV3("Tuple");
        TupleValue stringV4("Tuple");


        BOOST_CHECK(boost::apply_visitor(ConditionVis<Condition::GE>(), intV1.value, intV2.value));
        BOOST_CHECK(boost::apply_visitor(ConditionVis<Condition::GE>(), floatV1.value, floatV2.value));
        BOOST_CHECK(boost::apply_visitor(ConditionVis<Condition::GE>(), stringV1.value, stringV2.value));

        BOOST_CHECK(boost::apply_visitor(ConditionVis<Condition::GE>(), intV3.value, intV4.value));
        BOOST_CHECK(boost::apply_visitor(ConditionVis<Condition::GE>(), floatV3.value, floatV4.value));
        BOOST_CHECK(boost::apply_visitor(ConditionVis<Condition::GE>(), stringV3.value, stringV4.value));

        BOOST_CHECK(!boost::apply_visitor(ConditionVis<Condition::GE>(), intV2.value, intV1.value));
        BOOST_CHECK(!boost::apply_visitor(ConditionVis<Condition::GE>(), floatV2.value, floatV1.value));
        BOOST_CHECK(!boost::apply_visitor(ConditionVis<Condition::GE>(), stringV2.value, stringV1.value));
    }
    BOOST_AUTO_TEST_CASE(Conditions_fulfilled_TupleValue_ANY)
    {
        TupleValue intV1((int)4);
        TupleValue intV2((int)2);

        TupleValue floatV1(7.5f);
        TupleValue floatV2(1.1f);

        TupleValue stringV1("Tuple");
        TupleValue stringV2("ANYTHING");


        TupleValue intV3((int)4);
        TupleValue intV4((int)4);

        TupleValue floatV3(1.1f);
        TupleValue floatV4(1.1f);

        TupleValue stringV3("Tuple");
        TupleValue stringV4("Tuple");


        TupleValue intV5((int)4);
        TupleValue intV6((int)6);

        TupleValue floatV5(7.5f);
        TupleValue floatV6(11.1f);

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

    BOOST_AUTO_TEST_CASE(Conditions_fulfilled_TupleValue_WrongTypes)
    {
        TupleValue intValue((int)4);
        TupleValue floatValue(7.5f);
        TupleValue stringValue("Tuple");

        BOOST_CHECK(!boost::apply_visitor(ConditionVis<Condition::ANY>(), intValue.value, floatValue.value));
        BOOST_CHECK(!boost::apply_visitor(ConditionVis<Condition::ANY>(), intValue.value, stringValue.value));
        BOOST_CHECK(!boost::apply_visitor(ConditionVis<Condition::ANY>(), floatValue.value, stringValue.value));
    }

    BOOST_AUTO_TEST_CASE(Tuple_value_check_pattern)
    {
        TupleValue tupleValue1(45.45f);
        TuplePatternValue tuplePatValue1(30.f, Condition::EQ);
        TuplePatternValue tuplePatValue2(60.f, Condition::LE);

        BOOST_CHECK(!tupleValue1.fitsPattern(tuplePatValue1));
        BOOST_CHECK(tupleValue1.fitsPattern(tuplePatValue2));

    }

    BOOST_AUTO_TEST_CASE(Tuple_checkPattern_OK)
    {
        Tuple tuple;
        tuple.addValue(TupleValue(5));
        tuple.addValue(TupleValue(1.4f));
        tuple.addValue(TupleValue("zupa"));

        TuplePattern pattern;
        pattern.addValue(TuplePatternValue(2, Condition::GE));
        pattern.addValue(TuplePatternValue(1.4f));
        pattern.addValue(TuplePatternValue("arbuz", Condition::GR));

        BOOST_CHECK(tuple.checkPattern(pattern));
    }


    BOOST_AUTO_TEST_CASE(Tuple_checkPattern_FAIL_1)
    {
        Tuple tuple;
        tuple.addValue(TupleValue(5));
        tuple.addValue(TupleValue(1.4f));
        tuple.addValue(TupleValue(2.0f));
        tuple.addValue(TupleValue("zupa"));

        TuplePattern pattern;
        pattern.addValue(TuplePatternValue(2, Condition::GE));
        pattern.addValue(TuplePatternValue(1.4f));
        pattern.addValue(TuplePatternValue("arbuz", Condition::GR));

        BOOST_CHECK(!tuple.checkPattern(pattern));
    }


    BOOST_AUTO_TEST_CASE(Tuple_checkPattern_FAIL_2)
    {
        Tuple tuple;
        tuple.addValue(TupleValue(5));
        tuple.addValue(TupleValue(1.4f));
        tuple.addValue(TupleValue("zupa"));

        TuplePattern pattern;
        pattern.addValue(TuplePatternValue(12, Condition::GE));
        pattern.addValue(TuplePatternValue(1.0f, Condition::LS));
        pattern.addValue(TuplePatternValue("arbuz", Condition::GR));

        BOOST_CHECK(!tuple.checkPattern(pattern));
    }

    BOOST_AUTO_TEST_CASE(Linda_output)
    {
        Pipe pRequest(0);
        Pipe pResponse(1);
        Linda linda(pResponse, pRequest);

        Tuple tuple;
        tuple.addValue(TupleValue(5));
        tuple.addValue(TupleValue(1.4f));
        tuple.addValue(TupleValue("zupa"));

        BOOST_CHECK(linda.output(tuple));
        pRequest.closeDescriptors();
        pResponse.closeDescriptors();
    }

    BOOST_AUTO_TEST_CASE(Linda_input)
    {
        Pipe pRequest(0);
        Pipe pResponse(1);
        Linda linda(pResponse, pRequest);

        Tuple tuple;
        tuple.addValue(TupleValue(5));
        tuple.addValue(TupleValue(1.4f));
        tuple.addValue(TupleValue("zupa"));

        TuplePattern pattern;
        pattern.addValue(TuplePatternValue(5));
        pattern.addValue(TuplePatternValue(1.4f));
        pattern.addValue(TuplePatternValue("zupa"));

        Tuple tuple2;

        std::stringstream ss;
        boost::archive::text_oarchive oa(ss);

        oa << tuple;
        pResponse.writePipe(ss.str().c_str(), ss.str().size());

        BOOST_ASSERT(linda.read(pattern, 5, tuple2));

        BOOST_CHECK_EQUAL(tuple.getValues().size(), tuple2.getValues().size());
        pRequest.closeDescriptors();
        pResponse.closeDescriptors();
    }

    BOOST_AUTO_TEST_CASE(Tuple_space_insertTuple)
    {
        TupleSpace ts;
        Tuple t1;
        t1.addValue(TupleValue(std::string("tuple")));
        t1.addValue(TupleValue(std::string("space")));
        t1.addValue(TupleValue(int(3)));
        t1.addValue(TupleValue(float(0.1415)));
        Tuple t2;
        t2.addValue(TupleValue(std::string("adam")));
        t2.addValue(TupleValue(float(3.1415)));
        t2.addValue(TupleValue(std::string("kowalski")));

        ts.insertTuple(t1);
        ts.insertTuple(t2);

        TuplePattern p1;
        p1.addValue(TuplePatternValue(std::string("adam"), Condition::EQ));
        p1.addValue(TuplePatternValue(float(3.1415), Condition::EQ));
        p1.addValue(TuplePatternValue(std::string("kowalski"), Condition::EQ));

        TuplePattern p2;
        p2.addValue(TuplePatternValue(std::string("tuple"), Condition::EQ));
        p2.addValue(TuplePatternValue(std::string("space"), Condition::EQ));
        p2.addValue(TuplePatternValue(int(3), Condition::EQ));
        p2.addValue(TuplePatternValue(float(0.1415), Condition::EQ));

        Tuple f1, f2;
        ts.getTuple(p1, f1);
        ts.getTuple(p2, f2);

        BOOST_CHECK(f1.checkPattern(p1));
        BOOST_CHECK(f2.checkPattern(p2));
    }

    BOOST_AUTO_TEST_CASE(Tuple_space_eraseTuple)
    {
        TupleSpace ts;
        Tuple t1;
        t1.addValue(TupleValue(std::string("tuple")));
        t1.addValue(TupleValue(std::string("space")));
        t1.addValue(TupleValue(int(3)));
        t1.addValue(TupleValue(float(0.1415)));
        Tuple t2;
        t2.addValue(TupleValue(std::string("adam")));
        t2.addValue(TupleValue(float(3.1415)));
        t2.addValue(TupleValue(std::string("kowalski")));
        Tuple t3;
        t3.addValue(TupleValue(std::string("adam")));
        t3.addValue(TupleValue(float(3.1415)));

        Tuple t4;
        t4.addValue(TupleValue(std::string("adam")));

        ts.insertTuple(t1);
        ts.insertTuple(t2);
        ts.insertTuple(t3);
        ts.insertTuple(t4);

        TuplePattern p1;
        p1.addValue(TuplePatternValue(std::string("adam"), Condition::EQ));

        Tuple f1, f2;
        ts.getTuple(p1, f1);
        BOOST_CHECK(f1.checkPattern(p1));
        BOOST_CHECK(ts.removeTuple(p1));

        BOOST_CHECK(!ts.getTuple(p1, f2));

    }



BOOST_AUTO_TEST_SUITE_END()
