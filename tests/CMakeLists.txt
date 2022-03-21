FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.0.0-preview3
)

FetchContent_MakeAvailable(Catch2)

file(GLOB TEST_FILES *.cpp)

foreach(SRC_FILE ${TEST_FILES})
	get_filename_component(TEST ${SRC_FILE} NAME)
	
	add_executable(${TEST}.bin ${SRC_FILE})
	target_compile_features(${TEST}.bin PRIVATE cxx_std_17)
	target_link_libraries(${TEST}.bin PRIVATE Catch2::Catch2WithMain)
    target_link_libraries(${TEST}.bin PRIVATE	helloWorld)
	add_test(NAME ${TEST}
			COMMAND ${TEST}.bin)
endforeach(SRC_FILE)
enable_testing()
