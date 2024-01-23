# generated from ament/cmake/core/templates/nameConfig.cmake.in

# prevent multiple inclusion
if(_pubs_and_subs_CONFIG_INCLUDED)
  # ensure to keep the found flag the same
  if(NOT DEFINED pubs_and_subs_FOUND)
    # explicitly set it to FALSE, otherwise CMake will set it to TRUE
    set(pubs_and_subs_FOUND FALSE)
  elseif(NOT pubs_and_subs_FOUND)
    # use separate condition to avoid uninitialized variable warning
    set(pubs_and_subs_FOUND FALSE)
  endif()
  return()
endif()
set(_pubs_and_subs_CONFIG_INCLUDED TRUE)

# output package information
if(NOT pubs_and_subs_FIND_QUIETLY)
  message(STATUS "Found pubs_and_subs: 0.0.0 (${pubs_and_subs_DIR})")
endif()

# warn when using a deprecated package
if(NOT "" STREQUAL "")
  set(_msg "Package 'pubs_and_subs' is deprecated")
  # append custom deprecation text if available
  if(NOT "" STREQUAL "TRUE")
    set(_msg "${_msg} ()")
  endif()
  # optionally quiet the deprecation message
  if(NOT ${pubs_and_subs_DEPRECATED_QUIET})
    message(DEPRECATION "${_msg}")
  endif()
endif()

# flag package as ament-based to distinguish it after being find_package()-ed
set(pubs_and_subs_FOUND_AMENT_PACKAGE TRUE)

# include all config extra files
set(_extras "")
foreach(_extra ${_extras})
  include("${pubs_and_subs_DIR}/${_extra}")
endforeach()
