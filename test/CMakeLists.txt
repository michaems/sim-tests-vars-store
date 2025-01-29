set(UNIT_TEST_EXE unit_tests)
set(UNIT_TEST_CATCH2_SRC ${CMAKE_CURRENT_SOURCE_DIR}/unit-tests-catch2.cpp)
set(UNIT_TEST_INC_DIR ${CMAKE_SOURCE_DIR}/src)

add_executable (
    ${UNIT_TEST_EXE}
    ${UNIT_TEST_CATCH2_SRC}
)

target_include_directories(${UNIT_TEST_EXE} PUBLIC ${UNIT_TEST_INC_DIR})

target_link_libraries (
    unit_tests
    Catch2::Catch2WithMain
)

#add_custom_command(TARGET ${UNIT_TEST_EXE} POST_BUILD
#    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${UNIT_TEST_EXE}> ${PROJECT_BINARY_DIR}/${UNIT_TEST_EXE}
#    COMMENT "The target ${UNIT_TEST_EXE} copied to ${PROJECT_BINARY_DIR}/${UNIT_TEST_EXE}"
#)
