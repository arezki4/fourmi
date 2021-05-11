#include <iostream>
#include <cmath>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iomanip>      // pour setfill, setw
#include <sstream>      // pour ostringstream
#include <fstream>      // pour ofstream
#include <string>

using namespace std;

#define ASSERT(test) if (!(test)) cout << "Test failed in file " << __FILE__ \
                                       << " line " << __LINE__ << ": " #test << endl



const int MAXGRILLE = 80 ;
const int MAXENCOORD = MAXGRILLE*MAXGRILLE ;

struct Coord { int abcisse ; int ordonne ; } ;

struct EnsCoord {
   Coord tabcoord[MAXENCOORD];
   int nbELTS ;
} ;////////////////////////////////////////////////////////////////////////


/**creer des nouvelle coordonnées
 * @param[in] int x : abcisse de la coordonée
 * @param[in] int y : ordonnée de la coordonnée
   return : une coordonnée
 */
Coord nouvCoord ( int x , int y ) {
   Coord c ;
    c.abcisse = x ;
    c.ordonne = y ;
    return c ;
}

 /** afficher une coordonnée
 * @param[in] : coordonnée c
 **/
void afficheCoord (Coord c ){
    cout << "(" << c.abcisse << "," << c.ordonne << ")" << endl ;
}


/** verifier l'egalité de deux coordonnées
 * @param[in] c1 :premiere coordonnée
 * @param[in] c2 : deuxieme coordonnée
 * return : VRAI si elles sont egales FAUX si non
 **/
bool egalcoord (Coord c1 , Coord c2 ) {
   return ( c1.abcisse == c2.abcisse and c1.ordonne == c2.ordonne ) ;
 }

/** tester la fonction egalcoord
 **/
void testegalcoord () {
  ASSERT ( egalcoord (nouvCoord(2,1),nouvCoord(2,1))) ;
  ASSERT ( egalcoord (nouvCoord(5,0),nouvCoord(5,0))) ;
  ASSERT ( not egalcoord (nouvCoord(2,0),nouvCoord(2,1))) ;
}
/** afficher un ensemble de coordonnées
 * @param[in] E :  un ensemble de coordonnées
 **/
void afficheEnsCoord (EnsCoord E) {
  for ( int i = 0 ; i < E.nbELTS ; i++ ) {
      afficheCoord (E.tabcoord[i]) ;
}
}


/** creer un ensemble de coordonnées
 * return : un ensemble de coordonnées
 **/
EnsCoord nouvEnsCoord() {EnsCoord E ;
E.nbELTS = 0 ;
return E ;
}


/** chercher une coordonéées dans un ensemble de coordonées
 * @param[in] E : ensemble de coordonnées
 * @param[in] c : la coordonnée rechercheé
 * return ; la position de la coordonée si elle existe ,-1 si non
 **/
int chercheCoord (EnsCoord E,Coord c ){
for ( int i =0 ; i<E.nbELTS ; i++ ) {
   if (egalcoord(E.tabcoord[i],c)){
     return i ;
    }
 }
   return  -1 ;
}



/** Ajouter une coordonnées à un ensemble de coord
 * @param[in/out] E : ensemble de coordonnées
 * @param[in] c : coordonnée ajoutée
 **/
void ajouteEnsCoord (EnsCoord &E , Coord c ){
 if (chercheCoord ( E , c ) == -1 ) {
 E.tabcoord[E.nbELTS] = c ;
 E.nbELTS ++ ;
 }
 }




/** Modifier le coefficient d'un polynome
 * @param[in/out] E : ensemble de coordonnées
 * @param[in] c : coonrdonnée enlevée
 **/
void enleveEnsCoord (EnsCoord &E,Coord c ) {
for (int i =0 ; i< E.nbELTS ; i++){
 if(egalcoord (E.tabcoord[i] , c )) {
     E.tabcoord[i] = E.tabcoord[E.nbELTS-1] ;
     E.nbELTS -- ;
     }
 }
}



/** trouver les voisin d'une coordonnées
 * @param[in] c : coordonnée dont on cherche les voisin
 * return  E :l'ensemble de coordonnées voisines de c .
 **/
EnsCoord voisine (Coord c ){
EnsCoord E ;
E =nouvEnsCoord() ;
 for (int i = -1 ; i <=1 ; i++ ) {
     for (int j = -1 ; j <= 1; j++) {
     int x0 = i+c.abcisse ;
     int y0 = j+c.ordonne ;
     Coord c0 = nouvCoord (x0,y0);
     if (0<= x0 and x0 < MAXGRILLE
          and 0 <= y0 and y0<MAXGRILLE
           and not egalcoord(c0,c )
           ){

         ajouteEnsCoord(E,c0) ;
      }
     }
  }
  return E ;
}


/** Modifier le coefficient d'un polynome
 * @param[in] E : ensemble de coordonnées
 * return c : coordonnées choisis au hasard de E
 **/
Coord choixCoordHasard (EnsCoord E ) {

  int i  = rand () % E.nbELTS ;
    return E.tabcoord[i];
}




const int NBFourmi = 12 ;

struct Fourmi { Coord cord ;  int numfourmi ; int prtsucre ; } ;

typedef Fourmi tabfourmi[NBFourmi] ;




/** creer une fourmi
 * @param[in] Coord c : coordonneé dans laquelle la fourmi va etre creer
 * @param[in]  int n : le numero de la fourmi creé
 * return f : une fourmi de numero n et de coord c
 **/
Fourmi creefourmi (Coord c , int n ) {
    Fourmi f ;
    f.cord.abcisse = c.abcisse ;
    f.cord.ordonne = c.ordonne ;
    f.numfourmi = n ;
    f.prtsucre = 0 ;
    return f ;
 }



/** Donner les coordonnées d'une fourmi
 * @param[in] f : Fourmi dont on veuc connaitre les coordonnées
 * return c : les coordonnées de la fourmi f
 **/
Coord coordFourmi (Fourmi f ) {
  return  nouvCoord (f.cord.abcisse , f.cord.ordonne ) ;
   }




/** Donner le numero d'une fourmi
 * @param[in] f : Fourmi dont on veuc connaitre le numero
 * return int n : le numero de la fourmi f
 **/
int numFourmi (Fourmi f) {
   return f.numfourmi ;
}


/** Verifier si une fourmi porte le sucre ou non .
 * @param[in] f : fourmi qu'on veux verifier
 * return bool : Vrai si la fourmi porte du sucre Faux si non
 **/
bool porteSucre (Fourmi f){
   return f.prtsucre == 1 ;
}

/** Tester la fonction porteSucre
**/
void testporteSucre () {
  Coord c = nouvCoord (1,2) ;
  Fourmi f = creefourmi (c,0);
  ASSERT ( not porteSucre (f) );
  f.prtsucre = 1 ;
  ASSERT ( porteSucre(f)) ;
 }

/**verifier si la fourmi cherche le sucre ou non
 * @param[in] f : Fourmi qu'on veux verifier
 * return bool : Vrai si la fourmi ne porte pas le sucre ( cherche sucre ) Faux si non .
 **/
bool chercheSucre (Fourmi f ){
   return f.prtsucre == 0 ;
   }

/**tester la fonction chercheSucre .
**/

void testchercheSucre () {
    Coord c = nouvCoord (2,3);
    Fourmi f = creefourmi (c,2);
    ASSERT (chercheSucre(f));
    f.prtsucre=1;
    ASSERT (not chercheSucre(f));
  }


/** Verifier si une fourmi rentre au nid ou non .
 * @param[in] f : fourmi qu'on veux verifier
 * return bool : Vrai si la fourmi rentre au nid Faux si non
 **/
bool rentreNid (Fourmi f ){
    return f.prtsucre == 1;
}

/** decharger le sucre d'une fourmi
 * @param[in/out] f : fourmi portante du sucre
 **/
void dechargeSucre (Fourmi &f){
     if (f.prtsucre ==1 ){
       f.prtsucre = 0 ;
    } else {
     cout << "erreur dechargeSucre !!!!!!!!!!!!!!!!!!!!!!! " << endl ;
     exit (1) ;
     }
  }



/** charger le sucre sur fourmi
 * @param[in/out] f : fourmi qui charge le sucre
 **/
void chargeSucre (Fourmi &f){
   if (f.prtsucre !=1 ){
    f.prtsucre =1 ;
  }
}


/** Modifier le coefficient d'un polynome
 * @param[in/out]  f : fourmi qu'on veux deplacer
 * @param[in] c : coordonnée vers laquelle la fourmi se deplace
 **/
void deplaceFourmi (Fourmi &f,Coord c){
   f.cord.abcisse = c.abcisse ;
   f.cord.ordonne = c.ordonne ;

}


/** charger un tableau de fourmi
 * @param[out] t : un tableau de fourmi
 * @param[in] E : un ensemble de coordonnées pour cree des fourmi
 **/
void chargerTabFourmi (tabfourmi t, EnsCoord E){
 if ( E.nbELTS < NBFourmi ) {
      cout << " vous n'avez pas assez de coordonnées  " << endl ;
         //exit (1);
   }
  for (int i = 0 ; i<NBFourmi ; i++){
      t[i] = creefourmi (E.tabcoord[i],i) ;
  }
}


/** Modifier le coefficient d'un polynome
 * @param[in] t : tableau de fourmi .
 **/
void afficheTab(tabfourmi f ) {
   for (int i =0 ; i< NBFourmi ; i++) {
      afficheCoord (f[i].cord) ;
    cout << " le numfourmi"  <<" " << f[i].numfourmi <<" " <<  "elle porteSucre "<< f[i].prtsucre << endl ;
   }
}







struct Place {Coord cord; float pheronid; int pherosucre; int nid; int sucre; int Indf;};



//typedef Place Grille[MAXGRILLE][MAXGRILLE] ;


/** Creer une Place Vide
 * @param[in] c : coordonnée dans laquelle on veux creer la Place vide
 * return P : une PLace vide .
 **/
Place  creeplaceVide (Coord c ){
   Place p ;
   p.cord = c ;
   p.pheronid = 0 ;
   p.pherosucre = 0 ;
   p.nid = 0 ;
   p.sucre = 0 ;
   p.Indf = -1 ;
   return p ;
 }

/** afficher une Place ( juste pour tester )
 * @param[in] P ; place qu'on veux afficher .
 **/
void afficheplace (Place p ) {
cout <<" les coord de place est " ;
afficheCoord (p.cord) ;
cout << " le pheronid " << " " << p.pheronid << endl ;
cout <<  " le pherosucre " << " "<< p.pherosucre << endl ;
cout <<  " le nid " << " " << p.nid << endl ;
cout << " le sucre" << " " << p.sucre << endl ;
cout << " le numero de fourmi "<< " " <<p.Indf << endl ;
}


/** Trouver les coordonneés d'une PLace
 * @param[in] P : Place qu'on veux connaitre les coordonnées
 * return Coord c : les coordonnées de la Place p .
 **/
Coord coordPlace (Place p ){
    return p.cord ;
}


/** Trouver l'intensité du pheronid d'une PLace
 * @param[in] P : Place qu'on veux connaitre son pheronid
 * return float  : l'intensité de pheronid de la Place p .
 **/
float pheroNid (Place p ) {
   return p.pheronid ;
}


/** Trouver l'intensité du pheroSUcre d'une PLace
 * @param[in] P : Place qu'on veux connaitre son pherosucre
 * return int : intensité de pherosucre de la Place p .
 **/
int pheroSucre (Place p ) {
   return p.pherosucre ;
}


/** Trouver le numero de la fourmi qui se trouve dans la place p ;
 * @param[in] P : Place qu'on veux connaitre sa fourmi
 * return int : le numero de la fourmi de la Place p .
 **/
int numeroFourmi (Place p ) {
    return p.Indf ;
}



/** verifier si une Place contient du sucre ou non
 * @param[in] P : la place qu' on veux verifier
 * @param[in] bool : Vrai si elle contient du sucre Faux si non
 **/
bool contientSucre (Place p ) {
  return p.sucre != 0 ;
}


/** verifier si une Place contient un nid ou non
 * @param[in] P : la place qu' on veux verifier
 * @param[in] bool : Vrai si elle contient un NId Faux si non
 **/
bool contientNid (Place p ) {
    return p.nid == 1 ;
}


/** verifier si une Place est sur une piste pour trouver du sucre
 * @param[in] P : la place qu' on veux verifier
 * @param[in] bool : Vrai si elle est sur une piste Faux si non
 **/
bool surUnePiste(Place p ){
     return p.pherosucre != 0 ;
 }


/** verifier si une Place est vide ou non
 * @param[in] P : la place qu' on veux verifier
 * @param[in] bool : Vrai si elle est vide  Faux si non
 **/
bool placeVide(Place p) {
    return  (p.Indf ==-1 and
             p.sucre== 0 and
             p.nid ==  0  );
}


/** Poser du sucre sur une place vide
 * @param[in/out] P : place ou on veux poser le sucre
 **/
void poserSucre (Place &p) {
     if (placeVide (p)) {
     p.sucre = 15 ;
 }
}



/** Poser un nid sur une place vide
 * @param[in/out] P : place ou on veux poser le nid
 **/
void poserNid (Place &p ) {
    if (placeVide(p)){
    p.nid = 1 ;
}
}



/** Poser une fourmi sur une place vide
 * @param[in/out] P : place ou on veux poser la fourmi
 **/
void poserFourmi (Place &p , Fourmi f) {
      if (placeVide (p)){
      p.Indf = f.numfourmi ;
   }
}


/** deminuer la quantité du sucre sur une place vide
 * @param[in/out] P : place ou on veux demineur la quantité du sucre
 **/
void deminuerSucre (Place &p){
   if(p.sucre >= 1 ) {
      p.sucre = p.sucre -1 ;
   }
}


/**enlever un fourmi d'une place vide
 * @param[in/out] P : place ou on veux enlever la fourmi
 **/
void enleverFourmi (Place &p ){
    if (p.Indf != -1 ) {
        p.Indf = -1 ;
    }
}


/** Poser du pheronid sur une place vide
 * @param[in/out] P : place ou on veux poser le pheronid
 **/
void poserPheroNid (Place &p , float x ){
   if (  0 <= x and x <= 1 ) {
      p.pheronid = x ;
    }
    else{
     cout << "pheronid invalide "<< endl ;
    }
}


/** Poser du pherosucresucre sur une place vide
 * @param[in/out] P : place ou on veux poser le pherosucre
 **/
void poserPheroSucre (Place &p ) {
   p.pherosucre = 255 ;
}


/** deminuer l'intensité du pherosucre sur une place vide
 * @param[in/out] P : place ou on veux deminuer l'intensité du pherosucre
 **/
void deminuerPheroSucre(Place &p){
   if (p.pherosucre >= 5 ) {
   p.pherosucre = p.pherosucre - 5 ;
   }
 }



/** deplacer la fourmi de la premiere place vers la deuxieme place
 * @param[in/out] f  : la fourmi qu'on veux deplacer
 * @param[in/out] p1 : la place ou se trouve la fourmi
 * @param[in/out] p2 : la place vers laquelle on veux deplacer la fourmi
 **/
void deplacerFourmi (Fourmi &f , Place &p1 , Place &p2) {
    enleverFourmi (p1) ;
    poserFourmi (p2,f);
    f.cord=p2.cord ;
 }

/** trouver la place la plus proche du nid
 * @param[in] p1 : place qu'on verifie
 * @param[in] p2 : place a laqulle on compare p1
 * return bool : Vrai si p est plus proche au nid que p2
 **/
bool plusProcheNid (Place p1 , Place p2) {
     return (p1.pheronid > p2.pheronid) ;
 }


/** trouver la place la plus loin du nid
 * @param[in] p1 : place qu'on verifie
 * @param[in] p2 : place a laqulle on compare p1
 * return bool : Vrai si p est plus loin au nid que p2
 **/
bool plusLoinNid (Place p1 , Place p2) {
   return  p1.pheronid < p2.pheronid ;
}


/** Tester les deux fonction plusLoinNid et PlusProcheNid
 **/
void testplusNid () {
  Coord c = nouvCoord (12,3);
  Coord c1 = nouvCoord(14,9);
  float x , y ;
  x=0.9 ;
  y= 0.5 ;
  Place p = creeplaceVide (c);
  Place p1 = creeplaceVide (c1) ;
  poserPheroNid(p,x);
  poserPheroNid(p1,y);
  ASSERT (plusProcheNid(p,p1)) ;
  ASSERT (not plusProcheNid(p1,p)) ;
  ASSERT (plusLoinNid(p1,p)) ;
  ASSERT (not plusLoinNid(p,p1)) ;
}





typedef Place Grille[MAXGRILLE][MAXGRILLE] ;


/** charger une grille Vide
 * @param[in] g : la grille qu'on veux charger
 **/
void chargerGrilleVide (Grille g){
   Coord c ;
     for (int i = 0 ; i < MAXGRILLE ; i++ ) {
          for (int j = 0 ; j < MAXGRILLE ; j++ ) {
             c = nouvCoord (i,j) ;
             g[i][j] = creeplaceVide (c) ;
          }
     }
}

/** afficher la grille sur le terminal ( debut du projet )
 * @param[in] g : la grille qu'on veux cherhcer
 **/
void afficheGrille (Grille g)  {
  for (int i = 0 ; i < MAXGRILLE ; i++ ) {
    for (int j = 0; j <MAXGRILLE; j++){
       if ( g[i][j].Indf != -1 ) {
       cout<<"F" ;
       }else if(g[i][j].nid==1){
       cout << "N" ;
       }else if (g[i][j].sucre!=0){
       cout<<"S" ;
       }else{
       cout<<" " ;
       }
    }
     cout << endl ;
  }
}


/** affichage de pheronid de la grille ( pour verifier l'initialisation du pheronid
 * @param[in] g : la grille qu'on veux affichée
 **/
void affichePheroNid (Grille g ){
    for (int i =0 ; i < MAXGRILLE ; i++ ) {
       for(int j=0;j<MAXGRILLE;j++){

           cout << g[i][j].pheronid ;
       }
             cout<<endl;
     }
}


/** charger une PLace d'une grille
 * @param[in] g : la grille a partir de la quelle on veux charger la place
 * @param[in] c : la cordonnée de la place qu'on veux charger
 * return p : la place qu'on a charger
 **/
Place chargerPlace (Grille g , Coord c ) {
   return g[c.abcisse][c.ordonne] ;
}


/** ranger une PLace d'une grille
 * @param[in] g : la grille dans la quelle on veux ranger la place
 * @param[in] c : la cordonnée de la place qu'on veux charger
 **/
void rangerPlace (Grille g , Place p ) {
     g[p.cord.abcisse][p.cord.ordonne] = p ;
 }



/** placer les nid dans la grille
 * @param[in/out] g : grille sur la quelle on intervient
 * @param[in] E : ensemble des coordonnée ou on pose les nid
 **/
void placerNid (Grille g , EnsCoord E ){
   Place p ;
    for (int i =0 ; i<E.nbELTS ; i++ ) {
           p=chargerPlace(g,E.tabcoord[i]) ;
           poserNid(p);
           rangerPlace(g,p);
    }
}



/** placer le sucre dans la grille
 * @param[in/out] g : grille sur la quelle on intervient
 * @param[in] E : ensemble des coordonnée ou on pose le sucre
 **/
void placerSucre (Grille g , EnsCoord E){
 Place p ;
      for(int i =0 ; i < E.nbELTS ;i++ ) {
        p=chargerPlace(g,E.tabcoord[i]) ;
        poserSucre (p) ;
        rangerPlace(g,p);
      }
}



/** placer les nid dans la grille
 * @param[in/out] g : grille sur la quelle on intervient
 * @param[in] t : tableau des fourmi qu'on veux poser
 **/
void PlacerFourmis (Grille g , tabfourmi t){
    Place p ;
    Coord c ;
    for ( int i= 0 ; i < NBFourmi ; i++ ) {
         c = t[i].cord ;
         p = chargerPlace(g,c);
         poserFourmi(p,t[i]);
         rangerPlace(g,p);
    }
}


/** Inisialiser une grille
 * @param[out] g : la grille qu'on veux initialise
 * @param[in] N : ensemble des coordonnées des nids
 * @param[in] S : ensemble des coordonnées des sucres
 * @param[in] t : tableau de fourmi
 **/
void initialiserGrille ( Grille g,  EnsCoord N ,  EnsCoord S , tabfourmi t ) {
       chargerGrilleVide(g);
       placerNid ( g, N ) ;
       placerSucre(g,S) ;
       PlacerFourmis(g,t);
    }


/** premiere linearisation de pheronid ( la position des nids )
 * @param[in] g : la grille dont on veux lineariser le pheronid
 **/
void linearise1PheroNid (Grille g){
       for (int i = 0 ; i < MAXGRILLE ; i++ ) {
           for (int j =0 ; j<MAXGRILLE ; j++ ) {
              if ( g[i][j].nid == 1 ) {
                  g[i][j].pheronid = 1 ;
              }
            }
       }
}


/** linearisation de pheronid de la grille ( totalité de la grille )
 * @param[in] g : la grille dont on veux lineariser le pheronid
 **/
void lineariserPheroNid (Grille g){
    bool encore ;
    Place pv , pc ;
    Coord c ;
    EnsCoord E ;
    float m, phv,phc ;
    linearise1PheroNid(g);
  do {
    encore=false ;
       for (int i = 0 ; i < MAXGRILLE ; i++ ) {
          for (int j =0 ; j <MAXGRILLE ; j++) {
              c = nouvCoord(i,j) ;
              m = 0 ;
              E = voisine (c);
                for ( int n=0 ; n<E.nbELTS ; n++) {
                   pv=chargerPlace(g,E.tabcoord[n]);
                   phv = pheroNid(pv);
                   if (phv>m){
                      m = phv ;
                   }
                }
              m = max ( m- (float(1)/MAXGRILLE) , float(0) ) ;
             pc = chargerPlace (g,c);
             phc=pheroNid(pc);
               if (m>phc){
                 poserPheroNid(pc,m);
                 rangerPlace(g,pc);
                 encore=true ;
               }
          }
      }
  }
   while (encore) ;
}


/** deminuer pherosucre pour toute la grille
 * @param[in/out] g : la grille dont on veux deminuer le pherosucre
 **/
void deminuer_1_PheroSucre (Grille g){
    Coord c ;
    Place p ;
      for (int i =0;i<MAXGRILLE ; i++) {
         for (int j = 0 ; j < MAXGRILLE ; j++ ) {
                c = nouvCoord(i,j);
                p = chargerPlace (g,c);
                deminuerPheroSucre(p);
                rangerPlace(g,p);
        }
      }
}




/** premiere condition de deplacement
 * @param[in] f : fourmi qu'on veux deplacer
 * @param[in] p1 : place initiale de la fourmi
 * @param[in] p2 : place qu'on verifie si la condition 1 s'applique pour faire le deplacement
 * return bool : Vrai si la condition s'applique Faux si non
 **/
bool condition_1 (Fourmi f , Place p1 , Place p2 ) {
      return chercheSucre(f) and contientSucre (p2);
  }


/**premiere action : charger le sucre
 * @param[in/out] f : fourmi qu'on veux deplacer
 * @param[in/out] p1 : place initiale de la fourmi
 * @param[in/out] p2 : place d'ou la fourmi charge le sucre.
**/
void action_1 (Fourmi &f , Place &p1 ,Place &p2 ) {
     chargeSucre (f) ;
     deminuerSucre(p2) ;
     if ( p2.sucre > 0 ) {
     poserPheroSucre(p1);
     }
}

/** deuxieme condition de deplacement
 * @param[in] f : fourmi qu'on veux deplacer
 * @param[in] p1 : place initiale de la fourmi
 * @param[in] p2 : place qu'on verifie si la condition 2 s'applique pour faire le deplacement
 * return bool : Vrai si la condition s'applique Faux si non
 **/
bool  condition_2 (Fourmi f , Place p1 , Place p2 ){
    return rentreNid (f) and contientNid (p2) ;
}


/**deuxieme action : decharger le sucre
 * @param[in/out] f : fourmi qu'on veux deplacer
 * @param[in/out] p1 : place initiale de la fourmi
 * @param[in/out] p2 : place ou la fourmi decharge le sucre (nid).
**/
void action_2 (Fourmi &f , Place &p1, Place &p2){
       dechargeSucre (f) ;
       poserPheroSucre(p1);
}

/** troisieme condition de deplacement
 * @param[in] f : fourmi qu'on veux deplacer
 * @param[in] p1 : place initiale de la fourmi
 * @param[in] p2 : place qu'on verifie si la condition 3 s'applique pour faire le deplacement
 * return bool : Vrai si la condition s'applique Faux si non
 **/
bool condition_3 (Fourmi f , Place p1, Place p2){
   return    rentreNid(f)
         and placeVide(p2)
         and plusProcheNid(p2,p1);
  }


/**troisieme action : rentre vers le nid
 * @param[in/out] f : fourmi qu'on veux deplacer
 * @param[in/out] p1 : place initiale de la fourmi
 * @param[in/out] p2 : place vers laquelle la fourmi se deplace pour rentrer au nid
**/
void action_3 (Fourmi &f , Place &p1, Place &p2){
     deplacerFourmi(f,p1,p2) ;
     poserPheroSucre(p1);
  }

/** quatrieme condition de deplacement
 * @param[in] f : fourmi qu'on veux deplacer
 * @param[in] p1 : place initiale de la fourmi
 * @param[in] p2 : place qu'on verifie si la condition 4 s'applique pour faire le deplacement
 * return bool : Vrai si la condition s'applique Faux si non
 **/
bool condition_4 (Fourmi f , Place p1, Place p2){
     return           chercheSucre(f)
               and    surUnePiste(p1)
               and    placeVide(p2)
               and    plusLoinNid(p2,p1)
               and    surUnePiste(p2) ;
  }


/**quatrieme action : cherche le sucre1
 * @param[in/out] f : fourmi qu'on veux deplacer
 * @param[in/out] p1 : place initiale de la fourmi
 * @param[in/out] p2 : place vers laquelle la fourmi se deplace pour cherche le sucre
**/
void action_4 (Fourmi &f , Place &p1, Place &p2){
           deplacerFourmi(f,p1,p2) ;
 }



/**Cinqiéme condition de deplacement
 * @param[in] f : fourmi qu'on veux deplacer
 * @param[in] p1 : place initiale de la fourmi
 * @param[in] p2 : place qu'on verifie si la condition 5 s'applique pour faire le deplacement
 * return bool : Vrai si la condition s'applique Faux si non
 **/
bool condition_5 (Fourmi f , Place p1, Place p2 ) {
     return        chercheSucre(f)
             and   surUnePiste(p2)
             and   placeVide(p2) ;
 }


/**quatrieme action : cherche le sucre2
 * @param[in/out] f : fourmi qu'on veux deplacer
 * @param[in/out] p1 : place initiale de la fourmi
 * @param[in/out] p2 : place vers laquelle la fourmi se deplace pour cherche le sucre
**/
void action_5 (Fourmi &f, Place &p1, Place &p2 ) {
             deplacerFourmi(f,p1,p2) ;
 }

/** sixieme condition de deplacement
 * @param[in] f : fourmi qu'on veux deplacer
 * @param[in] p1 : place initiale de la fourmi
 * @param[in] p2 : place qu'on verifie si la condition 6 s'applique pour faire le deplacement
 * return bool : Vrai si la condition s'applique Faux si non
 **/
bool condition_6 (Fourmi &f , Place &p1, Place &p2) {
         return chercheSucre(f) and placeVide(p2) ;
  }

/**quatrieme action : se deplacer dans l'espoire de trouver le sucre
 * @param[in/out] f : fourmi qu'on veux deplacer
 * @param[in/out] p1 : place initiale de la fourmi
 * @param[in/out] p2 : place vers laquelle la fourmi se deplace
**/
void action_6 (Fourmi &f , Place &p1, Place &p2){
                 deplacerFourmi(f,p1,p2) ;
 }




/** verification des conditions suivant le numero de la condition
 * @param[in] int i : le numero de la condition
 * @param[in] f : fourmi qu'on veux deplacer
 * @param[in] p1 : place initiale de la fourmi
 * @param[in] p2 : place qu'on verifie si la condition 6 s'applique pour faire le deplacement
 * return bool : Vrai si la condition s'applique Faux si non
 **/
bool condition_n (int i , Fourmi f , Place p1, Place p2 ){
    if (i==1){
         return condition_1 (f,p1,p2);
     }else if (i==2){
         return condition_2 (f,p1,p2);
     }else if (i ==3 ) {
      return condition_3 (f,p1,p2);
      }else if (i==4){
         return condition_4(f,p1,p2);
      }else if (i==5){
         return condition_5(f,p1,p2);
      }else if (i==6){
          return condition_6(f,p1,p2);
       }else {
         cout << "erreur condition ;;;;;;;;;;;;;;;;;;;;;;;;;;"<<endl ;
         exit(1) ;
      }
  }


/**execution de l'action_n suivant l'indice i .
 * @param[in] int i  : le numero de l'action
 * @param[in/out] f  : fourmi qu'on veux deplacer
 * @param[in/out] p1 : place initiale de la fourmi
 * @param[in/out] p2 : place vers laquelle s'execute l'action
**/
void action_n (int i , Fourmi &f , Place &p1, Place &p2){
         if(i==1 ) {
           action_1(f,p1,p2);
         }else if (i==2){
            action_2(f,p1,p2);
         }else if (i==3){
              action_3(f,p1,p2);
         }else if(i==4){
              action_4(f,p1,p2);
         }else if(i==5){
              action_5(f,p1,p2);
          }else if(i==6){
             action_6(f,p1,p2);
          }else{
            cout << "erreur action,;;;;;;;;;;;;;;;;;;;;;;;"<<endl;
            exit(1);
           }
 }




// variable globale permettant de creer des noms de fichiers differents
int compteurFichier = 0;



/** dessiner une image de la grille pour une itteration
 * @param[in] g ; Grille qu'on veux dessiner
 **/
void dessinerImage(Grille g ){
int i,j;
int r,v,b;
ostringstream filename;
// creation d’un nouveau nom de fichier de la forme img347.ppm
filename<< "img" << setfill('0')<<setw(3) << compteurFichier <<".ppm" ;
//filename << "img" << setfill(’0’) << setw(3) << compteurFichier << ".ppm";
compteurFichier++;
cout << "Ecriture dans le fichier : " << filename.str() << endl;
// ouverture du fichier
ofstream fic(filename.str(), ios::out | ios::trunc);

// ecriture de l’entete
fic << "P3" << endl
<< MAXGRILLE << " " << MAXGRILLE << " " << endl
<< 255 << " " << endl;
// ecriture des pixels
    for (i = 0; i < MAXGRILLE; i++){
            for (j = 0; j < MAXGRILLE; j++){
// calcul de la couleur
                if (g[i][j].Indf != -1) {
                    r = 0;
                    v = 0;
                    b = 0;
                }else if (g[i][j].nid == 1 ) {
                    r =0 ;
                    v=0 ;
                    b=255;
                }else if (g[i][j].sucre !=0){
                    r=255 ;
                    v=255 ;
                    b=255 ;
                }else if (g[i][j].pherosucre !=0 ) {
                    r=((float(g[i][j].pherosucre)/255)*255)+60;
                    v=(((float(g[i][j].pherosucre)/255)*255)/3)+60 ;
                    b=0;
                }else {
                    r = 0;
                    v = g[i][j].pheronid*255;
                     b = 255;
                }
        // ecriture de la couleur dans le fichier
            fic << r << " " << v << " " << b << "    ";
        }
       // fin de ligne dans l’image
         fic << endl;
    }
// fermeture du fichier
  fic.close();
}





/**Mettre a jour une fourmi
 * @param[in/out] g : une Grille
 * @param[in/out] f : la fourmi qu'on veux mettre a jour
   return : une coordonnée
 */
void mettre_a_jour(Grille g , Fourmi &f ) {
   Coord cv ;
   Place pv ;
   Coord cf = coordFourmi (f);
   Place pf = chargerPlace(g,cf);
   EnsCoord E = voisine (cf) ;
   EnsCoord E_i =  nouvEnsCoord() ;
      for (int i=1;i<=6;i++){
          for(int j=0;j<E.nbELTS;j++){
          cv = E.tabcoord[j];
          pv = chargerPlace(g,cv);
             if (condition_n( i ,  f ,  pf,  pv )){
                     for (int n=0;n<E.nbELTS;n++){
                          cv =  E.tabcoord[n];
                          pv = chargerPlace(g,cv);
                        if(condition_n( i,  f ,  pf,  pv )){
                          ajouteEnsCoord (E_i,pv.cord);
                        }
                     }
                   cv = choixCoordHasard ( E_i );
                   pv = chargerPlace(g,cv);
                   action_n (i ,  f ,  pf,  pv);
                   rangerPlace(g,pf);
                   rangerPlace(g,pv);
                   return ;
                 }
         }
     }
}

 int main() {
    int abcisse ,ordonne ;

    ///////////////////////////////////////////////
   ////    Ensemble cooredonnées des Fourmi   ////
  ///////////////////////////////////////////////


   EnsCoord Ef = nouvEnsCoord();
   Coord cf ;
     for ( int i = 0 ; i < 12 ; i++ ) {
       abcisse=rand()%60;
       ordonne=rand()%60;
       cf = nouvCoord(abcisse,ordonne);
       ajouteEnsCoord (Ef,cf);
    }



   //////////////////////////////////////////////////
  /////    Ensemble des coordonnées des Nid   //////
 //////////////////////////////////////////////////


   Coord cn1 , cn2 ;
   EnsCoord En = nouvEnsCoord();
   cn1 = nouvCoord (10,10);
   cn2 = nouvCoord (MAXGRILLE-10,MAXGRILLE-10);

   ajouteEnsCoord(En, cn1);
   ajouteEnsCoord(En, cn2);



    ///////////////////////////////////////////////
   ////   Ensemble des Coordonnées du Sucre   ////
  ///////////////////////////////////////////////

     EnsCoord Es = nouvEnsCoord();
     Coord cs ;
     for ( int i = 0 ; i < MAXGRILLE/2 ; i++ ) {
       abcisse=rand()%MAXGRILLE;
       ordonne=rand()%MAXGRILLE;
       cs = nouvCoord(abcisse,ordonne);
       ajouteEnsCoord (Es,cs);
    }

    ////////////////////////////////
   /////     Simulation       /////
  ////////////////////////////////


    Grille G ;
    tabfourmi t ;
    chargerGrilleVide(G);
    chargerTabFourmi(t,Ef) ;
    initialiserGrille(G,En,Es,t);
    lineariserPheroNid(G);
    affichePheroNid (G);
    dessinerImage(G);
    for(int i =0 ; i<10000;i++){
     for(int j =0 ; j< NBFourmi;j++){
               mettre_a_jour(G,t[j]);
          }
      dessinerImage(G) ;
      deminuer_1_PheroSucre(G) ;
    }

}








