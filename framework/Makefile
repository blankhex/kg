SRCDIR	:= src
INCDIR	:= include
OBJDIR	:= bin

CXX			:= g++
CXXFLAGS	:= -I$(INCDIR)
AR			:= ar
MKDIR		:= mkdir
RM			:= del /q /s /f
RMDIR		:= rmdir /s /q

OBJS := $(wildcard $(SRCDIR)/*.cpp)
OBJS := $(patsubst %.cpp,%.o,$(OBJS))
OBJS := $(patsubst %.c,%.o,$(OBJS))
OBJS := $(subst $(SRCDIR)/,$(OBJDIR)/,$(OBJS))

DEPS := $(wildcard $(INCDIR)/*.hpp)

all: build

build: $(OBJDIR) framework.a

$(OBJDIR):
	$(MKDIR) $(OBJDIR)

framework.a: $(OBJS)
	$(AR) rcs $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	-$(RM) framework.a
	-$(RMDIR) $(OBJDIR)

.PHONY: clean