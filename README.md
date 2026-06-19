# Minishell

## Description

Minishell est une réimplémentation simplifiée d'un interpréteur de commandes Unix (shell).  
Le projet a pour objectif de comprendre le fonctionnement interne d'un shell en reproduisant certaines fonctionnalités de Bash :

- Lecture et affichage d'un prompt interactif
- Exécution de commandes externes
- Gestion des variables d'environnement
- Gestion des redirections et des pipes
- Implémentation de plusieurs builtins
- Gestion des signaux

---

## Fonctionnalités

### Exécution de commandes
- Recherche des exécutables via la variable `PATH`
- Exécution de commandes avec `fork()` et `execve()`
- Gestion du code de retour (`$?`)

### Builtins
- `echo` avec l'option `-n`
- `cd`
- `pwd`
- `export`
- `unset`
- `env`
- `exit`

### Redirections
- Entrée : `<`
- Sortie : `>`
- Ajout en fin de fichier : `>>`
- Here-document : `<<`

### Pipes
- Gestion des pipes (`|`)
- Exécution de plusieurs commandes chaînées

### Variables d'environnement
- Expansion des variables (`$USER`, `$HOME`, etc.)
- Gestion de la variable spéciale `$?`

### Gestion des guillemets
- Guillemets simples `'...'`
- Guillemets doubles `"..."`

### Signaux
- `Ctrl-C` : affiche un nouveau prompt, code retour : 130
- `Ctrl-D` : quitte le shell
- `Ctrl-\` : ignoré en mode interactif, code retour : 131

---

## Compilation

```bash
make
```

Règles disponibles :

```bash
make
make clean
make fclean
make re
```

---

## Utilisation

Lancer le shell :

```bash
./minishell
```

Exemples :

```bash
minishell$ ls -la
minishell$ echo "Hello World"
minishell$ cat file.txt | grep test
minishell$ echo $HOME
minishell$ cat << EOF
```

---

## Concepts abordés

- Processus et `fork()`
- `execve()`
- Descripteurs de fichiers
- Pipes et redirections
- Variables d'environnement
- Parsing d'une ligne de commande
- Gestion des signaux
- Gestion de la mémoire en C

---

## Auteurs

Projet réalisé dans le cadre du cursus de l'école 42.
