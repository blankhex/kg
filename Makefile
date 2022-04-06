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
TARGETS := s_lab01.exe s_lab02.exe s_final.exe
TARGETS += a_lab01.exe a_lab02.exe a_final.exe
TARGETS += m_lab01.exe m_lab02.exe m_final.exe
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
s_lab01.exe: $(OBJDIR)/s_lab01.o framework/framework.a
	$(CXX) $^ -o $@ $(LDFLAGS)

s_lab02.exe: $(OBJDIR)/s_lab02.o framework/framework.a
	$(CXX) $^ -o $@ $(LDFLAGS)

s_final.exe: $(OBJDIR)/s_final.o framework/framework.a
	$(CXX) $^ -o $@ $(LDFLAGS)

m_lab01.exe: $(OBJDIR)/m_lab01.o framework/framework.a
	$(CXX) $^ -o $@ $(LDFLAGS)

m_lab02.exe: $(OBJDIR)/m_lab02.o framework/framework.a
	$(CXX) $^ -o $@ $(LDFLAGS)

m_final.exe: $(OBJDIR)/m_final.o framework/framework.a
	$(CXX) $^ -o $@ $(LDFLAGS)

a_lab01.exe: $(OBJDIR)/a_lab01.o framework/framework.a
	$(CXX) $^ -o $@ $(LDFLAGS)

a_lab02.exe: $(OBJDIR)/a_lab02.o framework/framework.a
	$(CXX) $^ -o $@ $(LDFLAGS)

a_final.exe: $(OBJDIR)/a_final.o framework/framework.a
	$(CXX) $^ -o $@ $(LDFLAGS)
# ^^^	Добавьте свои цели сборки сюда	^^^