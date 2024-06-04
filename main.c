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
            printf("5 - Cor led status\n");
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
                    printf("Display: %s \n", getDisplayStatus(r0));
                    break;
                
                case 2:
                    //MODO DE EXIBIÇÃO
                    printf("Modo de exibição: %s \n", getExibicao(r0));
                    break;

                case 3:
                    //VELOCIDADE TESTAR
                    printf("Velocidade: %d ms \n", getVelocidade(r0));
                    break;

                case 4:
                    //CURSOR LIGADO OU DESLIGADO
                    printf("Cursor: %s \n", getLedOperacao(r0));
                    break;

                case 5:
                    printf("Cor led status: %s \n", getLedStatus(r0));
                    break;

                case 6:
                    printf("R:%d G:%d B:%d \n", getRed(r1), getGreen(r1), getBlue(r2));
                    break;

                case 7:
                    printf("Nível da bateria: %s \n", getBatteryLevel(r3));
                    break;

                case 8:
                    printf("Número de vezes que a mensagem passou pelo display: %d \n", getVezesMensagem(r3));
                    break;

                case 9:
                    printf("Temperatura atual: %d,%d\n", getTemperatura(r3)/10, getTemperatura(r3)%10);
                    //DECIMAL = RESTO DE DIVISAO POR 10, INTEIRO = QUOCIENTE DIVISAO POR 10
                    break;

                case 10:
                    printf("Mensagem: %s\n", getMensagem(r4));
                    break;
            }
        }
        else if(read_or_write == 2){
            printf("Digite sua opcao de write: \n");
            printf("1 - Display ligado ou desligado\n");
            printf("2 - Modo de exibição\n");
            printf("3 - Velocidade\n");
            printf("4 - Cursor ligado ou desligado\n");
            printf("5 - Cor led status\n");
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
                printf("Digite uma velocidade (1-63) em 100ms: \n"); //FAZER TRY CATCH PARA ERRO DE DIGITAÇÃO
                scanf("%d", &opcao_case3);
                if(opcao_case3 < 1 || opcao_case3 > 63)
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
                printf("3 - Ciano \n"); //AZUL + VERDE
                printf("4 - Vermelho \n"); //TROCADO COM VERMELHO
                printf("5 - Rosa \n"); //VERMELHO + AZUL
                printf("6 - Amarelo \n"); //VERMELHO + VERDE
                printf("7 - Branco \n"); //VERMELHO + VERDE + AZUL
                scanf("%d", &opcao_case5);
                if(opcao_case5 < 0 || opcao_case5 > 7){
                    printf("Valor inválido\n");
                    break;
                }
                setLedStatus(r0, opcao_case5);
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