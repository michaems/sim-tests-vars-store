#include <iostream>
#include <regex>
#include "simulator-tests-variables.cpp"


int main()
{
    auto vstore = VariableStore();
    for (int i=1; i<30; i++)
    {
        std::string name = "var_num_" + std::to_string(i);
        auto vv = vstore.createVariable(name);
        vv->setValue<int>(i);
    }

    std::regex reg1("[a-z]+_[a-z]+_1.");

    std::vector<VariableSharedPtr> vs = vstore.find(reg1);

    for (const VariableSharedPtr vsp : vs)
    {
        std::cout << "found and returned: " << vsp->getName() << " value = " << vsp->getValue<int>() << std::endl;
    }
}