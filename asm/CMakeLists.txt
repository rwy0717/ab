add_executable(ab-asm
	src/ab-asm-main.cpp
)

target_link_libraries(ab-asm
	PUBLIC
		ab-core
)

target_compile_features(ab-asm
	PUBLIC
		cxx_std_17
)
