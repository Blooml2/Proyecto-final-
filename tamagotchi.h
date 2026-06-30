#ifndef TAMAGOTCHI_H
#define TAMAGOTCHI_H

typedef struct {
    char nombre[30];
    int hambre;      // 0 = lleno, 100 = hambriento
    int energia;     // 100 = despierto, 0 = agotado
    int felicidad;   // 100 = feliz, 0 = triste
    int enfermo;     // 0 = sano, 1 = enfermo
    int edad;        // Ciclos de vida transcurridos
    int vivo;        // 1 = si, 0 = no
    long long ultimoAcceso; // Timestamp Unix del ultimo guardado
} Tamagotchi;

// Declaracion de Funciones 
void inicializarMascota(Tamagotchi *t);
void dibujarBarra(const char *label, int val, int max);
void dibujarMascota(Tamagotchi t);
void mostrarEstado(Tamagotchi t);
void pasarTiempo(Tamagotchi *t, int ciclos);
void alimentar(Tamagotchi *t);
void jugar(Tamagotchi *t);
void dormir(Tamagotchi *t);
void medicar(Tamagotchi *t);

// Persistencia y Utilidades
void guardarMascota(Tamagotchi t);
int cargarMascota(Tamagotchi *t);
void limpiarPantalla();

#endif
