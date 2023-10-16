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

tests: install
	@cd $(BUILD_DIR) ; $(MAKE) test ; cd ..
	$(BUILD_DIR)/$(TEST_EXEC)

gcov_report: install
	@cd $(BUILD_DIR) ; $(MAKE) gcov_report ; cd ..
	@open $(BUILD_DIR)/coverage_report/index.html

dvi:
	doxygen Doxyfile
	open $(BUILD_DIR)/html/index.html

dist: copy_dirs
	tar -cvzf maze.tar.gz src/
	@$(RM) -r src/

copy_dirs:
	$(MK) src
	cp -r $(MODEL_DIR) ./src
	cp -r $(VIEW_DIR) ./src
	cp -r $(CONTROLLER_DIR) ./src
	cp -r tests ./src
	cp -r examples ./src
	cp Makefile ./src
	cp Doxyfile ./src
	cp CMakeLists.txt ./src

uninstall:
	@$(RM) -r $(BUILD_DIR)

run:
	$(BUILD_DIR)/$(EXEC)

clean: uninstall
