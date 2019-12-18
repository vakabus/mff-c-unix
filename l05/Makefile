CFLAGS=-std=c99 -Wall -Wextra -pedantic -Werror
CFLAGS_SANITIZER=-fsanitize=address -fsanitize-address-use-after-scope -fno-omit-frame-pointer

BUILD_DIR=build
PROGRAM_NAME=palindrome

SOURCE_FILES=$(wildcard *.c)
OBJECT_FILES=$(addprefix $(BUILD_DIR)/,$(patsubst %.c,%.o,$(SOURCE_FILES)))

$(PROGRAM_NAME): $(OBJECT_FILES) $(SOURCE_FILES)
	gcc -o $(PROGRAM_NAME) $(wildcard $(BUILD_DIR)/*.o)

$(BUILD_DIR)/%.o %.c: %.c
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $(patsubst $(BUILD_DIR)/%.o,%.c,$@) -o $(patsubst %.c,$(BUILD_DIR)/%.o,$@)

.PHONY: clean
clean:
	-rm -rf $(BUILD_DIR)
	-rm $(PROGRAM_NAME)
