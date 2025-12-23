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
<p align="right">Неруш Е. С.</p>
<p align="right">Проверил:</p>
<p align="right">Иванюк Д.С.</p>
<br><br><br><br><br><br><br><br>
<p align="center">Брест 2025</p>

---

# Общее задание #
1. Ознакомиться с общей информацией о платформе **PLCnext** [здесь](https://www.plcnext.help/te/About/Home.htm).

2. Изучить проект [ptusa_main](https://github.com/savushkin-r-d/ptusa_main).

3. Используя **Visual Studio** собрать данные проект и продемонстрировать работоспособность на тестовом контроллере.

4. Написать отчет по выполненной работе в .md формате (readme.md) и с помощью pull request разместить его в следующем каталоге: trunk\as000xxyy\task_04\doc.
# Ход работы
## 1 - 2. 
Работа производится с контроллером, который применялся для выполнения задания 3.
Проект [ptusa_main](https://github.com/savushkin-r-d/ptusa_main) изучен.

## 3. 

### Сборка
Для начала необходимо склонировать репозиторий с проектом на локальный компьютер. 
Для этого используется следующая команда:
```bash
git clone --recurse-submodules https://github.com/savushkin-r-d/ptusa_main.git
```
На компьютере располагаем проект на диске D:. 

Для того, чтобы проект можно было собрать необходима установка [SDK](https://www.phoenixcontact.com/en-fr/products/controller-axc-f-2152-2404267?type=softw&utm_source=qr&utm_medium=print&utm_campaign=product_detection#downloads-link-target).
Перейдя по ссылке нужно спуститься вниз, выбрать пункт Software, где выбрать требуемую версию.
В данном случае используется версия 2024.6.

По указанной ссылке скачиваем выбранный архив. Его распаковку производим по адресу *D:\PLCnextSDK\AXCF2152_2024_6*.
Соответствие адреса необходимо для корректной сборки.

После этого необходимо изменить файл *CMakePresets.json*, расположенный в корне проекта ptusa_main.
Для данной версии SDK и пути к нему обязательно следующее содержание:

```json
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
	"ARP_DEVICE_VERSION": "2024.6.1 (24.6.1.93)",
  	"ARP_DEVICE_SHORT_VERSION": "2024_6",
      }
    }

 "name": "build-windows-AXCF2152-2024-LTS-Release",
 "displayName": "Build AXCF2152 (SDK 2024.6)",
 "configurePreset": "build-windows-AXCF2152-2024-LTS-Release"

```Expand commentComment on lines R80 to R122ResolvedCode has comments. Press enter to view.
Когда файл изменен, нужно открыть папку с проектом в Visual Studio. В качестве пресета для сборки выбрать 

***Build AXCF2152 (SDK 2024.6)***. Выполним сборку проекта (Ctrl+Shift+B). 

При успешном выполнении получим следующую структуру папок *D:\ptusa_main\bin\build\AXCF2152_2024_6\Release*. 

В ней и будет располагаться собранный бинарный файл ptusa_main.Expand commentComment on line R127ResolvedCode has comments. Press enter to view.

### Запуск на контроллере

Подключение к контроллеру описано в [отчете по заданию №3](https://github.com/Ivan160927777/TMAU-2025/blob/task_03/trunk/as06503/task_03/doc/readme.md). 
Здесь оно выполняется аналогично.

После выполнения подключения в программе PuTTY переходим по 
адресу /opt, где создаем каталог main. С помощью WinSCP помещаем

в данный каталог бинарный файл *ptusa_main*. Там же должны находиться файлы:

- main.io.lua
- main.modbus_srv.lua
- main.objects.lua
- main.plua
- main.profibus.lua
- main.restrictions.lua
- nvram.txt
- prrg.lua
- shared.lua

И каталоги:
- spec
- sys

Для файла ptusa_main устанавливаем минимально необходимые права доступа, например, на чтение, запись и исполнение для владельца и чтение/исполнение для группы (например, 750 или 755), чтобы обеспечить безопасность. Рекомендуется использовать команду:Expand commentComment on line R150ResolvedCode has comments. Press enter to view.

После запуска получили следующее сообщение:

```bash
./ptusa_main: error while loading shared libraries: libncurses.so.5: cannot open shared object file: No such file or directory
admin@axcf2152:/opt/main$ \
```
Данное сообщение говорит об отсутствии на контроллере стандартной библиотеки Linux **libncurses.so.5**.
Скачиваем ее на рабочий компьютер, и также помещаем в каталог с проектом.
Expand commentComment on line R159ResolvedCode has comments. Press enter to view.
После повторного введения команды на запуск
проект запустился. Получили следующее сообщение:
Expand commentComment on line R162ResolvedCode has comments. Press enter to view.
```
admin@axcf2152:/opt/main$ ./ptusa_main_Vanya  main.plua  sys_path ./sys/Expand commentComment on line R164ResolvedCode has comments. Press enter to view.
2025-12-18 11.33.14 INFO   (6) -> Program started (version 2025.12.1.0).
2025-12-18 11.33.14 WARNING(4) -> Bus couplers are enabled.
2025-12-18 11.33.14 NOTICE (5) -> script_name = "main.plua"
2025-12-18 11.33.14 NOTICE (5) -> current working directory: "/opt/main"
2025-12-18 11.33.14 NOTICE (5) -> path = ".", sys_path = "./sys", extra_paths = "./dair
y-sys"
Check shared devices
2025-12-18 11.33.14 DEBUG  (7) -> Total memory used: 492 of 30720 bytes[ 1.60% ].
2025-12-18 11.33.14 INFO   (6) -> Starting main loop! Sleep time is 2 ms.
2025-12-18 11.33.14 CRITIC (2) -> Network device : s7->"A100":"192.168.1.11" can't conn
ect : timeout (100 ms).
2025-12-18 11.33.14 CRITIC (2) -> Network device : s7->"A100":"192.168.1.11" can't conn
ect : timeout (100 ms).
2025-12-18 11.33.14 CRITIC (2) -> Network device : s7->"A100":"192.168.1.11" can't conn
ect : timeout (100 ms).
2025-12-18 11.33.14 ERROR  (3) -> 1-5-5 : Нет связи с EasyServer.
2025-12-18 11.33.14 ERROR  (3) -> 1-1-2 : Нет связи с узлом I/O 'A100' ('192.168.1.11',
'T1-PLCnext-Demo')

```
Таким образом, собранный проект запущен на тестовом контроллере.
Expand commentComment on line R186ResolvedCode has comments. Press enter to view.
**Вывод:** Проект ptusa_main запускается на тестовом контроллере. При его выполнении происходят ошибки, связанные с подключением к 
сетевому устройству с IP-адресом 192.168.1.11, а также с EasyServer.