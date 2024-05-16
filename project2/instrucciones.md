## Como hay que configurar esto?

Depedencias:
- `cmake`

Instalar con:
```shell
sudo apt-get install cmake
```
La version deberia ser como minimo 3.10.

### Compilacion

1. Crear una carpeta donde poner los archivos de configuration llamada `build`:
```shell
mkdir build
```

2. Entrar a la carpeta `build`:
```shell
cd build
```
Aqui es donde vas a compilar el proyecto, pero el executable estara en la carpeta principal del proyecto.

3. Correr `cmake`:
```shell
cmake ..
```
Tiene dos puntos porque el archivo de configuracion de `cmake` esta en la carpeta padre.

4. Compilar el proyecto:
```shell
make
```
Tan solo hay que escribir esta palabra, no hace falta poner nada mas.

### Ejecucion

Para ejecutar el programa, hay que correr el archivo `app` que se encuentra en la carpeta principal del proyecto:
```shell
../app
```

### Hacer todo a la vez
Simplemente juntar todos los comandos, desde la carpeta `build`:
```shell
cmake .. && make && ../app
```
