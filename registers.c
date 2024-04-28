#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h> //Error on windows so must use WSL or Linux
#include <unistd.h>
#include <sys/stat.h>

#define FILE_PATH "registers.bin"
#define FILE_SIZE 1024  // Same size as used in the first program
#define MASK 0xFFFF

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
    unsigned short *r15 = base_address + 0x0f;\
    
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
    printf("Current value of Mask: 0x%x\n", MASK);

    // Write a new value to R0
    *r0 = *r0 | 0x00;

    // Change the value of R0
    *r0 = (*r0 & 0xF000) | 0x0213; //Comeca pelo bit 0 na direita, cada casa = 4 bits

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
            printf("Opções de ações do modo de exibição: \n");
            printf("1 - estático \n");
            printf("2 - deslizante \n");
            printf("3 - piscante \n");
            printf("4 - deslizante/piscante \n");
            scanf("%d", &opcao);

            if(opcao == 1) 
            {

                *r0 = *r0 & ~(1 << 1  );
                *r0 = *r0 & ~(1 << 2  );
            }

            if(opcao == 2) 
            {
                *r0 = *r0 | (1 << 1  );
                *r0 = *r0 & ~(1 << 2  );
            }

            if(opcao == 3) 
            {
                *r0 = *r0 & ~(1 << 1  );
                *r0 = *r0 |  (1 << 2  );

            }

            if(opcao == 4) 
            {
                *r0 = *r0 | (1 << 1  );
                *r0 = *r0 | (1 << 2  );
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