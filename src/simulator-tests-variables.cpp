#include <type_traits>
#include <algorithm>
#include "simulator-tests-variables.h"

Variable::Variable(std::string name)
{
    m_name = name;
    m_type = SupTypes::Unsupported;
}

template<typename T>
void Variable::setValue(T value) 
{
    if constexpr (std::is_floating_point_v<T>)
    {
        m_value.f_value = static_cast<float>(value);
        m_type = SupTypes::TypeFloat;
        m_isValid = true;
    }
    else if constexpr (std::is_integral_v<T> && !std::is_same_v<T, bool>)
    {
        m_value.i_value = static_cast<int>(value);
        m_type = SupTypes::TypeInteger;
        m_isValid = true;
    }
    else if constexpr (std::is_integral_v<T> && std::is_same_v<T, bool>)
    {
        m_value.i_value = static_cast<bool>(value);
        m_type = SupTypes::TypeBoolean;
        m_isValid = true;
    }
    else
    {
        // Shall we invalidate the variable, if it has been set with 
        // valid value before?
        m_isValid = false;
        m_type = SupTypes::Unsupported;
    }
}

template<typename T>
T Variable::getValue() const 
{
    if constexpr (std::is_floating_point_v<T>)
    {
        return m_value.f_value;
    }
    else if constexpr (std::is_integral_v<T> && !std::is_same_v<T, bool>)
    {
        return m_value.i_value; 
    }
    else if constexpr (std::is_integral_v<T> && std::is_same_v<T, bool>)
    {
        return m_value.b_value;
    }
    else 
    {
        return nullptr;
    }
}

std::string Variable::getName() const
{
    return m_name;    
}

SupTypes Variable::getType()
{
    return m_type;
}

bool Variable::isValid()
{
    return m_isValid;
}

VariableStore::VariableStore() 
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
    VariableSharedPtr vv = nullptr;

    // Shall we find by an exact name or by substring. 
    // Right now it is by an exact name.
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


std::vector<VariableSharedPtr> VariableStore::find(std::regex& regexp)
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



