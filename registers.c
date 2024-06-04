#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h> //Error on windows so must use WSL or Linux
#include <unistd.h>
#include <sys/stat.h>

// Funcao para limpar a tela
void clrscr()
{
    int result = system("@cls||clear");
    if(result != 0)
    {
        printf("Erro ao limpar a tela\n");
    }
}

// Function to open or create the file and map it into memory
char *registers_map(const char *file_path, int file_size, int *fd)
{
    *fd = open(file_path, O_RDWR | O_CREAT, 0666);
    if (*fd == -1)
    {
        perror("Error opening or creating file");
        return NULL;
    }

    // Ensure the file is of the correct size
    if (ftruncate(*fd, file_size) == -1)
    {
        perror("Error setting file size");
        close(*fd);
        return NULL;
    }

    // Map the file into memory
    char *map = mmap(0, file_size, PROT_READ | PROT_WRITE, MAP_SHARED, *fd, 0);
    if (map == MAP_FAILED)
    {
        perror("Error mapping file");
        close(*fd);
        return NULL;
    }

    return map;
}

// Function to release mapped memory and file descriptor
int registers_release(void *map, int file_size, int fd)
{
    if (munmap(map, file_size) == -1)
    {
        perror("Error unmapping the file");
        close(fd);
        return -1;
    }

    if (close(fd) == -1)
    {
        perror("Error closing file");
        return -1;
    }

    return 0;
}

void toggleDisplay(unsigned short *r0)
{
    *r0 = *r0 ^ 0x01;
}

void setEstatico(unsigned short *r0)
{
    *r0 = *r0 & ~(1 << 1);
    *r0 = *r0 & ~(1 << 2);
}

void setDeslizante(unsigned short *r0)
{
    *r0 = *r0 | (1 << 1);
    *r0 = *r0 & ~(1 << 2);
}

void setPiscante(unsigned short *r0)
{
    *r0 = *r0 & ~(1 << 1);
    *r0 = *r0 | (1 << 2);
}

void setPiscanteDeslizante(unsigned short *r0)
{
    *r0 = *r0 | (1 << 1);
    *r0 = *r0 | (1 << 2);
}

void setVelocidade(unsigned short *r0, int velocidade)
{
    *r0 = *r0 & ~(0x3f << 3);      // Zera os bits de 3 a 8 (Responsáveis pela velocidade de 1-63)
    *r0 = *r0 | (velocidade << 3); // Pega os bits da velocidade
}

void toggleLedOperacao(unsigned short *r0)
{
    *r0 = *r0 ^ (1 << 9); // Toggle do bit 9
}

void desligaLedStatus(unsigned short *r0)
{
    *r0 = *r0 & ~(0x07 << 10); // Zera os bits de 10 ao 12 (Responsáveis pela cor)
}

void setLedStatus(unsigned short *r0, int opcao)
{
    desligaLedStatus(r0);
    *r0 = *r0 | (opcao << 10); // Pega os bits da cor
}

void setRGB(int red, int green, int blue, unsigned short *r1, unsigned short *r2)
{
    if (red < 0 || red > 255 || green < 0 || green > 255 || blue < 0 || blue > 255)
        return;
    *r1 = *r1 & ~(0xff << 0); // Zera os bits de 0 a 7 (Responsáveis pelo vermelho)
    *r1 = *r1 | (red << 0);   // Pega os bits do vermelho
    *r1 = *r1 & ~(0xff << 8); // Zera os bits de 8 a 15 (Responsáveis pelo verde)
    *r1 = *r1 | (green << 8); // Pega os bits do verde
    *r2 = *r2 & ~(0xff << 0); // Zera os bits de 0 a 7 (Responsáveis pelo azul)
    *r2 = *r2 | (blue << 0);  // Pega os bits do azul
}

void resetDefault(unsigned short *r0, unsigned short *r1, unsigned short *r2)
{
    if (!(*r0 & 0x01))
        toggleDisplay(r0);
    setEstatico(r0);
    setVelocidade(r0, 2);
    if (*r0 & (1 << 9))
        toggleLedOperacao(r0);
    setRGB(255, 255, 255, r1, r2);
    desligaLedStatus(r0);
}

void setMensagem(char mensagem[], unsigned short *r4)
{
    for (int i = 0; i < 12; i++)
    {
        unsigned short *r = r4 + i;
        *r = 0x0000; // Limpa o conteúdo do registrador + ou - Cache complica operacao
    }

    // ADICIONAR MENSAGEM AO DISPLAY
    for (int i = 0; i < 24; i++)
    {
        unsigned short *r = r4 + i / 2;
        if (i % 2 == 0)
        {
            *r = *r | mensagem[i];
        }
        else
        {
            *r = *r | (mensagem[i] << 8);
        }
    }
}

char *getDisplayStatus(unsigned short *r0)
{
    if (*r0 & 0x01)
        return "Ligado";
    return "Desligado";
}

char *getExibicao(unsigned short *r0)
{
    if (*r0 & 0x02)
    {
        if (*r0 & 0x04)
            return "Piscante e Deslizante";
        return "Deslizante";
    }
    if (*r0 & 0x04)
        return "Piscante";
    return "Estatico";
}

int getVelocidade(unsigned short *r0)
{
    return ((*r0 & (0x3f << 3)) >> 3) * 100;
}

char *getLedOperacao(unsigned short *r0)
{
    if (*r0 & (1 << 9))
        return "Ligado";
    return "Desligado";
}

char *getLedStatus(unsigned short *r0)
{
    int cor = (*r0 & (0x07 << 10)) >> 10;
    switch (cor)
    {
    case 0:
        return "Desligado";
    case 1:
        return "Azul";
    case 2:
        return "Verde";
    case 3:
        return "Ciano";
    case 4:
        return "Vermelho";
    case 5:
        return "Rosa";
    case 6:
        return "Amarelo";
    case 7:
        return "Branco";
    default:
        return "Desligado";
    }
}

int getRed(unsigned short *r1)
{
    return (*r1 & 0xff);
}

int getGreen(unsigned short *r1)
{
    return ((*r1 & (0xff << 8)) >> 8);
}

int getBlue(unsigned short *r2)
{
    return (*r2 & 0xff);
}

char *getBatteryLevel(unsigned short *r3)
{
    int level = *r3 & 0x03;
    switch (level)
    {
    case 0:
        return "Crítico";
    case 1:
        return "Baixo";
    case 2:
        return "Médio";
    case 3:
        return "Alto";
    default:
        return "ERRO";
    }
}   

int getVezesMensagem(unsigned short *r3)
{
    return (*r3 & 0x3c) >> 2;
}

int getTemperatura(unsigned short *r3)
{
    return (*r3 & (0xff << 6)) >> 6;
}

char *getMensagem(unsigned short *r4)
{
    static char mensagem[25];
    for (int i = 0; i < 24; i++)
    {
        unsigned short *r = r4 + i / 2;
        if (i % 2 == 0)
        {
            mensagem[i] = *r & 0xff;
        }
        else
        {
            mensagem[i] = (*r & 0xff00) >> 8;
        }
    }
    return mensagem;
}