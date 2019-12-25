if(NOT TARGET vdc::@PROJECT_NAME@)

  get_filename_component(@PROJECT_NAME@_PATH ${CMAKE_CURRENT_LIST_FILE} PATH)

  set(@PROJECT_NAME@_INCLUDE_DIR ${@PROJECT_NAME@_PATH}/../include)

  find_library(@PROJECT_NAME@_LIBRARY
      NAMES @PROJECT_NAME@
      PATHS ${@PROJECT_NAME@_PATH}/../lib)

  include(FindPackageHandleStandardArgs)
  find_package_handle_standard_args(@PROJECT_NAME@ DEFAULT_MSG
                                    @PROJECT_NAME@_LIBRARY @PROJECT_NAME@_INCLUDE_DIR)

  mark_as_advanced(@PROJECT_NAME@_INCLUDE_DIR @PROJECT_NAME@_LIBRARY)

  find_package(stdex REQUIRED)

  add_library(vdc::@PROJECT_NAME@ IMPORTED SHARED GLOBAL)
  set_target_properties(vdc::@PROJECT_NAME@
    PROPERTIES
      INTERFACE_COMPILE_FEATURES        "cxx_std_17"
      IMPORTED_LOCATION                 "${@PROJECT_NAME@_LIBRARY}"
      INTERFACE_INCLUDE_DIRECTORIES     "${@PROJECT_NAME@_INCLUDE_DIR};${stdex_INCLUDE_DIRS}"
      IMPORTED_LINK_INTERFACE_LIBRARIES "${stdex_LIBRARIES}"
      DEPLOYMENT_PATH                   "${@PROJECT_NAME@_PATH}/..")

endif()
