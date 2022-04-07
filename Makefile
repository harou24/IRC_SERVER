NAME = ft_irc


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
			@cmake -S . -B build -DTEST=ON
			@cmake --build build
			@ctest --output-on-failure --test-dir build
			
func:
			@mkdir -p build
			@cmake -S . -B build -DTEST=ON
			@cmake --build build
			@./build/apps/test_server_messaging.out "hello what's up!"
			
re: clean all

.PHONY = clean re $(NAME)

