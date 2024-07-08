#include <stdio.h>

unsigned char extract_bits(unsigned char num, int start, int length)
{
    unsigned char mask = (1 << length) - 1; // Cria uma máscara com 'length' bits de 1
    return (num >> start) & mask;           // Desloca o número para a direita e aplica a máscara
}

int main()
{
    unsigned char num;
    int start, length;

    printf("Insira um numero (0-255): ");
    scanf("%hhu", &num);

    printf("Insira a posicao inicial dos bits a serem extraidos (0-7): ");
    scanf("%d", &start);

    printf("Insira o comprimento dos bits a serem extraidos (1-8): ");
    scanf("%d", &length);

    if (start < 0 || start > 7 || length < 1 || length > 8 || (start + length) > 8)
    {
        printf("Valores de entrada invalidos.\n");
        return 1;
    }

    unsigned char result = extract_bits(num, start, length);
    printf("Numero: %d, Inicio: %d, Comprimento: %d, Resultado: %d\n",
           num, start, length, result);

    return 0;
}