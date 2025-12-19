<p align="center">Министерство образования Республики Беларусь</p>
<p align="center">Учреждение образования</p>
<p align="center">“Брестский Государственный технический университет”</p>
<p align="center">Кафедра ИИТ</p>
<br><br><br><br><br><br>
<p align="center"><strong>Лабораторная работа №3</strong></p>
<p align="center"><strong>По дисциплине</strong> “Теория и методы автоматического управления”</p>
<p align="center"><strong>Тема:</strong> “Работа с контроллером AXC F 2152”</p>
<br><br><br><br><br><br>
<p align="right"><strong>Выполнил</strong>:</p>
<p align="right">Студент 3 курса</p>
<p align="right">Группы АС-65</p>
<p align="right">Егоренков Н. Д.</p>
<p align="right"><strong>Проверил:</strong></p>
<p align="right">Дворанинович Д. А.</p>
<br><br><br><br><br>
<p align="center"><strong>Брест 2025</strong></p>

---


<p>Задание:<p>

Ознакомиться с основными характеристиками платформы PLCnext через официальную документацию.
Изучить пример из руководства.
Используя Visual Studio Code, создать проект “Hello PLCnext from AS0xxyy!”, собрать его и продемонстрировать работоспособность.
Написать отчет о проделанной работе в формате .md и отправить его через pull request в каталог: trunk\as000xxyy\task_03\doc.
<p> <strong>Цель работы:</strong> Создать и протестировать проект "Hello PLCnext from AS0xxyy!" на базе PLC-контроллера AXC F 2152.</p> <p> <strong>Ход работы:</strong> </p> <p>Первым этапом необходимо склонировать репозиторий проекта.</p> <p>Для компиляции файла *hello_PLCnext* используется следующий набор команд:</p>

 ``` bash
cmake --preset=build-windows-AXCF2152-2021.0.3.35554 .
```


 ``` bash
cmake --build --preset=build-windows-AXCF2152-2021.0.3.35554 --target all
```



 ``` bash
cmake --build --preset=build-windows-AXCF2152-2021.0.3.35554 --target install
```

Скриншоты выполнения работы:

![alt text](images/connect.png)

![alt text](images/network_configuration.png)

![alt text](images/PuTTY_connect.png)

![alt text](images/PuTTY_login_password.png)

![alt text](images/hello_PLCnext_settings.png)


<p> <strong>Вывод:</strong> В ходе лабораторной работы был успешно создан и протестирован проект "Hello PLCnext from AS0xxyy!", что позволило изучить основы взаимодействия с контроллером <em>AXC F 2152</em>.</p>