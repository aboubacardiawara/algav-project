# Algav-project (M1-2022-2023)
Le but du problème consiste à générer des diagrammes de décision binaires, réduits et ordonnés avec une approche analogue à celle présentée dans l’article de Newton et Verna [A Theoretical and Numerical Analysis of the Worst-Case Size of Reduced Ordered Binary Decision Diagrams](https://hal.archives-ouvertes.fr/hal-01880774/document).

## Structure du repository

### Helpers :
- [Figures/](Figures/): Contient toutes les figures générée dans le cadre du projet
- [library/](library/) : Contient le code source de la librairie de nombre arbitraire utilisée et un script bash d'installation rapide vérifier et tester Linux/MacOs/MacM1
- [Visualisation/](Visualisation/) : A la suite des tests les resultats et images .dot sont générées ici.

### Code Source :
- [src/arithmetic_lib/](src/arithmetic_lib/) : Code compilé en natif de la librairie arithmetique
- [src/decision_tree/](src/decision_tree/) : Fichiers sources des arbres ROBDD
- [src/tests/](src/tests/) : Fichiers sources des tests du projets
- [src/warming_up/](src/warming_up/) : Fichiers sources de la premiere partie de l'enoncée 

## Usage
At the root of the project, execute:
```sh
  bash ./library/quick_install.sh #1
  make && ./warming_up.test.out #2
  make && ./tree.test.out 38 #3
  #Genere un arbre basé sur table de verité de 38 avec le nombre minimal de variables
```
## TODO

- [ ] Using Array instead of vector (src/warming_up/warming_up.h) (Important)
- [ ] Using String_Linked_List (with cache) instad of concatenation (For .dot conversion and lukas building)

# Utiles
- [Enoncé Projet](devoir_prog_AlgAv.pdf)


