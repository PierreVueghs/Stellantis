# Stellantis

- [x] Fichier de sortie csv avec State, ~~LoD (entier),~~ et le résultat

- [x] Remplacer en sortie 0, 1...4 par A, SD, D, ED, Asl

- [x] ~~Remplacer LoD (entier) par A, SD, D, ED, Asl~~

- [x] ~~Calculer LoD (entier) à partir de :~~

	~~for i=1:height(TrainingEvalSet)
	    if TrainingEvalSet.LoD(i)>=0 && TrainingEvalSet.LoD(i)<2.3
	        TrainingEvalSet.LoD_5lvls(i)=0;
	    elseif TrainingEvalSet.LoD(i)>=2.3 && TrainingEvalSet.LoD(i)<4.5
	        TrainingEvalSet.LoD_5lvls(i)=1;
	    elseif TrainingEvalSet.LoD(i)>=4.5 && TrainingEvalSet.LoD(i)<6.8
	        TrainingEvalSet.LoD_5lvls(i)=2;
	    elseif TrainingEvalSet.LoD(i)>=6.8 && TrainingEvalSet.LoD(i)<8.4
	        TrainingEvalSet.LoD_5lvls(i)=3;
	    elseif TrainingEvalSet.LoD(i)>=8.4
	        TrainingEvalSet.LoD_5lvls(i)=4;
	    end
	end~~

- [x] Format du fichier csv	
	1. Première colonne du fichier csv = indice du testPremière colonne du fichier d’entrée. Il n’y a pas de nom à cette colonne. Ajouter ‘Index’ comme nom et recopier la première colonne du fichier entrée. 
	2. id. Recopier la colonne fournie en entrée. 
	3. Timestamp. Recopier la colonne fournie en entrée.
	4. Output. Sortie du modèle. ▪A▪SD▪D▪ED▪Asl
	5. State. Recopier la colonne du fichier d’entrée. ▪A▪SD▪D▪ED▪Asl
	6. LoD. Recopier la colonne du fichier d’entrée (virgule flottante)

- [x] Integration du modele physiologique

- [x] Correction d'un bug dans les fonctions findNextGreaterOrEqual et findNextGreaterThan de ModelPredictor. Les indices retournés ne peuvent pas dépasser la taille du vecteur-1, de sorte qu'il y aura toujours une valeur $z$ pour le calcul de la fonction de Gauss.

- [x] Suppression du test de sécurité préalable à la fonction $\log$. Avant l'appel au logarithme, je comparais la valeur d'entrée. Si cette valeur était nulle (ou négative), je la remplaçais par l'epsilon machine. Supprimer ce test a permis de recaler exactement les résultats du modèle de pression.

- [x] Correction d'un bug dans LoadTestData, lors de la lecture du fichier csv. Si certaines cellules sont vides (ce qui se traduit par plusieurs virgules consécutives), la méthode C que j'employais skippait les virgules comme un seul bloc, provoquant un shift des cellules égal au nombre de cellules vides. Ce problème n'apparaissait que pour le modèle physiologique, le modèle de pressions n'utilisant que les premières colonnes du fichier, heureusement totalement remplies. L'utilisation de méthodes C++ (std::getline) a permis de régler ce problème.

- [x] Ajout d'un test au lancement du programme pour tester que le premier argument est bien un fichier d'extension .csv

- [x] Remplacement du séparateur csv de ";" à "," pour être conforme au format du fichier d'entrée

- [x] Ajout d'un fichier README.txt pour description lors de la livraison