# Stellantis

Version du programme en exécutable, qui tourne sur un point d'entrée uniquement. L'optimisation du programme initial, qui permettait de traiter plusieurs points de de données, a été supprimée. La lecture de fichiers csv a été supprimée. Il s'agit d'une étape intermédiaire de simplification du code avant la création d'une DLL. La DLL sera ensuite testée sur un fichier csv depuis un exécutable annexe.

- [x] Suppression de la classe LoadDataTest

- [x] Suppression de la boucle sur les données, puisqu'on travaille dorénavant point à point

- [x] Remplacement de la classe Matrix, utilisée précédemment pour travailler sur tous les points d'entrée, par un vecteur de doubles

