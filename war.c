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
} territorios;

// --- Protótipos das Funções ---
// Declarações antecipadas de todas as funções que serão usadas no programa, organizadas por categoria.
// Funções de setup e gerenciamento de memória:
void liberarMemoria(territorios* mapa);
// Funções de interface com o usuário:
void exibirMapa(const territorios* mapa, int total);
// Funções de lógica principal do jogo:
void FaseDeAtaque(territorios* mapa, int total);
// função para cadastro dos territórios:
void cadastroTerritorios(territorios* mapa, int total);
// --- Função Principal (main) ---
// Função principal que orquestra o fluxo do jogo, chamando as outras funções em ordem.
int main() {

    srand(time(NULL)); // Inicializa a semente para geração de números aleatórios.

    printf("### BEM VINDO AO WAR ### \n\n## Iniciando o cadastro dos territórios... ##\n\n");

int total_territorios;

    printf("Quantos territórios deseja cadastrar?\n");
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
        printf("\n### MENU PRINCIPAL ###\n");
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
    printf("\nMemória liberada com sucesso. Até logo!\n");
}

// Funções de interface com o usuário:
void exibirMapa(const territorios* mapa, int total) {
    
    printf("\n      ### MAPA ATUAL ###\n\n");
    printf("%-10s %-20s %-20s %-10s\n",  "ID", "Território", "Cor do Exército", "Tropas");
    for (int i = 0; i < total; i++) {
        printf("%-10d %-20s %-20s %-10d\n", i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}

// Funções de lógica principal do jogo:
void FaseDeAtaque(territorios* mapa, int total) {
    int atacante, defensor;
    printf("\n### FASE DE ATAQUE ###\n");

    exibirMapa(mapa, total); // Exibe o mapa para que o jogador possa escolher os territórios.

    printf("Escolha o território atacante (1-%d) ou pressione 0 para sair: ", total);
    scanf("%d", &atacante);
    if (atacante == 0) {
        printf("Ataque cancelado.\n");
        return;
    }
    printf("Escolha o território defensor (1-%d): ", total);
    scanf("%d", &defensor);

    // garante que os índices são válidos.
    if (atacante < 1 || atacante > total || defensor < 1 || defensor > total || atacante == defensor) {
        printf("Índices inválidos. Tente novamente.\n");
        return;
    }

    // Ataque iniciado.
    printf("%s Tropas: %d\nAtaca:\n%s Tropas: %d\n", mapa[atacante - 1].nome, mapa[atacante - 1].tropas, mapa[defensor - 1].nome, mapa[defensor - 1].tropas);

    // Lógica de ataque simplificada: defensor perde 1 tropa.

    int dadoAtacante = rand() % 6 + 1; // Rola um dado de 6 faces para o atacante.
    int dadoDefensor = rand() % 6 + 1; // Rola um dado de 6 faces para o defensor.

    printf("Dado do Atacante: %d\nDado do Defensor: %d\n", dadoAtacante, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        mapa[defensor - 1].tropas -= 1; // Defensor perde 1 tropa.
        printf("Atacante vence! %s perde 1 tropa.\n", mapa[defensor - 1].nome);
    } else {
        printf("Defensor vence!\n");
    }

    // Verifica se o defensor foi conquistado.
    if (mapa[defensor - 1].tropas <= 0) {
        printf("%s foi conquistado por %s!\n", mapa[defensor - 1].nome, mapa[atacante - 1].nome);
        mapa[defensor - 1].tropas = 1; // O novo dono mantém 1 tropa.
        strcpy(mapa[defensor - 1].cor, mapa[atacante - 1].cor); // O defensor agora tem a cor do atacante.
    }
    
}


// função para cadastro dos territórios:
void cadastroTerritorios(territorios* mapa, int total) {

    for (int i = 0; i < total; i++)
    {
        printf("# Território N°%d #\n\n", i + 1);

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

// alocarMapa():
// Aloca dinamicamente a memória para o vetor de territórios usando calloc.
// Retorna um ponteiro para a memória alocada ou NULL em caso de falha.

// inicializarTerritorios():
// Preenche os dados iniciais de cada território no mapa (nome, cor do exército, número de tropas).
// Esta função modifica o mapa passado por referência (ponteiro).

// liberarMemoria():
// Libera a memória previamente alocada para o mapa usando free.

// exibirMenuPrincipal():
// Imprime na tela o menu de ações disponíveis para o jogador.

// exibirMapa():
// Mostra o estado atual de todos os territórios no mapa, formatado como uma tabela.
// Usa 'const' para garantir que a função apenas leia os dados do mapa, sem modificá-los.

// exibirMissao():
// Exibe a descrição da missão atual do jogador com base no ID da missão sorteada.

// faseDeAtaque():
// Gerencia a interface para a ação de ataque, solicitando ao jogador os territórios de origem e destino.
// Chama a função simularAtaque() para executar a lógica da batalha.

// simularAtaque():
// Executa a lógica de uma batalha entre dois territórios.
// Realiza validações, rola os dados, compara os resultados e atualiza o número de tropas.
// Se um território for conquistado, atualiza seu dono e move uma tropa.

// sortearMissao():
// Sorteia e retorna um ID de missão aleatório para o jogador.

// verificarVitoria():
// Verifica se o jogador cumpriu os requisitos de sua missão atual.
// Implementa a lógica para cada tipo de missão (destruir um exército ou conquistar um número de territórios).
// Retorna 1 (verdadeiro) se a missão foi cumprida, e 0 (falso) caso contrário.

// limparBufferEntrada():
// Função utilitária para limpar o buffer de entrada do teclado (stdin), evitando problemas com leituras consecutivas de scanf e getchar.
