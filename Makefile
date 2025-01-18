THIS_MK_ABSPATH := $(abspath $(lastword $(MAKEFILE_LIST)))
THIS_MK_DIR := $(dir $(THIS_MK_ABSPATH))

# Enable pipefail for all commands
SHELL=/bin/bash -o pipefail

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
# Environment check
##############################################################################
REPO_ROOT_DIR := $(THIS_MK_DIR)
WORK_ROOT_DIR := $(THIS_MK_DIR)/work

VENV_DIR := $(REPO_ROOT_DIR)/venv
VENV_PIP := $(VENV_DIR)/bin/pip
ifneq ($(https_proxy),)
PIP_PROXY := --proxy $(https_proxy)
else
PIP_PROXY :=
endif
VENV_PIP_INSTALL := $(VENV_PIP) install $(PIP_PROXY) --timeout 90
VENV_PYTHON := $(VENV_DIR)/bin/python
VENV_CLANG_FORMAT := $(VENV_DIR)/bin/clang-format

BOOST_VERSION ?= 1.86.0
BOOST_VERSION_MOD := $(subst .,_,$(BOOST_VERSION))
BOOT_ROOTDIR ?= $(REPO_ROOT_DIR)/boost
export BOOST_ROOTDIR

##############################################################################
# Set default goal before any targets. The default goal here is "test"
##############################################################################
DEFAULT_TARGET := test

.DEFAULT_GOAL := default
.PHONY: default
default: $(DEFAULT_TARGET)

##############################################################################
# Makefile starts here
##############################################################################

$(WORK_ROOT_DIR):
	mkdir -p $(WORK_ROOT_DIR)

venv:
	python3 -m venv venv
	$(VENV_PIP_INSTALL) --upgrade pip
	$(VENV_PIP_INSTALL) -r requirements.txt

boost: |$(WORK_ROOT_DIR)
	cd $(WORK_ROOT_DIR) && wget https://archives.boost.io/release/$(BOOST_VERSION)/source/boost_$(BOOST_VERSION_MOD).tar.bz2
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

# Deep clean using git
.PHONY: dev-clean
dev-clean :
	git clean -dfx --exclude=/.vscode --exclude=.lfsconfig

.PHONY: prepare-tools
prepare-tools : venv boost

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


###############################################################################
#                                HELP
###############################################################################
.PHONY: help
help:
	$(info Build)
	$(info ----------------)
	$(info ALL Targets : all)
