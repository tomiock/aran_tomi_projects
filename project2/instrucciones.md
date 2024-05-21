## Como hay que configurar esto?

Dependencias:
- `cmake`

Instalar con:
```shell
sudo apt-get install cmake
```
La version deberia ser como minimo 3.10.

### Compilacion

1. Correr `cmake`:
```shell
cmake -S . -B build -DUSE_SMALL_DATASET=ON
```
Usamos una flag para especificar que el dataset que tenemos que usar es `small.h`.

2. Compilar el proyecto:
```shell
cmake --build build
```

### Ejecucion

Para ejecutar el programa, hay que correr el archivo `app` que se encuentra en la carpeta principal del proyecto:
```shell
./app
```

### Hacer todo a la vez
Simplemente juntar todos los comandos, desde la carpeta principal del proyecto:
```shell
cmake -S .. -B . -DUSE_SMALL_DATASET=ON && cmake --build build
```

### Compilar con `debug` flags:
```
cmake -S . -B build -DUSE_SMALL_DATASET=ON -DCMAKE_BUILD_TYPE=DEBUG 
```

