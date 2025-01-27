#include <type_traits>
#include <algorithm>
#include "simulator-tests-variables.h"

Variable::Variable(std::string name) : m_name(name)
{
    
}

Variable::~Variable()
{

}

template<typename T>
void Variable::setValue(T value) 
{
    // Compile time error occurs,
    // if wrong type is provided.
    m_value = value;
}

template<typename T>
T Variable::getValue() const 
{
    if (std::holds_alternative<T>(m_value))
    {
        return std::get<T>(m_value);
    }
    else
    {
        // What to return if wrong type is provided.
    } 
}

std::string Variable::getName() const
{
    return m_name;    
}

VariableStore::VariableStore()
{

}

VariableStore::~VariableStore()
{

}

VariableSharedPtr VariableStore::createVariable(std::string name) 
{
    auto vsp = std::make_shared<Variable>(name);
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



