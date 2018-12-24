add_executable(ab-dump
	src/ab-dump-main.cpp
)

target_link_libraries(ab-dump
	PUBLIC
		ab-core
)
