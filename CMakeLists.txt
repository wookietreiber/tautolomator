
  # -----------------------------------------------------------------
  # project definition
  # -----------------------------------------------------------------

cmake_minimum_required (VERSION 2.6)

project (tautolomator)

  # -----------------------------------------------------------------
  # sources
  # -----------------------------------------------------------------

set(SRCDIR "${CMAKE_CURRENT_SOURCE_DIR}/src/main/c")

set(TAUTOLOMATOR_SRCS
  ${SRCDIR}/gset.c
  ${SRCDIR}/utils.c
  ${SRCDIR}/logic.c
  ${SRCDIR}/main.c
)

set(TAUTOLOMATOR_H
  ${SRCDIR}/gset.h
  ${SRCDIR}/utils.h
  ${SRCDIR}/logic.h
)

  # -----------------------------------------------------------------
  # dependencies
  # -----------------------------------------------------------------

INCLUDE (FindPkgConfig)
pkg_check_modules (GLIB REQUIRED glib-2.0)

include_directories(
  ${GLIB_INCLUDE_DIRS}
)

link_directories(
  ${GLIB_LIBRARY_DIRS}
)

set(TAUTOLOMATOR_LIBS
  ${GLIB_LIBRARIES}
)

  # -----------------------------------------------------------------
  # end products
  # -----------------------------------------------------------------

add_executable(tautolomator ${TAUTOLOMATOR_SRCS} ${TAUTOLOMATOR_H})
target_link_libraries(tautolomator ${TAUTOLOMATOR_LIBS})

  # -----------------------------------------------------------------
  # installation
  # -----------------------------------------------------------------

install (TARGETS tautolomator DESTINATION bin)

