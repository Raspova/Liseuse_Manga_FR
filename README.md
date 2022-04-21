
![Banner](asset/banner.jpeg)
# Intro
Liseuse de Manga. 

Je voulais lire Berserk. Sushi-scan est le meilleur site de scan "gratuit". 

Mais : 

- Trop de pub (en haut, en bas, sur les côtés, addBlock est dectecté…une horreur). 
- Quand tu changes de page elle ne revient pas au bon niveau. 
- On ne peut pas zoomer sur l'image elle-même. 

Le but de mon projet : rendre l'environnement de lecture infiniment plus agréable.  

De
![ex](asset/reademeEx1.jpeg)
A
![exemple](asset/reademeEx.jpeg)


# Usage and install

The makefile is at the root (need the SFML library) :
```
make 
./liseuse MangaName Tome Page UploaderNumber
berserk : ./liseuse Berserk  1 0 -1
one punch man : ./liseuse OPM 1 0 2
```

En inspectant une page dans le navigateur, la page sushi-scan qui vous intéresse, vous verrez dans la partie network les ‘calls’ que fait le site à chaque changement de page, ça devrait ressembler à ceci : "https://i0.wp.com/sushi-scan.su/wp-content/uploads2/OPMTome1-001.jpg". De là vous pourrez tirer vos arguments : 

- MangaName : tout ce qu’il y a avant "Tome" jusqu'au '/' ici OPM 
- Tome : start at 1 
- UploaderNumber : numéro après "upload" dans l'url qu’on cible -1 s’il n'y a pas de numéro. 

C'est un peu fastidieux, je sais, mais ne vous inquiétez pas. Je planifie de rajouter un parseur qui automatisera tout ça pour vous un jour. Il ne marche pas avec tous les mangas, certains n'ayant pas le même début d'url, ce problème sera réglé avec le parseur, d'autres n'étant pas stockés en jpg, le problème sera réglé au cas par cas. 
 


#### Simple and Fast Multimedia Library (SFML )
`sudo apt-get install libsfml-dev`
OR
`sudo dnf install SFML-devel.x86_64`

#### Control

##### Mode normal

1. Click droit : page suivante 
1. Click milieu : précédente 
1. Molette : up - down de la page 
1. Molette + ctrl : zoom 
1. Click gauche : mode libre 

##### Mode libre 

1. La page suit les mouvements de la souris 
1. Molette : zoom
1. Click gauche : mode normal 

esc: exit 