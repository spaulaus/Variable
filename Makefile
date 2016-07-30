#!/bin/make
SHELL=/bin/bash

#Define the virtual paths
vpath %.cpp src/
vpath %.hpp inc/
vpath %.o obj/

#Set some of the compile options
CXX = g++
CXXFLAGS = -fPIC -g -Wall $(CINCLUDEDIRS)
LDLIBS = -ldl -lpthread
CINCLUDEDIRS = -Iinc
c++SrcSuf = cpp

#Set the name of the program to be compiled
PROGRAM = test
VERSION = $(shell git describe --abbrev=0 --tags)

#Define Objects
TESTO = test.o

#Define the name of the header
HEADER_NAME = Variable.hpp
#Install Path
HEADER_INSTALL_PATH = /home/vincent/programs/inc


#Make the object list and prefix the object directory
OBJS = $(TESTO) 
OBJDIR = obj
OBJS_W_DIR = $(addprefix $(OBJDIR)/,$(OBJS))

.SUFFIXES: .$(c++SrcSuf)

all: $(OBJS_W_DIR) $(PROGRAM)

$(OBJS_W_DIR): | $(OBJDIR)

$(OBJDIR):
	mkdir $(OBJDIR)

$(PROGRAM): $(OBJS_W_DIR)
	$(CXX) $(CXXFLAGS) $(LDLIBS) $^ -o $@

$(OBJDIR)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean header
clean: 
	@echo "Cleaning..."
	@rm -f $(OBJDIR)/* $(PROGRAM) *~ src/*~ include/*~

header: $(HEADER_NAME)
	cp $^ $(HEADER_INSTALL_PATH)
