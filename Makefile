SHELL := /bin/sh
MKDIR ?= mkdir
RMDIR ?= rmdir

WARNINGS := \
	-Wall -Wpedantic \
	-Wshadow -Wpointer-arith -Wcast-qual -Wextra

CWARNINGS := $(WARNINGS) -Wmissing-prototypes -Wstrict-prototypes

CFLAGS ?= $(CWARNINGS) -std=c90
CXXFLAGS ?= $(WARNINGS) -std=c++98
DEPFLAGS ?= 

EXE := main
_SRC := main.c
SRCDIR ?= .
OBJDIR := .objdir
DEPDIR := .depdir

SRC := $(addprefix $(SRCDIR)/, $(_SRC))

# OBJ := $(addprefix $(OBJDIR)/, \
# 	$(addsuffix .o, $(filter %.c,$(_SRC))) \
# 	$(addsuffix .o, $(filter %.cpp,$(_SRC))) \
# )
OBJ := $(addprefix $(OBJDIR)/, \
	$(addsuffix .o, $(_SRC)) \
)

DEP := $(addprefix $(DEPDIR)/, \
	$(addsuffix .d, $(_SRC)) \
)

# be silent unless VERBOSE
ifndef VERBOSE
.SILENT: ;
endif

# default target
.PHONY: all
all: $(EXE) ## build executable

.PHONY: help
help: ## show this help
	@# print all lines with descriptions but not that line
	@awk -F':.*##' '/: [^#]*##/{ printf("%12s: %s\n", $$1, $$2)}' $(MAKEFILE_LIST)

.PHONY: debug
#debug: CFLAGS += -D_DEBUG -g
#debug: CXXFLAGS += -D_DEBUG -g
debug: CFLAGS := $(filter-out -O2,$(CFLAGS)) -D_DEBUG -g
debug: CXXFLAGS := $(filter-out -O2,$(CXXFLAGS)) -D_DEBUG -g
debug: $(EXE) ## build with debug enabled

.PHONY: print-%
print-%:
	@echo '$*=$($*)'

.PHONY: run
run: $(EXE) ## run program
	@./$(EXE)

.PHONY: debugrun
debugrun: debug run ## run debug version

$(EXE): $(OBJ)
	echo "Link $^ -> $@"
	$(CC) $(LDFLAGS) -o $@ $(OBJ)

#$(OBJDIR)/%.c.o: $(SRCDIR)/%.c
#	echo "Compile $< -> $@"
#	$(CC) $(CFLAGS) -c -o $@ $<
$(OBJDIR)/%.c.o: $(DEPDIR)/%.c.d
	echo "Compile $(SRCDIR)/$*.c -> $@"
	$(CC) $(CFLAGS) -c -o $@ $*.c

#$(OBJDIR)/%.cpp.o: $(SRCDIR)/%.cpp
#	echo "Compile $< -> $@"
#	$(CXX) $(CXXFLAGS) -c -o $@ $<
$(OBJDIR)/%.cpp.o: $(DEPDIR)/%.cpp.d
	echo "Compile $(SRCDIR)/$*.cpp -> $@"
	$(CXX) $(CXXFLAGS) -c -o $@ $*.cpp

$(DEPDIR)/%.c.d: $(SRCDIR)/%.c
	echo "Dependencies $(SRCDIR)/$< -> $@"
	$(CC) $(DEPFLAGS) -MM -MT '$$(OBJDIR)/$*.c.o' -MF $@ $<
	sed -i 's,^\([^:]\+.o\):,\1 $$(DEPDIR)/$*.c.d:,' $@

$(DEPDIR)/%.cpp.d: $(SRCDIR)/%.cpp
	echo "Dependencies $(SRCDIR)/$< -> $@"
	$(CXX) $(DEPFLAGS) -MM -MT '$$(OBJDIR)/$*.cpp.o' -o $*.o -MF $@ $<
	sed -i 's,^\([^:]\+.o\):,\1 $$(DEPDIR)/$*.c.d:,' $@

# include dependencies
ifneq ($(MAKECMDGOALS),clean)
-include $(wildcard $(DEP))
endif

# depend on directory
$(OBJ): | $(OBJDIR)/.keepme
$(DEP): | $(DEPDIR)/.keepme

# create directory
$(OBJDIR)/.keepme:
	$(MKDIR) $(OBJDIR)
	touch $@

# create directory
$(DEPDIR)/.keepme:
	$(MKDIR) $(DEPDIR)
	touch $@

# delete stuff
.PHONY: mostlyclean
mostlyclean: ## delete everything created, leave executable
	echo "Cleaning"
ifneq ($(wildcard $(OBJDIR)),)
	-$(RM) $(OBJ)
	-$(RM) $(OBJDIR)/.keepme
	-$(RMDIR) $(OBJDIR)
endif

ifneq ($(wildcard $(DEPDIR)),)
	-$(RM) $(DEP)
	-$(RM) $(DEPDIR)/.keepme
	-$(RMDIR) $(DEPDIR)
endif

.PHONY: clean
clean: mostlyclean ## delete everything this Makefile created
	-$(RM) $(EXE)

