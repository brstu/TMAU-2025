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
<p align="right">Езепчук А.С.</p>
<p align="right">Проверил:</p>
<p align="right">Дворанинович Д.А.</p>
<br><br><br><br><br><br><br><br>
<p align="center">Брест 2025</p>

---
## Цели работы
1. Ознакомиться с документацией по платформе PLCnext (https://www.plcnext.help/te/About/Home.htm)).
2. Проанализировать проект (https://github.com/savushkin-r-d/ptusa_main).
3. Выполнить сборку проекта в Visual Studio 2022 и проверить его работу на тестовом контроллере.
4. Подготовить отчет в формате Markdown (`readme.md`) и разместить его через pull request в каталоге:  
   `trunk\as000xxyy\task_04\doc`.

---

## Ход выполнения

### 1. Ознакомление
Работа велась с тем же контроллером, что использовался в задании 3, AXC F 2152.  
Суть проекта **ptusa_main** была изучена, все знания для выполнения задания получены.

### 2. Сборка проекта

#### Подготовка
Первым шагом является скачивание исходного кода проекта с платформы GitHub с использованием команды git clone:
```
git clone --recurse-submodules https://github.com/savushkin-r-d/ptusa_main.git
```
Проект размещен на диске D:.
Для сборки мы установливаем PLCnext SDK.
Использована версия 2021.6, распакованная в каталог:
```
D:\PLCnextSDK\AXCF2152_2021_6.
```

#### Настройка CMakePresets.json
В корне проекта изменен файл CMakePresets.json.
Пример конфигурации для SDK 2021.6:
```
json
{
  "name": "build-windows-AXCF2152-2021-LTS-Release",
  "displayName": "Build AXCF2152 (SDK 2021.6)",
  "description": "Сборка для AXCF2152 с использованием PLCnext SDK 2021.6",
  "inherits": "windows-AXCF-default",
  "generator": "MinGW Makefiles",
  "environment": {
    "ARP_DEVICE": "AXCF2152",
    "ARP_DEVICE_VERSION": "2021.6.0",
    "ARP_DEVICE_SHORT_VERSION": "2021_6",
    "PLCNEXT_SDK_ROOT": "D:/PLCnextSDK/AXCF2152_2021_6",
    "ARP_SDK_PACKAGE_NAME": "x86_64-w64-mingw32"
  },
  "cacheVariables": {
    "CMAKE_TOOLCHAIN_FILE": {
      "value": "D:/PLCnextSDK/AXCF2152_2021_6/toolchain.cmake",
      "type": "FILEPATH"
    }
  }
}
```
#### Сборка в Visual Studio
1) Открыть проект в Visual Studio.

2) В качестве пресета выбрать: Build AXCF2152 (SDK 2021.6).

3) Выполнить сборку (Ctrl+Shift+B) либо вкладка Сборка -> Собрать все.

После успешной компиляции бинарный файл ptusa_main находится в каталоге:
```
D:\ptusa_main\bin\build\AXCF2152_2021_6\Release.
```
Этот файл необходимо сделать исполняемым с помощью chmod 777.

Для запуска используется команда ./ptusa_main ./main.plua sys_patch ./sys/

### 3. Запуск на контроллере
Подключение выполняется аналогично заданию №3 (см. отчет).

#### Действия

В PuTTY перейти в каталог /opt и создать папку task4.

С помощью WinSCP загрузить туда бинарный файл ptusa_main и вспомогательные скрипты:
```
main.profibus.lua

main.restrictions.lua

nvram.txt

prrg.lua

shared.lua

main.io.lua

main.modbus_srv.lua

main.objects.lua

main.plua


```
Также должны присутствовать каталоги sys и spec.

Установить права доступа (например, chmod 755 ptusa_main).


Первый запуск завершился ошибкой:

```
./ptusa_main: error while loading shared libraries: libncurses.so.5: cannot open shared object file: No such file or directory
admin@axcf2152:/opt/task4$ \
```
На контроллере отсутствовала библиотека libncurses.so.5.
Для ее получения необходимо было поискать в интернете. В конечном счете был найден репозиторий на GitHub в котором она была. Мы вставили ее в проект и все стало работать корректно.
```
admin@axcf2152:/opt/task4$ ./ptusa_main  main.plua  sys_path ./sys/
2023-12-20 03.36.25 INFO   (6) -> Program started (version 2025.12.1.0).
2023-12-20 03.36.25 WARNING(4) -> Bus couplers are enabled.
2023-12-20 03.36.25 NOTICE (5) -> script_name = "main.plua"
2023-12-20 03.36.25 NOTICE (5) -> current working directory: "/opt/main"
2023-12-20 03.36.25 NOTICE (5) -> path = ".", sys_path = "./sys", extra_paths = "./dair
y-sys"
Check shared devices
2023-12-20 03.36.25 DEBUG  (7) -> Total memory used: 492 of 30720 bytes[ 1.60% ].
2023-12-20 03.36.52 INFO   (6) -> Starting main loop! Sleep time is 2 ms.
2023-12-20 03.36.25 CRITIC (2) -> Network device : s7->"A100":"192.168.1.11" can't conn
ect : timeout (100 ms).
2023-12-20 03.36.27 CRITIC (2) -> Network device : s7->"A100":"192.168.1.11" can't conn
ect : timeout (100 ms).
2023-12-20 03.36.28 CRITIC (2) -> Network device : s7->"A100":"192.168.1.11" can't conn
ect : timeout (100 ms).
2023-12-20 03.36.20 ERROR  (3) -> 1-5-5 : Нет связи с EasyServer.
2023-12-20 03.36.30 ERROR  (3) -> 1-1-2 : Нет связи с узлом I/O 'A100' ('192.168.1.11',
'T1-PLCnext-Demo')
```
### Итог
Проект ptusa_main был собран и запущен на тестовом контроллере.
Проект работает, однако выявлены сетевые ошибки при взаимодействии с устройством по адресу 192.168.1.11 и с EasyServer.

### Вывод
Задача выполнена, проект запускается, но требует дополнительной настройки сетевых соединений, они будут выполнятся в задании 5.