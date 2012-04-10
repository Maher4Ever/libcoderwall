cmake_minimum_required (VERSION 2.6)

set (CODERWALL_SRCS
  coderwall.c
  coderwall_utils.c
  coderwall_memory.c
  coderwall_http.c
  coderwall_json.c
)

# Export the sources to the whole project. Kinda hacky though!
set (CODERWALL_SRCS ${CODERWALL_SRCS} PARENT_SCOPE)

# Extract the dirrname of Yajl from its path. WTF YAJL!!
string(REPLACE ${CODERWALL_VENDORS_SOURCE_DIR} "" CODERWALL_YAJL_DIRNAME
  ${CODERWALL_YAJL_DIR})

include_directories (
  "${PROJECT_SOURCE_DIR}/include"
  "${CODERWALL_CURL_DIR}/include"

  # WTF yajl... Y U NO USE STANDARDS?!
  "${CODERWALL_VENDORS_BINARY_DIR}/yajl/${CODERWALL_YAJL_DIRNAME}/include"
)

# Make the coderwall c library
add_library(coderwall STATIC ${CODERWALL_SRCS})

target_link_libraries (coderwall
  libcurl
  yajl_s
)
