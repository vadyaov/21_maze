CURR_DIR := .
BUILD_DIR := $(CURR_DIR)/build
MODEL_DIR := $(CURR_DIR)/model
VIEW_DIR := $(CURR_DIR)/view
CONTROLLER_DIR := $(CURR_DIR)/controller

RM := rm -f
MK := mkdir -p

EXEC := maze
TEST_EXEC := test
ARCHIVE := $(CURR_DIR)/$(EXEC)

all: install run

install:
	@$(MK) $(BUILD_DIR)
	@cmake $(CURR_DIR) -B $(BUILD_DIR)
	@cd $(BUILD_DIR) ; $(MAKE) ; cd ..

test: install
	@cd $(BUILD_DIR) ; $(MAKE) test ; cd ..
	$(BUILD_DIR)/$(TEST_EXEC)

gcov_report: install
	@cd $(BUILD_DIR) ; $(MAKE) gcov_report ; cd ..
	@open $(BUILD_DIR)/coverage_report/index.html

uninstall:
	@$(RM) -r $(BUILD_DIR)

run:
	$(BUILD_DIR)/$(EXEC)

clean: uninstall
