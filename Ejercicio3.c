#include <stdio.h>  // Permite usar printf y fgets.
#include <stdlib.h> // Permite usar rand y srand.
#include <string.h> // Permite usar strlen, strcspn y strcpy.
#include <time.h>   // Permite usar time.

// Convierte un bit en una representación de voltaje.
void transmitir_bit_nrz(int bit)
{
    if (bit == 1)
    {
        printf("[ +5V ] ");
    }
    else
    {
        printf("[ -5V ] ");
    }
}

// Imprime los 8 bits de un carácter.
void imprimir_bits(unsigned char caracter)
{
    for (int posicion = 7; posicion >= 0; posicion--)
    {
        int bit = (caracter >> posicion) & 1;
        printf("%d", bit);
    }
}

// Imprime la señal de voltaje correspondiente a los bits de un carácter.
void imprimir_senal(unsigned char caracter)
{
    for (int posicion = 7; posicion >= 0; posicion--)
    {
        int bit = (caracter >> posicion) & 1;
        transmitir_bit_nrz(bit);
    }
}

// Muestra cada carácter con sus bits y sus señales.
void mostrar_transmision(const char texto[])
{
    size_t longitud = strlen(texto);

    for (size_t i = 0; i < longitud; i++)
    {
        unsigned char caracter = (unsigned char)texto[i];

        printf("Caracter '%c' (ASCII %u):\n", texto[i], caracter);

        printf("Bits:         ");
        imprimir_bits(caracter);
        printf("\n");

        printf("Senal fisica: ");
        imprimir_senal(caracter);
        printf("\n\n");
    }
}

int main(void)
{
    char texto_original[100];
    char texto_recibido[100];

    printf("Introduce una palabra para transmitir: ");

    fgets(texto_original, sizeof(texto_original), stdin);

    texto_original[strcspn(texto_original, "\n")] = '\0';

    if (strlen(texto_original) == 0)
    {
        printf("No se introdujo ningun texto.\n");
        return 1;
    }

    strcpy(texto_recibido, texto_original);

    printf("\n--- TRANSMISION ORIGINAL ---\n\n");

    mostrar_transmision(texto_original);

    size_t longitud = strlen(texto_recibido);
    size_t total_bits = longitud * 8;

    srand((unsigned int)time(NULL));

    size_t bit_global = (size_t)(rand() % total_bits);

    size_t indice_caracter = bit_global / 8;

    int bit_dentro_caracter = bit_global % 8;

    int posicion_real = 7 - bit_dentro_caracter;

    texto_recibido[indice_caracter] ^= (1u << posicion_real);

    printf("\n--- TRANSMISION DESPUES DEL BIT-FLIP ---\n\n");

    mostrar_transmision(texto_recibido);

    printf("--- RESULTADO ---\n\n");

    printf("Texto transmitido: %s\n", texto_original);
    printf("Texto recibido:    %s\n", texto_recibido);

    return 0;
}