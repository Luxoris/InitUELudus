# InitiationUnreal4C-
Initiation à Ue4, exercices Ludus Académie Bachelor

- Exercice 1 :  - Blueprint d'ouverture de porte avec trigger box, en fonction du poids des éléments.
- Exercice 2 :  - Classes C++ reprenant l'ouverture de la porte, répartie en 2 composants "OpenDoor" et "MassTriggerBox". 
                    Ainsi qu'un BP réalisant les appels entre les composants.
                - Classe C++ PressurePlateDoor enfant de AStaticMeshActor et implémentant les 2 composants.

Les différents systèmes sont tous présent dans le Level1. Les portes reprennent de gauche à droite : une instance de la classe c++ pure, une instance de classe BP avec les composants c++, et une instance de class complétement en BP.

## Note : Penser à ajouter le startercontent dans content avant de lancer le moteur.