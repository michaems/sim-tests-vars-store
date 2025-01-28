#include <iostream>
#include <regex>
#include "simulator-tests-variable.cpp"
#include "simulator-tests-variables-store.cpp"


void testVariable();
void testVstore();

int main()
{
    
    testVariable();
    testVstore();

    return 0;
}

void testVariable()
{
    auto vble = Variable("var_1", 25.2, 1.0, 100.0, "var-1-with-double");
    std::cout << "Var name = " << vble.getName() << std::endl;
    std::cout << "Var value = " << vble.getValue<double>() << std::endl;
    std::cout << "Var desc = " << vble.getDesc() << std::endl;

    auto vble1 = Variable("var_2_integer", 25, 1, 10, "second var as int");
    std::cout << "Var name = " << vble1.getName() << std::endl;
    std::cout << "Var value = " << vble1.getValue<int>() << std::endl;
    std::cout << "Var desc = " << vble1.getDesc() << std::endl;


    auto vble3 = Variable("var_3_bool", true, false, true, "Third var as bool");
    std::cout << "Var name = " << vble3.getName() << std::endl;
    std::cout << "Var value = " << vble3.getValue<bool>() << std::endl;
    std::cout << "Var desc = " << vble3.getDesc() << std::endl;
}

void testVstore()
{
    auto vstore = VariableStore();
    for (int i=1; i<30; i++)
    {
        std::string name = "var_num_" + std::to_string(i);
        auto vv = vstore.createVariable<double>(name, 1.5 + i, 1.0, 100.5, "a short desc for " + std::to_string(1.5 + i));
    }

    std::regex reg1("[a-z]+_[a-z]+_1.");

    std::vector<VariableSharedPtr> vs = vstore.find(reg1);

    for (const VariableSharedPtr vsp : vs)
    {
        std::cout << "found and returned: " << vsp->getName() << " value = " 
                << vsp->getValue<double>() << " desc = " << vsp->getDesc() << std::endl;
    }
}