<p align="center"> Министерство образования Республики Беларусь</p>
<p align="center">Учреждение образования</p>
<p align="center">“Брестский Государственный Технический университет”</p>
<p align="center">Кафедра ИИТ</p>
<br><br><br><br><br><br><br>
<p align="center">Лабораторная работа №4</p>
<p align="center">По дисциплине “Теория и методы автоматического управления”</p>
<p align="center">Тема: “Работа с контроллером AXC F 2152”</p>
<br><br><br><br><br>
<p align="right">Выполнил:</p>
<p align="right">Студент 3 курса</p>
<p align="right">Группы АС-66</p>
<p align="right">Янчук А.Ю.</p>
<p align="right">Проверил:</p>
<p align="right">Иванюк Д.С.</p>
<br><br><br><br><br><br><br><br>
<p align="center">Брест 2025</p>

---
## Цели работы
1. Ознакомиться с документацией по платформе **PLCnext** ([ссылка](https://www.plcnext.help/te/About/Home.htm)).
2. Проанализировать проект [ptusa_main](https://github.com/savushkin-r-d/ptusa_main).
3. Выполнить сборку проекта в **Visual Studio** и проверить его работу на тестовом контроллере.
4. Подготовить отчет в формате Markdown (`readme.md`) и разместить его через pull request в каталоге:  
   `trunk\as000xxyy\task_04\doc`.

---

## Ход выполнения

### 1. Ознакомление
Работа велась с тем же контроллером, что использовался в предыдущем задании.  
Проект **ptusa_main** изучен, структура и назначение модулей понятны.

---

### 2. Сборка проекта

#### Подготовка
Первым шагом было скачивание исходного кода проекта с GitHub с использованием команды clone:
```
git clone --recurse-submodules https://github.com/savushkin-r-d/ptusa_main.git
```
Проект размещен на диске D:.
Для сборки требуется установка PLCnext SDK.
Использована версия 2024.6, распакованная в каталог:
```
D:\PLCnextSDK\AXCF2152_2024_6.
```

Настройка CMakePresets.json
В корне проекта изменен файл CMakePresets.json.
Пример конфигурации для SDK 2024.6:
```
json
{
  "name": "build-windows-AXCF2152-2024-LTS-Release",
  "displayName": "Build AXCF2152 (SDK 2024.6)",
  "description": "Сборка для AXCF2152 с использованием PLCnext SDK 2024.6",
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
}
```
Сборка в Visual Studio:
1) Открыть проект в Visual Studio.

2) В качестве пресета выбрать: Build AXCF2152 (SDK 2024.6).

3) Выполнить сборку (Ctrl+Shift+B).

После успешной компиляции бинарный файл ptusa_main находится в каталоге:
```
D:\ptusa_main\bin\build\AXCF2152_2024_6\Release.
```

### 3. Запуск на контроллере
Подключение выполняется аналогично заданию №3 (см. отчет).

Действия: 

В PuTTY перейти в каталог /opt и создать папку main.

С помощью WinSCP загрузить туда бинарный файл ptusa_main и вспомогательные скрипты:
```

main.io.lua

main.modbus_srv.lua

main.objects.lua

main.plua

main.profibus.lua

main.restrictions.lua

nvram.txt

prrg.lua

shared.lua
```
Также должны присутствовать каталоги ```spec и sys.```

Установить права доступа (например, chmod 755 ptusa_main).


Первый запуск завершился ошибкой:

```
./ptusa_main: error while loading shared libraries: libncurses.so.5: cannot open shared object file: No such file or directory
admin@axcf2152:/opt/main$ \
```
На контроллере отсутствовала библиотека libncurses.so.5.
После её загрузки и размещения в каталоге проекта запуск прошел успешно.
```
admin@axcf2152:/opt/main$ ./ptusa_main_Artem  main.plua  sys_path ./sys/
2023-12-20 03.35.38 INFO   (6) -> Program started (version 2025.12.1.0).
2023-12-20 03.35.38 WARNING(4) -> Bus couplers are enabled.
2023-12-20 03.35.38 NOTICE (5) -> script_name = "main.plua"
2023-12-20 03.35.38 NOTICE (5) -> current working directory: "/opt/main"
2023-12-20 03.35.38 NOTICE (5) -> path = ".", sys_path = "./sys", extra_paths = "./dair
y-sys"
Check shared devices
2023-12-20 03.35.38 DEBUG  (7) -> Total memory used: 492 of 30720 bytes[ 1.60% ].
2023-12-20 03.35.38 INFO   (6) -> Starting main loop! Sleep time is 2 ms.
2023-12-20 03.35.38 CRITIC (2) -> Network device : s7->"A100":"192.168.1.11" can't conn
ect : timeout (100 ms).
2023-12-20 03.35.40 CRITIC (2) -> Network device : s7->"A100":"192.168.1.11" can't conn
ect : timeout (100 ms).
2023-12-20 03.35.42 CRITIC (2) -> Network device : s7->"A100":"192.168.1.11" can't conn
ect : timeout (100 ms).
2023-12-20 03.35.43 ERROR  (3) -> 1-5-5 : Нет связи с EasyServer.
2023-12-20 03.35.44 ERROR  (3) -> 1-1-2 : Нет связи с узлом I/O 'A100' ('192.168.1.11',
'T1-PLCnext-Demo')
```
Итог
Проект ptusa_main собран и запущен на тестовом контроллере.
Работа подтверждена, однако выявлены сетевые ошибки при взаимодействии с устройством по адресу 192.168.1.11 и с EasyServer.

Вывод: задача выполнена, проект запускается, но требует дополнительной настройки сетевых соединений.