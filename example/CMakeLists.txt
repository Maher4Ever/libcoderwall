cmake_minimum_required (VERSION 2.6)

project ("Coderwall User Info CLI")

# Add the libcoderwall headers to the include path.
include_directories("${CODERWALL_SOURCE_DIR}/include")

# Compile the binary
add_executable(coderwall_user coderwall_user.c)

# Link libcoderwall to the binary
target_link_libraries(coderwall_user coderwall)
