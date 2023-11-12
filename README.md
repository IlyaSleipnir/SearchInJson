# Задание

Напишите самостоятельно, без использования сторонних библиотек, консольную
программу, которая, принимая на вход путь до json-файла и искомый ключ, выполняет
поиск всех значений соответствующие этому ключу. Формат работы с программой
должен быть такой:

file.json

{

&emsp;&emsp;"x": "y",

&emsp;&emsp;"y": "z",
  
&emsp;&emsp;"z": {
  
&emsp;&emsp;&emsp;&emsp;"x": "y",
    
&emsp;&emsp;&emsp;&emsp;"y": 1,
    
&emsp;&emsp;&emsp;&emsp;"z": "z",
    
&emsp;&emsp;&emsp;&emsp;"a": {
    
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;"z": 0
      
&emsp;&emsp;&emsp;&emsp;}
    
&emsp;&emsp;}
  
}


application -f file.json -k z

На выходе

/z: {

&emsp;&emsp;"x": "y",

&emsp;&emsp;"y": 1,

&emsp;&emsp;"z": "z",

&emsp;&emsp;"a": {

&emsp;&emsp;&emsp;&emsp;"z": 0

&emsp;&emsp;}

}

/z/z: "z"

/z/a/z: 0

По ключу -h вывести описание программы и входных параметров.
