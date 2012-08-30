#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* ******************************************************************
 *                DEFINICION DE LOS TIPOS DE DATOS
 * *****************************************************************/
typedef struct vector
{
    size_t tam;
    int *datos;
} vector_t;

/* ******************************************************************
 *                    PRIMITIVAS DEL VECTOR
 * *****************************************************************/

// Crea un vector de tamaño tam
// Post: vector es una vector vacío de tamaño tam
vector_t* vector_crear(size_t tam);

// Destruye el vector
// Pre: el vector fue creado
// Post: se eliminaron todos los elementos del vector
void vector_destruir(vector_t *vector);

// Cambia el tamaño del vector
// Pre: el vector fue creado
// Post: el vector cambió de tamaño a nuevo_tam y devuelve true
// o el vector queda intacto y devuelve false si no se pudo cambiar el tamaño
// a nuevo_tam
bool vector_redimensionar(vector_t *vector, size_t nuevo_tam);

// Almacena en valor el dato guardado en la posición pos del vector
// Pre: el vector fue creado
// Post: se almacenó en valor el dato en la posición pos. Devuelve false si la
// posición es inválida (fuera del rango del vector, que va de 0 a tamaño-1)
bool vector_obtener(vector_t *vector, size_t pos, int *valor);

// Almacena el valor en la posición pos
// Pre: el vector fue creado
// Post: se almacenó el valor en la posición pos. Devuelve false si la posición
// es inválida (fuera del rango del vector, que va de 0 a tamaño-1) y true si
// se guardó el valor con éxito.
bool vector_guardar(vector_t *vector, size_t pos, int valor);

// Devuelve el tamaño del vector
// Pre: el vector fue creado
size_t vector_obtener_tamanio(vector_t *vector);

/* ******************************************************************
 *                        IMPLEMENTACION
 * *****************************************************************/

// Crea un vector de tamaño tam
// Post: vector es una vector vacío de tamaño tam
vector_t* vector_crear(size_t tam)
{
    vector_t* vector = malloc(sizeof(vector_t));
    if (vector == NULL) return NULL;

    vector->datos = malloc(tam * sizeof(int));
    if (vector->datos == NULL)
    {
        free(vector);
        return NULL;
    }
    vector->tam = tam;
    return vector;
}

// Destruye el vector
// Pre: el vector fue creado
// Post: se eliminaron todos los elementos del vector
void vector_destruir(vector_t *vector)
{
    free(vector);
}


// Cambia el tamaño del vector
// Pre: el vector fue creado
// Post: el vector cambió de tamaño a nuevo_tam y devuelve true
// o el vector queda intacto y devuelve false si no se pudo cambiar el tamaño
// a nuevo_tam
bool vector_redimensionar(vector_t *vector, size_t tam_nuevo)
{
    int* datos_nuevo = realloc(vector->datos, tam_nuevo * sizeof(int));
    // Cuando tam_nuevo es 0, es correcto que devuelva NULL
    // En toda otra situación significa que falló el realloc
    if (tam_nuevo > 0 && datos_nuevo == NULL)
    {
        return false;
    }
    vector->datos = datos_nuevo;
    vector->tam = tam_nuevo;
    return true;
}

// Almacena en valor el dato guardado en la posición pos del vector
// Pre: el vector fue creado
// Post: se almacenó en valor el dato en la posición pos. Devuelve false si la
// posición es inválida (fuera del rango del vector, que va de 0 a tamaño-1)
bool vector_obtener(vector_t *vector, size_t pos, int *valor)
{
    if (pos >= 0 && pos < (vector->tam))
        {
            *valor = *vector[pos].datos;
        }


    return false;
}

// Almacena el valor en la posición pos
// Pre: el vector fue creado
// Post: se almacenó el valor en la posición pos. Devuelve false si la posición
// es inválida (fuera del rango del vector, que va de 0 a tamaño-1) y true si
// se guardó el valor con éxito.
bool vector_guardar(vector_t *vector, size_t pos, int valor)
{
    if (pos >= 0 &&  pos < (vector->tam))
        {
            vector[pos].datos = malloc(vector->tam * sizeof(int));


            *vector[pos].datos = valor;
            return true;
        }

    return false;
}

// Devuelve el tamaño del vector
// Pre: el vector fue creado
size_t vector_obtener_tamanio(vector_t *vector)
{
    return vector->tam;
}


/* ******************************************************************
 *                        PRUEBAS UNITARIAS
 * *****************************************************************/

/* Función auxiliar para imprimir si estuvo OK o no. */
void print_test(char* name, bool result)
{
    printf("%s: %s\n", name, result? "OK" : "ERROR");
}

/* Prueba que las primitivas del vector funcionen correctamente. */
void prueba_vector()
{
    /* Declaro las variables a utilizar */
    vector_t* v1;
    vector_t* v2;
    int valor1, valor2;

    /* Pruebo la creación de un vector de tamanio 0 */
    v1 = vector_crear(0);
    print_test("Prueba vector crear v1 con tamanio 0", v1 != NULL);
    print_test("Prueba vector obtener tamanio v1 es 0", vector_obtener_tamanio(v1) == 0);

    /* Pruebo la creación de un vector de tamanio 5 */
    v2 = vector_crear(5);
    print_test("Prueba vector crear v2 con tamanio 5", v2 != NULL);
    print_test("Prueba vector obtener tamanio v2 es 5", vector_obtener_tamanio(v2) == 5);

    /* Pruebo que guardar en un vector de tamanio 0 devuelve false */
    print_test("Prueba vector guardar en v1[0] es false", !vector_guardar(v1, 0, 5));
    print_test("Prueba vector guardar en v1[1] es false", !vector_guardar(v1, 1, 10));

    /* Pruebo que guardar en un vector de tamanio 5 funciona para posiciones menores que 5 */
    print_test("Prueba vector guardar 20 en v2[0] es true", vector_guardar(v2, 0, 20));
    print_test("Prueba vector guardar 30 en v2[1] es true", vector_guardar(v2, 1, 30));

    /* Pruebo que guardar en un vector de tamanio 5 no funciona para posiciones mayores o iguales que 5 */
    print_test("Prueba vector guardar 35 en v2[5] es false", !vector_guardar(v2, 5, 35));
    print_test("Prueba vector guardar 40 en v2[6] es false", !vector_guardar(v2, 6, 40));

    /* Pruebo que obtener valores de un vector de tamaño 0 devuelve false */
    print_test("Prueba vector obtener v1[0] es false", !vector_obtener(v1, 0, &valor1));
    print_test("Prueba vector obtener v1[1] es false", !vector_obtener(v1, 1, &valor1));

    /* Pruebo obtener los valores de un vector previamente guardados */
    vector_obtener(v2, 0, &valor1);
    print_test("Prueba vector obtener v2[0] es 20", valor1 == 20);
    vector_obtener(v2, 1, &valor2);
    print_test("Prueba vector obtener v2[1] es 30", valor2 == 30);

    /* Pruebo que tratar de obtener valores de posiciones inválidas devuelve false */
    print_test("Prueba vector obtener v2[5] es false", !vector_obtener(v2, 5, &valor1));
    print_test("Prueba vector obtener v2[6] es false", !vector_obtener(v2, 6, &valor1));

    /* Pruebo redimensionar un vector de 5 a 10 posiciones */
    vector_redimensionar(v2, 10);
    print_test("Prueba vector redimensionar v2 con tamanio 10", vector_obtener_tamanio(v2) == 10);

    /* Pruebo guardar y obtener un valor del vector redimensionado */
    print_test("Prueba vector guardar 50 en v2[6] es true", vector_guardar(v2, 6, 50));
    vector_obtener(v2, 6, &valor1);
    print_test("Prueba vector obtener v2[6] es 50", valor1 == 50);

    /* Pruebo redimensionar un vector de 10 a 3 posiciones */
    vector_redimensionar(v2, 3);
    print_test("Prueba vector redimensionar v2 con tamanio 3", vector_obtener_tamanio(v2) == 3);
    print_test("Prueba vector guardar 50 en v2[6] es false", !vector_guardar(v2, 6, 50));
    print_test("Prueba vector obtener v2[6] es false", !vector_obtener(v2, 6, &valor1));

    /* Pruebo que los valores en las posiciones que quedan se conservan después de redimensionar */
    vector_obtener(v2, 0, &valor1);
    print_test("Prueba vector obtener v2[0] es 20 despues de redimensionar", valor1 == 20);

    /* Destruyo los vectores para liberar la memoria pedida */
    vector_destruir(v1);
    vector_destruir(v2);
};


/* ******************************************************************
 *                        PROGRAMA PRINCIPAL
 * *****************************************************************/

/* Programa principal. */
int main(void)
{

    /* Ejecuta todas las pruebas unitarias. */
    prueba_vector();

    return 0;
}


