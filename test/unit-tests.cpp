#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "simulator-tests-variable.cpp"
#include "simulator-tests-variables-store.cpp"


// Testing with Integer type
TEST(SimulatorVariableTests, testVariableWithIntegerValue)
{
    std::cout<<"Creating a Variable and setting its value as int"<<std::endl;
    
    int expValue = 25;

    Variable v1("var1_int", expValue, 1, 100, "desc for int");
    
    // Verify that:
    // 1. Value is correctly set
    EXPECT_EQ(expValue, v1.getValue<int>());

    // 2. Name is correctly set.
    EXPECT_EQ("var1_int", v1.getName());

    // 3. Description is correctly set.
    EXPECT_EQ("desc for int", v1.getDesc());

    // 4. Change the value and verify it is correct.
    v1.setValue<int>(35);
    EXPECT_EQ(35, v1.getValue<int>());
}

// Testing with Floating point type
TEST(SimulatorVariableTests, testVariableWithDoubleValue)
{
    std::cout<<"Creating a Variable and setting its value as double."<<std::endl;
    
    double expValue = 50.5;
    
    Variable v2("var2_double", expValue, 1.0, 120.6, "desc for double");
    v2.setValue<float>(expValue);
    
    // Verify that:
    // 1. Value is correctly set
    EXPECT_EQ(expValue, v2.getValue<double>());

    // 2. Name is correctly set.
    EXPECT_EQ("var2_double", v2.getName());

    // 3. Description is correctly set.
    EXPECT_EQ("desc for double", v2.getDesc());

    // 4. Change the value and verify it is correct.
    v2.setValue<double>(75.4);
    EXPECT_EQ(75.4, v2.getValue<double>());
}


// Testing with Boolean type
TEST(SimulatorVariableTests, testVariableWithBooleanValue)
{
    std::cout<<"Creating a Variable and setting its value as boolean."<<std::endl;
    
    bool expValue = true;
    
    Variable v3("var3_boolean", expValue, false, true, "desc for bool");
    
    // Verify that:
    // 1. Value is correctly set
    EXPECT_EQ(expValue, v3.getValue<bool>());

    // 2. Name is correctly set.
    EXPECT_EQ("var3_boolean", v3.getName());

    // 3. Description is correctly set.
    EXPECT_EQ("desc for bool", v3.getDesc());

    // The same verification with "true" value
    expValue = true;
    v3.setValue<bool>(expValue);

    // Verify that:
    // 4. Value is correctly set
    EXPECT_EQ(expValue, v3.getValue<bool>());
}


TEST(SimulatorVariableStoreTests, testVerifyTheStoreContainsCorrectAmountOfVariables)
{
    // Create a VariableStore with 100 integers and make sure the data is saved.
    auto vstore = VariableStore();
    for (int i=0; i<100; i++)
    {
        std::string name = "var_num_" + std::to_string(i);
        auto vv = vstore.createVariable(name, i, i-10, i+50, "desc for " + std::to_string(i));
    }

    // 1. Verify the store hase 100 Variables
    EXPECT_EQ(100, vstore.getVariablesCount());
}

TEST(SimulatorVariableStoreTests, testVerifyTheStoreReturnsCorrectVariableWithGet)
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
    EXPECT_TRUE(vs != nullptr);

    EXPECT_EQ("var_num_50", vs->getName());
    EXPECT_EQ(50, vs->getValue<int>());

    vs = vstore.get("var_num_82");
    EXPECT_TRUE(vs != nullptr);

    EXPECT_EQ("var_num_82", vs->getName());
    EXPECT_EQ(82, vs->getValue<int>());

    // 2. If given Varaible not found, then nullpointer returned.
    vs = vstore.get("var_num_190");
    EXPECT_TRUE(vs == nullptr);



}

TEST(SimulatorVariableStoreTests, testVerifyTheStoreReturnsCorrectVariablesWithRegex)
{
    // Create a VariableStore with 100 integers.
    auto vstore = VariableStore();
    for (int i=0.5; i<100; i++)
    {
        std::string name = "var_num_" + std::to_string(i);
        auto vv = vstore.createVariable(name, i, i-10, i+50, "desc for " + std::to_string(i));
    }

    std::regex regex1("[a-z]+_[a-z]+_2.");

    std::vector<VariableSharedPtr> vs = vstore.find(regex1);

    // 1. vs vector should contain 10 Variables having 1 in their name (from 20 to 29)
    EXPECT_EQ(10, vs.size());

    // 2. Checking some rundom Variable in vs vector.
    VariableSharedPtr vsp12 = vs.at(2);
    EXPECT_EQ("var_num_22", vsp12->getName());
    EXPECT_EQ(22, vsp12->getValue<int>());
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}