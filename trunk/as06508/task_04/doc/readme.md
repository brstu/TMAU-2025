<p align="center">Министерство образования Республики Беларусь</p>
<p align="center">Учреждение образования</p>
<p align="center">“Брестский Государственный технический университет”</p>
<p align="center">Кафедра ИИТ</p>
<br><br><br><br><br><br>
<p align="center"><strong>Лабораторная работа №4</strong></p>
<p align="center"><strong>По дисциплине</strong> “Теория и методы автоматического управления”</p>
<p align="center"><strong>Тема:</strong> “Работа с контроллером AXC F 2152”</p>
<br><br><br><br><br><br>
<p align="right"><strong>Выполнил</strong>:</p>
<p align="right">Студент 3 курса</p>
<p align="right">Группы АС-65</p>
<p align="right">Кисель М.С.</p>
<p align="right"><strong>Проверил:</strong></p>
<p align="right">Иванюк Д. С.</p>
<br><br><br><br><br>
<p align="center"><strong>Брест 2025</strong></p>

---
<p> <strong>Цель:</strong> Используя Visual Studio , собрать данный проект и продемонстрировать его функциональность на тестовом контроллере.</p> 

<p> <strong>Решение:</strong> </p>

<p>1. Требования</p>

Перед началом должны быть установлены:

PLCnext Toolchain 2024.6
PLCnext SDK для AXC F 2152

Например, установлен по пути:

```
D:\PLCnextSDK\AXCF2152_2024_6\
```

Visual Studio 2022 + workloads:

Desktop development with C++

C++ for Linux Development


Git

<p>2. Клонирование репозитория ptusa_main</p>

Создайте рабочую папку:

```
D:\TMAU\TMAU_Lab4\
```

Клонируем репозиторий:

```
git clone https://github.com/savushkin-r-d/ptusa_main
```

Получим:

```
D:\TMAU\TMAU_Lab4\ptusa_main\
```

<p>3. Настройка файла CMakePresets.json</p>

Откройте в VS2022 только что клонированную папку ptusa_main и в ней найдите файл:

```
ptusa_main/CMakePresets.json
```

В нем нужно исправить только две части:

Добавьте в блок configurePresets:

```
    {
  "name": "build-windows-AXCF2152-2024-LTS-Release",
  "displayName": "Windows AXCF2152 2024 LTS Release",
  "description": "Build for AXCF2152 using PLCnext SDK 2024.6",
  "inherits": "windows-AXCF-default",
  "generator": "MinGW Makefiles",

  "environment": {
    "ARP_DEVICE": "AXCF2152",
    "ARP_DEVICE_VERSION": "2024.6.0",
    "ARP_DEVICE_SHORT_VERSION": "2024_6",
    "PLCNEXT_SDK_ROOT": "D:/PLCnextSDK/AXCF2152_2024_6",
    "ARP_SDK_PACKAGE_NAME": "x86_64-w64-mingw32"
  },

  "cacheVariables": {
    "CMAKE_TOOLCHAIN_FILE": {
      "value": "D:/PLCnextSDK/AXCF2152_2024_6/toolchain.cmake",
      "type": "FILEPATH"
    }
  }
},
```

Дополнительно проверьте чтобы в конце блока configurePresets блоки windows-AXCF-default и AXCF-default выглядели похожим образом:

```
[
  {
    "name": "windows-AXCF-default",
    "hidden": true,
    "inherits": "AXCF-default",
    "generator": "MinGW Makefiles",
    "environment": {
      "PLCNEXT_SDK_ROOT": "D:/PLCnextSDK/$env{ARP_DEVICE}_$env{ARP_DEVICE_SHORT_VERSION}"
    },
    "cacheVariables": {
      "CMAKE_MAKE_PROGRAM": "D:/PLCnextSDK/$env{ARP_DEVICE}_$env{ARP_DEVICE_SHORT_VERSION}/sysroots/$env{ARP_SDK_PACKAGE_NAME}/usr/bin/make.exe"
    }
  },
  {
    "name": "AXCF-default",
    "hidden": true,
    "generator": "MinGW Makefiles",
    "binaryDir": "${sourceDir}/bin/build/$env{ARP_DEVICE}_$env{ARP_DEVICE_SHORT_VERSION}",
    "cacheVariables": {
      "CMAKE_INSTALL_PREFIX": "${sourceDir}/bin/install",
      "CMAKE_TOOLCHAIN_FILE": {
        "value": "D:/PLCnextSDK/AXCF2152_2024_6/toolchain.cmake",
        "type": "FILEPATH"
      },
      "ARP_DEVICE": "AXCF2152",
      "ARP_DEVICE_VERSION": "2024.6.0 (24.6.0.81)",
      "ARP_DEVICE_SHORT_VERSION": "2024_6"
    }
  }
]
```


Добавьте в блок buildPresets:

```
{
  "name": "build-windows-AXCF2152-2024-LTS-Release",
  "displayName": "Build AXCF2152 (SDK 2024.6)",
  "configurePreset": "build-windows-AXCF2152-2024-LTS-Release"
},
```

<p>4. Генерация CMake в Visual Studio</p>

Откройте VS2022 → Открыть папку → выберите:

```
D:\TMAU\TMAU_Lab4\ptusa_main\
```

Вверху выбирите конфигурацию Build AXCF2152 (SDK 2024.6) и запустите.
После успешной компиляции:
Build → Build All

<p>5. Проверка результата</p>

После долгой и успешной сборки появляется файл:

```
D:\TMAU\TMAU_Lab4\ptusa_main\bin\build\AXCF2152_2024_6\Release\ptusa_main
```

Файл без расширения - это и есть итоговый бинарник для PLCnext.


<p>6. Подключение и настройка</p>
Далее необходимо следовать главе Этап подключения и настройки в Лабораторной работе №3 до момента успешного входа в систему.

После этого необходимо создать каталог в корневом каталоге контроллера, например /opt/main/ и перенести файлы с расширениями .lua и .plua, каталоги spec и sys из проекта T1-PLCnext-Demo и исполняемый файл на контроллер с помощью программы WinSCP.

Все файлы с расширениями .lua и .plua, каталоги spec и sys нужно брать из проекта T1-PLCnext-Demo, который можно получить с помощью:

```
git clone --recurse-submodules https://github.com/savushkin-r-d/T1-PLCnext-Demo
```

Далее важно не забыть выдать права на выполнение нашему исполняемому файлу ptusa_main (можно прожать галочку "Выполнение" в настройках или использовать команду chmod 755 ptusa_main)

<p>7. Запуск программы</p>
Для того, чтобы запустить программу, необходимо выполнить команду:

```
./ptusa_main  main.plua  sys_path ./sys/
```

```
admin@axcf2152:~$ cd opt/main
-sh: cd: opt/main: No such file or directory 
admin@axcf2152:~$ cd /opt/main
admin@axcf2152:/opt/main$ ls
main.io.lua  main.plua  main.modbus_srv.lua
nvr am.txt  shared.lua  main.profibus.lua
main.objects.lua  main.restrictions.lua  prg.lua
ptusa_main  spec sys
admin@axcf2152:/opt/main$ ./ptusa_main main.plua sys_path ./sys/
```

Далее возникла ошибка:

```
\./ptusa_main: error while loading shared libraries: libncurses.so.5: cannot open shared object file: No such file or directory
admin@axcf2152:/opt/main$ \
```

Проблема в том, что необходимо установить библиотеку libncurses.so.5 с интернета. Что и было выполнено, и при повторном запуске:

```
admin@axcf2152:/opt/main$ ./ptusa_main main.plua sys_path ./sys/
2023-12-20 03.54.14 INFO(6) -> Program started (version 2025.12.1.0) .
2023-12-20 03.54.14 WARNING (4) -> Bus couplers are enabled.
2023-12-20 03.54.14 NOTICE (5) -> script name = "main.plua"
2023-12-20 03.54.14 NOTICE (5) -> current working directory: "/opt/main"
2023-12-20 03.54.14 NOTICE (5) -> path = ".", sys_path = "./sys", extra paths =
"./dairy-sys"
Check shared devices
2023-12-20 03.54.14 DEBUG (7) -> Total memory used: 492 of 30720 bytes[ 1.60% ]
2023-12-20 03.54.14 INFO (6) -> Starting main loop! Sleep time is 2 ms.
2023-12-20 03.54.15 CRITIC (2) -> Network device : s7->"A100":"192.168.1.11" can
't connect : timeout (100 ms) .
2023-12-20 03.54.16 CRITIC (2) -> Network device : s7->"A100":"192.168.1.11" can
't connect : timeout (100 ms) .
2023-12-20 03.54.18 CRITIC (2) -> Network device : s7->"A100":"192.168.1.11" can
't connect : timeout (100 ms) .
2023-12-20 03.54.19 ERROR(3) -> 1-5-5 : Нет связи с EasyServer.
2023-12-20 03.54.20 ERROR(3) -> 1-1-2 : Нет связи с узлом I/О 'A100' ('192.168.1.11', T1-PLCnext-Demo")
```

Логи показывают, что ptusa_main запустился корректно:

```
Program started (version 2025.12.1.0).
script name = "main.plua"
current working directory: "/opt/main"
sys_path = "./sys"
```

Это значит что программа скомпилирована правильно, Lua-скрипты загружены, sys-папка найдена, библиотека libncurses.so.5 исправно работает. То есть сам запуск работает корректно.

Критические ошибки: проблема не в программе, а в сети / конфигурации контроллеров

Вот ключевые строки:

```
CRITIC (2) -> Network device : s7->"A100":"192.168.1.11" can't connect: timeout (100 ms)
```

Эта ошибка повторяется много раз, возможно потому, что контроллер не может установить связь с устройством A100 по адресу 192.168.1.11. Устройство не отвечает (таймаут 100 мс).

А затем появляется:

```
ERROR(3) -> 1-5-5 : Нет связи с EasyServer.
```

и

```
ERROR(3) -> 1-1-2 : Нет связи с узлом I/O 'A100' ('192.168.1.11', "PLCnext-Demo")
```

Но так как задача лабораторной просто: Используя Visual Studio, собрать данный проект и продемонстрировать работоспособность на тестовом контроллере.

То эти ошибки можно не исправлять.
