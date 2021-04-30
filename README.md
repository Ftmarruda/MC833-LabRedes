# MC833-LabRedes
Laboratório Pratico de redes
Disponível em: https://classroom.google.com/c/MjYzMTE3MTA2NDky/a/MzA3MDY2NDkwNDkx/details

Desenvolvido por Fe e Silvs

## Utilizando SQLite3 com C:

Para compilar programas contendo a biblioteca __sqlite3.h__, utilize a flag ```-lsqlite3``` do GCC.

**Por exemplo:**

```gcc servidor.c -lsqlite3 -std=c99 -o servidor```

Se ainda persistirem os erros, executar o seguinte comando:

```sudo apt-get install libsqlite3-dev```

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

## Bibliografia

[https://zetcode.com/db/sqlitec/]
[http://www.steves-internet-guide.com/tcpip-ports-sockets/]
[https://www.youtube.com/watch?v=LtXEMwSG5-8&t=1414s]
[https://www.binarytides.com/server-client-example-c-sockets-linux/]