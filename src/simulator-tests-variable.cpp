#include <type_traits>
#include <algorithm>
#include <cassert>
#include "simulator-tests-variable.h"



Variable::Variable(std::string name, VariableVariant value, VariableVariant minLimit, VariableVariant maxLimit, std::string desc) 
    : m_name(name), m_value(value), m_minLimit(minLimit), m_maxLimit(maxLimit), m_desc(desc)
{
    // if any logic is needed for 
    // min and max limits, to be added
    // later.    

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
auto Variable::getValue() const 
{
    assert(std::holds_alternative<T>(m_value));
    return std::get<T>(m_value);
}

std::string Variable::getName() const
{
    return m_name;    
}

std::string Variable::getDesc() const
{
    return m_desc;
}





