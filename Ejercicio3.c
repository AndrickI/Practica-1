#include <stdio.h>  // Permite utilizar printf() y fgets().
#include <stdlib.h> // Permite utilizar rand() y srand().
#include <string.h> // Permite utilizar strlen(), strcspn() y strcpy().
#include <time.h>   // Permite utilizar time() para obtener el tiempo actual.

// Convierte un bit en una representación simulada de voltaje.
void transmitir_bit_nrz(int bit) // Recibe como parámetro un bit con valor 0 o 1.
{
    if (bit == 1) // Comprueba si el bit recibido tiene valor 1.
    {
        printf("[ +5V ] "); // Representa el bit 1 mediante una señal de +5 Volts.
    }
    else // Se ejecuta cuando el bit recibido no tiene valor 1, es decir, cuando vale 0.
    {
        printf("[ -5V ] "); // Representa el bit 0 mediante una señal de -5 Volts.
    }
}

// Imprime los 8 bits que forman un carácter.
void imprimir_bits(unsigned char caracter)            // Recibe un carácter para mostrar su representación binaria.
{                                                     // Inicio de la función imprimir_bits.
    for (int posicion = 7; posicion >= 0; posicion--) // Recorre las 8 posiciones del byte, desde la 7 hasta la 0.
    {
        int bit = (caracter >> posicion) & 1; // Desplaza el carácter y obtiene únicamente el bit de la posición actual.
        printf("%d", bit);                    // Imprime el bit obtenido, que puede ser 0 o 1.
    }
}

// Imprime la representación de voltaje correspondiente a los 8 bits de un carácter.
void imprimir_senal(unsigned char caracter) // Recibe un carácter para convertir sus bits en señales simuladas.
{
    for (int posicion = 7; posicion >= 0; posicion--) // Recorre las 8 posiciones del carácter desde la 7 hasta la 0.
    {
        int bit = (caracter >> posicion) & 1; // Extrae el bit que se encuentra en la posición actual.
        transmitir_bit_nrz(bit);              // Envía el bit a la función que lo representa como +5V o -5V.
    }
}

// Muestra cada carácter del texto junto con sus bits y sus señales físicas simuladas.
void mostrar_transmision(const char texto[]) // Recibe el texto completo que se desea mostrar.
{
    size_t longitud = strlen(texto); // Obtiene la cantidad de caracteres que contiene el texto.

    for (size_t i = 0; i < longitud; i++) // Recorre cada carácter del texto desde la primera posición hasta la última.
    {
        unsigned char caracter = (unsigned char)texto[i]; // Guarda el carácter actual como un valor sin signo.

        printf("Caracter '%c' (ASCII %u):\n", texto[i], caracter); // Imprime el carácter actual y su valor ASCII.

        printf("Bits:         "); // Imprime una etiqueta antes de mostrar la representación binaria.
        imprimir_bits(caracter);  // Llama a la función que imprime los 8 bits del carácter.
        printf("\n");             // Realiza un salto de línea después de mostrar los bits.

        printf("Senal fisica: "); // Imprime una etiqueta antes de mostrar las señales de voltaje.
        imprimir_senal(caracter); // Llama a la función que convierte cada bit en +5V o -5V.
        printf("\n\n");           // Imprime dos saltos de línea para separar visualmente cada carácter.
    }
}

// Función principal del programa.
int main(void) // Punto de inicio de la ejecución del programa.
{
    char texto_original[100]; // Arreglo que almacena el texto original introducido por el usuario.
    char texto_recibido[100]; // Arreglo que almacena una copia del texto que posteriormente sufrirá el Bit-Flip.

    printf("Introduce una palabra para transmitir: "); // Solicita al usuario el texto que desea transmitir.

    fgets(texto_original, sizeof(texto_original), stdin); // Lee desde el teclado hasta 99 caracteres y los guarda en texto_original.

    texto_original[strcspn(texto_original, "\n")] = '\0'; // Sustituye el salto de línea generado por Enter por el fin de cadena.

    if (strlen(texto_original) == 0) // Comprueba si el usuario introdujo una cadena vacía.
    {
        printf("No se introdujo ningun texto.\n"); // Informa al usuario que no se recibió ningún texto.
        return 1;                                  // Termina el programa indicando que ocurrió un problema con la entrada.
    }
    strcpy(texto_recibido, texto_original); // Copia el texto original para poder modificar la copia sin alterar el original.
    printf("\n--- TRANSMISION ORIGINAL ---\n\n");
    mostrar_transmision(texto_original); // Muestra los caracteres, bits y señales del mensaje original.

    size_t longitud = strlen(texto_recibido); // Obtiene la cantidad de caracteres presentes en el mensaje.
    size_t total_bits = longitud * 8;         // Calcula el número total de bits considerando 8 bits por carácter.
    srand((unsigned int)time(NULL));          // Utiliza el tiempo actual como semilla para generar números pseudoaleatorios.

    size_t bit_global = (size_t)(rand() % total_bits); // Selecciona aleatoriamente uno de los bits de todo el mensaje.
    size_t indice_caracter = bit_global / 8;           // Calcula a qué carácter del texto pertenece el bit seleccionado.

    int bit_dentro_caracter = bit_global % 8;    // Calcula qué posición ocupa el bit dentro de los 8 bits del carácter.
    int posicion_real = 7 - bit_dentro_caracter; // Convierte la posición visual izquierda-derecha a la posición binaria real.

    texto_recibido[indice_caracter] ^= (1u << posicion_real); // Invierte únicamente el bit seleccionado utilizando XOR.

    printf("\n--- TRANSMISION DESPUES DEL BIT-FLIP ---\n\n"); // Imprime el encabezado de la transmisión después de modificar un bit.
    mostrar_transmision(texto_recibido);                      // Muestra nuevamente caracteres, bits y señales después del Bit-Flip.
    printf("--- RESULTADO ---\n\n");                          // Imprime el encabezado de la comparación final.
    printf("Texto transmitido: %s\n", texto_original);        // Muestra el texto que originalmente se deseaba transmitir.
    printf("Texto recibido:    %s\n", texto_recibido);        // Muestra el texto obtenido después de modificar un bit.

    return 0; // Finaliza correctamente la ejecución del programa.
}