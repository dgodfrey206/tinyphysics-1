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
)

#target_link_libraries(unittest_tinyphysics snowball)

ADD_CUSTOM_TARGET(
    unittest
    unittest_tinyphysics -s -d yes
    DEPENDS unittest_tinyphysics
    )

#===============================================================================
# Overall testing
#===============================================================================

ADD_CUSTOM_TARGET(
    test
    DEPENDS unittest)