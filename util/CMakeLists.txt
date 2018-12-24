add_library(ab-util
	src/ab-util-SharedLock.cpp
	src/ab-util-Process.cpp
	src/ab-util-SexprPrinter.cpp
)

target_compile_features(ab-util
	PUBLIC
		cxx_std_17
)

target_compile_options(ab-util
	PRIVATE
		${OMR_ENHANCED_WARNINGS_FLAG}
)

target_link_libraries(ab-util
	PUBLIC
		ab-base
)

target_include_directories(ab-util
	PUBLIC
		$<BUILD_INTERFACE: include>
		$<BUILD_INTERFACE: ${CMAKE_CURRENT_BINARY_DIR}/include>
)

add_subdirectory(test)
