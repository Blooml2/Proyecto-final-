#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tamagotchi.h"

void limpiarPantalla() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void inicializarMascota(Tamagotchi *t) {
    t->hambre = 20;
    t->energia = 80;
    t->felicidad = 60;
    t->enfermo = 0;
    t->edad = 0;
    t->vivo = 1;
}

void dibujarBarra(const char *label, int val, int max) {
    int caracteres = 10; 
    int llenos = (val * caracteres) / max;
    if (llenos > caracteres) llenos = caracteres;
    if (llenos < 0) llenos = 0;

    printf("%-10s [", label);
    for (int i = 0; i < caracteres; i++) {
        if (i < llenos) printf("#");
        else printf(".");
    }
    printf("] %d/%d\n", val, max);
}

void dibujarMascota(Tamagotchi t) {
    if (!t.vivo) {
        printf("    -------    \n");
        printf("   /       \\  \n");
        printf("  /  R.I.P  \\ \n");
        printf("  |  %-5s  | \n", t.nombre);
        printf("  |         |  \n");
        printf("  -----------  \n");
    } else if (t.enfermo) {
        printf("   (x_x)  🤢 \n");
        printf("   <|  |>    \n");
        printf("   _|_|_     \n");
    } else if (t.energia < 30) {
        printf("    zzz      \n");
        printf("   (u_u)  💤 \n");
        printf("   <|  |>    \n");
        printf("   _|_|_     \n");
    } else if (t.hambre > 70) {
        printf("    hambre!  \n");
        printf("   (•_•)  🍖 \n");
        printf("   <(  )>    \n");
        printf("   _|_|_     \n");
    } else { 
        printf("     !!      \n");
        printf("   (^.^)  😊 \n");
        printf("   <|  |>    \n");
        printf("   _|_|_     \n");
    }
}

void mostrarEstado(Tamagotchi t) {
    printf("=================================\n");
    printf(" Mascota: %s | Edad: %d\n", t.nombre, t.edad);
    printf(" Estado:  %s\n", t.enfermo ? "ENFERMO (Necesita medicina)" : "Sano");
    printf("=================================\n");
    
    dibujarMascota(t);
    
    printf("---------------------------------\n");
    dibujarBarra("Hambre", t.hambre, 100);
    dibujarBarra("Energia", t.energia, 1000); // Mapped out of 100 max limits
    dibujarBarra("Felicidad", t.felicidad, 100);
    printf("=================================\n");
}

void pasarTiempo(Tamagotchi *t, int ciclos) {
    if (ciclos <= 0) return;
    int multiplicador = t->enfermo ? 2 : 1;

    t->edad += ciclos;
    t->hambre += (10 * multiplicador * ciclos);
    t->energia -= (8 * multiplicador * ciclos);
    t->felicidad -= (5 * multiplicador * ciclos);

    // Probabilidad de enfermarse durante descuidos
    if (!t->enfermo && (t->hambre > 70 || t->energia < 30 || t->felicidad < 30)) {
        if ((rand() % 100) < 45) { 
            t->enfermo = 1;
        }
    }

    // CONTROL DE LIMITES (Evita errores de valores mayores a 100 o menores a 0)
    if (t->hambre > 100)     t->hambre = 100;
    if (t->hambre < 0)       t->hambre = 0;
    if (t->energia > 100)    t->energia = 100;
    if (t->energia < 0)      t->energia = 0;
    if (t->felicidad > 100)  t->felicidad = 100;
    if (t->felicidad < 0)    t->felicidad = 0;

    // Condiciones fatales
    if (t->hambre >= 100 || t->energia <= 0 || t->felicidad <= 0) {
        t->vivo = 0;
    }
}

void alimentar(Tamagotchi *t) {
    if (t->hambre <= 0) {
        printf("\n%s ya esta completamente lleno.\n", t->nombre);
        return;
    }
    printf("\nAlimentas a %s. ¡Nam nam!\n", t->nombre);
    t->hambre -= 25;
    t->felicidad += 5;
    
    if (t->hambre < 0) t->hambre = 0;
    if (t->felicidad > 100) t->felicidad = 100;
}

void jugar(Tamagotchi *t) {
    if (t->energia < 25) {
        printf("\n%s esta muy cansado para jugar.\n", t->nombre);
        return;
    }
    if (t->enfermo) {
        printf("\n%s se siente mal para jugar.\n", t->nombre);
        return;
    }

    printf("\nJuegas con %s.\n", t->nombre);
    t->felicidad += 30;
    t->energia -= 20;
    t->hambre += 15;

    if (t->felicidad > 100) t->felicidad = 100;
    if (t->hambre > 100)    t->hambre = 100;
    if (t->energia < 0)     t->energia = 0;
}

void dormir(Tamagotchi *t) {
    if (t->energia >= 100) {
        printf("\n%s no tiene sueno.\n", t->nombre);
        return;
    }
    printf("\n%s toma una siesta. Zzz...\n", t->nombre);
    t->energia += 45;
    t->hambre += 10;

    if (t->energia > 100) t->energia = 100;
    if (t->hambre > 100)    t->hambre = 100;
}

void medicar(Tamagotchi *t) {
    if (!t->enfermo) {
        printf("\n%s no necesita medicina.\n", t->nombre);
        return;
    }
    printf("\nLe das medicina a %s.\n", t->nombre);
    t->enfermo = 0;
    t->felicidad += 15;
    if (t->felicidad > 100) t->felicidad = 100;
}

void guardarMascota(Tamagotchi t) {
    FILE *archivo = fopen("tamagotchi.dat", "wb");
    if (archivo != NULL) {
        fwrite(&t, sizeof(Tamagotchi), 1, archivo);
        fclose(archivo);
    }
}

int cargarMascota(Tamagotchi *t) {
    FILE *archivo = fopen("tamagotchi.dat", "rb");
    if (archivo == NULL) return 0;
    fread(t, sizeof(Tamagotchi), 1, archivo);
    fclose(archivo);
    return 1; 
}
