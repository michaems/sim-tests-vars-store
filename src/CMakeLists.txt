
set(EXE_NAME ${PROJECT_NAME})
set(LIB_NAME simulator-variables-lib)


add_executable (
    ${EXE_NAME} 
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
) 

add_library (
    ${LIB_NAME}
    STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/simulator-tests-variable.cpp
)

target_include_directories(${LIB_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${EXE_NAME} ${LIB_NAME})

add_custom_command(TARGET ${EXE_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${EXE_NAME}> ${PROJECT_BINARY_DIR}/${EXE_NAME}
    COMMENT "The target ${EXE_NAME} copied to ${PROJECT_BINARY_DIR}/${EXE_NAME}"
)

