# 👾 Motor de Simulación Tamagotchi

> **Contextualización del Problema**
> El objetivo principal de este proyecto es desarrollar un simulador de mascota virtual (Tamagotchi) basado en estados finitos y lógica determinista, diseñado para ejecutarse en una interfaz de línea de comandos (CLI) multiplataforma. El sistema funciona como un ciclo de vida continuo donde una entidad dinámica (la mascota) debe mantenerse con vida balanceando sus estadísticas vitales interconectadas (Hambre, Energía y Felicidad) mediante reglas de desgaste continuo y progresión del tiempo en segundo plano (offline).

---

## 📋 Especificaciones y Mecánicas del Sistema

1. **🐣 Creación de la Mascota:** El sistema debe permitir al usuario asignar un nombre alfanumérico personalizado de hasta **30 caracteres** a una nueva mascota durante la primera ejecución del programa.

2. **📊 Inicialización de Atributos Base:** El sistema debe configurar automáticamente a la nueva mascota con los siguientes valores vitales por defecto:
   * **Hambre:** 20%
   * **Energía:** 80%
   * **Felicidad:** 60%
   * **Edad:** 0 ciclos
   * **Estado de enfermedad:** Inactivo
   * **Estado de vida:** Activo

3. **☠️ Control del Estado de Muerte:** El sistema debe evaluar constantemente los límites vitales en cada actualización. Si el Hambre alcanza el **100%**, la Energía cae a **0%**, o la Felicidad disminuye a **0%**, el estado de la mascota cambiará permanentemente a "Fallecido", terminando el ciclo del juego.

4. **⏳ Progresión del Tiempo Activo:** El sistema debe permitir que cada acción interactiva exitosa que el usuario elija dentro del menú principal haga avanzar el reloj interno del sistema en exactamente **1 ciclo de simulación**.

5. **🌙 Simulación de Tiempo en Ausencia (Progreso Offline):** Al arrancar, el sistema debe leer el reloj de la computadora, calcular la diferencia en segundos transcurridos desde el último guardado, convertir dicho delta en ciclos de simulación y aplicar de forma retroactiva el impacto en las estadísticas de la mascota.

6. **📉 Tasas Estadísticas de Desgaste:** Durante un ciclo de tiempo estándar, el sistema aplicará de forma automática:
   * Incremento de **10 puntos** en el Hambre.
   * Reducción de **8 puntos** en la Energía.
   * Reducción de **5 puntos** en la Felicidad.

7. **🦠 Matriz de Infección y Enfermedad:** Si cualquiera de las estadísticas críticas supera los umbrales de descuido (Hambre > 70%, Energía < 30% o Felicidad < 30%), el sistema ejecutará un cálculo de probabilidad aleatoria (**45% de probabilidad**) para activar el estado "Enfermo". Mientras este estado esté activo, todas las tasas de desgaste por ciclo se **duplicarán**.

8. **🍖 Mecanismo de Nutrición (Alimentar):** El sistema debe permitir al usuario alimentar a la mascota para **reducir** el nivel de Hambre en 25 puntos e **incrementar** la Felicidad en 5 puntos. Si el valor de Hambre ya se encuentra en 0%, la acción debe ser rechazada informando al usuario.

9. **🎾 Mecanismo de Recreación (Jugar):** El sistema debe permitir al usuario jugar con la mascota para **aumentar** su Felicidad en 30 puntos, **restando** 20 puntos de Energía e **incrementando** el Hambre en 15 puntos. El sistema bloqueará esta acción si la mascota se encuentra enferma o si su nivel de Energía es inferior a 25 puntos.

10. **💤 Mecanismo de Descanso (Dormir):** El sistema debe permitir al usuario poner a dormir a la mascota para **restaurar** su Energía en 45 puntos e **incrementar** el Hambre en 10 puntos. Esta acción debe ser bloqueada si la Energía ya se encuentra en su capacidad máxima del 100%.

11. **💊 Mecanismo de Atención Médica (Curar):** El sistema debe permitir al usuario administrar medicina a la mascota para **desactivar** el estado "Enfermo" e **incrementar** la Felicidad en 15 puntos. Si la mascota ya se encuentra sana, la acción debe ser rechazada.

12. **🚧 Restricción de Límites Estrictos:** El sistema debe garantizar que ninguna acción de juego o procesamiento de desgaste cause que los valores de Hambre, Energía o Felicidad desborden los límites lógicos absolutos de entre **0% y 100%**.

13. **💾 Guardado Automático del Progreso:** El juego debe guardar por sí mismo la información de la mascota (nombre, estadísticas y la hora actual) en un archivo llamado `tamagotchi.dat` cada vez que el jugador realice una acción con éxito o decida salir del juego, evitando que se pierda el progreso al cerrar el programa.

14. **🗑️ Depuración de Archivos por Fallecimiento:** Si el estado de la mascota cambia a "Fallecido", el sistema debe **eliminar físicamente** el archivo de guardado local (`tamagotchi.dat`) para asegurar que el usuario sea redirigido forzosamente a la creación de una nueva mascota en la siguiente ejecución.

15. **🖥️ Gestión de Interfaz Multiplataforma:** El sistema debe identificar el entorno operativo de ejecución para limpiar la terminal de comandos de forma dinámica (`cls` en sistemas Windows y `clear` en sistemas Unix/Linux/macOS), asegurando que la interfaz se visualice de forma estática y limpia sin acumular texto hacia abajo.

16. **🛡️ Integridad ante Ausencia de Datos:** El sistema debe gestionar de manera segura los flujos de lectura de archivos. En caso de que el archivo de guardado local no exista o se encuentre dañado, el sistema debe manejar la excepción redirigiendo al flujo de inicialización en lugar de provocar un cierre forzado del software.

17. **✅ Tolerancia a Errores de Entrada (Robustez):** El sistema debe validar que los datos ingresados por el usuario en el teclado coincidan con el tipo esperado por el menú (enteros). Si se introducen caracteres alfabéticos o símbolos inválidos, el sistema debe limpiar el búfer de entrada, omitir la acción errónea y solicitar el dato nuevamente sin congelar el programa.

18. **⏱️ Escalabilidad del Factor de Tiempo:** La constante de conversión que define cuántos segundos del mundo real equivalen a 1 ciclo de juego (ej. 30 segundos) debe estar centralizada como una **macro o constante global**, permitiendo ajustar la velocidad de la simulación en fases de desarrollo futuras sin alterar la lógica interna de las funciones.
