#include <stdio.h>

// Função para extrair bits específicos de um número
unsigned char extract_bits(unsigned char num, int start, int length)
{
    unsigned char mask = (1 << length) - 1; // Cria uma máscara com 'length' bits de 1
    return (num >> start) & mask;           // Desloca o número para a direita e aplica a máscara
}

// Função para testar a extração de bits
void test_extract_bits(unsigned char num, int start, int length, unsigned char expected)
{
    unsigned char result = extract_bits(num, start, length);
    printf("Número: %d, Início: %d, Comprimento: %d, Resultado: %d, Esperado: %d\n",
           num, start, length, result, expected);
    if (result == expected)
    {
        printf("Teste bem-sucedido!\n");
    }
    else
    {
        printf("Teste falhou.\n");
    }
}

int main()
{
    // Testes com diferentes valores em decimal
    test_extract_bits(171, 4, 4, 10);  // 1010 1011 -> 1010 (esperado 10)
    test_extract_bits(255, 0, 8, 255); // 1111 1111 -> 1111 1111 (esperado 255)
    test_extract_bits(195, 6, 2, 3);   // 1100 0011 -> 11 (esperado 3)
    test_extract_bits(120, 3, 3, 3);   // 0111 1000 -> 111 (esperado 3)
    test_extract_bits(15, 0, 4, 15);   // 0000 1111 -> 1111 (esperado 15)
    test_extract_bits(165, 1, 3, 2);   // 1010 0101 -> 010 (esperado 2)

    return 0;
}