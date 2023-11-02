CURR_DIR := .
BUILD_DIR := $(CURR_DIR)/build
MODEL_DIR := $(CURR_DIR)/model
VIEW_DIR := $(CURR_DIR)/view
CTR_DIR := $(CURR_DIR)/controller

RM := rm -f
MK := mkdir -p

EXEC := maze
TEST_EXEC := test
ARCHIVE := $(CURR_DIR)/$(EXEC)

CLANG := clang-format -n

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

clang:
	$(CLANG) $(MODEL_DIR)/maze/* $(MODEL_DIR)/cave/* $(MODEL_DIR)/BaseLoader.h
	$(CLANG) $(CTR_DIR)/*
	$(CLANG) $(VIEW_DIR)/*.h $(VIEW_DIR)/main.cc $(VIEW_DIR)/other/* $(VIEW_DIR)/maze/* $(VIEW_DIR)/cave/*

copy_dirs:
	$(MK) src
	cp -r $(MODEL_DIR) ./src
	cp -r $(VIEW_DIR) ./src
	cp -r $(CTR_DIR) ./src
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
