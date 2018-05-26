# net
searchable text server

Searchable texts are written with the purpose to be easily searched. In fact search operations happen very often while an author is creating such a text. They help to simplify input prompting with options. Each word gets connected to a small number of other words, each of them provided with a category. Categories are chosen freely by the author. Several authors help each other defining categories.

This format can be used by machines to communicate with humans. When all sorts of machines put their status information into a common channel they can be found by you and me. Attaching a search engine to such a channel makes good sense. Now it is of now use because only software developers understand messages of their machines.

Highlights:
* code covered with unit tests
* fast and clean node removal
* fast export to dump file
* reusing identifies
* Docker container

Requirements:
* Linux

Dependencies:
* pthread

Build with:
```bash
sudo make --always-make install
```
Run tests with:
```bash
make --always-make test
```

Build Docker image:
```
docker build --tag mem-memov:net .
```

Run Docker container:
```
docker run --detach --publish 43152:43152 --name mem_memov_net_container mem-memov:net
```

Searchable text example:
```
Молодая рыжая собака — помесь такса с дворняжкой — очень похожая мордой на лисицу бегала взад и вперед по тротуару беспокойно оглядывалась по сторонам.

собака
    цвет: рыжий
    возраст: молодой
    порода: помесь
        части:
            часть: такса
            часть: дворняжка
    части:
        часть: морда
            сходство: лиса
    действия:
        действие: бегать
            место: тротуар
                положение: сверху
            направление: взад
            направление: вперёд
        действие: оглядываться
            направление: стороны
            образ: беспокойно


Изредка она останавливалась и, плача, приподнимая то одну озябшую лапу, то другую, старалась дать себе отчет: как это могло случиться, что она заблудилась?

она: собака
    части:
        лапы:
            действия:
                действие: озябнуть
            части:
                часть: лапа
                    место: справа
                    место: спереди
                часть: лапа
                    место: слева
                    место: спереди
    действия:
        действие: останавливаться
            частота: изредка
        действие: плакать
        действие: приподнимать
            предмет: ^она.части.лапы
            образ: поочерёдно
        действие: дать
            направление: ^она
            предмет: отчёт
                содержание: это
                    действия:
                        действие: случиться
                            вероятность: возможно
                            событие:
                                участник: ^она
                                    действия:
                                        действие: заблудиться
            

Запросы:
    она?
    собака

    собака?
    цвет
    возраст
    порода
    части
    действия

    собака.действия.действие?
    бегать
    оглядываться
    останавливаться
    плакать
    приподнимать
    дать
    заблудиться

    часть?
    такса
    дворняжка
    лапы
    лапа

    помесь.части.часть?
    такса
    дворняжка
```