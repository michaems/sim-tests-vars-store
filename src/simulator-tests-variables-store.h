#ifndef _SIMULATOR_TESTS_VARIABLE_STORE_
#define _SIMULATOR_TESTS_VARIABLE_STORE_



class VariableStore
{
public:
    VariableStore();
    ~VariableStore();

    template<typename T>
    VariableSharedPtr createVariable(std::string name, T value, T min, T max, std::string desc="desc-not-set");

    VariableSharedPtr get(const std::string& name);
    std::vector<VariableSharedPtr> find(const std::regex& regexp);

    int getVariablesCount();


private:
    std::vector<VariableSharedPtr> m_variables;
};
#endif