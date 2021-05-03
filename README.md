# To-do

- [X] Instruções sobre como digitar o IP local do servidor. Pode colocar como argumento pra execuçãp do programa tb.
- [X] Passar o caminho do banco como parametro
- [ ] Documentar as mensagens JSON e seus formatos
- [ ] Falar como se desconectar corretamente do servidor -> configurar fechamento seguro com control+c
- [ ] Fork do servidor
- [ ] Mandar erro se tiver que criar usuário que já existe
- [ ] Mudar retorno da função parse() em jsonParser.h? já mandar as msgs do servidor pro usuário prontas?
- [ ] Ajustar retorno das funções que fazem o sql para as funções que realizam o parse.
- [X] Ajustar funções que adicionam skill e experiencia à usuários
- [ ] Definir um json de resposta: {"response": "Success"/"Failed", "object": {retorno}}, precisa do retorno com as listas.
- [ ] Ajustar as listagens para ter os joins necessários e mostrar tudo do usuário?



# MC833-LabRedes
Laboratório Pratico de redes
Disponível em: https://classroom.google.com/c/MjYzMTE3MTA2NDky/a/MzA3MDY2NDkwNDkx/details

Desenvolvido por Fe e Silvs

## Estrutura
* Dentro da pasta lib temos bibliotecas utilizadas tanto pelo cliente quanto pelo servidor.
* Dentro da pasta client temos todo o desenvolvimento da aplicação do lado do cliente.
* Dentro da pasta server temos todo o desenvolvimento do servidor e seu banco de dados.

## Requisitos

- SQLite3

## Compilação
* Para compilar o cliente, utilize o seguinte comando na raiz do projeto:
>```gcc -std=c99 -pedantic -Wall -o ./bin/cliente ./client/cliente.c ./lib/cJSON.c```

* Para compilar o servidor, utilize o seguinte comando na raiz do projeto:
>```gcc -std=c99 -pedantic -Wall -o ./bin/servidor ./server/servidor.c ./lib/cJSON.c -lsqlite3```

# Execução
Primeiramente você deve ligar o servidor, pegando seu ip. Para isso, em um terminal para o servidor rode ```hostname -I```, isso deve retornar um ip. Após isso, rode o executável do servidor por ```./bin/servidor server/app.db```, onde "server/app.db" é o caminho relativo do terminal ao banco de dados do servidor.
Com o servidor ligado e tendo seu ip em mãos, podemos rodar a aplicação do cliente por ```./bin/cliente ip```, onde ip é a exatamente o ip retornado por ```hostname -I``

## Utilizando SQLite3 com C:

Para compilar programas contendo a biblioteca __sqlite3.h__, utilize a flag ```-lsqlite3``` do GCC.

**Por exemplo:**

>```gcc -std=c99 -pedantic -Wall -o ./bin/servidor ./server/servidor.c ./lib/cJSON.c -lsqlite3```

Se ainda persistirem os erros, executar o seguinte comando:

>```sudo apt-get install libsqlite3-dev```

## Banco de Dados

Criamos um banco de dados em arquivo utilizando SQLite3.

As tabelas são as seguintes:

### Profiles

Armazena as seguintes informações dos perfis:

- Email -> Chave primária
- Name
- Surname
- Address
- Education
- Graduation_Year

### Experiences

Armazena uma experiência de um usuário. Cada usuário pode ter mais de uma experiência, mas cada experiência só pertence à um usuário.

- Experience_ID -> Chave primária
- Profile_Email -> Chave extrangeira
- Experience_Description

### Skills

Armazena uma habilidades. As colunas seguem:

- Skill_ID -> Chave primária
- Skill_Description

### Profiles_Skills

Uma habilidade pode pertencer à mais de um perfil. Um perfil pode ter mais de uma habilidade. Dessa maneira, precisamos construir uma tabela intermediaria para descrever essas relações.

- Profile_Email -> Chave Extrangeira
- Skill_ID -> Chave Extrangeira.

usar a flag -lcjson , escrever sobre jsonfy

para compilar: gcc -o cliente cliente.c cJSON.c  -lsqlite3 

## cJSON

utilizamos a biblioteca cJSON para trabalhar com JSON dentro do C.

### JSONfier.h

JSONfier.h é um arquivo intermediario entre client_requests.h e cJSON.c que cria mensagens padronizadas que serão enviadas para o servidor.
Essas mensagens são strings que seguem o formato JSON, e que podem ser parseadas no servidor para se obter informações. 


## Bibliografia

[https://zetcode.com/db/sqlitec/]
[http://www.steves-internet-guide.com/tcpip-ports-sockets/]
[https://www.youtube.com/watch?v=LtXEMwSG5-8&t=1414s]
[https://www.binarytides.com/server-client-example-c-sockets-linux/]
[https://github.com/DaveGamble/cJSON]