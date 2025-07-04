#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR 300
#define MIN_AGNO 1980
#define MAX_AGNO 2025

struct n{
    char *titulo;
    char *consola;
    int agno;
    float ventas;
    struct n *sgte;
};

typedef struct n Nodo;
typedef Nodo *Lista;

void pedirTitulo(char titulo[]) {
    int largo = 0;

    while(largo == 0) {
        printf("Ingrese el t%ctulo del juego: ", 161);

        if (fgets(titulo, sizeof(char) * MAX_STR, stdin) == NULL) {
            printf("Error al leer el t%ctulo.\n", 161);
            continue;
        }

        titulo[strcspn(titulo, "\n")] = '\0';

        largo = strlen(titulo);

        if (largo == 0) {
            printf("El t%ctulo no puede estar vac%co.\n", 161, 161);
        }
    }
}

void pedirConsola(char consola[]) {
    int largo = 0;

    while(largo == 0) {
        printf("Ingrese el nombre de la consola: ");

        if (fgets(consola, sizeof(char) * MAX_STR, stdin) == NULL) {
            printf("Error al leer el nombre de la consola.\n");
            continue;
        }

        consola[strcspn(consola, "\n")] = '\0';

        largo = strlen(consola);

        if (largo == 0) {
            printf("El nombre de la consola no puede estar vac%co.\n", 161);
        }
    }
}

int pedirAgno() {
    bool valido;
    int agno;

    valido = false;

    while(!valido) {
        printf("Ingrese el a%co (entre %d y %d): ", 164, MIN_AGNO, MAX_AGNO);

        if(scanf("%d", &agno) != 1) {
            printf("Entrada inv%clida.\n", 160);
        } else if(agno < MIN_AGNO || agno > MAX_AGNO) {
            printf("A%co fuera de rango.\n", 164);
        } else {
            valido = true;
        }

        while(getchar() != '\n' && getchar() != EOF);
    }

    return agno;
}

float pedirVentas() {
    bool valido;
    float ventas;

    valido = false;

    while(!valido) {
        printf("Ingrese la cantidad de unidades vendidas (en millones): ");

        if(scanf("%f", &ventas) != 1) {
            printf("Entrada inv%clida.\n", 160);
        } else if(ventas < 0) {
            printf("La cantidad de unidades vendidas no puede ser negativa.\n");
        } else {
            valido = true;
        }

        while(getchar() != '\n' && getchar() != EOF);
    }

    return ventas;
}

int pedirOpcionMenu() {
    int opcion = 0;
    int minimo = 1;
    int maximo = 14;
    bool valido = false;

    while(!valido || opcion < minimo || opcion > maximo) {
        printf("\nMen%c de opciones:\n", 163);
        printf(" 1. Borrar la lista de juegos.\n");
        printf(" 2. Mostrar la lista de juegos.\n");
        printf(" 3. Contar la cantidad de juegos.\n");
        printf(" 4. Buscar el juego m%cs vendido para una consola.\n", 160);
        printf(" 5. Agregar un nuevo juego al inicio.\n");
        printf(" 6. Agregar un nuevo juego a una lista ordenada por a%co.\n", 164);
        printf(" 7. Invertir la lista de juegos.\n");
        printf(" 8. Ordenar la lista de juegos por a%co.\n", 164);
        printf(" 9. Seleccionar juegos lanzados en un a%co determinado.\n", 164);
        printf("10. Eliminar de la lista los juegos para una consola determinada.\n");
        printf("11. Calcular el promedio de unidades vendidas para los juegos de la lista.\n");
        printf("12. Seleccionar los juegos lanzados antes de un a%co determinado.\n", 164);
        printf("13. Calcular la cantidad total de unidades vendidas entre todos los juegos lanzados en un a%co dado.\n", 164);
        printf("14. Borrar la lista de juegos y salir.\n\n");
        printf("Ingrese opci%cn (entero entre %d y %d): ", 162, minimo, maximo);

        valido = scanf("%d", &opcion);
        while (getchar() != '\n');

        if(!valido || opcion < minimo || opcion > maximo) {
            printf("Opci%cn no v%clida.\n", 162, 160);
        }
    }

    return opcion;
}

Lista crearNodo(char *titulo, char *consola, int agno, float ventas) {
    Lista p;

    p = malloc(sizeof(Nodo));

    if (p == NULL) {
        printf("No hay memoria suficiente para crear el nodo.\n");
        return NULL;
    }

    p->titulo = strdup(titulo);

    if (p->titulo == NULL) {
        free(p);
        printf("No hay memoria suficiente para crear el nodo.\n");
        return NULL;
    }

    p->consola = strdup(consola);

    if (p->consola == NULL) {
        free(p->titulo);
        free(p);
        printf("No hay memoria suficiente para crear el nodo.\n");
        return NULL;
    }

    p->agno = agno;
    p->ventas = ventas;
    p->sgte = NULL;
    return p;
}

Lista borrarNodo(Lista nodo) {
    free(nodo->titulo);
    free(nodo->consola);
    free(nodo);
    return NULL;
}

Lista leerArchivo(char *nombreArchivo) {
    FILE *archivo;
    char linea[MAX_STR], *titulo, *consola, *strAgno, *strVentas;
    int agno;
    float ventas;
    Lista L, nuevo, aux;
    bool valido;

    archivo = fopen(nombreArchivo, "r");

    if (archivo == NULL) {
        printf("Error al abrir el archivo. El programa se cerrar%c.\n", 160);
        exit(EXIT_FAILURE);
    }

    L = NULL;

    while(fgets(linea, sizeof(linea), archivo)) {
        valido = true;
        linea[strcspn(linea, "\n")] = 0;
        titulo = strtok(linea, ";");
        consola = strtok(NULL, ";");
        strAgno = strtok(NULL, ";");
        strVentas = strtok(NULL, ";");

        if (titulo == NULL || consola == NULL || strAgno == NULL || strVentas == NULL) {
            printf("Error al leer el archivo.  El programa se cerrar%c.\n", 160);
            valido = false;
        }

        if(valido) {
            agno = atoi(strAgno);
            ventas = atof(strVentas);
            nuevo = crearNodo(titulo, consola, agno, ventas);

            if (nuevo != NULL) {
                nuevo->sgte = L;
                L = nuevo;
            }
        } else {
            printf("L%cnea con errores ha sido omitida.\n", 161);
        }
    }

    fclose(archivo);
    return L;
}

Lista anular(Lista L) {
    Lista aux;

    while(L != NULL) {
        aux = L;
        L = L ->sgte;
        aux = borrarNodo(aux);
    }

    return L;
}

void mostrar(Lista L) {
    Lista indice;

    indice = L;

    if(L == NULL) {
        printf("Lista vac%ca.\n\n", 161);
        return;
    }

    while (indice != NULL) {
        printf("T%ctulo: %s, Consola: %s, A%co: %d, Ventas: %.2f\n",
               161, indice->titulo, indice->consola, 164, indice->agno, indice->ventas);
        indice = indice->sgte;
    }

    printf("\n");
}

int largo(Lista L) {
    int largo;
    Lista indice;

    largo = 0;
    indice = L;

    while(indice != NULL) {
        largo++;
        indice = indice->sgte;
    }

    return largo;
}

Lista buscarMasVendidoConsola(Lista L, char *consola) {
    Lista indice, mejor;

    indice = L;
    mejor = NULL;

    while(indice != NULL) {
        if(strcmp(consola, indice->consola) == 0) {
            if(mejor == NULL || indice->ventas > mejor->ventas) {
                mejor = indice;
            }
        }

        indice = indice->sgte;
    }

    return mejor;
}

Lista insertarInicio(Lista L, char *titulo, char *consola, int agno, float ventas) {
    Lista nuevo;

    nuevo = crearNodo(titulo, consola, agno, ventas);

    if(nuevo == NULL) {
        printf("Error al crear el nodo.\n");
        return L;
    }

    nuevo->sgte = L;
    return nuevo;
}

Lista insertarOrdenadoAgno(Lista L, char *titulo, char *consola, int agno, float ventas) {
    Lista nuevo, indice;

    nuevo = crearNodo(titulo, consola, agno, ventas);

    if(nuevo == NULL) {
        printf("Error al crear el nodo.\n");
        return L;
    }

    if(L == NULL) {
        return nuevo;
    }

    if(agno < L->agno) {
        nuevo->sgte = L;
        return nuevo;
    }

    indice = L;

    while(indice->sgte != NULL && agno > indice->sgte->agno) {
        indice = indice->sgte;
    }

    nuevo->sgte = indice->sgte;
    indice->sgte = nuevo;
    return L;
}

Lista invertir(Lista L) {
    Lista M, auxiliar;

    if(L == NULL) {
        return NULL;
    }

    M = NULL;

    while(L != NULL) {
        auxiliar = L;
        L = L->sgte;
        auxiliar->sgte = M;
        M = auxiliar;
    }

    return M;
}

Lista ordenarPorAgno(Lista L) {
    Lista M, aux;

    M = NULL;

    while(L != NULL) {
        aux = L;
        L = L->sgte;
        M = insertarOrdenadoAgno(M, aux->titulo, aux->consola, aux->agno, aux->ventas);
        aux = borrarNodo(aux);
    }

    return M;
}

Lista seleccionarAgno(Lista L, int agno) {
    Lista M, indice;

    M = NULL;

    indice = L;

    while(indice != NULL) {
        if(agno == indice->agno) {
            M = insertarInicio(M, indice->titulo, indice->consola, indice->agno, indice->ventas);
        }

        indice = indice->sgte;
    }

    return M;
}

Lista eliminarConsola(Lista L, char *consola) {
    Lista indice, aux;

    while(L != NULL && strcmp(consola, L->consola) == 0) {
        aux = L;
        L = L->sgte;
        aux = borrarNodo(aux);
    }

    if(L == NULL) {
        return NULL;
    }

    indice = L;

    while(indice->sgte != NULL) {
        if(strcmp(consola, indice->sgte->consola) == 0) {
            aux = indice->sgte;
            indice->sgte = aux->sgte;
            aux = borrarNodo(aux);
        } else {
            indice = indice->sgte;
        }
    }

    return L;
}

float calcularPromedioVentas(Lista L) {
    float suma, promedio;
    int cantidad;
    Lista indice;

    suma = 0;
    cantidad = largo(L);
    indice = L;

    while(indice != NULL) {
        suma = suma + indice->ventas;
        indice = indice->sgte;
    }

    promedio = suma / cantidad;
    return promedio;
}

Lista seleccionarAnteriores(Lista L, int agno) {
    Lista M, indice;

    M = NULL;
    indice = L;

    while(indice != NULL) {
        if(agno > indice->agno) {
            M = insertarInicio(M, indice->titulo, indice->consola, indice->agno, indice->ventas);
        }

        indice = indice->sgte;
    }

    return M;
}

float calcularTotalVentasAgno(Lista L, int agno) {
    float suma;
    Lista indice;
    int cantidad;

    suma = 0;
    cantidad = largo(L);
    indice = L;

    while(indice != NULL) {
        if(agno == indice->agno) {
            suma = suma + indice->ventas;
        }

        indice = indice->sgte;
    }

    return suma;
}

int main() {
    Lista L = NULL, M = NULL, N = NULL, aux = NULL;
    char nombreArchivo[MAX_STR], consola[MAX_STR], titulo[MAX_STR];
    int agno, n, opcion;
    float ventas;

    printf("Ingrese el nombre del archivo: ");
    scanf("%s", &nombreArchivo);
    L = leerArchivo(nombreArchivo);

    while(opcion != 14) {
        opcion = pedirOpcionMenu();

        switch(opcion) {
            case 1:
                // Borrar la lista de juegos.
                L = anular(L);
                mostrar(L);
                break;
            case 2:
                // Mostrar la lista de juegos.
                printf("Lista de juegos:\n");
                mostrar(L);
                break;
            case 3:
                // Contar la cantidad de juegos.
                n = largo(L);
                printf("La lista tiene %d juegos.\n", n);
                break;
            case 4:
                // Buscar el juego más vendido para una consola.
                pedirConsola(consola);
                aux = buscarMasVendidoConsola(L, consola);
                printf("El juego m%cs vendido para %s es %s (%.2f millones).\n", 160, consola, aux->titulo, aux->ventas);
                aux = NULL;
                break;
            case 5:
                // Agregar un nuevo juego al inicio.
                pedirTitulo(titulo);
                pedirConsola(consola);
                agno = pedirAgno();
                ventas = pedirVentas();
                L = insertarInicio(L, titulo, consola, agno, ventas);
                mostrar(L);
                break;
            case 6:
                // Agregar un nuevo juego a una lista ordenada por año.
                pedirTitulo(titulo);
                pedirConsola(consola);
                agno = pedirAgno();
                ventas = pedirVentas();
                L = insertarOrdenadoAgno(L, titulo, consola, agno, ventas);
                mostrar(L);
                break;
            case 7:
                // Invertir la lista de juegos.
                L = invertir(L);
                mostrar(L);
                break;
            case 8:
                // Ordenar la lista de juegos por año.
                L = ordenarPorAgno(L);
                mostrar(L);
                break;
            case 9:
                // Seleccionar juegos lanzados en un año determinado.
                agno = pedirAgno();
                M = seleccionarAgno(L, agno);
                mostrar(M);
                break;
            case 10:
                // Eliminar de la lista los juegos para una consola determinada.
                pedirConsola(consola);
                L = eliminarConsola(L, consola);
                mostrar(L);
                break;
            case 11:
                // Calcular el promedio de unidades vendidas para los juegos de la lista.
                ventas = calcularPromedioVentas(L);
                printf("En promedio, se vendieron %.2f copias de cada juego.\n", ventas);
                break;
            case 12:
                // Seleccionar los juegos lanzados antes de un año determinado.
                agno = pedirAgno();
                N = seleccionarAnteriores(L, agno);
                mostrar(N);
                break;
            case 13:
                // Calcular la cantidad total de unidades vendidas entre todos los juegos lanzados en un año dado.
                agno = pedirAgno();
                ventas = calcularTotalVentasAgno(L, agno);
                printf("Se vendieron %.2f juegos en %d.\n", ventas, agno);
            default:
                break;
        }
    }

    L = anular(L);
    M = anular(M);
    N = anular(N);
    return 0;
}
