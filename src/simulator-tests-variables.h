#ifndef _SIMULATOR_TESTS_VARIABLES_
#define _SIMULATOR_TESTS_VARIABLES_

#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <regex>
#include <type_traits>
#include <variant>

using VariableVariant = std::variant<int, bool, float>;

class Variable 
{
public:
    Variable() = delete;
    Variable(std::string name);
    ~Variable();

    template<typename T>
    void setValue(T value);

    template<typename T>
    T getValue() const;

    std::string getName() const;
private:
    std::string m_name;
    VariableVariant m_value;
};

typedef std::shared_ptr<Variable> VariableSharedPtr;


class VariableStore
{
public:
    VariableStore();
    ~VariableStore();

    VariableSharedPtr createVariable(std::string name);

    VariableSharedPtr get(const std::string& name);
    std::vector<VariableSharedPtr> find(const std::regex& regexp);

    int getVariablesCount();


private:
    std::vector<VariableSharedPtr> m_variables;

};

#endif