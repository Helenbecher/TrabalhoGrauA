#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int opcao;
    srand(time(NULL));  

    do {
        printf("\n===== MENU PRINCIPAL =====\n");
        printf("1 - Nova Simulacao\n");
        printf("2 - Sair do Programa\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
        
            int populacao_total, infectados_iniciais, dias;
            float taxa_contagio, porcent_vacinados, eficacia_vacina;

            printf("Populacao total: ");
            scanf("%d", &populacao_total);

            printf("Numero de pessoas inicialmente infectadas: ");
            scanf("%d", &infectados_iniciais);

            printf("Taxa de contagio (0 a 100%%): ");
            scanf("%f", &taxa_contagio);

            printf("Porcentagem da populacao vacinada (0 a 100%%): ");
            scanf("%f", &porcent_vacinados);

            printf("Eficacia da vacina (0 a 100%%): ");
            scanf("%f", &eficacia_vacina);

            printf("Numero de dias da simulacao: ");
            scanf("%d", &dias);

            
            int total_infectados = infectados_iniciais;
            int vacinados = (populacao_total * porcent_vacinados) / 100;
            int vacinados_infectados = 0;
            int dia;

            printf("\n--- INICIO DA SIMULACAO ---\n");
            for (dia = 1; dia <= dias; dia++) {
                
                int evento_chance = rand() % 100 + 1;
                float taxa_evento = taxa_contagio;

                if (evento_chance <= 5) {
                    printf("Dia %d: Evento - Mutacao mais contagiosa! (+50%%)\n", dia);
                    taxa_evento *= 1.5;
                } else if (evento_chance <= 10) {
                    printf("Dia %d: Evento - Midia gera alerta! (-30%%)\n", dia);
                    taxa_evento *= 0.7;
                } else if (evento_chance <= 20) {
                    printf("Dia %d: Evento - Isolamento voluntario! (-20%%)\n", dia);
                    taxa_evento *= 0.8;
                } else if (evento_chance <= 35) {
                    printf("Dia %d: Evento - Aglomeracao! (+25%%)\n", dia);
                    taxa_evento *= 1.25;
                }

                
                int novos_estimados = (int)(total_infectados * (taxa_evento / 100.0));

                int vacinados_susceptiveis = (int)(vacinados * (1 - (eficacia_vacina / 100.0)));
                int nao_vacinados_susceptiveis = populacao_total - total_infectados - vacinados;
                int suscetiveis = vacinados_susceptiveis + nao_vacinados_susceptiveis;

                int novos_infectados = novos_estimados;
                if (novos_infectados > suscetiveis) {
                    novos_infectados = suscetiveis;
                }

                total_infectados += novos_infectados;

                int novos_vacinados_infectados = (int)((float)vacinados_susceptiveis / suscetiveis * novos_infectados);
                vacinados_infectados += novos_vacinados_infectados;

                printf("Dia %d: %d infectados (+%d)\n", dia, total_infectados, novos_infectados);

                if (suscetiveis <= 0) {
                    printf("Todos os suscetiveis foram infectados. Simulacao encerrada no dia %d.\n", dia);
                    break;
                }
            }

            int saudaveis = populacao_total - total_infectados;
            printf("\n=== RESULTADOS FINAIS ===\n");
            printf("Total infectados: %d\n", total_infectados);
            printf("Populacao vacinada: %d\n", vacinados);
            printf("Vacinados infectados: %d\n", vacinados_infectados);
            printf("Populacao saudavel: %d\n", saudaveis);

        } else if (opcao != 2) {
            printf("Opcao invalida!\n");
        }

    } while (opcao != 2);

    printf("Programa encerrado.\n");
    return 0;
}