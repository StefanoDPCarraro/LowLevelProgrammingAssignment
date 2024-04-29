#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h> //Error on windows so must use WSL or Linux
#include <unistd.h>
#include <sys/stat.h>

#define FILE_PATH "registers.bin"
#define FILE_SIZE 1024  // Same size as used in the first program

// Function to open or create the file and map it into memory
char* registers_map(const char* file_path, int file_size, int* fd) {
    *fd = open(file_path, O_RDWR | O_CREAT, 0666);
    if (*fd == -1) {
        perror("Error opening or creating file");
        return NULL;
    }

    // Ensure the file is of the correct size
    if (ftruncate(*fd, file_size) == -1) {
        perror("Error setting file size");
        close(*fd);
        return NULL;
    }

    // Map the file into memory
    char *map = mmap(0, file_size, PROT_READ | PROT_WRITE, MAP_SHARED, *fd, 0);
    if (map == MAP_FAILED) {
        perror("Error mapping file");
        close(*fd);
        return NULL;
    }

    return map;
}

// Function to release mapped memory and file descriptor
int registers_release(void* map, int file_size, int fd) {
    if (munmap(map, file_size) == -1) {
        perror("Error unmapping the file");
        close(fd);
        return -1;
    }

    if (close(fd) == -1) {
        perror("Error closing file");
        return -1;
    }

    return 0;
}

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
    while (1)
    {
        printf("Digite sua opcao: \n");
        scanf("%d", &opcao);
        switch (opcao)
        {
        case 1:
            *r0 = *r0 ^ 0x01;
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

                *r0 = *r0 & ~(1 << 1  );
                *r0 = *r0 & ~(1 << 2  );
            }

            if(opcao_case2 == 2) 
            {
                *r0 = *r0 | (1 << 1  ); //Nao inverte pois or com 0 vira operaçao neutra - Para virar 1 no bit especifico no caminhamento
                *r0 = *r0 & ~(1 << 2  ); //Inverte pois and com 1 vira operaçao neutra - Para virar 0 no bit especifico no caminhamento
            }

            if(opcao_case2 == 3) 
            {
                *r0 = *r0 & ~(1 << 1  );
                *r0 = *r0 |  (1 << 2  );

            }

            if(opcao_case2 == 4) 
            {
                *r0 = *r0 | (1 << 1  );
                *r0 = *r0 | (1 << 2  );
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
            *r0 = *r0 & ~(0x3f << 3); //Zera os bits de 3 a 8 (Responsáveis pela velocidade)
            *r0 = *r0 | (1 << opcao_case3 + 2); //Pega os bits da velocidade denominados por aux + 2
            break;

        case 4:
            *r0 = *r0 ^ (1 << 9); //Toggle do bit 9
            break;

        case 5:
            int opcao_case5 = 0;
            printf("Selecione uma opcao de cor: \n"); //FAZER TRY CATCH PARA ERRO DE DIGITAÇÃO
            printf("0 - Desligado \n");
            printf("1 - Vermelho \n"); //TROCADO COM AZUL
            printf("2 - Verde \n"); 
            printf("3 - Azul \n"); //TROCADO COM VERMELHO
            scanf("%d", &opcao_case5);
            *r0 = *r0 & ~(0x07 << 10); //Zera os bits de 10 ao 12 (Responsáveis pela cor)
            if(opcao_case5 > 0 && opcao_case5 < 4)
            {
                *r0 = *r0 | (1 << 9 + opcao_case5); //Pega os bits da cor denominados por aux + 10
                break;
            }
            printf("Valor inválido\n");
            break;

        case 6:
            //IMPLEMENTAR DEFAULT
            break;

        case 7:
            int opcao_case7_vermelho = 0;
            int opcao_case7_verde = 0;
            int opcao_case7_azul = 0;
            printf("Digite um valor de vermelho (0-255): \n");
            scanf("%d", &opcao_case7_vermelho);
            if(opcao_case7_vermelho < 0 || opcao_case7_vermelho > 255)
            {
                printf("Valor inválido\n");
                break;
            }
            *r1 = *r1 & ~(0xff); //Zera os bits de 0 a 7
            *r1 = *r1 | opcao_case7_vermelho; //Pega os bits do valor de vermelho
            printf("Digite um valor de verde (0-255): \n");
            scanf("%d", &opcao_case7_verde);
            if(opcao_case7_verde < 0 || opcao_case7_verde > 255)
            {
                printf("Valor inválido\n");
                break;
            }
            *r1 = *r1 & ~(0xff << 8); //Zera os bits de 8 a 15
            *r1 = *r1 | (opcao_case7_verde << 8); //Pega os bits do valor de verde
            printf("Digite um valor de azul (0-255): \n");
            scanf("%d", &opcao_case7_azul);
            if(opcao_case7_azul < 0 || opcao_case7_azul > 255)
            {
                printf("Valor inválido\n");
                break;
            }
            *r2 = *r2 & ~(0xff); //Zera os bits de 0 a 7
            *r2 = *r2 | opcao_case7_azul; //Pega os bits do valor de azul
            break;
        
        case 8:
            //METODO READ-ONLY
            break;

        case 9:
            //METODO READ-ONLY
            break;
        
        case 10:
            //METODO READ-ONLY
            break;

        case 11:
            char mensagem[25];
            printf("Digite uma mensagem de até 24 caracteres: \n");
            scanf(" %[^\n]", mensagem);
            printf("Mensagem: %s\n", mensagem);
            //ZERAR AS PALAVRAS DE R4 a R15
            for(int i = 4; i < 16; i++)
            {
                unsigned short *r = base_address + i;
                *r = 0x0000;
            }
            for(int i = 0; i < sizeof(mensagem) - 1; i++)
            {
                unsigned short *r = r4 + i/2;
                if(i % 2 == 0)
                {
                    *r = *r & ~(0xff);
                    *r = *r | mensagem[i];
                }
                else
                {
                    *r = *r & ~(0xff << 8);
                    *r = *r | (mensagem[i] << 8);
                }
            }
            break;

        default:
            break;
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