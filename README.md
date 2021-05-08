# MC833-LabRedes
Laboratório Pratico de redes
Disponível em: https://classroom.google.com/c/MjYzMTE3MTA2NDky/a/MzA3MDY2NDkwNDkx/details

Documentado em: https://docs.google.com/document/d/1-KrSTiqHg5B6wJTbwrwL4xNw6y8HJFNvjDU0lH-WqGc/edit?usp=sharing

Desenvolvido por Fe e Silvs

## Estrutura
* Dentro da pasta lib, temos bibliotecas utilizadas tanto pelo cliente quanto pelo servidor.
* Dentro da pasta client, temos todo o desenvolvimento da aplicação do lado do cliente.
* Dentro da pasta server, temos todo o desenvolvimento do servidor e seu banco de dados.

## Requisitos

- SQLite3

## Compilação
* Para compilar o cliente, utilize o seguinte comando na raiz do projeto:
>```gcc -std=c99 -pedantic -Wall -o ./bin/cliente ./client/cliente.c ./lib/cJSON.c```

* Para compilar o servidor, utilize o seguinte comando na raiz do projeto:
>```gcc -std=c99 -pedantic -Wall -o ./bin/servidor ./server/servidor.c ./lib/cJSON.c -lsqlite3```

# Execução
Primeiramente você deve ligar o servidor, utilizando o comando

```./bin/servidor server/app.db``` na pasta raíz,

onde "server/app.db" é o caminho relativo do terminal ao banco de dados do servidor.

<hr>

Após isso, deve-se anotar o IP local do servidor para que o cliente consiga se conectar.

Para descobrir o IP local de seu servidor em computadores Linux rode:

```hostname -I```,

Em computadores MacOS, essa informação pode ser obtida nas configurações de redes.

<hr>

Com o servidor ligado e tendo seu IP em mãos, podemos rodar a aplicação do cliente por 

```./bin/cliente [IP]```, na pasta raíz.

## Utilizando SQLite3 com C:

Para compilar programas contendo a biblioteca __sqlite3.h__, utilize a flag ```-lsqlite3``` do GCC.

**Por exemplo:**

>```gcc -std=c99 -pedantic -Wall -o ./bin/servidor ./server/servidor.c ./lib/cJSON.c -lsqlite3```

Se ainda persistirem os erros, executar o seguinte comando:

>```sudo apt-get install libsqlite3-dev```

Ou obtenha SQLite3 por meio do site [https://www.sqlite.org/index.html].

## Banco de Dados

Criamos um banco de dados em arquivo utilizando SQLite3.

Para visualizar o banco de dados, recomendamos a utilização do SQLiteStudio [https://sqlitestudio.pl].

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

Uma habilidade pode pertencer à mais de um perfil. Um perfil pode ter mais de uma habilidade. Dessa maneira, precisamos construir uma tabela intermediária para descrever essas relações.

- Profile_Email -> Chave Extrangeira
- Skill_ID -> Chave Extrangeira.

## cJSON

utilizamos a biblioteca cJSON para trabalhar com JSON dentro do C.

### JSONfier.h

JSONfier.h é um arquivo intermediario entre client_requests.h e cJSON.c que cria mensagens padronizadas que serão enviadas para o servidor.
Essas mensagens são strings que seguem o formato JSON, e que podem ser parseadas no servidor para se obter informações. 

## Demais informações

Para informações mais detalhadas, verifique a documentação do projeto:

https://docs.google.com/document/d/1-KrSTiqHg5B6wJTbwrwL4xNw6y8HJFNvjDU0lH-WqGc/edit?usp=sharing

## Bibliografia

https://zetcode.com/db/sqlitec/

http://www.steves-internet-guide.com/tcpip-ports-sockets/

https://www.youtube.com/watch?v=LtXEMwSG5-8&t=1414s

https://www.binarytides.com/server-client-example-c-sockets-linux/

https://github.com/DaveGamble/cJSON
