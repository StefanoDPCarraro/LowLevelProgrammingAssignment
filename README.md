# Trabalho Software Básico

## Pré-requisitos:
1. Uso de sistema Linux ou Terminal WSL.
2. Instalação do compilador GCC, caso não instalado.
3. Instalação do Make.

(Para instalar, digite o nome no terminal e siga as instruções exibidas.)

---

## Comandos do Makefile:
- `make`: Compila os arquivos de maneira estática.
- `make static`: Também compila os arquivos de maneira estática.
- `make dynamic`: Compila os arquivos de maneira dinâmica.
- `make clean`: Limpa todos os arquivos criados pelo compilador.

---

## Executando o Controller:
Após entender a diferença entre os comandos do Makefile e compilar da maneira preferida, será criado um arquivo executável chamado "controller". Para executá-lo, digite `./controller` na pasta onde ele está localizado.

---

## Executando o Emulador:
Para executar o emulador, abra outro terminal Linux na mesma pasta.
É necessário permitir que o emulador seja executado com o comando `chmod u+x ./emulator`.
Por fim, execute o emulador com o comando `./emulator` na mesma pasta.

---

## IMPORTANTE:
1. O controlador pode armazenar até 48 letras, mas apenas as 24 ativas no momento do encerramento serão mantidas. Assim, instruir a troca de mensagem logo após abrir o controlador fará com que ele limpe a mensagem na tela.
2. Todas as funções do emulador foram testadas várias vezes em diferentes cenários, mas existem casos muito específicos de mensagens em que o comportamento pode não ser exatamente o esperado. Por exemplo, mesmo com o código para limpar toda a mensagem antes de registrar uma nova, pode haver caracteres aleatórios após o final da palavra. Se isso acontecer, basta interromper o emulador e abrir novamente para garantir o funcionamento correto.
3. Todas as funções são exibidas no console no menu, ocultas atrás das opções "read" e "write".

