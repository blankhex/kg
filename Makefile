SRCDIR	:= src
INCDIR	:= include
OBJDIR	:= bin

CXX			:= g++
CXXFLAGS	:= -I$(INCDIR) -Iframework/include
LDFLAGS		:= -lfreeglut -lopengl32 -lglu32
MKDIR		:= mkdir
RM			:= del /q /s /f
RMDIR		:= rmdir /s /q

OBJS := $(wildcard $(SRCDIR)/*.cpp)
OBJS := $(patsubst %.cpp,%.o,$(OBJS))
OBJS := $(patsubst %.c,%.o,$(OBJS))
OBJS := $(subst $(SRCDIR)/,$(OBJDIR)/,$(OBJS))

DEPS := $(wildcard $(INCDIR)/*.hpp framework/include/*.hpp)

# vvv	Добавьте свои цели сборки сюда	vvv
TARGETS := lab01.exe lab02.exe final.exe m_lab01.exe
# ^^^	Добавьте свои цели сборки сюда	^^^

all: build

build: $(OBJDIR) $(TARGETS)

$(OBJDIR):
	$(MKDIR) $(OBJDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

framework/framework.a: $(DEPS)
	$(MAKE) -C framework

clean:
	$(MAKE) -C framework clean
	-$(RM) $(TARGETS)
	-$(RMDIR) $(OBJDIR)
	
.PHONY: clean

# vvv	Добавьте свои цели сборки сюда	vvv
lab01.exe: $(OBJDIR)/lab01.o framework/framework.a
	$(CXX) $^ -o $@ $(LDFLAGS)

lab02.exe: $(OBJDIR)/lab02.o framework/framework.a
	$(CXX) $^ -o $@ $(LDFLAGS)

final.exe: $(OBJDIR)/final.o framework/framework.a
	$(CXX) $^ -o $@ $(LDFLAGS)

m_lab01.exe: $(OBJDIR)/m_lab01.o framework/framework.a
	$(CXX) $^ -o $@ $(LDFLAGS)
# ^^^	Добавьте свои цели сборки сюда	^^^