THIS_MAKEFILE_DIR := $(abspath $(patsubst %/,%,$(dir $(lastword $(MAKEFILE_LIST)))))

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
WORK_ROOT_DIR := $(THIS_MAKEFILE_DIR)/work

VENV_DIR := $(REPO_ROOT_DIR)/venv
VENV_PIP := $(VENV_DIR)/bin/pip
VENV_PYTHON := $(VENV_DIR)/bin/python
VENV_CLANG_FORMAT := $(VENV_DIR)/bin/clang-format

BOOST_VERSION := 1.86.0
BOOST_VERSION_MOD := $(subst .,_,$(BOOST_VERSION))

##############################################################################
# Makefile starts here
##############################################################################

$(WORK_ROOT_DIR):
	mkdir -p $(WORK_ROOT_DIR)

venv:
	python3 -m venv venv
	$(VENV_PIP) install --upgrade pip
	$(VENV_PIP) install -r requirements.txt

boost: |$(WORK_ROOT_DIR)
	cd $(WORK_ROOT_DIR) && wget https://boostorg.jfrog.io/artifactory/main/release/$(BOOST_VERSION)/source/boost_$(BOOST_VERSION_MOD).tar.bz2
	cd $(WORK_ROOT_DIR) && tar --bzip2 -xf boost_$(BOOST_VERSION_MOD).tar.bz2
	cd $(WORK_ROOT_DIR)/boost_$(BOOST_VERSION_MOD) && ./bootstrap.sh --prefix=$(REPO_ROOT_DIR)/boost
	cd $(WORK_ROOT_DIR)/boost_$(BOOST_VERSION_MOD) && ./b2 install \
		--with-filesystem \
		--with-regex \
		--build-type=minimal \
		--link=static
	rm -rf $(WORK_ROOT_DIR)/boost_$(BOOST_VERSION_MOD) $(WORK_ROOT_DIR)/boost_$(BOOST_VERSION_MOD).tar.bz2


.PHONY: clean
clean:
	rm -rf venv $(WORK_ROOT_DIR)

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
