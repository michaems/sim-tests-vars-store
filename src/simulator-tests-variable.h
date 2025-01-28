#ifndef _SIMULATOR_TESTS_VARIABLE_
#define _SIMULATOR_TESTS_VARIABLE_
#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <regex>
#include <type_traits>
#include <variant>

using VariableVariant = std::variant<int, bool, double>;


class Variable 
{
public:
    Variable() = delete;
    Variable(std::string name, 
             VariableVariant value, 
             VariableVariant minLimit, 
             VariableVariant maxLimit, 
             std::string desc);
    ~Variable();

    template<typename T>
    void setValue(T value);

    template<typename T>
    auto getValue() const;

    std::string getName() const;
    std::string getDesc() const;
private:
    std::string m_name;
    std::string m_desc;
    VariableVariant m_minLimit;
    VariableVariant m_maxLimit;
    VariableVariant m_value;
    
};

typedef std::shared_ptr<Variable> VariableSharedPtr;

#endif