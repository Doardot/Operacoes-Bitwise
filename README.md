## Operações Bitwise

O presente trabalho consiste na pesquisa e escrita de um documento sobre os operadores bitwise, e no desenvolvimento de dois programas em C, que visam resolver os respectivos problemas:
- Manipulação de flags em um sistema de permissões
- Criação de uma máscara de bits para extração de bits específicos de um número

## Como executar
Para executar o projeto, é necessário ter um compilador C instalado na máquina.

### Como instalar
#### No Windows
   - Instale um compilador C como o MinGW:
   - Baixe o instalador do MinGW no [site oficial do MinGW](https://osdn.net/projects/mingw/releases/).
   - Siga as instruções de instalação.
   - Adicione o MinGW à variável de ambiente PATH do sistema.
   
#### No linux
   - Instale o GCC (GNU Compiler Collection):
   - Abra um terminal.
   - Execute o comando: `sudo apt-get update` (para atualizar a lista de pacotes).
   - Execute o comando: `sudo apt-get install gcc` (para instalar o GCC).

### Como compilar e executar 
1. Clone o repositório.
2. Abra o projeto na IDE de sua preferência.
   - Caso esteja utilizando o Visual Studio Code, você pode usar a extensão "C/C++" da Microsoft.
   - Caso esteja utilizando o Code::Blocks ou qualquer outra IDE para C, não será necessário baixar nenhuma extensão adicional.

3. Compile o arquivo C:
   - Abra o prompt de comando.
   - Navegue até o diretório do projeto.
   - Compile os arquivos da pasta desejada
   - Para compilar os arquivos na pasta `ManipuladorFlag`:
   ```bash
   cd ManipuladorFlag
   gcc -o ManipuladorFlag ManipuladorFlag.c
   gcc -o ManipuladorFlagExemplo ManipuladorFlagExemplo.c
   ```
   - Para compilar o arquivo na pasta `MascaraDeBits`:
   ```bash
   cd MascaraDeBits
   gcc -o MascaraDeBits MascaraDeBits.c
   ```

4. Execute o programa compilado:
   - No diretório `ManipuladorFlag`:
   ```bash
   .\ManipuladorFlag
   .\ManipuladorFlagExemplo
   ```
   - No diretório `MascaraDeBits`:
   ```bash
   .\MascaraDeBits
   ```

## Tecnologias
- C

## Autores

- Eduardo Tavares
- <a href="https://github.com/Doardot">GitHub</a></li>

- Vicenzo Frusciante
- <a href="https://github.com/VicenzoMF">GitHub</a></li>
