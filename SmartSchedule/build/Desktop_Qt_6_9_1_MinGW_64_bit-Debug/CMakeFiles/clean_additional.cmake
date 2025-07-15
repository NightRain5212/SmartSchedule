# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\SmartSchedule_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\SmartSchedule_autogen.dir\\ParseCache.txt"
  "SmartSchedule_autogen"
  )
endif()
