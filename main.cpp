#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <stdexcept>
#include <random>  // Добавлен для более современного генератора случайных чисел

std::vector<std::vector<int>> create_maze(int dim) {
    // Создаем генератор случайных чисел
    std::random_device rd;
    std::mt19937 gen(rd());

    // Create a grid filled with walls
    std::vector<std::vector<int>> maze(2 * dim + 1, std::vector<int>(2 * dim + 1, 1));

    // Define the starting point
    int x = 0, y = 0;
    maze[2 * x + 1][2 * y + 1] = 0;

    // Initialize the stack with the starting point
    std::vector<std::pair<int, int>> stack;
    stack.emplace_back(x, y);
    
    while (!stack.empty()) {
        auto [x, y] = stack.back();  // Используем структурную привязку C++17

        // Define possible directions
        std::vector<std::pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        std::shuffle(directions.begin(), directions.end(), gen);  // Используем новый генератор

        bool moved = false;
        for (const auto& [dx, dy] : directions) {
            int nx = x + dx, ny = y + dy;
            if (nx >= 0 && ny >= 0 && nx < dim && ny < dim && maze[2 * nx + 1][2 * ny + 1] == 1) {
                maze[2 * nx + 1][2 * ny + 1] = 0;
                maze[2 * x + 1 + dx][2 * y + 1 + dy] = 0;
                stack.emplace_back(nx, ny);
                moved = true;
                break;
            }
        }
        if (!moved) {
            stack.pop_back();
        }
    }
    
    // Create an entrance and an exit
    maze[1][0] = 0;
    maze[2 * dim - 1][2 * dim] = 0;

    return maze;
}

void printMaze(const std::vector<std::vector<int>>& maze) {
    for (const auto& row : maze) {
        for (int cell : row) {
            std::cout << (cell == 1 ? '#' : ' ');  // Более компактный вывод
        }
        std::cout << '\n';
    }
}

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "Russian");
    srand(time(nullptr));
    if (argc!= 2) {
        throw std::invalid_argument("Неверное количество аргументов. Ожидается один аргумент - размер лабиринта.");
    }

    int dim;
    try {
        dim = std::stoi(argv[1]);
        if (dim <= 0) {
            throw std::invalid_argument("Размер лабиринта должен быть положительным.");
        }
    } catch (const std::invalid_argument& e) {
        std::cerr << e.what() << '\n';
        return 1;
    }

    printMaze(create_maze(dim));

    return 0;
}