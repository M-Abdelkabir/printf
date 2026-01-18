# 0x11. C - printf (ALX SE Project)

## Description
Ce projet consiste en une réimplémentation personnalisée de la fonction standard `printf` en langage C. Réalisé dans le cadre du cursus **ALX Software Engineering**, il démontre une maîtrise de la gestion des arguments variadiques, du parsing de chaînes de caractères et de la manipulation de bas niveau.

> **Philosophie du projet :** "I don't like to use the function that build it by another people, I prefer to understand the logic behind them."

## Structure du Dépôt
L'architecture du projet est modulaire pour garantir une meilleure lisibilité et maintenance :

| Fichier | Description |
| :--- | :--- |
| `_printf.c` | Point d'entrée principal; contient la boucle de parsing. |
| `main.h` | Header contenant les prototypes, structures et bibliothèques standard. |
| `functions.c` | Logique de traitement des spécificateurs de base (`s`, `c`, `d`, `i`). |
| `flags.c` | Gestion des drapeaux de formatage (`+`, `space`, `#`). |
| `width.c` | Calcul et gestion de la largeur de champ. |
| `lenght.c` | Gestion des modificateurs de longueur (`l`, `h`). |
| `main.c` | Fichier de test pour vérifier le comportement de la fonction. |

## Spécificateurs Supportés
Le projet implémente les fonctionnalités suivantes :
* **Basiques :** `%c` (caractère), `%s` (chaîne), `%%` (pourcentage).
* **Numériques :** `%d`, `%i` (entiers signés).
* **Conversion :** `%b` (conversion binaire personnalisée).
* **Avancés :** `%u` (unsigned), `%o` (octal), `%x` / `%X` (hexadécimal).
* **Formatage :** Gestion précise des **Flags**, de la **Largeur** (width) et de la **Précision**.

## Installation et Utilisation

### Compilation
Utilisez la commande suivante pour compiler tous les fichiers `.c` :
```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o printf
