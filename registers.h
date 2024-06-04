void clrscr();
char* registers_map(const char* file_path, int file_size, int* fd);
int registers_release(void* map, int file_size, int fd);
void toggleDisplay(unsigned short *r0);
void setEstatico(unsigned short *r0);
void setDeslizante(unsigned short *r0);
void setPiscante(unsigned short *r0);
void setPiscanteDeslizante(unsigned short *r0);
void setVelocidade(unsigned short *r0, int velocidade);
void toggleLedOperacao(unsigned short *r0);
void desligaLedStatus(unsigned short *r0);
void setLedStatus(unsigned short *r0, int opcao);
void setRGB(int red, int green, int blue, unsigned short *r1, unsigned short *r2);
void resetDefault(unsigned short *r0, unsigned short *r1, unsigned short *r2);
void setMensagem(char mensagem[], unsigned short *r4);
char* getDisplayStatus(unsigned short *r0);
char* getExibicao(unsigned short *r0);
int getVelocidade(unsigned short *r0);
char* getLedOperacao(unsigned short *r0);
char* getLedStatus(unsigned short *r0);
int getRed(unsigned short *r1);
int getGreen(unsigned short *r1);
int getBlue(unsigned short *r2);
char* getBatteryLevel(unsigned short *r3);
int getVezesMensagem(unsigned short *r3);
int getTemperatura(unsigned short *r3);
char* getMensagem(unsigned short *r4);
void toggleMensagem(char *novaMensagem1,char *novaMensagem2, unsigned short *r4);