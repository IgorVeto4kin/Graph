BUILD_DIR := build

EXECUTABLE := main

.PHONY: all build clean tests

all: build

build:
	@mkdir -p $(BUILD_DIR)
	@cd $(BUILD_DIR) && cmake ..
	@$(MAKE) -C $(BUILD_DIR)


clean:
	@$(MAKE) -C $(BUILD_DIR) clean
	@rm -rf $(BUILD_DIR)


tests: 
	./run_tests.sh