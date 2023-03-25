#!/bin/sh
verifie_fichier()
{
	if test ! -f $1
	then
		echo "Fichier en entré inexistant, vous devrez entrer la feuille de calcul sur l'entrée standard"
	else
		fichier_in=1
		echo "Fichier existant"
		nom_fichier_in=$1
	fi
}
out_resultat() {
	fichier_out=1
	if [ -f $1 ]
	then
		echo "$1 existe deja"
	else
		touch $1
		echo "On creer le fichier $1"
	fi
	nom_fichier_out=$1
}
scin_sep() {
	if [ $# -eq 1 ]
	then
		scin="$1"
	fi
}
slin_sep() {
	if [ $# -eq 1 ]
	then
		slin="$1"
	fi
}
scout_sep() {
	if [ $# -eq 1 ]
	then
		scout="$1"	
	fi
}
slout_sep() {
	if [ $# -eq 1 ]
	then
		slout="$1"
	fi
}
verification_option() {
	if [ $# -ne 0 ]
	then
		case $1 in
			"-in")
				verifie_fichier $2
				;;
			"-out")
				out_resultat $2
				;;
			"-scin")
				scin_sep $2
				;;
			"-scout")
				scout_sep $2
				;;		
			"-slin")
				slin_sep $2
				;;
			"-slout")
				slout_sep $2
				;;
			*)
				echo "ERREUR : Option de commande invalide !" && exit 0
		esac
		shift
		shift
		verification_option $@
	fi
}

fichier_in=0
fichier_out=0
scin="\t"
slin="\n"
scout="$scin"
slout="$slin"
verification_option $@
echo "Fichier IN : "$fichier_in""
test "$fichier_in" -eq 1 && echo "Nom fichier in : "$nom_fichier_in""
echo "Fichier OUT : "$fichier_out""
test "$fichier_out" -eq 1 && echo "Nom fichier out : "$nom_fichier_out""
echo "Le separateur de colonne IN est : '$scin'"
echo "Le sepateur de ligne IN est : '$slin'"
echo "Le separateur de colonne OUT est : '$scout'"
echo "Le separateur de ligne OUT est  : '$slout'"
