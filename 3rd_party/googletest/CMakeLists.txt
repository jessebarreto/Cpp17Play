

# Googletest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# include(ExternalProject)
# ExternalProject_Add(
#     googletest
#     URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
#     INSTALL_COMMAND ""
# )
# ExternalProject_Get_Property(
#     googletest 
#     binary_dir
# )

# add_library(gtest UNKNOWN IMPORTED)
# add_library(gtest_main UNKNOWN IMPORTED)
# set_target_properties(
#     gtest 
#     PROPERTIES
#     IMPORTED_LOCATION ${binary_dir}/libgtest.a
# )
# set_target_properties(
#     gtest_main 
#     PROPERTIES
#     IMPORTED_LOCATION ${binary_dir}/libgtest_main.a
# )
# add_dependencies(gtest googletest)
# add_dependencies(gtest_main googletest)