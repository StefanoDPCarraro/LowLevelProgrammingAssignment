# TrabalhoSoftwareBasico
Pré-requisitos: 
1 - Uso de sistema linux ou terminal wsl
2 - Instalação do compilador gcc, caso não instalado
3 - Instalação do make.
(Para instalar apenas digitar o nome no terminal e ele mostrará o comando)
===============================================
Comandos do Makefile:
make: Compila os arquivos(de maneira estática).
make static: Também compila os arquivos de maneira estática
make dynamic: Compila os arquivos de maneira dinâmica
make clean: Limpa todos os arquivos que foram criados pelo compilador
===============================================
Executando o controller:
Após ver a diferença entre os comandos Makefile e compilar da maneira que preferir, é criado um arquivo executável com o nome controller.
Para rodar este arquivo basta digitar ./controller na pasta em que ele se localiza.
===============================================
Execuntando o emulador:
Para executar o emulador, abra outro terminal linux nesta pasta.
É necessário permitir o emulador ser executado com o comando chmod u+x ./emulator
Por fim é possível executar o emulador com o comando ./emulator na pasta que ele se encontra
===============================================
IMPORTANTE:
1 - No controlador é possível guardar 48 letras, no entanto apenas as 24 ativas na hora do encerramento ficarão guardadas na hora que o controller for encerrado. Sendo assim passar a instrução de trocar mensagem logo que abrir o controller fará com que ele limpe a mensagem na tela.
2 - Todas as funções do emulador foram testadas várias vezes em diversas possibilidades e existem alguns cenários de mensagens muito específicas é possível que o comportamento não seja exatamente como o esperado (por exemplo, como mostrado em uma aula, mesmo com o código para limpar toda mensagem antes de registrar uma nova, continua estando sujeito a sobrar algum caractére aleatório depois do final da palavra), caso acontecer algum destes cenários, apenas dar break no emulador e abrir de novo já é o bastante para garantir que ele volte a funcionar como o esperado, permitindo mudar a mensagem de maneira correta desta vez.
3 - Todas as funções são mostradas no console no menu, escondidas atrás das opções read e write.