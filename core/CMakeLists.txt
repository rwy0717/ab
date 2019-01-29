
ab_add_jinja_cxx_template(
	INPUT  include/Ab/Wasm/OpCode.hpp.jinja
	OUTPUT include/Ab/Wasm/OpCode.hpp
	DATA_FILES
		${CMAKE_SOURCE_DIR}/data/wasm_operators.yaml
)

ab_add_jinja_cxx_template(
	INPUT  include/Ab/InternalOpCode.hpp.jinja
	OUTPUT include/Ab/InternalOpCode.hpp
	DATA_FILES
		${CMAKE_SOURCE_DIR}/data/internal_operators.yaml
)

ab_add_jinja_cxx_template(
	INPUT  include/Ab/InternalFunctionBuilder.hpp.jinja
	OUTPUT include/Ab/InternalFunctionBuilder.hpp
	DATA_FILES
		${CMAKE_SOURCE_DIR}/data/internal_operators.yaml
)

ab_add_jinja_cxx_template(
	INPUT  include/Ab/Interpreter.hpp.jinja
	OUTPUT include/Ab/Interpreter.hpp
	DATA_FILES
		${CMAKE_SOURCE_DIR}/data/internal_operators.yaml
		${CMAKE_SOURCE_DIR}/data/interpreter_state.yaml
)

ab_add_jinja_cxx_template(
	INPUT  src/ab-core-Interpreter.cpp.jinja
	OUTPUT src/ab-core-Interpreter.cpp
	DATA_FILES
		${CMAKE_SOURCE_DIR}/data/internal_operators.yaml
		${CMAKE_SOURCE_DIR}/data/interpreter_state.yaml
)

add_library(ab-core
	include/Ab/Wasm/OpCode.hpp
	include/Ab/InternalOpCode.hpp
	include/Ab/InternalFunctionBuilder.hpp
	include/Ab/Interpreter.hpp
	src/ab-core-Interpreter.cpp
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
	# omrgc
	ab-base
	ab-util
)

add_subdirectory(test)
