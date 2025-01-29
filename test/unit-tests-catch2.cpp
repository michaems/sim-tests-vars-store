#include <catch2/catch_test_macros.hpp>
#include "simulator-tests-variable.cpp"
#include "simulator-tests-variables-store.cpp"


TEST_CASE("Test Variable With Integer Value")
{
    int expValue = 25;

    Variable v1("var1_int", expValue, 1, 100, "desc for int");
    
    // Verify that:
    // 1. Value is correctly set
    REQUIRE(expValue == v1.getValue<int>());

    // 2. Name is correctly set.
    REQUIRE("var1_int" == v1.getName());

    // 3. Description is correctly set.
    REQUIRE("desc for int" == v1.getDesc());

    // 4. Change the value and verify it is correct.
    v1.setValue<int>(35);
    REQUIRE(35 == v1.getValue<int>());
}

// Testing with Floating point type
TEST_CASE("Test Variable With Double value")
{
    double expValue = 50.5;
    
    Variable v2("var2_double", expValue, 1.0, 120.6, "desc for double");
    v2.setValue<float>(expValue);
    
    // Verify that:
    // 1. Value is correctly set
    REQUIRE(expValue == v2.getValue<double>());

    // 2. Name is correctly set.
    REQUIRE("var2_double" == v2.getName());

    // 3. Description is correctly set.
    REQUIRE("desc for double" == v2.getDesc());

    // 4. Change the value and verify it is correct.
    v2.setValue<double>(75.4);
    REQUIRE(75.4 == v2.getValue<double>());
}

// Testing with Boolean type
TEST_CASE("Test Variable With Boolean value")
{
    bool expValue = true;
    
    Variable v3("var3_boolean", expValue, false, true, "desc for bool");
    
    // Verify that:
    // 1. Value is correctly set
    REQUIRE(expValue == v3.getValue<bool>());

    // 2. Name is correctly set.
    REQUIRE("var3_boolean" == v3.getName());

    // 3. Description is correctly set.
    REQUIRE("desc for bool" == v3.getDesc());

    // The same verification with "true" value
    expValue = true;
    v3.setValue<bool>(expValue);

    // Verify that:
    // 4. Value is correctly set
    REQUIRE(expValue == v3.getValue<bool>());
}

// Testing VariableStore
TEST_CASE("Verify the Store contains correct amount of Variables")
{
    // Create a VariableStore with 100 integers and make sure the data is saved.
    auto vstore = VariableStore();
    for (int i=0; i<100; i++)
    {
        std::string name = "var_num_" + std::to_string(i);
        auto vv = vstore.createVariable(name, i, i-10, i+50, "desc for " + std::to_string(i));
    }

    // 1. Verify the store hase 100 Variables
    REQUIRE(100 == vstore.getVariablesCount());
}

TEST_CASE("Verify the Store returns correct Variable with Get")
{
    // Create a VariableStore with 100 integers.
    auto vstore = VariableStore();
    for (int i=0; i<100; i++)
    {
        std::string name = "var_num_" + std::to_string(i);
        auto vv = vstore.createVariable(name, i, i-10, i+50, "desc for " + std::to_string(i));
    }

    // 1. Verify the store finds by name and returns a Varible shared pointer correctly
    VariableSharedPtr vs = vstore.get("var_num_50");
    REQUIRE_FALSE(vs == nullptr);

    REQUIRE("var_num_50" == vs->getName());
    REQUIRE(50 == vs->getValue<int>());

    vs = vstore.get("var_num_82");
    REQUIRE_FALSE(vs == nullptr);

    REQUIRE("var_num_82" == vs->getName());
    REQUIRE(82 == vs->getValue<int>());

    // 2. If given Varaible not found, then nullpointer returned.
    vs = vstore.get("var_num_190");
    REQUIRE_FALSE(vs != nullptr);
}


TEST_CASE("Verify the Store returns correct Variables With Regex")
{
    // Create a VariableStore with 100 integers.
    auto vstore = VariableStore();
    for (int i=0; i<100; i++)
    {
        std::string name = "var_num_" + std::to_string(i);
        auto vv = vstore.createVariable(name, i, i-10, i+50, "desc for " + std::to_string(i));
    }

    std::regex regex1("[a-z]+_[a-z]+_2.");

    std::vector<VariableSharedPtr> vs = vstore.find(regex1);

    // 1. vs vector should contain 10 Variables having 2 in their name (from 20 to 29)
    REQUIRE(10 == vs.size());

    // 2. Checking some rundom Variable in vs vector.
    VariableSharedPtr vsp22 = vs.at(2);
    REQUIRE("var_num_22" == vsp22->getName());
    REQUIRE(22 == vsp22->getValue<int>());
}