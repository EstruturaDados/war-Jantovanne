// ============================================================================
//         PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO
// ============================================================================
//        
// ============================================================================
//
// OBJETIVOS:
// - Modularizar completamente o código em funções especializadas.
// - Implementar um sistema de missões para um jogador.
// - Criar uma função para verificar se a missão foi cumprida.
// - Utilizar passagem por referência (ponteiros) para modificar dados e
//   passagem por valor/referência constante (const) para apenas ler.
// - Foco em: Design de software, modularização, const correctness, lógica de jogo.
//
// ============================================================================

// Inclusão das bibliotecas padrão necessárias para entrada/saída, alocação de memória, manipulação de strings e tempo.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <locale.h>

// --- Constantes Globais ---
// Definem valores fixos para o número de territórios, missões e tamanho máximo de strings, facilitando a manutenção.

#define TAM_STRING 50

// --- Estrutura de Dados ---
// Define a estrutura para um território, contendo seu nome, a cor do exército que o domina e o número de tropas.

typedef struct
{
    char nome[TAM_STRING];
    char cor[TAM_STRING];
    int tropas;
    char missao[TAM_STRING];
    int IDmissao;
} territorios;

// --- Protótipos das Funções ---
// Declarações antecipadas de todas as funções que serão usadas no programa, organizadas por categoria.
// Funções de setup e gerenciamento de memória:
void liberarMemoria(territorios* mapa);
// Funções de interface com o usuário:
void exibirMapa(const territorios* mapa, int total);
// Funções de lógica principal do jogo:
void FaseDeAtaque(territorios* mapa, int total);
// Sorteia e designa uma missão para o atacante.
void sortearMissao(territorios* mapa, int indice, int atacante);
// verifica se o jogador cumpriu a missão sorteada.
void verificarVitoria(territorios* mapa, int atacante, int defensor, int dadoAtacante, int dadoDefensor);
// função para cadastro dos territórios:
void cadastroTerritorios(territorios* mapa, int total);
// --- Função Principal (main) ---
// Função principal que orquestra o fluxo do jogo, chamando as outras funções em ordem.
int main() {
    setlocale(LC_ALL, ".UTF-8"); // Configura o locale para português, permitindo a exibição correta de caracteres acentuados.

    srand(time(NULL)); // Inicializa a semente para geração de números aleatórios.

    printf("===============================\n");
    printf(" BEM VINDO AO WAR  \n");
    printf("===============================");

    printf("\nIniciando o cadastro dos territórios...\n\n");

int total_territorios;
    printf("========================================\n");
    printf("Quantos territórios deseja cadastrar?\n");
    printf("========================================\n");
    setbuf(stdin, NULL);
    scanf("%d", &total_territorios);

    // Aloca dinamicamente a memória para o vetor de territórios usando calloc, garantindo que a memória seja inicializada com zeros.
    territorios *t =  (territorios*) calloc(total_territorios, sizeof(territorios));
    // Verifica se a alocação foi bem-sucedida.
if (t == NULL)
{
    printf("Erro ao alocar memória para o mapa.\n");
    return 1;
}
    // Chamada da função de cadastro.
    cadastroTerritorios(t, total_territorios);

    // Exibe o mapa após o cadastro.
    exibirMapa(t, total_territorios);

    // Loop principal do jogo, onde o jogador pode escolher entre atacar, exibir mapa ou sair.
    int opcao; 

    do
    {
        printf("===============================");
        printf("\n MENU PRINCIPAL \n");
        printf("===============================\n");
        printf("1. Fase de Ataque\n");
        printf("2. Mostrar Mapa\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            FaseDeAtaque(t, total_territorios);
            break;
        
        case 2:
            exibirMapa(t, total_territorios);
            break;

        case 0:
            printf("Encerrando o jogo...\n");
            break;

        default:
            printf("Opção inválida. Tente novamente.\n");
            break;
        }

        // Pausa para que o jogador possa ler os resultados antes da próxima rodada.
        printf("\nPressione Enter para continuar...");
        getchar(); // Limpa o buffer do teclado
        getchar(); // Aguarda o Enter

    } while (opcao != 0);

    // Limpa a memória alocada ao encerrar o programa.
    liberarMemoria(t);
    
    

    // 1. Configuração Inicial (Setup):
    // - Define o locale para português.
    // - Inicializa a semente para geração de números aleatórios com base no tempo atual.
    // - Aloca a memória para o mapa do mundo e verifica se a alocação foi bem-sucedida.
    // - Preenche os territórios com seus dados iniciais (tropas, donos, etc.).
    // - Define a cor do jogador e sorteia sua missão secreta.

    // 2. Laço Principal do Jogo (Game Loop):
    // - Roda em um loop 'do-while' que continua até o jogador sair (opção 0) ou vencer.
    // - A cada iteração, exibe o mapa, a missão e o menu de ações.
    // - Lê a escolha do jogador e usa um 'switch' para chamar a função apropriada:
    //   - Opção 1: Inicia a fase de ataque.
    //   - Opção 2: Verifica se a condição de vitória foi alcançada e informa o jogador.
    //   - Opção 0: Encerra o jogo.
    // - Pausa a execução para que o jogador possa ler os resultados antes da próxima rodada.

    // 3. Limpeza:
    // - Ao final do jogo, libera a memória alocada para o mapa para evitar vazamentos de memória.

    return 0;
}

// --- Implementação das Funções ---
void liberarMemoria(territorios* mapa) {
    free(mapa);
    printf("------------------------------------------------\n");
    printf("Memória liberada com sucesso. Até logo!\n");
    printf("------------------------------------------------\n");
}

// Funções de interface com o usuário:
void exibirMapa(const territorios* mapa, int total) {
    printf("================================\n");
    printf("  MAPA ATUAL \n");
    printf("================================\n\n");
    printf("%-10s %-20s %-20s %-10s\n",  "ID", "Território", "Cor do Exército", "Tropas");
    for (int i = 0; i < total; i++) {
        printf("---------------------------------------------------------\n");
        printf("%-10d %-20s %-20s %-10d\n", i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
        printf("---------------------------------------------------------\n");
    }
}

// Funções de lógica principal do jogo:
void FaseDeAtaque(territorios* mapa, int total) {
    int atacante, defensor;
    printf("================================\n");
    printf("FASE DE ATAQUE \n");
    printf("OBS: O território com maior quantidade de tropas terá uma vantagem de dobrar o valor do dado(x2)\n");
    printf("================================\n");

    exibirMapa(mapa, total); // Exibe o mapa para que o jogador possa escolher os territórios.

    printf("----------------------------------------------------------------\n");
    printf("Escolha o território atacante (1-%d) ou pressione 0 para sair: \n", total);
    printf("----------------------------------------------------------------\n");
    scanf("%d", &atacante);
    if (atacante == 0) {
        printf("Ataque cancelado.\n");
        return;
    } else if (mapa[atacante - 1].missao[0] == '\0')
    {
        sortearMissao(mapa, total, atacante - 1); // Sorteia e designa uma missão para o território atacante, caso ele não tenha uma.
    }
    
    // Exibe o território atacante e o objetivo da missão sorteada.
    printf("----------------------------------------------------------------\n");
    printf("Território atacante: %s\n", mapa[atacante - 1].nome);
    printf("Objetivo: %s\n", mapa[atacante - 1].missao);
    printf("----------------------------------------------------------------\n");

    printf("Escolha o território defensor (1-%d): ", total);
    scanf("%d", &defensor);

    // garante que os índices são válidos.
    if (atacante < 1 || atacante > total || defensor < 1 || defensor > total || atacante == defensor || strcmp(mapa[atacante - 1].cor, mapa[defensor - 1].cor) == 0) {
        printf("Índices inválidos. Tente novamente.\n");
        return;
    }
        
    // Ataque iniciado.
    printf("------------------------------------------\n");
    printf("%s Tropas: %d\nAtaca:\n%s Tropas: %d\n", mapa[atacante - 1].nome, mapa[atacante - 1].tropas, mapa[defensor - 1].nome, mapa[defensor - 1].tropas);
    printf("------------------------------------------\n");

    int dadoAtacante = rand() % 10 + 1; // Rola um dado de 10 faces para o atacante.
    int dadoDefensor = rand() % 10 + 1; // Rola um dado de 10 faces para o defensor.

    printf("Dado do Atacante: %d\nDado do Defensor: %d\n", dadoAtacante, dadoDefensor);
   
    // Aplicando a lógica da vantagem do território com mais tropas.
    if (mapa[atacante - 1].tropas > mapa[defensor - 1].tropas)
    {
        printf("Vantagem aplicada para o atacante: %d x 2 = %d\n", dadoAtacante, dadoAtacante * 2);
        dadoAtacante = dadoAtacante * 2;
        
    } else if (mapa[defensor -1].tropas > mapa[atacante - 1].tropas)
    {
        printf("Vantagem aplicada para o defensor: %d x 2 = %d\n", dadoDefensor, dadoDefensor * 2);
        dadoDefensor = dadoDefensor * 2;
    }

    // Lógica de ataque: ataque vence(defensor perde uma tropa), ataque perde(ataque perde uma tropa).
    if (dadoAtacante >= dadoDefensor) {
        mapa[defensor - 1].tropas -= 1; // Defensor perde 1 tropa.
        printf("=======================================\n");
        printf("Atacante vence! %s perde 1 tropa.\n", mapa[defensor - 1].nome);
        printf("=======================================\n");
    } else {
        mapa[atacante - 1].tropas -= 1; // Atacante perde 1 tropa.
        printf("=======================================\n");
        printf("Defensor vence! %s perde 1 tropa.\n", mapa[atacante - 1].nome);
        printf("=======================================\n");
    }

    // Verifica se o defensor foi conquistado.
    if (mapa[defensor - 1].tropas <= 0) {
        printf("-----------------------------\n");
        printf("%s foi conquistado por %s!\n", mapa[defensor - 1].nome, mapa[atacante - 1].nome);
        printf("-----------------------------\n");
        mapa[defensor - 1].tropas = 1; // O novo dono mantém 1 tropa.
        strcpy(mapa[defensor - 1].cor, mapa[atacante - 1].cor); // O defensor agora tem a cor do atacante.
    }
    verificarVitoria(mapa, atacante - 1, defensor - 1, dadoAtacante, dadoDefensor); // Verifica se o jogador cumpriu a missão sorteada.
    
}


// função para cadastro dos territórios:
void cadastroTerritorios(territorios* mapa, int total) {

    for (int i = 0; i < total; i++)
    {
        printf("========================================\n");
        printf(" Território N°%d \n", i + 1);
        printf("========================================\n");

        printf("Insira o nome do %d° território: \n", i + 1);
        setbuf(stdin, NULL); //Limpa o buffer do teclado
        fgets(mapa[i].nome, TAM_STRING, stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = 0; // Remove o '\n' que o fgets pega

        printf("Insira a cor do %d° território: \n", i + 1);
        fgets(mapa[i].cor, TAM_STRING, stdin);
        mapa[i].cor[strcspn(mapa[i].cor, "\n")] = 0;

        printf("Insira a quantidade de tropas do %d° território: \n", i + 1);
        scanf("%d", &mapa[i].tropas);
        printf("\n");
        

    }
}

// Sorteia e designa uma missão para o atacante.
void sortearMissao(territorios* mapa, int indice, int atacante) {

    int indiceAleatorio;
    char* missao[3] = {"Derrotar 1 tropa do território: ", "Conquistar o território: ", "Conquistar qualquer território"};

    int missaoSorteada = rand() % 3; // Sorteia um número entre 0 e 2 para escolher a missão.
    // Sorteia um indice aleatório que seja diferente do território atacante.
    do
    {
     indiceAleatorio = rand() % indice; // Sorteia um índice aleatório para escolher um território para a missão.
    } while (indiceAleatorio == atacante || strcmp(mapa[indiceAleatorio].cor, mapa[atacante].cor) == 0); // Garante que o território sorteado para a missão seja diferente do território atacante.
    sprintf(mapa[atacante].missao, "%s%s", missao[missaoSorteada], mapa[indiceAleatorio].nome); // Atribui a missão sorteada ao território sorteado.
    mapa[atacante].IDmissao = missaoSorteada; // Atribui o ID da missão sorteada.
}

// verifica se o jogador cumpriu a missão sorteada.
void verificarVitoria(territorios* mapa, int atacante, int defensor, int dadoAtacante, int dadoDefensor) {
    // Implementa a lógica para verificar se o jogador cumpriu a missão sorteada.
    switch (mapa[atacante].IDmissao)
    {
    case 0:
        if (dadoAtacante >= dadoDefensor )
        {
            printf("========================================\n");
            printf("Missão cumprida: %s!\n", mapa[atacante].missao);
            printf("========================================\n");
            mapa[atacante].missao[0] = '\0'; // Limpa a missão do atacante para que ele possa receber uma nova missão na próxima fase de ataque.
        } else
        {
            printf("==============================================\n");
            printf("Missão não cumprida... Continue tentando!\n");
            printf("==============================================\n");
        }
        break;
    case 1:

        if (strstr(mapa[atacante].missao, mapa[defensor].nome) != NULL && strcmp(mapa[defensor].cor, mapa[atacante].cor) == 0)
        {
            printf("========================================\n");
            printf("Missão cumprida: %s!\n", mapa[atacante].missao);
            printf("========================================\n");
            mapa[atacante].missao[0] = '\0';
        } else
        {
            printf("==============================================\n");
            printf("Missão não cumprida... Continue tentando!\n");
            printf("==============================================\n");
        }
        break;
    case 2:
        if (strcmp(mapa[defensor].cor, mapa[atacante].cor) == 0)
        {
            printf("========================================\n");
            printf("Missão cumprida: %s!\n", mapa[atacante].missao);
            printf("========================================\n");
            mapa[atacante].missao[0] = '\0';
        } else
        {
            printf("==============================================\n");
            printf("Missão não cumprida... Continue tentando!\n");
            printf("==============================================\n");
        }
        break;
    
    default:
        break;
    }
}