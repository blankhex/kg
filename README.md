# KG Framework
## Как использовать
После скачивания фреймворка - создайте поместите исходный код программ в папку src
и добавьте правила сборки в Makefile

### До добавления
```
...

# vvv	Добавьте свои цели сборки сюда	vvv
TARGETS := 
# ^^^	Добавьте свои цели сборки сюда	^^^

all: build

...

# vvv	Добавьте свои цели сборки сюда	vvv

# ^^^	Добавьте свои цели сборки сюда	^^^
```

### После добавления
```
...

# vvv	Добавьте свои цели сборки сюда	vvv
TARGETS := m_lab01.exe
# ^^^	Добавьте свои цели сборки сюда	^^^

all: build

...

# vvv	Добавьте свои цели сборки сюда	vvv
m_lab01.exe: $(OBJDIR)/m_lab01.o framework/framework.a
	$(CXX) $^ -o $@ $(LDFLAGS)
# ^^^	Добавьте свои цели сборки сюда	^^^
```

## Конфигурация VS:Code
Чтобы VS:Code не ругался на отсутсвущие заголовки, необходимо прописать includePath
```
${workspaceFolder}/include/**
${workspaceFolder}/framework/include/**
```