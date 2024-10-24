THIS_MAKEFILE_DIR := $(patsubst %/,%,$(dir $(lastword $(MAKEFILE_LIST))))

# Enable second expansion
.SECONDEXPANSION:

# Clear all built in suffixes
.SUFFIXES:

##############################################################################
# Special use variables
##############################################################################
NULL :=
SPACE := $(NULL) $(NULL)
INFO_INDENT := $(SPACE)$(SPACE)$(SPACE)

##############################################################################
# Variables
##############################################################################
REPO_ROOT_DIR := $(THIS_MAKEFILE_DIR)
VENV_DIR := $(REPO_ROOT_DIR)/venv
VENV_PIP := $(VENV_DIR)/bin/pip
VENV_PYTHON := $(VENV_DIR)/bin/python
VENV_CLANG_FORMAT := $(VENV_DIR)/bin/clang-format


##############################################################################
# Makefile starts here
##############################################################################

venv:
	python3 -m venv venv
	$(VENV_PIP) install --upgrade pip
	$(VENV_PIP) install -r requirements.txt

.PHONY: clean
clean:
	rm -rf venv

.PHONY: dev-clean
dev-clean:
	git clean -dfx -e .vscode/


##############################################################################
# Style checks
##############################################################################
CLANG_CHECK_FILES := $(shell git ls-files *.c* *.h)

.PHONY: style-check-clang
style-check-clang: |venv
	$(VENV_CLANG_FORMAT) --dry-run --Werror  $(CLANG_CHECK_FILES)

.PHONY: style-format-clang
style-format-clang: |venv
	$(VENV_CLANG_FORMAT) -style=file -i $(CLANG_CHECK_FILES)
