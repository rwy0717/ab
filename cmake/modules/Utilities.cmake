function(get_git_commit output_variable)
	exec_program(
		"git"
		${CMAKE_CURRENT_SOURCE_DIR}
		ARGS "describe" "--all" "--long" "HEAD"
		OUTPUT_VARIABLE ${output_variable}
	)
endfunction(get_git_commit)

function(project_version project major minor patch)
	set(${project}_MAJOR CACHE STRING "Major version number" FORCE)
	set(${project}_MINOR CACHE STRING "minor version number" FORCE)
	set(${project}_PATCH CACHE STRING "Patch number" FORCE)
	set(${project}_COMMIT CACHE STRING "COMMIT-NOTFOUND" FORCE)

	get_git_commit(${project}_COMMIT)

	set(${project}_VERSION CACHE STRING
		"${major}.${minor}.${patch}"
		"Project Version" FORCE
	)
endfunction(project_version)

# define a new test binary.
# Usage: add_ab_test(<name> [<libs>...])
# Note that gtest_main will be automatically linked into the executable. You do not need to define main().
function(add_ab_test name)
	add_executable(${name} ${name}.cpp)
	target_link_libraries(${name} gtest_main ${ARGN})
	add_test(${name} ${name})
	set_target_properties(${name}
		PROPERTIES
			CXX_CLANG_TIDY ""  # Disable because gtest errors a lot.
			CXX_STANDARD 17
	)
endfunction(add_ab_test)

# Add a jinja-generated source file
# Usage:
#  ab_add_generated_source(
#    INPUT <input>
#    OUTPUT <output>
#    DATA_FILES <data-file>...
#  )
function(ab_add_generated_source)
	cmake_parse_arguments("ARG" "" "INPUT;OUTPUT" "DATA_FILES" "${ARGN}")
	message(STATUS "${ARG_INPUT}")
	add_custom_command(
		COMMAND
			python3 ${CMAKE_SOURCE_DIR}/scripts/generate-cxx.py
			--datadir=${CMAKE_SOURCE_DIR}/data
			${CMAKE_CURRENT_SOURCE_DIR}/${ARG_INPUT}
			${CMAKE_CURRENT_BINARY_DIR}/${ARG_OUTPUT}
		MAIN_DEPENDENCY ${ARG_INPUT}
		OUTPUT ${ARG_OUTPUT}
		DEPENDS ${ARG_DATA_FILES}
	)
endfunction(ab_add_generated_source)
