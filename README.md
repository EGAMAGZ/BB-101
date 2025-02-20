# BB-101

Biblioteca de C para el curso de introducción de BB-101

## Descripción de la Biblioteca BB-101

La biblioteca BB-101 es un conjunto de funciones en C diseñadas para facilitar
la entrada de datos del usuario. Proporciona una interfaz sencilla para obtener
diferentes tipos de datos, incluyendo enteros, números de punto flotante,
caracteres y cadenas. Además, incluye una función para realizar preguntas de
sí/no, lo que permite una interacción más dinámica con el usuario.

## Funciones Disponibles

- **obtener_entero**: Permite al usuario ingresar un número entero.
- **obtener_entero_positivo**: Solicita un número entero positivo.
- **obtener_decimal**: Permite la entrada de un número de punto flotante.
- **obtener_decimal_grande**: Solicita un número de punto flotante de doble
  precisión.
- **obtener_entero_largo**: Permite la entrada de un número entero largo.
- **obtener_entero_muy_largo**: Solicita un número entero de muy largo tamaño.
- **preguntar_si_no**: Realiza una pregunta al usuario y espera una respuesta de
  sí o no.
- **obtener_caracter**: Permite al usuario ingresar un solo carácter.
- **obtener_texto**: Solicita una cadena de texto al usuario.

## Instalación

### En Windows

1. **Instalar Chocolatey**: Si aún no tienes Chocolatey instalado, abre una
   terminal de PowerShell como administrador y ejecuta el siguiente comando:

   ```powershell
    Set-ExecutionPolicy Bypass -Scope Process -Force;
    [System.Net.ServicePointManager]::SecurityProtocol =
    [System.Net.ServicePointManager]::SecurityProtocol -bor 3072; iex ((New-Object
    System.Net.WebClient).DownloadString('<https://community.chocolatey.org/install.ps1>'))
    ````

2. **Instalar Make**: Una vez que Chocolatey esté instalado, puedes instalar Make ejecutando el siguiente comando en la terminal:

    ```powershell
    choco install make
    ```

3. **Clonar el Repositorio**: Clona el repositorio que contiene la biblioteca BB-101 en tu máquina local.

4. **Compilar la Biblioteca**: Navega al directorio del proyecto en la terminal y ejecuta el siguiente comando para compilar la biblioteca:

   ```bash
   make
   ```

5. **Instalar la Biblioteca**: Para instalar la biblioteca en el sistema,
   ejecuta:

   ```bash
   make install
   ```

6. **Desinstalar la Biblioteca**: Si necesitas desinstalar la biblioteca, puedes
   hacerlo con:

   ```bash
   make uninstall
   ```

### En Linux y macOS

1. **Instalar Make**: Asegúrate de tener `make` instalado. En la mayoría de las distribuciones de Linux, puedes instalarlo usando el gestor de paquetes correspondiente (por ejemplo, `apt`, `yum`, `brew` en macOS).

2. **Clonar el Repositorio**: Clona el repositorio que contiene la biblioteca BB-101 en tu máquina local.

3. **Compilar la Biblioteca**: Navega al directorio del proyecto en la terminal y ejecuta el siguiente comando para compilar la biblioteca:

   ```bash
   make
   ```

4. **Instalar la Biblioteca**: Para instalar la biblioteca en el sistema,
   ejecuta:

   ```bash
   make install
   ```

5. **Desinstalar la Biblioteca**: Si necesitas desinstalar la biblioteca, puedes
   hacerlo con:

   ```bash
   make uninstall
   ```

## Pruebas

Para probar la biblioteca, puedes ejecutar la tarea `test`, que compila y
ejecuta un programa de ejemplo utilizando la biblioteca dinámica global. Para
hacerlo, simplemente ejecuta:

```bash
make test
```

## Limpieza

Si deseas limpiar los archivos generados durante la compilación, puedes usar la
tarea `clean`:

```bash
make clean
```

Esto eliminará los directorios de construcción, las bibliotecas y el ejecutable
de prueba.
