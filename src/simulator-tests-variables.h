#ifndef _SIMULATOR_TESTS_VARIABLES_
#define _SIMULATOR_TESTS_VARIABLES_

#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <regex>
#include <type_traits>

// Supported types
enum class SupTypes 
{
    Unsupported = 0,
    TypeBoolean,
    TypeInteger,
    TypeFloat
};

typedef union 
{
    bool b_value;
    int  i_value;
    float f_value;
} union_var;


class Variable 
{
public:
    Variable() = delete;
    Variable(std::string name);

    template<typename T>
    void setValue(T value);

    template<typename T>
    T getValue() const;

    SupTypes getType();

    bool isValid();

    std::string getName() const;
private:
    SupTypes m_type;
    std::string m_name;
    union_var m_value;
    bool m_isValid;
};

typedef std::shared_ptr<Variable> VariableSharedPtr;

class VariableStore
{
public:
    VariableStore();

    VariableSharedPtr createVariable(std::string name);

    VariableSharedPtr get(const std::string& name);
    std::vector<VariableSharedPtr> find(std::regex& regexp);

    int getVariablesCount();


private:
    std::vector<VariableSharedPtr> m_variables;

};

#endif