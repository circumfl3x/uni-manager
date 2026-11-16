# UniDistributor (Распределение абитуриентов)

Приложение с графическим интерфейсом на C++ (Qt Widgets) для автоматического распределения абитуриентов по университетам с учетом их баллов, приоритета вузов и количества доступных мест.

## Инструкция по сборке и запуску

Для сборки используется система **CMake**.

### Linux (Arch Linux)
**1. Установите необходимые пакеты:**
```bash
sudo pacman -S --needed base-devel cmake ninja qt6-base qt6-tools git \
```

**2. Соберите проект:**
```bash
mkdir build
cd build
cmake .. -G Ninja
cmake --build .
```

**3. Запустите приложение:**
```bash
./UniDistributor
```


### Инструкция для Windows
**1. Подготовка:**
Убедитесь, что у вас установлены:
*   Visual Studio 2026 с компонентом «Разработка классических приложений на C++».
*   Qt 6 (компонент **MSVC 2022 64-bit**).
*   CMake.

**2. Соберите проект:**
Откройте командную строку (`cmd`) в корневой папке проекта и выполните команды (замените путь к Qt на свой!):
```cmd
mkdir build
cd build
cmake .. -G "Visual Studio 18 2026" -A x64 -DCMAKE_PREFIX_PATH="C:/Qt/6.7.3/msvc2022_64"
```
**3. Запустите приложение:**
```bash
cmake --build . --config Release
.\Release\UniDistributor.exe
```
