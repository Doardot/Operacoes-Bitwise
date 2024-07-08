#include <stdio.h>
#include <stdlib.h>

// Definindo as permissões como constantes
#define PERM_READ 0x01    // 0000 0001
#define PERM_WRITE 0x02   // 0000 0010
#define PERM_EXECUTE 0x04 // 0000 0100
#define PERM_DELETE 0x08  // 0000 1000
#define PERM_CREATE 0x10  // 0001 0000
#define PERM_RENAME 0x20  // 0010 0000
#define PERM_COPY 0x40    // 0100 0000
#define PERM_MOVE 0x80    // 1000 0000

// Função para adicionar uma permissão
void set_permission(unsigned char *flags, unsigned char perm)
{
    *flags |= perm;
}

// Função para remover uma permissão
void clear_permission(unsigned char *flags, unsigned char perm)
{
    *flags &= ~perm;
}

// Função para verificar uma permissão
int check_permission(unsigned char flags, unsigned char perm)
{
    return flags & perm;
}

// Função para imprimir as permissões
void print_permissions(unsigned char flags)
{
    printf("Permissoes atuais: ");
    if (flags & PERM_READ)
        printf("READ ");
    if (flags & PERM_WRITE)
        printf("WRITE ");
    if (flags & PERM_EXECUTE)
        printf("EXECUTE ");
    if (flags & PERM_DELETE)
        printf("DELETE ");
    if (flags & PERM_CREATE)
        printf("CREATE ");
    if (flags & PERM_RENAME)
        printf("RENAME ");
    if (flags & PERM_COPY)
        printf("COPY ");
    if (flags & PERM_MOVE)
        printf("MOVE ");
    printf("\n");
}

// Função para salvar permissões em um arquivo
int save_permissions(const char *filename, unsigned char flags)
{
    FILE *file = fopen(filename, "wb");
    if (file == NULL)
    {
        perror("Erro ao abrir o arquivo para escrita");
        return -1;
    }
    fwrite(&flags, sizeof(unsigned char), 1, file);
    fclose(file);
    return 0;
}

// Função para carregar permissões de um arquivo
unsigned char load_permissions(const char *filename)
{
    FILE *file = fopen(filename, "rb");
    if (file == NULL)
    {
        perror("Erro ao abrir o arquivo para leitura");
        exit(EXIT_FAILURE);
    }
    unsigned char flags;
    fread(&flags, sizeof(unsigned char), 1, file);
    fclose(file);
    return flags;
}

// Função para tentar escrever uma mensagem no arquivo
int write_message(const char *filename, const char *message)
{
    FILE *file = fopen(filename, "a"); // Abrir em modo de adição
    if (file == NULL)
    {
        perror("Erro ao abrir o arquivo para escrita");
        return -1;
    }
    fprintf(file, "%s\n", message);
    fclose(file);
    return 0;
}

void run_test()
{
    const char *filename = "permissions.txt";
    unsigned char permissions = 0; // Nenhuma permissão inicialmente

    // Adicionando permissões
    set_permission(&permissions, PERM_READ);
    set_permission(&permissions, PERM_WRITE);
    set_permission(&permissions, PERM_EXECUTE);
    printf("Apos adicionar READ, WRITE e EXECUTE:\n");
    print_permissions(permissions);

    // Salvando permissões no arquivo
    if (save_permissions(filename, permissions) == 0)
    {
        printf("Permissoes salvas com sucesso.\n");
    }
    else
    {
        printf("Falha ao salvar permissoes.\n");
    }

    // Carregando permissões do arquivo
    permissions = load_permissions(filename);
    printf("Permissoes carregadas do arquivo:\n");
    print_permissions(permissions);

    // Removendo a permissão de escrita
    clear_permission(&permissions, PERM_WRITE);
    printf("Apos remover WRITE:\n");
    print_permissions(permissions);

    // Tentando salvar permissões no arquivo sem permissão de escrita
    if (check_permission(permissions, PERM_WRITE))
    {
        if (save_permissions(filename, permissions) == 0)
        {
            printf("Permissoes salvas com sucesso.\n");
        }
        else
        {
            printf("Falha ao salvar permissoes.\n");
        }
    }
    else
    {
        printf("Permissao de escrita nao concedida. Nao e possivel salvar o arquivo.\n");
    }

    // Tentando escrever uma mensagem no arquivo sem permissão de escrita
    if (check_permission(permissions, PERM_WRITE))
    {
        if (write_message(filename, "Esta eh uma mensagem de teste.") == 0)
        {
            printf("Mensagem escrita com sucesso.\n");
        }
        else
        {
            printf("Falha ao escrever mensagem.\n");
        }
    }
    else
    {
        printf("Permissao de escrita nao concedida. Nao eh possivel escrever no arquivo.\n");
    }

    // Carregando permissões do arquivo novamente para verificação final
    permissions = load_permissions(filename);
    printf("Permissoes carregadas do arquivo (final):\n");
    print_permissions(permissions);
}

int main()
{
    run_test();
    return 0;
}
