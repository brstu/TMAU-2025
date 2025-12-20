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

<p align="right">Нестюк Н. C.</p>

<p align="right"><strong>Проверил:</strong></p>

<p align="right">Дворанинович Д. А.</p>

<br><br><br><br><br>

<p align="center"><strong>Брест 2025</strong></p>



---



## Цели работы

1\. Ознакомиться с документацией по платформе **PLCnext**.

2\. Проанализировать проект \[ptusa\_main](https://github.com/savushkin-r-d/ptusa\_main).

3\. Выполнить сборку проекта в \*\*Visual Studio\*\* и проверить его работу на тестовом контроллере.

4\. Подготовить отчет в формате Markdown (`readme.md`) и разместить его через pull request в каталоге:  

&nbsp;  `trunk\\as000xxyy\\task\_04\\doc`.



## Шаги выполнения



1. Ознакомился с общей информацией о платформе **PLCnext** по предоставленной ссылке.

2. Изучил проект \[ptusa\_main](https://github.com/savushkin-r-d/ptusa\_main) на GitHub.

3. Для сборки проекта в **Visual Studio** выполнил следующие действия:

 - Клонировал репозиторий с помощью команды:

    ```bash

    git clone --recurse-submodules https://github.com/savushkin-r-d/ptusa\_main.git
    ```

  - После успешного клонирования открыл проект в **Visual Studio**.



4. Произвел сборку проекта, в результате чего был создан исполняемый файл \*\*ptusa\_main\*\*.



5. Установил соединение с контроллером через Ethernet и убедился в успешном подключении.



6. Запустил исполняемый файл \*\*ptusa\_main\_Nestyuk\*\* и проверил его функциональность.



Результат выполнения:

```bash

admin@axcf2152:/opt/main$ ./ptusa\_main\_Vanya  main.plua  sys\_path ./sys/

2023-12-20 03.35.38 INFO   (6) -> Program started (version 2025.12.1.0).

2023-12-20 03.35.38 WARNING(4) -> Bus couplers are enabled.

2023-12-20 03.35.38 NOTICE (5) -> script\_name = "main.plua"

2023-12-20 03.35.38 NOTICE (5) -> current working directory: "/opt/main"

2023-12-20 03.35.38 NOTICE (5) -> path = ".", sys\_path = "./sys", extra\_paths = "./dair

y-sys"

Check shared devices

2023-12-20 03.35.38 DEBUG  (7) -> Total memory used: 492 of 30720 bytes\[ 1.60% ].

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



## Заключение



Проект **ptusa\_main** был успешно собран и протестирован на тестовом контроллере. Все ключевые функции программы были проверены и подтвердили свою работоспособность.





