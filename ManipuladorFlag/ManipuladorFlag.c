#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definindo as permissoes como constantes
#define PERM_READ    0x01   // 0000 0001
#define PERM_WRITE   0x02   // 0000 0010
#define PERM_EXECUTE 0x04   // 0000 0100
#define PERM_DELETE  0x08   // 0000 1000
#define PERM_CREATE  0x10   // 0001 0000
#define PERM_RENAME  0x20   // 0010 0000
#define PERM_COPY    0x40   // 0100 0000
#define PERM_MOVE    0x80   // 1000 0000

// Funcao para adicionar uma permissao
void set_permission(unsigned char *flags, unsigned char perm) {
    *flags |= perm;
}

// Funcao para remover uma permissao
void clear_permission(unsigned char *flags, unsigned char perm) {
    *flags &= ~perm;
}

// Funcao para verificar uma permissao
int check_permission(unsigned char flags, unsigned char perm) {
    return flags & perm;
}

// Funcao para imprimir as permissoes
void print_permissions(unsigned char flags) {
    printf("Permissoes atuais: ");
    if (flags & PERM_READ) printf("READ ");
    if (flags & PERM_WRITE) printf("WRITE ");
    if (flags & PERM_EXECUTE) printf("EXECUTE ");
    if (flags & PERM_DELETE) printf("DELETE ");
    if (flags & PERM_CREATE) printf("CREATE ");
    if (flags & PERM_RENAME) printf("RENAME ");
    if (flags & PERM_COPY) printf("COPY ");
    if (flags & PERM_MOVE) printf("MOVE ");
    printf("\n");
}

// Funcao para salvar permissoes em um arquivo
int save_permissions(const char *filename, unsigned char flags) {
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo para escrita");
        return -1;
    }
    fwrite(&flags, sizeof(unsigned char), 1, file);
    fclose(file);
    return 0;
}

// Funcao para carregar permissoes de um arquivo
unsigned char load_permissions(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo para leitura");
        exit(EXIT_FAILURE);
    }
    unsigned char flags;
    fread(&flags, sizeof(unsigned char), 1, file);
    fclose(file);
    return flags;
}

// Funcao para tentar escrever uma mensagem no arquivo
int write_message(const char *filename, const char *message) {
    FILE *file = fopen(filename, "a"); // Abrir em modo de adicao
    if (file == NULL) {
        perror("Erro ao abrir o arquivo para escrita");
        return -1;
    }
    fprintf(file, "%s\n", message);
    fclose(file);
    return 0;
}

int main() {
    const char *filename = "permissions.txt";
    unsigned char permissions = 0; // Nenhuma permissao inicialmente
    int opcao;

    // Menu para escolher as permissoes iniciais a serem adicionadas
    do {
        printf("\nEscolha as permissoes iniciais que deseja adicionar:\n");
        printf("1. READ\n");
        printf("2. WRITE\n");
        printf("3. EXECUTE\n");
        printf("4. DELETE\n");
        printf("5. CREATE\n");
        printf("6. RENAME\n");
        printf("7. COPY\n");
        printf("8. MOVE\n");
        printf("Digite o numero da permissao (0 para parar): ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                set_permission(&permissions, PERM_READ);
                printf("Permissao READ adicionada.\n");
                break;
            case 2:
                set_permission(&permissions, PERM_WRITE);
                printf("Permissao WRITE adicionada.\n");
                break;
            case 3:
                set_permission(&permissions, PERM_EXECUTE);
                printf("Permissao EXECUTE adicionada.\n");
                break;
            case 4:
                set_permission(&permissions, PERM_DELETE);
                printf("Permissao DELETE adicionada.\n");
                break;
            case 5:
                set_permission(&permissions, PERM_CREATE);
                printf("Permissao CREATE adicionada.\n");
                break;
            case 6:
                set_permission(&permissions, PERM_RENAME);
                printf("Permissao RENAME adicionada.\n");
                break;
            case 7:
                set_permission(&permissions, PERM_COPY);
                printf("Permissao COPY adicionada.\n");
                break;
            case 8:
                set_permission(&permissions, PERM_MOVE);
                printf("Permissao MOVE adicionada.\n");
                break;
            case 0:
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
                break;
        }
    } while (opcao != 0);

    // Exibir permissoes selecionadas
    printf("\nPermissoes iniciais selecionadas:\n");
    print_permissions(permissions);

    // Salvando permissoes no arquivo
    if (save_permissions(filename, permissions) == 0) {
        printf("\nPermissoes salvas com sucesso no arquivo '%s'.\n", filename);
    } else {
        printf("\nFalha ao salvar permissoes no arquivo '%s'.\n", filename);
        return 1;
    }

    // Carregando permissoes do arquivo
    permissions = load_permissions(filename);
    printf("\nPermissoes carregadas do arquivo '%s':\n", filename);
    print_permissions(permissions);

    // Verificando permissao de escrita para escrever uma mensagem no arquivo
    if (check_permission(permissions, PERM_WRITE)) {
        char message[100];
        printf("\nDigite o texto que deseja escrever no arquivo: ");
        getchar(); // Limpar o buffer de entrada
        fgets(message, sizeof(message), stdin);
        // Remover o caractere de nova linha do final da string, se presente
        char *pos;
        if ((pos = strchr(message, '\n')) != NULL) {
            *pos = '\0';
        }

        if (write_message(filename, message) == 0) {
            printf("Mensagem escrita com sucesso no arquivo '%s'.\n", filename);
        } else {
            printf("Falha ao escrever mensagem no arquivo '%s'.\n", filename);
        }
    } else {
        printf("\nPermissao de escrita nao concedida. Nao e possivel escrever no arquivo '%s'.\n", filename);
    }

    // Carregando permissoes do arquivo novamente para verificacao final
    permissions = load_permissions(filename);
    printf("\nPermissoes carregadas do arquivo '%s' (final):\n", filename);
    print_permissions(permissions);

    return 0;
}
