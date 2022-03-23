NAME = serverclient

BUILD_D = build

all: $(NAME)


$(NAME): $(BUILD_D)


$(BUILD_D):
			@mkdir -p build
			@cmake -S . -B build
			@cmake --build build

clean:
			@git clean -d -f -X
			@rm -rf build

test:
			@mkdir -p build
			@cmake -S . -B build
			@cmake --build build
			@ctest --output-on-failure --test-dir build 
			
