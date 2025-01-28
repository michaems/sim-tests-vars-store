#include "simulator-tests-variables-store.h"



VariableStore::VariableStore()
{

}

VariableStore::~VariableStore()
{

}

template<typename T>
VariableSharedPtr VariableStore::createVariable(std::string name, T value, T min, T max, std::string desc)
{
    
    auto vsp = std::make_shared<Variable>(name, value, min, max, desc);
    m_variables.push_back(vsp);
    return vsp;
}

VariableSharedPtr VariableStore::get(const std::string& name)
{
     VariableSharedPtr vv;

    auto it = std::find_if(m_variables.begin(), m_variables.end(), 
                           [&name](VariableSharedPtr vsp) {
                               return vsp->getName() == name;
                           });

    if (it != m_variables.end())
    {
        vv = *it;
    }

    return vv;
}


std::vector<VariableSharedPtr> VariableStore::find(const std::regex& regexp)
{
    std::vector<VariableSharedPtr> vvsp;
    
    // Going through all variables and looking for mutch.
    for (const VariableSharedPtr vsp : m_variables)
    {
        bool found = false;
        try
        {
            found = std::regex_match(vsp->getName(), regexp);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
    
        if(found)
        {
            vvsp.push_back(vsp);
        }
    }
    
    return vvsp;
}

int VariableStore::getVariablesCount()
{
    return m_variables.size();
}