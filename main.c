#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h> //Error on windows so must use WSL or Linux
#include <unistd.h>
#include <sys/stat.h>
#include "registers.h"

#define FILE_PATH "registers.bin"
#define FILE_SIZE 1024  // Same size as used in the first program

int main() {
    int fd;
    // Open the file and map it into memory
    char* map = registers_map(FILE_PATH, FILE_SIZE, &fd);
    if (map == NULL) {
        return EXIT_FAILURE;
    }

    unsigned short *base_address = (unsigned short *)map;
    unsigned short *r0 = base_address + 0x00;
    unsigned short *r1 = base_address + 0x01;
    unsigned short *r2 = base_address + 0x02;
    unsigned short *r3 = base_address + 0x03;
    unsigned short *r4 = base_address + 0x04;
    unsigned short *r5 = base_address + 0x05;
    unsigned short *r6 = base_address + 0x06;
    unsigned short *r7 = base_address + 0x07;
    unsigned short *r8 = base_address + 0x08;
    unsigned short *r9 = base_address + 0x09;
    unsigned short *r10 = base_address + 0x0a;
    unsigned short *r11 = base_address + 0x0b;
    unsigned short *r12 = base_address + 0x0c;
    unsigned short *r13 = base_address + 0x0d;
    unsigned short *r14 = base_address + 0x0e;
    unsigned short *r15 = base_address + 0x0f;
    
    printf("Current value of R0: 0x%02x\n", *r0);
    printf("Current value of R1: 0x%02x\n", *r1);
    printf("Current value of R2: 0x%02x\n", *r2);
    printf("Current value of R3: 0x%02x\n", *r3);
    printf("Current value of R4: 0x%02x\n", *r4);
    printf("Current value of R5: 0x%02x\n", *r5);
    printf("Current value of R6: 0x%02x\n", *r6);
    printf("Current value of R7: 0x%02x\n", *r7);
    printf("Current value of R8: 0x%02x\n", *r8);
    printf("Current value of R9: 0x%02x\n", *r9);
    printf("Current value of R10: 0x%02x\n", *r10);
    printf("Current value of R11: 0x%02x\n", *r11);
    printf("Current value of R12: 0x%02x\n", *r12);
    printf("Current value of R13: 0x%02x\n", *r13);
    printf("Current value of R14: 0x%02x\n", *r14);
    printf("Current value of R15: 0x%02x\n", *r15);

    // & = AND, | = OR, ^ = XOR, ~ = NOT

    // Write a new value to R0
    *r0 = *r0 | 0x00;

    int opcao = 0;
    int read_or_write = 0;
    while (1)
    {   
        printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= \n");
        printf("0 - Break \n");
        printf("1 - Read \n");
        printf("2 - Write \n");
        printf("Digite sua opcao: ");
        scanf("%d", &read_or_write);
        if(read_or_write == 1){
            printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= \n");
            printf("1 - Display ligado ou desligado\n");
            printf("2 - Modo de exibição\n");
            printf("3 - Velocidade\n");
            printf("4 - Cursor ligado ou desligado\n");
            printf("5 - Cor\n");
            printf("6 - Valor rgb da mensagem\n");
            printf("7 - Nível da bateria\n");
            printf("8 - Número de vezes que a mensagem passou pelo display\n");
            printf("9 - Temperatura atual\n");
            printf("10 - Mensagem\n");
            printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= \n");
            printf("Digite sua opcao de read: ");
            scanf("%d", &opcao);
            printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= \n");
            clrscr();
            printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= \n");
            printf("Output: \n");
            switch (opcao)
            {
                case 1:
                    //DISPLAY LIGADO OU DESLIGADO
                    if(*r0 & 0x01)
                    {
                        printf("Display ligado, valor 1\n");
                    }
                    else
                    {
                        printf("Display desligado, valor 0\n");
                    }
                    break;
                
                case 2:
                    //MODO DE EXIBIÇÃO
                    if(*r0 & 0x02)
                    {
                        if(*r0 & 0x04)
                        {
                            printf("Modo de exibição: Deslizante/Piscante\n");
                        }
                        else
                        {
                            printf("Modo de exibição: Piscante\n");
                        }
                    }
                    else
                    {
                        if(*r0 & 0x04)
                        {
                            printf("Modo de exibição: Deslizante\n");
                        }
                        else
                        {
                            printf("Modo de exibição: Estático\n");
                        }
                    }
                    break;

                case 3:
                    //VELOCIDADE TESTAR
                    int velocidade = (*r0 & 0x3f) >> 2;
                    printf("Velocidade: %d\n", velocidade);
                    break;

                case 4:
                    //CURSOR LIGADO OU DESLIGADO
                    if(*r0 & 0x200)
                    {
                        printf("Cursor ligado, valor 1\n");
                    }
                    else
                    {
                        printf("Cursor desligado, valor 0\n");
                    }
                    break;

                case 5:
                    //COR
                    int cor = (*r0 & 0x07) >> 3;
                    if(cor == 0)
                    {
                        printf("Cor: Desligado\n");
                    }
                    if(cor == 1)
                    {
                        printf("Cor: Vermelho\n");
                    }
                    if(cor == 2)
                    {
                        printf("Cor: Verde\n");
                    }
                    if(cor == 3)
                    {
                        printf("Cor: Azul\n");
                    }
                    break;

                case 6:
                    //VALOR DE VERMELHO, VERDE E AZUL
                    int vermelho = *r1 & 0xff;
                    int verde = (*r1 & 0xff00) >> 8;
                    int azul = *r2 & 0xff;
                    printf("Valor de vermelho: %d\n", vermelho);
                    printf("Valor de verde: %d\n", verde);
                    printf("Valor de azul: %d\n", azul);
                    break;

                case 7:
                    //MOSTRA O NIVEL DE BATERIA, R3 bits 0-1
                    //Nível da bateria: Crítico (0), Baixo (1), Médio (2), Alto (3)
                    int nivel_bateria = *r3 & 0x03;
                    if(nivel_bateria == 0)
                    {
                        printf("Nível da bateria: Crítico\n");
                    }
                    if(nivel_bateria == 1)
                    {
                        printf("Nível da bateria: Baixo\n");
                    }
                    if(nivel_bateria == 2)
                    {
                        printf("Nível da bateria: Médio\n");
                    }
                    if(nivel_bateria == 3)
                    {
                        printf("Nível da bateria: Alto\n");
                    }
                    break;

                case 8:
                    //MOSTRA NUMERO DE VEZES QUE A MENSAGEM PASSOU PELO DISPLAY, R3 BITS 2-5
                    int vezes_mensagem = (*r3 & 0x3c) >> 2;
                    printf("Número de vezes que a mensagem passou pelo display: %d\n", vezes_mensagem);
                    break;

                case 9:
                    //MOSTRA TEMPERATURA ATUAL EM CELSIUS VEZES 10, R3 BITS 6-15
                    int temperatura = (*r3 & 0xffc0) >> 6;
                    //PRINT DA TEMPERATURA EM VIRGULA
                    printf("Temperatura atual: %d,%d\n", temperatura/10, temperatura%10);
                    break;

                case 10:
                    //MENSAGEM
                    char mensagem[25];
                    for(int i = 0; i < 24; i++)
                    {
                        unsigned short *r = r4 + i/2;
                        if(i % 2 == 0)
                        {
                            mensagem[i] = *r & 0xff;
                        }
                        else
                        {
                            mensagem[i] = (*r & 0xff00) >> 8;
                        }
                    }
                    printf("Mensagem: %s\n", mensagem);
                    break;
            }
            printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= \n");
        }
        else if(read_or_write == 2){
            printf("Digite sua opcao de write: \n");
            printf("1 - Display ligado ou desligado\n");
            printf("2 - Modo de exibição\n");
            printf("3 - Velocidade\n");
            printf("4 - Cursor ligado ou desligado\n");
            printf("5 - Cor\n");
            printf("6 - Restaurar config default\n");
            printf("7 - Valor rgb da mensagem\n");
            printf("8 - Mensagem\n");
            scanf("%d", &opcao);
            switch (opcao)
            {
            case 1:
                toggleDisplay(r0);
                break;

            case 2:
                int opcao_case2 = 0;
                printf("Opções de ações do modo de exibição: \n");
                printf("1 - estático \n");
                printf("2 - deslizante \n");
                printf("3 - piscante \n");
                printf("4 - deslizante/piscante \n");
                scanf("%d", &opcao_case2);

                if(opcao_case2 == 1) 
                {
                    setEstatico(r0);
                }

                if(opcao_case2 == 2) 
                {
                    setDeslizante(r0);
                }

                if(opcao_case2 == 3) 
                {
                    setPiscante(r0);
                }

                if(opcao_case2 == 4) 
                {
                    setPiscanteDeslizante(r0);
                }
                break;

            case 3:
                int opcao_case3 = 0;
                printf("Digite uma velocidade (1-6) em 100ms: \n"); //FAZER TRY CATCH PARA ERRO DE DIGITAÇÃO
                scanf("%d", &opcao_case3);
                if(opcao_case3 < 1 || opcao_case3 > 6)
                {
                    printf("Valor inválido\n");
                    break;
                }
                setVelocidade(r0, opcao_case3);
                break;

            case 4:
                toggleLedOperacao(r0);
                break;

            case 5:
                int opcao_case5 = 0;
                printf("Selecione uma opcao de cor: \n"); //FAZER TRY CATCH PARA ERRO DE DIGITAÇÃO
                printf("0 - Desligado \n");
                printf("1 - Azul \n"); //TROCADO COM AZUL
                printf("2 - Verde \n"); 
                printf("3 - Vermelho \n"); //TROCADO COM VERMELHO
                printf("AZUL E VERMELHO DEVERIAM SER TROCADOS NO EMULADOR");
                scanf("%d", &opcao_case5);
                setLedStatus(r0, opcao_case5);
                printf("Valor inválido\n");
                break;

            case 6:
                resetDefault(r0, r1, r2);
                break;

            case 7:
                int opcao_case7_vermelho = 0;
                int opcao_case7_verde = 0;
                int opcao_case7_azul = 0;
                printf("Digite um valor de vermelho (0-255): \n");
                scanf("%d", &opcao_case7_vermelho);
                printf("Digite um valor de verde (0-255): \n");
                scanf("%d", &opcao_case7_verde);
                printf("Digite um valor de azul (0-255): \n");
                scanf("%d", &opcao_case7_azul);
                setRGB(opcao_case7_vermelho, opcao_case7_verde, opcao_case7_azul, r1, r2);
                break;
            case 8:
                char mensagem[25];
                printf("Digite a mensagem: ");
                scanf(" %[^\n]", mensagem);
                setMensagem(mensagem, r4);
            default:
                break;
            }
        }
        else if(read_or_write == 0)
        {
            break;
        }
        else
        {
            printf("Valor inválido\n");
        }
    }
    

    // Exibir os novos valores dos registradores
    printf("New value of R0: 0x%04x\n", *r0);


    // Release resources
    if (registers_release(map, FILE_SIZE, fd) == -1) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}