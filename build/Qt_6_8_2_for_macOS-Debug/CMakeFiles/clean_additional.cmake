# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/Cyles_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/Cyles_autogen.dir/ParseCache.txt"
  "Cyles_autogen"
  )
endif()
