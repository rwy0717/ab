
ab_add_generated_source(
	INPUT  include/Ab/Wasm/OpCode.hpp.jinja
	OUTPUT include/Ab/Wasm/OpCode.hpp
	DATA_FILES
		${CMAKE_SOURCE_DIR}/data/wasm-operators.yaml
)

add_library(ab-core
	include/Ab/Wasm/OpCode.hpp
	src/ab-core-Process.cpp
	src/ab-core-Version.cpp
	src/Wasm/ab-core-wasm-Loader.cpp
	src/Wasm/ab-core-wasm-Reader.cpp
)

target_compile_features(ab-core
	PUBLIC
		cxx_std_17
)

target_include_directories(ab-core
	PUBLIC
		$<BUILD_INTERFACE: include>
		$<BUILD_INTERFACE: ${CMAKE_CURRENT_BINARY_DIR}/include>
)

target_link_libraries(ab-core
	omrgc
	ab-base
	ab-util
)

add_subdirectory(test)
