<p align="center">Министерство образования Республики Беларусь</p>
<p align="center">Учреждение образования</p>
<p align="center">«Брестский государственный технический университет»</p>
<p align="center">Кафедра ИИТ</p>
<br><br><br><br><br><br><br>
<p align="center">Лабораторная работа №5</p>
<p align="center">По дисциплине «Теория и методы автоматического управления»</p>
<p align="center">Тема: «Работа с контроллером AXC F 2152»</p>
<br><br><br><br><br>
<p align="right">Выполнил:</p>
<p align="right">Студент 3-го курса</p>
<p align="right">Группы АС-66</p>
<p align="right">Неруш Е. С.</p>
<p align="right">Проверила:</p>
<p align="right">Иванюк Д.С.</p>
<br><br><br><br><br>
<p align="center">Брест 2025</p>

---

## Задание: 
Используя Visual Code создать тестовый проект "Hello PLCnext from AS0xxyy!", собрать его и продемонстрировать работоспособность на тестовом контроллере. Выводить должно анекдот.

### Этап подготовки
1. Установка Git LFS

Устанавливаем Git LFS, необходимый для корректной загрузки бинарных файлов проекта.

2. Клонирование SCADA-компонентов

Клонируем репозиторий с компонентами EasyServer, Monitor и DbEditorXML:

git clone --recurse-submodules https://github.com/savushkin-r-d/SCADA-ptusa-bin

3. Настройка SCADA-компонентов

Выполняем настройку следующих компонентов:

DbEditorXML

EasyServer

Monitor

5. Запуск проекта

Запуск приложения осуществляется из PowerShell следующей командой:

.\ptusa_main.exe `
  --script d:/T1-PLCnext-Demo/main.plua `
  --sys_path d:/T1-PLCnext-Demo/sys `
  --extra_paths d:/T1-PLCnext-Demo/dairy-sys `
  --path d:/T1-PLCnext-Demo `
  --debug

6. Результат выполнения

В процессе запуска происходит инициализация Lua-скриптов, загрузка конфигурации и переход в основной цикл:

INFO    -> Program started (version 2025.12.1.0)
DEBUG   -> Init Lua...
NOTICE  -> script_name = "d:/T1-PLCnext-Demo/main.plua"
NOTICE  -> path = "d:/T1-PLCnext-Demo"

Device manager [64]:
    1. V1
    2. V2
    3. Y1V1      Донный клапан
    ...
   64. HLA1

Init Lua Ok.
INFO    -> Starting main loop! Sleep time is 2 ms.
Accepted connection from 127.0.0.1
G_CURRENT_PROTOCOL_VERSION = 104, host =[T1-PLCnext-Demo]
Expand commentComment on lines R64 to R80ResolvedCode has comments. Press enter to view.

Данный вывод подтверждает успешную загрузку проекта, корректную инициализацию устройств и запуск основного цикла.

7. Изменение логики запуска ламп

Перед запуском приложения был изменён файл main.plua. Логика инициализации вынесена в функцию user_init, что позволило избежать дублирования кода:

function user_init()
    local TIME = 200
    local now = get_millisec()

    A5HL8_info.start_time = now
    A5HL6_info.start_time = now
    A5HL4_info.start_time = now - TIME * 3
    A5HL2_info.start_time = A5HL4_info.start_time
    A5HL7_info.start_time = A5HL2_info.start_time - TIME / 3
    A5HL5_info.start_time = now
    A5HL3_info.start_time = A5HL5_info.start_time
    A5HL1_info.start_time = now
end

В результате была изменена последовательность включения ламп, что отразилось на поведении системы в Monitor.

![](../images/monitor.png)
<br>
| _Результат работы программы_