<p align="center">Министерство образования Республики Беларусь</p>
<p align="center">Учреждение образования</p>
<p align="center">«Брестский государственный технический университет»</p>       
<p align="center">Кафедра ИИТ</p>
<br><br><br><br>
<p align="center">Лабораторная работа №5</p>
<p align="center">По дисциплине: «ТИМАУ»</p>
<p align="center"><strong>Тема:</strong> “Работа с контроллером AXC F 2152”</p>
<br><br><br>
<p align="right">Выполнил</p> 
<p align="right">Студент 3-го курса</p>
<p align="right">Группы АС-66</p>
<p align="right">Рогожин А.С./</p>
<p align="right">Проверил</p>
<p align="right">Дворанинович Д.А.</p>
<br><br><br>
<p align="center">Брест 2025</p>

---

### Ход работы
1. Клонируем репозиторий T1-PLCnext-Demo вместе с подмодулями:

git clone --recurse-submodules https://github.com/savushkin-r-d/T1-PLCnext-Demo

2. Установка Git LFS, необходимого для корректной загрузки бинарных файлов проекта.

3. Клонирование SCADA-компонентов (EasyServer, Monitor и DbEditorXML):

git clone --recurse-submodules https://github.com/savushkin-r-d/SCADA-ptusa-bin

4. Настройка SCADA-компонентов:

DbEditorXML
EasyServer
Monitor

5. Запуск проекта осуществляется из PowerShell следующей командой:

.\ptusa_main.exe `
  --script d:/T1-PLCnext-Demo/main.plua `
  --sys_path d:/T1-PLCnext-Demo/sys `
  --extra_paths d:/T1-PLCnext-Demo/dairy-sys `
  --path d:/T1-PLCnext-Demo `
  --debug

6. Результаты выполнения

При запуске происходит инициализация Lua-скриптов, загрузка конфигурации и переход в основной цикл:

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

Этот вывод подтверждает успешную загрузку проекта, корректную инициализацию устройств и запуск основного цикла.

7. Изменение логики запуска ламп

Перед запуском приложения был изменён файл main.plua. Логика инициализации вынесена в функцию user_init, что позволяет избежать дублирования кода:

function user_init()
    local TIME = 150
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

# Заключение
В ходе лабораторной работы была изменена последовательность включения ламп, что отразилось на поведении системы в мониторе.
