# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Transcriptomics_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Transcriptomics_autogen.dir\\ParseCache.txt"
  "Transcriptomics_autogen"
  )
endif()
