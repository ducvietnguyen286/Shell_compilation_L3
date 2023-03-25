set title 'Comparaison des algorithmes de tris'
set xlabel 'Taille de la liste'
set ylabel 'Nombre comparaisons'
plot 'resultat.dat' using 1:2 title 'Tri par Selection' with linespoints
replot 'resultat.dat' using 1:3 title 'Tri par insertion' with linespoints
replot 'resultat.dat' using 1:4 title 'Tri à Bulles' with linespoints
replot 'resultat.dat' using 1:5 title 'Tri Fusion' with linespoints
replot 'resultat.dat' using 1:6 title 'Tri Rapide' with linespoints
replot 'resultat.dat' using 1:7 title 'Tri par Tas' with linespoints
pause -1
