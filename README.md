# Streamflix
Streamflix is a university project for Programming Laboratory (C)

# StreamFlix - Catálogo de Conteúdo de Streaming (Streaming Content Catalog)

## 📖 Descrição (Description)

**Português**:  
O **StreamFlix** é um programa em C que permite gerenciar um catálogo de conteúdos de streaming. Ele utiliza arquivos CSV para armazenar os dados e oferece funcionalidades como adicionar, remover, editar e pesquisar conteúdos. Além disso, o programa permite que os utilizadores criem listas personalizadas, registrem interações com os conteúdos (play, pause, resume) e gerenciem favoritos.  

Este projeto foi desenvolvido como parte do trabalho prático da disciplina de **Laboratórios de Programação** na **Universidade Aberta**.

**English**:  
**StreamFlix** is a C program that allows managing a catalog of streaming content. It uses CSV files to store data and offers functionalities such as adding, removing, editing, and searching for content. Additionally, the program allows users to create custom lists, record interactions with content (play, pause, resume), and manage favorites.  

This project was developed as part of the practical work for the **Programming Laboratories** course at **Universidade Aberta**.

---

## ✨ Funcionalidades (Features)

**Português**:
- **Gerenciamento de Catálogo**:
  - Carregar conteúdos do arquivo `catálogo.csv`.
  - Adicionar, remover, editar e pesquisar conteúdos no catálogo.
  - Salvar automaticamente as alterações no arquivo `catálogo.csv`.

- **Favoritos**:
  - Adicionar conteúdos aos favoritos.
  - Exibir os conteúdos favoritos de cada utilizador.

- **Interações**:
  - Registar ações como "play", "pause" e "resume" para cada conteúdo.
  - Salvar as interações no arquivo `interactions.csv`.

- **Listas Personalizadas**:
  - Criar listas personalizadas.
  - Adicionar e remover conteúdos das listas.
  - Exibir os conteúdos de uma lista.
  - Salvar as listas no arquivo `lists.csv`.

- **Recomendações**:
  - Gerar recomendações personalizadas com base nas interações dos utilizadores.

**English**:
- **Catalog Management**:
  - Load content from the `catálogo.csv` file.
  - Add, remove, edit, and search for content in the catalog.
  - Automatically save changes to the `catálogo.csv` file.

- **Favorites**:
  - Add content to favorites.
  - Display favorite content for each user.

- **Interactions**:
  - Record actions such as "play," "pause," and "resume" for each content.
  - Save interactions in the `interactions.csv` file.

- **Custom Lists**:
  - Create custom lists.
  - Add and remove content from lists.
  - Display the content of a list.
  - Save lists in the `lists.csv` file.

- **Recommendations**:
  - Generate personalized recommendations based on user interactions.

---

## 🗂️ Estrutura do Projeto (Project Structure)

```plaintext
efolio25/
├── src/                    # Código-fonte do projeto / Project source code
│   ├── main.c              # Arquivo principal com a função `main` / Main file with the `main` function
│   ├── menus.c             # Implementação dos menus do programa / Menu implementation
│   ├── streaming.c         # Funções relacionadas ao catálogo de streaming / Streaming catalog functions
│   ├── personal_list.c     # Funções para gerenciar listas personalizadas / Custom list management functions
│   ├── favorite.c          # Funções para gerenciar favoritos / Favorite management functions
│   ├── recommended.c       # Funções para gerar recomendações / Recommendation generation functions
│   ├── csv_handler.c       # Funções para manipulação de arquivos CSV / CSV file handling functions
├── data/                   # Arquivos de dados / Data files
│   ├── catálogo.csv        # Catálogo de conteúdos de streaming / Streaming content catalog
│   ├── interactions.csv    # Registo de interações dos utilizadores / User interaction log
│   ├── lists.csv           # Listas personalizadas dos utilizadores / User custom lists
│   ├── favorites.csv       # Conteúdos favoritos dos utilizadores / User favorite content
├── build/                  # Diretório para os arquivos compilados / Compiled files directory
│   ├── main                # Arquivo executável gerado após a compilação / Executable file
│   ├── obj/                # Diretório para os arquivos objeto (.o) / Object files directory
├── Makefile                # Arquivo Makefile para automatizar a compilação / Makefile for build automation
├── README.md               # Documentação do projeto / Project documentation
```

---

## ⚙️ Como Compilar e Executar (How to Compile and Run)

### Pré-requisitos (Prerequisites)

- GCC (Compilador C / C Compiler)
- Terminal (Linux/Mac) ou MinGW (Windows)

### Compilação (Compilation)

1. Certifique-se de que o arquivo `Makefile` está configurado corretamente.  
   Ensure the `Makefile` is correctly configured.
2. No terminal, execute o comando:  
   In the terminal, run the command:

   ```bash
   make
   ```

### Execução (Execution)

1. Após a compilação, o executável será gerado no diretório `./build`.  
   After compilation, the executable will be generated in the `./build` directory.
2. Execute o programa com o comando:  
   Run the program with the command:

   ```bash
   ./build/main
   ```

### Limpeza (Cleanup)

Para remover os arquivos compilados, execute:  
To remove compiled files, run:

```bash
make clean
```

---

## 📄 Estrutura dos Arquivos CSV (CSV File Structure)

### `catálogo.csv`

**Português**: Armazena os conteúdos do catálogo no seguinte formato:  
**English**: Stores catalog content in the following format:

```
Título,Género,Duração,Classificação Etária,Visualizações
Title,Genre,Duration,Age Rating,Views
```

Exemplo / Example:

```
Breaking Bad,Drama,50,18,1000000
Stranger Things,Ficção Científica,45,16,800000
```

### `interactions.csv`

**Português**: Armazena as interações dos utilizadores no seguinte formato:  
**English**: Stores user interactions in the following format:

```
Utilizador,Título,Ação
User,Title,Action
```

Exemplo / Example:

```
user1,Breaking Bad,play
user1,Stranger Things,pause
```

### `lists.csv`

**Português**: Armazena as listas personalizadas no seguinte formato:  
**English**: Stores custom lists in the following format:

```
Nome da Lista,Título 1,Título 2,...
List Name,Title 1,Title 2,...
```

Exemplo / Example:

```
Minha Lista Favorita,Breaking Bad,Stranger Things
My Favorite List,Breaking Bad,Stranger Things
```

### `favorites.csv`

**Português**: Armazena os conteúdos favoritos dos utilizadores no seguinte formato:  
**English**: Stores user favorite content in the following format:

```
Utilizador,Título
User,Title
```

Exemplo / Example:

```
user1,Breaking Bad
user2,Stranger Things
```

---

## 🧑‍💻 Autor (Author)

**Fábio Machado**  
Disciplina: Laboratórios de Programação  
Universidade Aberta  

---

## 📜 Licença (License)

**Português**: Este projeto foi desenvolvido para fins educacionais e não possui uma licença específica. Sinta-se à vontade para utilizá-lo e modificá-lo conforme necessário.  
**English**: This project was developed for educational purposes and does not have a specific license. Feel free to use and modify it as needed.