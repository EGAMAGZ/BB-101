#include "bb101.h"

#include <ctype.h>
#include <errno.h>
#include <float.h>
#include <limits.h>
#include <math.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef char *string;

/**
 * Número de cadenas asignadas por obtener_texto.
 */
static size_t numero_asignaciones = 0;

/**
 * Arreglo de cadenas asignadas por obtener_texto.
 */
static string *strings_generados = NULL;

#undef obtener_texto
string obtener_texto(va_list *argumentos, const string mensaje, ...)
{
    // Verificar que no se exceda el número máximo de asignaciones.
    if (numero_asignaciones == SIZE_MAX / sizeof(string))
    {
        return NULL;
    }

    string buffer = NULL;
    size_t capacidad = 0;
    size_t tamano = 0;
    int caracter_actual;

    // Mostrar mensaje si se proporciona.
    if (mensaje != NULL)
    {
        va_list lista_argumentos;
        if (argumentos == NULL)
        {
            va_start(lista_argumentos, mensaje);
        }
        else
        {
            va_copy(lista_argumentos, *argumentos);
        }
        vprintf(mensaje, lista_argumentos);
        va_end(lista_argumentos);
    }

    // Leer caracteres de la entrada hasta fin de línea o EOF.
    while ((caracter_actual = fgetc(stdin)) != EOF && caracter_actual != '\n' &&
           caracter_actual != '\r')
    {

        // Asegurar espacio para el nuevo carácter y el terminador nulo.
        if (tamano + 1 >= capacidad)
        {
            size_t nueva_capacidad = (capacidad == 0) ? 16 : capacidad * 2;
            // Comprobar posible desbordamiento.
            if (nueva_capacidad <= capacidad)
            {
                free(buffer);
                return NULL;
            }
            string temp = realloc(buffer, nueva_capacidad * sizeof(char));
            if (temp == NULL)
            {
                free(buffer);
                return NULL;
            }
            buffer = temp;
            capacidad = nueva_capacidad;
        }
        buffer[tamano++] = (char)caracter_actual;
    }

    // Si no se leyó nada y se alcanzó EOF, liberar memoria y retornar NULL.
    if (tamano == 0 && caracter_actual == EOF)
    {
        free(buffer);
        return NULL;
    }

    // Si se leyó '\r', verificar si le sigue '\n' (para Windows).
    if (caracter_actual == '\r')
    {
        caracter_actual = fgetc(stdin);
        if (caracter_actual != '\n' && caracter_actual != EOF)
        {
            if (ungetc(caracter_actual, stdin) == EOF)
            {
                free(buffer);
                return NULL;
            }
        }
    }

    // Ajustar el buffer al tamaño exacto y añadir el terminador nulo.
    string string_capturado = realloc(buffer, (tamano + 1) * sizeof(char));
    if (string_capturado == NULL)
    {
        free(buffer);
        return NULL;
    }
    string_capturado[tamano] = '\0';

    // Almacenar la cadena generada en el arreglo global.
    string *tmp =
        realloc(strings_generados, (numero_asignaciones + 1) * sizeof(string));
    if (tmp == NULL)
    {
        free(string_capturado);
        return NULL;
    }
    strings_generados = tmp;
    strings_generados[numero_asignaciones++] = string_capturado;

    return string_capturado;
}

static void desmantelamiento(void)
{
    if (strings_generados != NULL)
    {
        for (size_t i = 0; i < numero_asignaciones; i++)
        {
            free(strings_generados[i]);
        }
        free(strings_generados);
    }
}

// Función de inicialización.
// Dependiendo del compilador, se puede utilizar un atributo constructor.
int INITIALIZER(setup)
{
    setvbuf(stdout, NULL, _IONBF, 0);
    atexit(desmantelamiento);
    return 0;
}
