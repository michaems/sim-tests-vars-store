#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "simulator-tests-variables.cpp"


// Testing with Integer type
TEST(SimulatorVariableTests, testVariableWithIntegerValue)
{
    std::cout<<"Creating a Variable and setting its value as int"<<std::endl;
    
    int expValue = 25;

    Variable v1("var1_int");
    v1.setValue<int>(expValue);
    
    // Verify that:
    // 1. Value is correctly set
    EXPECT_EQ(expValue, v1.getValue<int>());

    // 2. Name is correctly set.
    EXPECT_EQ("var1_int", v1.getName());

    //3. Type is correctly set
    EXPECT_EQ(SupTypes::TypeInteger, v1.getType());

}

// Testing with Floating point type
TEST(SimulatorVariableTests, testVariableWithFloatValue)
{
    std::cout<<"Creating a Variable and setting its value as float."<<std::endl;
    
    float expValue = 50.5;
    
    Variable v2("var2_float");
    v2.setValue<float>(expValue);
    
    // Verify that:
    // 1. Value is correctly set
    EXPECT_EQ(expValue, v2.getValue<float>());

    // 2. Name is correctly set.
    EXPECT_EQ("var2_float", v2.getName());

    //3. Type is correctly set
    EXPECT_EQ(SupTypes::TypeFloat, v2.getType());
}


// Testing with Boolean type
TEST(SimulatorVariableTests, testVariableWithBooleanValue)
{
    std::cout<<"Creating a Variable and setting its value as boolean."<<std::endl;
    
    bool expValue = false;
    
    Variable v3("var3_boolean");
    v3.setValue<bool>(expValue);
    
    // Verify that:
    // 1. Value is correctly set
    EXPECT_EQ(expValue, v3.getValue<bool>());

    // 2. Name is correctly set.
    EXPECT_EQ("var3_boolean", v3.getName());

    //3. Type is correctly set
    EXPECT_EQ(SupTypes::TypeBoolean, v3.getType());

    // The same verification with "true" value
    expValue = true;
    v3.setValue<bool>(expValue);

    // Verify that:
    // 1. Value is correctly set
    EXPECT_EQ(expValue, v3.getValue<bool>());

    // 2. Type is correctly set
    EXPECT_EQ(SupTypes::TypeBoolean, v3.getType());

}

TEST(SimulatorVariableTests, testVerifyTheValueIsInvalidated)
{
    std::cout<<"Creating a Variable and makeing sure it \
        has been invalidated after second set"<<std::endl;
    
    int expValue = 100;
    
    Variable v4("var4_valid");
    v4.setValue<int>(expValue);
    
    // Verify that:
    // 1. Value is correctly set
    EXPECT_EQ(expValue, v4.getValue<int>());

    // 2. Variable is valid
    EXPECT_EQ(true, v4.isValid());

    // 3. Tring to set an unsupported type
    v4.setValue<std::string>("test_string");

    // 4. Verify isValid() function returnes false.
    EXPECT_EQ(false, v4.isValid());

}

TEST(SimulatorVariableStoreTests, testVerifyTheStoreConstainsCorrectAmountOfVariables)
{
    // Create a VariableStore with 100 integers and make sure the data is saved.
    auto vstore = VariableStore();
    for (int i=0; i<100; i++)
    {
        std::string name = "var_num_" + std::to_string(i);
        auto vv = vstore.createVariable(name);
        vv->setValue<int>(i);
    }

    // 1. Verify the store hase 100 Variables
    EXPECT_EQ(100, vstore.getVariablesCount());
}

TEST(SimulatorVariableStoreTests, testVerifyTheStoreResturnsCorrectVariableWithGet)
{
    // Create a VariableStore with 100 integers.
    auto vstore = VariableStore();
    for (int i=0; i<100; i++)
    {
        std::string name = "var_num_" + std::to_string(i);
        auto vv = vstore.createVariable(name);
        vv->setValue<int>(i);
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
}

TEST(SimulatorVariableStoreTests, testVerifyTheStoreResturnsCorrectVariablesWithRegex)
{
    // Create a VariableStore with 100 integers.
    auto vstore = VariableStore();
    for (int i=0; i<100; i++)
    {
        std::string name = "var_num_" + std::to_string(i);
        auto vv = vstore.createVariable(name);
        vv->setValue<int>(i);
    }

    std::regex regex1("[a-z]+_[a-z]+_1.");

    std::vector<VariableSharedPtr> vs = vstore.find(regex1);

    // 1. vs vector should contain 10 Variables having 1 in their name (from 10 to 19)
    EXPECT_EQ(10, vs.size());

    // 2. Checking some rundom Variable in vs vector.
    VariableSharedPtr vsp12 = vs.at(2);
    EXPECT_EQ("var_num_12", vsp12->getName());
    EXPECT_EQ(12, vsp12->getValue<int>());


}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}