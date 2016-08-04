#===============================================================================
# Unit tests
#===============================================================================

FILE(
    GLOB_RECURSE
    unittest_files
    unitary/*
    )

ADD_EXECUTABLE(
    unittest_tinyphysics
    ${unittest_files}
    )

TARGET_INCLUDE_DIRECTORIES(
    unittest_tinyphysics
    PUBLIC
    catch/
    ../src/cpp
)

ADD_DEPENDENCIES(unittest_tinyphysics tinyphysics-geometry)
TARGET_LINK_LIBRARIES(unittest_tinyphysics tinyphysics-geometry)

ADD_CUSTOM_TARGET(
    unittest
    unittest_tinyphysics -s -d yes
    DEPENDS unittest_tinyphysics
    )

#===============================================================================
# Overall testing
#===============================================================================

ADD_CUSTOM_TARGET(
    build_tests
    DEPENDS unittest_tinyphysics)

ADD_CUSTOM_TARGET(
    test
    DEPENDS unittest)