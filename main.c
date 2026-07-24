#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tamagotchi.h"

int main() {
    Tamagotchi miMascota;
    int opcion;
    time_t tiempoActual = time(NULL);

    srand(tiempoActual);
    limpiarPantalla();

    if (cargarMascota(&miMascota)) {
        // Control critico: si el archivo guardado ya estaba muerto, avisar y limpiar
        if (!miMascota.vivo) {
            printf("Tu mascota anterior habia fallecido. Inicializando una nueva historia...\n");
            remove("tamagotchi.dat");
            printf("Dale un nombre a tu nueva mascota: ");
            scanf("%29s", miMascota.nombre);
            inicializarMascota(&miMascota);
            miMascota.ultimoAcceso = (long long)tiempoActual;
            guardarMascota(miMascota);
        } else {
            printf("=================================\n");
            printf(" ¡Partida cargada exitosamente! \n");
            printf("=================================\n");

            long long segundosPasados = (long long)tiempoActual - miMascota.ultimoAcceso;
            int ciclosTranscurridos = segundosPasados / SEGUNDOS_POR_CICLO;

            if (ciclosTranscurridos > 0) {
                printf("\nHan pasado %d ciclos en tiempo real desde tu ultima visita...\n", ciclosTranscurridos);
                pasarTiempo(&miMascota, ciclosTranscurridos);
                printf("Presiona ENTER para continuar...");
                getchar();
            }
        }
    } else {
        printf("=================================\n");
        printf("     NUEVO TAMAGOTCHI EN C       \n");
        printf("=================================\n");
        printf("Dale un nombre a tu mascota: ");
        scanf("%29s", miMascota.nombre);
        inicializarMascota(&miMascota);
        miMascota.ultimoAcceso = (long long)tiempoActual;
        guardarMascota(miMascota);
    }

    while (miMascota.vivo) {
        limpiarPantalla(); 
        mostrarEstado(miMascota);

        printf("\n--- ACCIONES ---\n");
        printf("1. Alimentar\n");
        printf("2. Jugar\n");
        printf("3. Hacer dormir\n");
        printf("4. Dar medicina\n");
        printf("5. No hacer nada\n");
        printf("6. Salir y Guardar\n");
        printf("Elige una opcion: ");

        if (scanf("%d", &opcion) != 1) {
            printf("\n--- Entrada invalida. Selecciona un numero ---\n");
            while (getchar() != '\n'); 
            printf("Presiona ENTER para continuar...");
            getchar();
            continue;
        }

        if (opcion == 6) {
            miMascota.ultimoAcceso = (long long)time(NULL);
            guardarMascota(miMascota);
            printf("\nPartida guardada de forma segura. ¡Hasta luego!\n");
            break;
        }

        int accionExitosa = 0;

        switch (opcion) {
            case 1: accionExitosa = alimentar(&miMascota); break;
            case 2: accionExitosa = jugar(&miMascota); break;
            case 3: accionExitosa = dormir(&miMascota); break;
            case 4: accionExitosa = medicar(&miMascota); break;
            case 5: printf("\nDejas pasar el tiempo libre...\n"); accionExitosa = 1; break;
            default: printf("\nOpcion invalida.\n"); continue;
        }

        // Solo avanza el ciclo si la accion realmente se ejecuto con exito
        if (accionExitosa) {
            pasarTiempo(&miMascota, 1);

            // Guarda automaticamente el progreso
            if (miMascota.vivo) {
                miMascota.ultimoAcceso = (long long)time(NULL);
                guardarMascota(miMascota);
            }
        }

        printf("\nPresiona ENTER para continuar...");
        getchar(); getchar(); 
    }

    // Gestion explicita de fin de partida si la mascota fallece
    if (!miMascota.vivo) {
        limpiarPantalla();
        mostrarEstado(miMascota);
        printf("\n=================================\n");
        printf(" X_X ¡Oh no! %s ha muerto.\n", miMascota.nombre);
        printf(" Vivio durante %d ciclos.\n", miMascota.edad);
        printf("=================================\n");
        remove("tamagotchi.dat"); // Elimina el archivo corrupto/muerto automaticamente
    }

    return 0;
}
