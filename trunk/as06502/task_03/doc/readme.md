<p align="center"> Министерство образования Республики Беларусь</p>
<p align="center">Учреждение образования</p>
<p align="center">“Брестский Государственный технический университет”</p>
<p align="center">Кафедра ИИТ</p>
<br><br><br><br><br><br><br>
<p align="center">Лабораторная работа №3</p>
<p align="center">По дисциплине “Теория и методы автоматического управления”</p>
<p align="center">Тема: "Работа с контроллером AXC F 2152"</p>
<br><br><br><br><br>
<p align="right">Выполнил:</p>
<p align="right">Студент 3 курса</p>
<p align="right">Группы АС-65</p>
<p align="right">Грущинский Д.Д</p>
<p align="right">Проверил:</p>
<p align="right">Дворанович Д.Д.</p>
<br><br><br><br><br>
<p align="center">Брест 2025</p>

---

**Цель работы:** Запустить проект на контроллере AXCF 2152.

## Ход работы:
Для начала сделал форк репозитория savushkin-r-d/PLCnext-howto. Затем установил MVS19 для компиляции, а также CMake, CMake Tool и MinGW.

Открыл проект "Hello PLCnext" в папке PLCnext-howto/HowTo build program через MVS и нашёл файл Cpp.

Если при компиляции возникала ошибка, переходил в папку PLCnext-howto-master/HowTo build program Hello PLCnext/Hello-PLCnext/CmakeCashe и указывал путь к файлу ninja в строке "CMAKE_MAKE_PROGRAM:FILEPATH". По умолчанию путь к ninja — C:/Program Files (x86)/MicrosoftVisualStudio/2022/Community/Common7/IDE/CommonExtensions/Microsoft/CMake/Ninja/ninja.exe. После обновления пути сборка проходила успешно.

Далее установил WinSCP и PuTTY. Настроил сеть в разделе "Панель управления" -> "Сеть и Интернет" -> "Центр управления сетями и общим доступом". Подключил Ethernet с IP-адресом 192.168.1.1 и маской 255.255.255.0.

В PuTTY ввёл IP-адрес контроллера 192.168.1.10 для подключения.

В WinSCP также ввёл IP-адрес 192.168.1.10, указал логин "admin" и пароль, указанный на контроллере.

После успешного входа в файловую систему контроллера перенёс туда файл "hello_PLCnext" и назначил ему полные права доступа, чтобы исключить ошибку "permission denied".

Через терминал контроллера запустил файл "hello_PLCnext" командой `./hello_PLCnext`. При корректном выполнении всех шагов в терминале появилось сообщение: "Hello PLCnext".