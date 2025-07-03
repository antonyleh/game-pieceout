# Piece Out - Jeu de Puzzle en C++/SFML

## 📋 Description

**Piece Out** est un jeu de puzzle développé en C++ avec la bibliothèque SFML. Le joueur manipule des pièces sur un plateau pour atteindre des objectifs spécifiques, comme faire sortir une pièce d'une zone ou la placer sur une position cible.

## 🏗️ Architecture

Le projet suit une architecture **MVC** (Modèle-Vue-Contrôleur) avec l'utilisation de plusieurs patrons de conception :

### Patrons de conception utilisés

- **Décorateur** : Permet d'enchaîner des effets (déplacement, rotation, symétrie) sur les pièces
- **Visiteur** : Délègue les actions aux classes appropriées
- **Commande** : Gestion de l'historique avec fonction "Undo"

### Diagramme UML

![Diagramme UML du projet Piece Out](diagramme.png)

*Le diagramme UML complet montre les relations entre les classes GameController, GameModel, Piece et ses dérivées, ainsi que l'implémentation des patrons Décorateur et Visiteur.*

## 🎮 Fonctionnalités

- **Manipulation des pièces** : Déplacement par cliquer-glisser
- **Transformations** : Rotation et symétrie des pièces
- **Flèches directionnelles** : Indicateurs visuels des mouvements possibles
- **Système d'annulation** : Fonction "Undo" pour revenir à l'état précédent
- **Détection de collisions** : Empêche la superposition des pièces
- **Niveaux multiples** : Plusieurs configurations de jeu disponibles

## 🛠️ Technologies utilisées

- **Langage** : C++
- **Bibliothèque graphique** : SFML (Simple and Fast Multimedia Library)
- **Gestion mémoire** : Smart pointers (`shared_ptr`)
- **Architecture** : MVC avec patrons de conception

## 📦 Installation

### Prérequis

- Compilateur C++ compatible C++11 ou supérieur
- SFML 2.5+ installé sur votre système
- CMake (optionnel mais recommandé)

### Compilation

Le projet utilise un Makefile pour simplifier la compilation.

bash
# Cloner le repository
git clone https://github.com/yourusername/piece-out.git
cd piece-out

# Compiler le projet
make

# Lancer l'exécutable
./pieceOut

# Nettoyer les fichiers objets et l'exécutable
make clean
```

## 🚀 Utilisation

```bash
# Lancer le jeu
./PieceOut
```

### Contrôles

- **Clic gauche** : Sélectionner et déplacer une pièce
- **Clic sur flèche** : Déplacer la pièce dans la direction indiquée
- **U** : Annuler la dernière action (Undo)
- **ESC** : Quitter le jeu

## 🐛 Problèmes résolus

1. **Cohérence de l'annulation** : Sauvegarde complète de l'état des pièces (position, orientation, propriétés)
2. **Collisions** : Vérification systématique avant chaque déplacement
3. **Gestion des pivots** : Ajustement dynamique lors des rotations avec décorateurs
4. **Cycle de vie des objets** : Utilisation de `shared_ptr` pour éviter les doubles destructions

## 👥 Auteurs

- **Asso Ali Mullud**
- **Antony Lehmann**

## 📝 Licence

Ce projet est développé dans le cadre d'un projet universitaire.
