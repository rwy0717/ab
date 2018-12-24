cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

# Module path

list(APPEND CMAKE_MODULE_PATH
	${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules
	${CMAKE_CURRENT_SOURCE_DIR}/external/omr/cmake/modules
)

# Versioning

set(AB_VERSION_MAJOR 0)
set(AB_VERSION_MINOR 0)
set(AB_VERSION_PATCH 1)
set(AB_VERSION ${AB_VERSION_MAJOR}.${AB_VERSION_MINOR}.${AB_VERSION_PATCH})

project(abigail
	VERSION ${AB_VERSION}
	LANGUAGES C CXX
)

# Module Imports

include(FindClangTidy)
include(OmrPlatform)
include(Utilities)

# Global Configuration

get_git_commit(GIT_COMMIT)

set(AB_COMMIT ${GIT_COMMIT})

configure_file(
	"config.hpp.in"
	"include/Ab/Config.hpp"
)

omr_platform_global_setup()

enable_testing()

# OMR Configuration

set(OMR_EXAMPLE OFF CACHE INTERNAL "Disable the OMR example VM")
set(OMR_FVTEST OFF CACHE INTERNAL "Disable OMR Testing in Ab")
set(OMR_GC ON CACHE INTERNAL "Enable OMR GC in Ab, for Om")
set(OMR_JITBUILDER ON CACHE INTERNAL "Enable OMR Jitbuilder, for Ab")
set(OMR_OM ON CACHE INTERNAL "Enable Om")
set(OMR_WARNINGS_AS_ERRORS OFF CACHE INTERNAL "Disable warnings as errors")

# Misc utilities

set(CMAKE_EXPORT_COMPILE_COMMANDS true)

if(CLANG_TIDY_FOUND)
	set(CMAKE_CXX_CLANG_TIDY ${CLANG_TIDY_EXECUTABLE})
endif()

# ab_base: basic configuration

add_library(ab-base INTERFACE)

target_compile_features(ab-base
	INTERFACE
		cxx_std_17
)

target_compile_options(ab-base
	INTERFACE
)

target_include_directories(ab-base
	INTERFACE
		${CMAKE_CURRENT_BINARY_DIR}/include
)

# External projects

add_subdirectory(external)

# Sub directories

add_subdirectory(asm)
add_subdirectory(core)
add_subdirectory(dump)
add_subdirectory(doc)
add_subdirectory(interpreter)
add_subdirectory(util)
