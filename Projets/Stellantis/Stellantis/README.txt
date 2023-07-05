Ce document décrit la procédure d'appel de l'exécutable DrowsinessPrediction.exe, ainsi que le format d'export des résultats.


Définitions
-----------
Modèle pression : modèle utilisant comme données d'entrées uniquement des données issues de capteurs de pression dans le siège.
Modèle physiologique : modèle utilisant comme données d'entrées des données cardiaques et respiratoires en plus des données issues de capteurs de pression dans le siège.


Lancement
---------
L'exécutable accepte 2 paramètres :
* le chemin absolu vers le fichier contenant les données d'entrées. Ce fichier doit être au format CSV, avec 
  l'extension .csv
* un second paramètre (quelconque) qui active l'utilisation du modèle physiologique

Par défaut, c'est le modèle de pressions qui est utilisé pour la prédiction.
Si plus de deux paramètres sont fournis à l'exécutable, c'est le modèle de pressions qui est utilisé pour la
prédiction.

Pour lancer l'exécutable, procédez comme suit :
* Ouvrez une invite de commande Windows (dans la barre de recherche, tapez "cmd")
* Par défaut, l'invite de commande Windows est situé à la racine du dossier utilisateur
* Placez-vous dans un dossier de travail, où le fichier de résultats sera généré. L'utilisateur doit avoir les droits d'écriture dans ce dossier.
  Ce dossier ne doit pas être obligatoirement le dossier contenant l'exécutable ou le fichier d'entrées.
* Dans l'invite de commande, référencez le chemin complet de l'exécutable, puis le chemin complet du fichier d'entrées, puis (éventuellement)
  une troisième valeur (quelconque) pour utiliser le modèle physiologique à la place du modèle de pressions

Par exemple :
C:\Users\myUser> C:\Users\myUser\Documents\Projets\Exe\Release\DrowsinessPrediction.exe C:\Users\myUser\Documents\Projets\Inputs\features_150s_normalized_sliding90s.csv something


Résultats
---------
L'exécutable génère un fichier CSV à l'endroit où l'exécutable est appelé. Le fichier s'appelle results.csv.
/!\ L'utilisateur doit avoir les droits d'écriture dans le dossier d'où est appelé l'exécutable.

Le fichier results.csv contient 6 colonnes :
	1. Index : l'indice de l'échantillon courant. 
	2. id : l'identifiant du sujet. Cette colonne provient directement de la colonne "id" du fichier csv d'entrée.
	3. Timestamp : le pas de temps de l'échantillon. Cette colonne provient directement de la colonne "Timestamp" du fichier csv d'entrée.
	4. Output. Cette colonne est la sortie calculée par le modèle implanté dans l'exécutable. Les 5 niveaux de somnolence, ▪A▪SD▪D▪ED▪Asl, sont codés comme suit :
		* A : Awake
		* SD : Slightly Drowsy
		* D : Drowsy
		* ED : Extremely Drowsy
		* Asl : Asleep
	5. State : l'état du sujet, lors de la mesure courante. Cette colonne provient directement de la colonne "State" du fichier csv d'entrée.
	6. LoD : le niveau de somnolence, lors de la mesure courante. Cette colonne provient directement de la colonne "LoD" du fichier csv d'entrée.

Les colonnes "id", "Timestamp", "State" et "LoD" sont fournies dans le fichier de sortie en vue de faciliter l'analyse des données.
Si le fichier csv d'entrée ne contient pas ces colonnes, ou si les labels de ces colonnes ne sont pas respectés, ces colonnes seront vides dans le
fichier results.csv.
