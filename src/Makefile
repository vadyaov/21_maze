CURR_DIR := .
BUILD_DIR := $(CURR_DIR)/build
MODEL_DIR := $(CURR_DIR)/model
VIEW_DIR := $(CURR_DIR)/view
CONTROLLER_DIR := $(CURR_DIR)/controller

RM := rm -f
MK := mkdir -p

EXEC := maze
ARCHIVE := $(CURR_DIR)/$(EXEC)

all: install run

install:
	@$(MK) $(BUILD_DIR)
	@cmake $(CURR_DIR) -B $(BUILD_DIR)
	@cd $(BUILD_DIR) ; $(MAKE) ; cd ..

uninstall:
	@$(RM) -r $(BUILD_DIR)

run:
	$(BUILD_DIR)/maze

clean: uninstall
