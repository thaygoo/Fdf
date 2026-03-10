# FdF - Fil de Fer

🚀 **Un visualiseur 3D isométrique** développé en C, utilisant la MiniLibX.

Le but est de créer un programme qui prend un fichier contenant une carte de points d'altitudes (en 2D) et de la représenter en 3D sous forme de paysages filaires.

---

## 📸 Aperçu

Ce programme transforme une simple matrice de valeurs d'altitude comme celle-ci :
```
0  0  0  0  0
0 10  10 10  0
0 10  10 10  0
0  0  0  0  0
```
En une véritable représentation 3D isométrique filaire !

---

## 🛠️ Fonctionnalités

*   **Affichage 3D filaire** (Wireframe).
*   **Projection isométrique**.
*   **Parsing robuste** de maps (gestion des couleurs).
*   **Interface interactive** : possibilité de déplacer (translater), zoomer, ou fermer la fenêtre proprement.
*   **MiniLibX** : Utilisation de la bibliothèque graphique interne de 42.

---

## ⚙️ Prérequis

Assurez-vous d'avoir installé les paquets suivants pour compiler et exécuter le projet avec la MiniLibX sous Linux :

*   `gcc` ou `clang`
*   `make`
*   `xorg`, `libxext-dev`, `libbsd-dev`, `libz-dev`

Sous Ubuntu/Debian :
```bash
sudo apt-get install gcc make xorg libxext-dev libbsd-dev libz-dev
```

---

## 🚀 Installation & Exécution

1. **Cloner le répertoire**
   ```bash
   git clone https://github.com/thaygoo/Fdf.git
   cd Fdf
   ```

2. **Compiler le projet**
   La compilation générera l'exécutable `fdf`.
   ```bash
   make
   ```

3. **Lancer le programme**
   Passez une carte au format `.fdf` en argument. Des cartes de test sont fournies dans `resources/maps/`.
   ```bash
   ./fdf resources/maps/42.fdf
   ```

---

## 🎮 Contrôles

*   **Échap (ESC)** : Quitter le programme proprement.
*   **Croix de la fenêtre** : Fermer la fenêtre.

---

## 🏗️ Structure du Projet

*   `*.c` : Fichiers sources gérant l'initialisation, le dessin, les calculs de projection, et le parsing.
*   `fdf.h` : Fichier d'en-tête principal contenant les structures et prototypes.
*   `resources/libft/` : Bibliothèque standard C personnalisée (Libft + printf + gnl).
*   `resources/minilibx-linux/` : Bibliothèque graphique pour l'affichage.
*   `resources/maps/` : Démonstration et cartes pour tester le visualiseur.

---
