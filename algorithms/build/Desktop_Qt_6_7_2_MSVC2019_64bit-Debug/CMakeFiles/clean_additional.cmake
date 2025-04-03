# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\algorithms_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\algorithms_autogen.dir\\ParseCache.txt"
  "algorithms_autogen"
  )
endif()
