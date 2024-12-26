# Имя исполняемого файла
TARGET = mgm

# Исходный файл
SRC = mgm.cpp

# Компилятор
CXX = g++

# Флаги компилятора
CXXFLAGS = -Wall -Wextra -O2

# Правило по умолчанию
all: $(TARGET)

# Правило для сборки
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Правило очистки
clean:
	rm -f $(TARGET)
