# UniDistributor
Распределение абитуриентов по вузам с учетом приоритета, проходных баллов и количества мест.

## Сборка на Linux
sudo pacman -S qt6-base cmake ninja
mkdir build && cd build
cmake .. -G Ninja
cmake --build .
./UniDistributor

## Сборка на Windows
(инструкция с cmake -G "Visual Studio 18 2026"...)