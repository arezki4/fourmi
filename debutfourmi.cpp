#include <iostream>
#include <cmath>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <map>
#include <iomanip>      // pour setfill, setw
#include <sstream>      // pour ostringstream
#include <fstream>      // pour ofstream
#include <string>

using namespace std;
// variable globale permettant de creer des noms de fichiers differents
int compteurFichier = 0;

#define ASSERT(test) if (!(test)) cout << "Test failed in file " << __FILE__ \
                                       << " line " << __LINE__ << ": " #test << endl



const int MAXGRILLE = 40 ;
const int MAXENCOORD = MAXGRILLE*MAXGRILLE ;
const int NBFourmi = 12 ;

///////////////////////////////Les Structures///////////////////////////

struct Coord { int abcisse ;
               int ordonne ;
} ;

struct EnsCoord {
   Coord tabcoord[MAXENCOORD];
   int nbELTS ;
} ;

struct Fourmi { Coord cord ;
                int numfourmi ;
                int prtsucre ;
} ;

typedef Fourmi tabfourmi[NBFourmi] ;

struct Place {Coord cord;
              float pheronid;
              int pherosucre;
              int nid;
			  int sucre;
              int Indf;
};

typedef Place Grille[MAXGRILLE][MAXGRILLE] ;

////////////////////////////////////////////////////////coordonnées ///////////////////////////////////////////////

Coord nouvCoord ( int x , int y ) {
   Coord c ;
    c.abcisse = x ;
    c.ordonne = y ;
    return c ;
}


void afficheCoord (Coord c ){
    cout << "(" << c.abcisse << "," << c.ordonne << ")" << endl ;
}




bool egalcoord (Coord c1 , Coord c2 ) {
    return ( c1.abcisse == c2.abcisse and c1.ordonne == c2.ordonne ) ;
 }


void testegalcoord () {
  ASSERT ( egalcoord (nouvCoord(2,1),nouvCoord(2,1))) ;
  ASSERT ( egalcoord (nouvCoord(5,0),nouvCoord(5,0))) ;
  ASSERT ( not egalcoord (nouvCoord(2,0),nouvCoord(2,1))) ;
}

void afficheEnsCoord (EnsCoord E) {
  for ( int i = 0 ; i < E.nbELTS ; i++ ) {
      afficheCoord (E.tabcoord[i]) ;
}
}

EnsCoord nouvEnsCoord() {
EnsCoord E ;
E.nbELTS = 0 ;
return E ;
}


int chercheCoord (EnsCoord E,Coord c ){
for ( int i =0 ; i<E.nbELTS ; i++ ) {
   if (egalcoord(E.tabcoord[i],c)){
     return i ;
    }
 }
   return  -1 ;
}


void ajouteEnsCoord (EnsCoord &E , Coord c ){
 if (chercheCoord ( E , c ) == -1 ) {
 E.tabcoord[E.nbELTS] = c ;
 E.nbELTS ++ ;
 }
 }

void enleveEnsCoord (EnsCoord &E,Coord c ){
for (int i =0 ; i< E.nbELTS ; i++){
 if(egalcoord (E.tabcoord[i] , c )) {
     E.tabcoord[i] = E.tabcoord[E.nbELTS-1] ;
     E.nbELTS -- ;
     }
 }
}


EnsCoord voisine (Coord c ){
EnsCoord E ;
E =nouvEnsCoord() ;
//Coord c0 ;
 for (int i = -1 ; i <=1 ; i++ ) {
     for (int j = -1 ; j <= 1; j++) {
     int x0 = i+c.abcisse ;
     int y0 = j+c.ordonne ;
     Coord c0 = nouvCoord (x0,y0);
     if (0<= x0 and x0 < MAXGRILLE
          and 0 <= y0 and y0<MAXGRILLE
           and not egalcoord(c0,c ))
           {

         ajouteEnsCoord(E,c0) ;
      }
     }
  }
  return E ;
}


Coord choixCoordHasard (EnsCoord E ) {

  int i  = rand () % E.nbELTS ;

  return E.tabcoord[i];
}



/*
////////////////////////////////////////////////////////le main pour tester les coordonnées /////////////////////////////////////////
int main () {
 //srand (time(null)) ;
Coord c0 = nouvCoord (2,1) ;
afficheCoord (c0) ;
testegalcoord();
Coord c1 = nouvCoord(2,1);
Coord c2 = nouvCoord(3,4);
Coord c3 = nouvCoord(0,0);
EnsCoord E = nouvEnsCoord();
ajouteEnsCoord (E,c1);
ajouteEnsCoord (E,c2);
ajouteEnsCoord (E,c3);
afficheEnsCoord(E) ;
cout<<"ajout d'un element :" << endl ;
ajouteEnsCoord (E,nouvCoord(4,0));
afficheEnsCoord(E) ;
cout <<" deuxieme ajout" << endl;
ajouteEnsCoord (E,nouvCoord(4,0));
afficheEnsCoord(E) ;
cout << "enlever element" << endl;
enleveEnsCoord(E,c1);
afficheEnsCoord(E) ;
EnsCoord f = nouvEnsCoord();
Coord c1 = nouvCoord(0,0);
f = voisine (c1) ;
afficheEnsCoord(f) ;
Coord c5 = choixCoordHasard(f) ;
afficheCoord (c5) ;
} */






/////////////////////////////////////////////////FOURMI ///////////////////////////////////////////////////



Fourmi creefourmi (Coord c , int n ) {
    Fourmi f ;
    f.cord.abcisse = c.abcisse ;
    f.cord.ordonne = c.ordonne ;
    f.numfourmi = n ;
    f.prtsucre = 0 ;
    return f ;
 }

///////////fonction qui retourne les coordonées d'une fourmi


Coord coordFourmi (Fourmi f ) {
  return  nouvCoord (f.cord.abcisse , f.cord.ordonne ) ;
   }




//////////fonction qui retourne le numéro d'une fourmi


int numFourmi (Fourmi f) {
   return f.numfourmi ;
}


////////////fonction qui renvoie vrai si la fourmi porte du sucre ,faux si non


bool porteSucre (Fourmi f){
   return f.prtsucre == 1 ;
}


////////////tester la fonction porteSucre

void testporteSucre () {
  Coord c = nouvCoord (1,2) ;
  Fourmi f = creefourmi (c,0);
  ASSERT ( not porteSucre (f) );
  f.prtsucre = 1 ;
  ASSERT ( porteSucre(f)) ;
 }

//////////fonction qui renvoie vrai si la fourmi ne porte pas de sucre , faux si non

bool chercheSucre (Fourmi f ){
   return f.prtsucre == 0 ;
   }

/////////tester la fonction chercheSucre .

void testchercheSucre () {
    Coord c = nouvCoord (2,3);
    Fourmi f = creefourmi (c,2);
    ASSERT (chercheSucre(f));
    f.prtsucre=1;
    ASSERT (not chercheSucre(f));
  }



bool rentreNid (Fourmi f ){
    return f.prtsucre == 1;
}


void dechargeSucre (Fourmi &f){
     if (f.prtsucre ==1 ){
       f.prtsucre = 0 ;
  }
}


void chargeSucre (Fourmi &f){
   if (f.prtsucre !=1 ){
    f.prtsucre =1 ;
  }
}


void deplaceFourmi (Fourmi &f,Coord c){
   f.cord.abcisse = c.abcisse ;
   f.cord.ordonne = c.ordonne ;

}


void chargerTabFourmi (tabfourmi t, EnsCoord E){
 if ( E.nbELTS < NBFourmi ) {
      cout << " vous n'avez pas assez de coordonnées  " << endl ;
         //exit (1);
   }
  for (int i = 0 ; i<NBFourmi ; i++){
      t[i] = creefourmi (E.tabcoord[i],i) ;
  }
}


void afficheTab(tabfourmi f ) {
   for (int i =0 ; i< NBFourmi ; i++) {
      afficheCoord (f[i].cord) ;
    cout << " le numfourmi"  <<" " << f[i].numfourmi <<" " <<  "elle porteSucre "<< f[i].prtsucre << endl ;
   }
}


/*int main () {
   Coord c0 , c1,c3,c4,c5,c6 ;
   Fourmi f ;
   tabfourmi Tabf ;
   c0 = nouvCoord (2,1);
   c1 = nouvCoord (2,0);
   f = creefourmi ( c0 , 0 ) ;
  // afficheCoord (f.cord);
  //
 cout << "apres deplacement " << endl ;
   deplaceFourmi (f,c1) ;
  // afficheCoord (f.cord ) ;
   EnsCoord E = nouvEnsCoord();
   Coord c2 = nouvCoord(2,1);
   E = voisine (c2) ;
   c3 = nouvCoord (11,8);
   c4 = nouvCoord (12,9);
   c5 = nouvCoord (13,9);
   c6 = nouvCoord (17,25 ) ;
   ajouteEnsCoord (E,c3);
   ajouteEnsCoord (E,c4);
   ajouteEnsCoord (E,c5);
   ajouteEnsCoord (E,c6);
   afficheEnsCoord(E) ;
   chargerTabFourmi(Tabf,E) ;
   cout << "apres chrgement " << endl ;
   afficheTab (Tabf);
    cout << f.prtsucre << endl ;
   cout << f.numfourmi << endl ;
   afficheCoord (coordFourmi (f)) ;
   testporteSucre() ;
   testchercheSucre();
   } */


//////////////////////////////////////////////////////////////////////Grille ///////////////////////////////////////////////////////


///////////////constructeur /////////////////////
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

void afficheplace (Place p ) {
cout <<" les coord de place est " ;
afficheCoord (p.cord) ;
cout << " le pheronid " << " " << p.pheronid << endl ;
cout <<  " le pherosucre " << " "<< p.pherosucre << endl ;
cout <<  " le nid " << " " << p.nid << endl ;
cout << " le sucre" << " " << p.sucre << endl ;
cout << " le numero de fourmi "<< " " <<p.Indf << endl ;
}
//////// acces /////////////
Coord coordPlace (Place p ){
    return p.cord ;
}


float pheroNid (Place p ) {
   return p.pheronid ;
}

int pheroSucre (Place p ) {
   return p.pherosucre ;
}

////////////////////////////////predicat sur une place ////////////////////////////////////////////////

int numeroFourmi (Place p ) {
    return p.Indf ;
}

bool contientSucre (Place p ) {
  return p.sucre != 0 ;
}

bool contientNid (Place p ) {
    return p.nid == 1 ;
}


bool surUnePiste(Place p ){
     return p.pherosucre != 0 ;
 }
bool placeVide(Place p) {
    return  (p.Indf ==-1 and
             p.sucre== 0 and
             p.nid ==  0  );
}

/////////////////////////  Modification  /////////////////////

void poserSucre (Place &p) {
     if (placeVide (p)) {
     p.sucre = 15 ;
 }
}

void poserNid (Place &p ) {
    if (placeVide(p)){
    p.nid = 1 ;
}
}

void poserFourmi (Place &p , Fourmi f) {
      if (placeVide (p)){
      p.Indf = f.numfourmi ;
   }
}


void enleverFourmi (Place &p ){
    if (p.Indf != -1 ) {
        p.Indf = -1 ;
    }
}

void poserPheroNid (Place &p , float x ){
   if (  0 <= x and x <= 1 ) {
      p.pheronid = x ;
    }
    else{
     cout << "pheronid invalide "<< endl ;
    }
}

void poserPheroSucre (Place &p ) {
   p.pherosucre = 255 ;
}

void diminuerPheroSucre(Place &p){
   if (p.pherosucre >= 5 ) {
   p.pherosucre = p.pherosucre - 5 ;
   }
 }




////////////// modification sur////////////////////// deux place //////////////////

void deplacerFourmi (Fourmi &f , Place &p1 , Place &p2) {
    enleverFourmi (p1) ;
    poserFourmi (p2,f);
    f.cord=p2.cord ;
 }


bool plusProcheNid (Place p1 , Place p2) {
     return (p1.pheronid > p2.pheronid) ;
 }

bool plusLoinNid (Place p1 , Place p2) {
   return  p1.pheronid < p2.pheronid ;
}

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



//////////////////////////////////////  main PLACCEEEEEE //////////////
/*int main () {
    testplusNid () ;
    Coord c = nouvCoord (3,11);
    Coord c1 = nouvCoord (11,3) ;
 	Place p = creeplaceVide (c);
 	Place p1 = creeplaceVide (c1) ;
 	Fourmi f  = creefourmi ( c , 0 ) ;
 	float x = 0.9 ;
    afficheplace (p) ;
    cout << "apres modification" << endl ;
    poserFourmi (p,f);
    poserSucre (p);
    poserNid (p) ;
    poserPheroNid(p,x);
    afficheplace(p);
    deplacerFourmi (f,p,p1);
    afficheplace (p) ;
    cout<<"place 2 " << endl ;
    afficheplace (p1) ;
    cout << " fourmi" << endl ;
    afficheCoord (f.cord);

    }*/





/////////////////////////////////////////GRILLE//////////////////////////////////////////////////////////

///////////constructeur /////////////////

void chargerGrilleVide (Grille g){
   Coord c ;
     for (int i = 0 ; i < MAXGRILLE ; i++ ) {
          for (int j = 0 ; j < MAXGRILLE ; j++ ) {
             c = nouvCoord (i,j) ;
             g[i][j] = creeplaceVide (c) ;
          }
     }
}

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

void affichePheroNid (Grille g ){
    for (int i =0 ; i < MAXGRILLE ; i++ ) {
       for(int j=0;j<MAXGRILLE;j++){

           cout << g[i][j].pheronid ;
       }
             cout<<endl;
     }
}

////////////////////////////////////////////acces et modification ///////////////////////////////////////////////////

Place chargerPlace (Grille g , Coord c ) { //////////////////pour accéder à une place à modifier dans la Grille.
   return g[c.abcisse][c.ordonne] ;
}


void rangerPlace (Grille g , Place p ) {//////////////////////pour ranger la place dans la Grille aprés l'avoir modifier.
     g[p.cord.abcisse][p.cord.ordonne] = p ;
 }


////////////placer des nid dans une grille avec un ensemble de coord

void placerNid (Grille g , EnsCoord E ){
   Place p ;
    for (int i =0 ; i<E.nbELTS ; i++ ) {
           p=chargerPlace(g,E.tabcoord[i]) ;
           poserNid(p);
           rangerPlace(g,p);
    }
}


/////////////placer du sucre dans une grille avec un ensemble de coord


void placerSucre (Grille g , EnsCoord E){
 Place p ;
      for(int i =0 ; i < E.nbELTS ;i++ ) {
        p=chargerPlace(g,E.tabcoord[i]) ;
        poserSucre (p) ;
        rangerPlace(g,p);
      }
}


///////////placer des fourmi dans une grille


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



///////////////////////////////initialiser une grille /////////////////////////////////////////

void initialiserGrille ( Grille g,  EnsCoord N ,  EnsCoord S , tabfourmi t ) {
       chargerGrilleVide(g);
       placerNid ( g, N ) ;
       placerSucre(g,S) ;
       PlacerFourmis(g,t);
    }



void linearise1PheroNid (Grille g){
       for (int i = 0 ; i < MAXGRILLE ; i++ ) {
           for (int j =0 ; j<MAXGRILLE ; j++ ) {
              if ( g[i][j].nid == 1 ) {
                  g[i][j].pheronid = 1 ;
              }
            }
       }
}

///////////////////l'inerarise l'intensite du pheroNid dans la grille

void lineariserPheroNid (Grille g){
    bool encore ;
    Place pv , pc ;
    Coord c ;
    EnsCoord E ;
    float max, phv,phc ;
    linearise1PheroNid(g);
  do {
    encore=false ;
       for (int i = 0 ; i < MAXGRILLE ; i++ ) {
          for (int j =0 ; j <MAXGRILLE ; j++) {
              E = nouvEnsCoord() ;
              c = nouvCoord(i,j) ;
              E = voisine (c);
                for ( int n=0 ; n<E.nbELTS ; n++) {
                   pv=chargerPlace(g,E.tabcoord[n]);
                   phv = pheroNid(pv);
                   if (phv>max){
                      max = phv ;
                   }
                }
             if(max-(1/MAXGRILLE)>0){
              max = max-(float(1)/MAXGRILLE) ;
             }else{
              max = 0 ;
             }
             // = max ( m- (1/MAXGRILLE) , 0.00 ) ;
             pc = chargerPlace (g,c);
             phc=pheroNid(pc);
               if (max>phc){
                 poserPheroNid(pc,max);
                 rangerPlace(g,pc);
                 encore=true ;
               }
          }
      }
  }
   while (encore) ;
}

//////////////////////evaporation du pheroSucre

void diminuerPheroSucre (Grille g){
    Coord c ;
    Place p ;
      for (int i =0;i<MAXGRILLE ; i++) {
         for (int j = 0 ; j < MAXGRILLE ; j++ ) {
                c = nouvCoord(i,j);
                p = chargerPlace (g,c);
                diminuerPheroSucre(p);
                rangerPlace(g,p);
        }
      }
}

///////////////////////////////////condition et action///////////////////Régle de deplacement///////////////////////////////

bool condition1(Fourmi f ,Place p1 ,Place p2 ){
	return chercheSucre(f) && contientSucre(p2);
}

void action1(Fourmi &f ,Place &p1 ,Place &p2){
	chargeSucre(f);
	poserPheroSucre(p1);
}

bool condition2(Fourmi f ,Place p1 ,Place p2 ){
	return rentreNid(f)&& contientNid(p2);
}

void action2(Fourmi &f ,Place &p1 ,Place &p2){
     poserSucre(p2);
}

bool condition3(Fourmi f ,Place p1 ,Place p2 ){
 	 return rentreNid(f) && placeVide(p2) && plusProcheNid(p2,p1);
}

void action3(Fourmi &f ,Place &p1 ,Place &p2){
	deplacerFourmi(f,p1,p2);
	pheroSucre(p2);
}

bool condition4(Fourmi f ,Place p1 ,Place p2 ){
	return chercheSucre(f) && surUnePiste(p1) && placeVide(p2) && plusLoinNid(p2,p1) && surUnePiste(p2);
}

void action4(Fourmi &f ,Place &p1 ,Place &p2){
	deplacerFourmi(f,p1,p2);
}

bool condition5(Fourmi f ,Place p1 ,Place p2 ){
	return chercheSucre(f)&& surUnePiste(p2) && placeVide(p2);
}

void action5(Fourmi &f ,Place &p1 ,Place &p2 ){
	deplacerFourmi(f,p1,p2);
}

bool condition6(Fourmi f ,Place p1 ,Place p2 ){
	return chercheSucre(f) && placeVide(p2);
}

void action6(Fourmi &f ,Place &p1 ,Place &p2){
	deplacerFourmi(f,p1,p2);
}


////////////////////////////////Mouvements des fourmis/////////////////////////////////////

bool condition_n(int n,Fourmi f ,Place p1 ,Place p2 ){
	if (n=1){
		return condition1;
	}
	else if (n=2){
		return condition2;
	}
	else if (n=3){
		return condition3;
	}
	else if (n=4){
		return condition4;
	}
	else if (n=5){
		return condition5;
	}
	else if (n=6){
		return condition6;
	}
	else{
		return cout<<"erreur"<<endl;
	exit(1);
	}
}


void action_n(int n,Fourmi &f ,Place &p1 ,Place &p2){
	if(n=1){action1;}
	else if(n=2){action2;}
	else if(n=3){action3;}
	else if(n=4){action4;}
	else if(n=5){action5;}
	else if(n=6){action6;}
	else{ cout<<"erreur"<<endl;
	exit(1);
	}
}

//////////////////////////////////Fonction de mise a jour des fourmis/////////////////////////////////////
void MAJuneFourmi(Grille &g , Fourmi &f){
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


//////////////////////////////////////les Fonction Vérif//////////////////////////////////////
void VerifGrilleCoord(Grille g){/////////////////test que tout est cohérent
	 for (int i = 0 ; i < MAXGRILLE ; i++ ) {
          for (int j =0 ; j <MAXGRILLE ; j++) {
			  Coord c= nouvCoord(i,j);
			  Place p;
			  p=chargerPlace(g,c);
			  if(not egalcoord(c,p.cord )){
				  cout<<"la place au coordonnée ne correspond pas"<<endl;
			      exit(1);
			  }
		  }
	 }
}

void VerifFourmiGrille(Grille g, tabfourmi f){///////////////////test de la cohérence de la simulation aprés chaque mouvement
	for(int i=0 ; i<NBFourmi ; i++){
		Coord c= f[i].cord;
		Place p;
		p=chargerPlace(g,c);
		if(f[i].numfourmi != i){
			cout<<"la fourmi au coordonnée ne corespond pas"<<endl;
			exit(1);
		}
	}
}

///////////////////////////////////affichage ///////////////////////////////

//////////////////// action dessinant une Grilllle

void dessinerGrille(Grille g ){
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
       				 b = 0; 
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

//////////////////////Programme Principale/////////////////////////

int main() {
   Grille g ;
    chargerGrilleVide(g);
   // ensemble coordonnee fourmi
   Coord c0, c1, c2, c3 ,c4 ,c5, c6,c7, c8 ,c9,c10,c11 ;
   tabfourmi t ;
   chargerGrilleVide(g);
   EnsCoord Ef = nouvEnsCoord();
   c0  = nouvCoord (1,8);
   c1  = nouvCoord (5,2);
   c2  = nouvCoord (10,8);
   c3  = nouvCoord (19,7);
   c4  = nouvCoord (9,0);
   c5  = nouvCoord (4,9);
   c6  = nouvCoord (10,14) ;
   c7  = nouvCoord (5,15);
   c8  = nouvCoord (3,10);
   c9  = nouvCoord (9,6);
   c10 = nouvCoord (18,14);
   c11 = nouvCoord (19,19);

   ajouteEnsCoord (Ef,c0);
   ajouteEnsCoord (Ef,c1);
   ajouteEnsCoord (Ef,c2);
   ajouteEnsCoord (Ef,c3);
   ajouteEnsCoord (Ef,c4);
   ajouteEnsCoord (Ef,c5);
   ajouteEnsCoord (Ef,c6);
   ajouteEnsCoord (Ef,c7);
   ajouteEnsCoord (Ef,c8);
   ajouteEnsCoord (Ef,c9);
   ajouteEnsCoord (Ef,c10);
   ajouteEnsCoord (Ef,c11);
   chargerTabFourmi(t,Ef) ;

   /////////////// ensemble Nid///////////////////////////
   Coord cn1 , cn2 ;
   EnsCoord En = nouvEnsCoord();
   cn1 = nouvCoord (10,10);
   cn2 = nouvCoord (16,16);

   ajouteEnsCoord(En, cn1);
   ajouteEnsCoord(En, cn2);


   /////////////////////ensemble sucre///////////////////////////
   EnsCoord Es = nouvEnsCoord();
   Coord cs1,cs2,cs3,cs4,cs5,cs6,cs7,cs8, cs9;
   cs1  = nouvCoord (15,8);
   cs2  = nouvCoord (10,7);
   cs3  = nouvCoord (8,8);
   cs4  = nouvCoord (19,0);
   cs5  = nouvCoord (5,9);
   cs6  = nouvCoord (2,18) ;
   cs7  = nouvCoord (2,18);
   cs8  = nouvCoord (7,8);
   cs9  = nouvCoord (0,0);

   ajouteEnsCoord (Es,cs1);
   ajouteEnsCoord (Es,cs2);
   ajouteEnsCoord (Es,cs3);
   ajouteEnsCoord (Es,cs4);
   ajouteEnsCoord (Es,cs5);
   ajouteEnsCoord (Es,cs6);
   ajouteEnsCoord (Es,cs7);
   ajouteEnsCoord (Es,cs8);
   ajouteEnsCoord (Es,cs9);
/////////////////////Simulation////////////////////////////////
   chargerTabFourmi(t,Ef) ;
   initialiserGrille(g,En,Es,t);
   afficheGrille (g) ;
   lineariserPheroNid(g);
   linearise1PheroNid(g);
   //affichePheroNid (g);
   dessinerGrille(g);
   VerifGrilleCoord(g);
   VerifFourmiGrille(g,t);
    for(int i =0 ; i<100;i++){
   	 for(int j =0 ; j< NBFourmi;j++){
               MAJuneFourmi(g,t[j]);
          }
		 dessinerGrille(g);
	     diminuerPheroSucre(g);
	}
  Coord c100 = nouvCoord (0,0);
   Place p100 = chargerPlace(g,c100);
    
   cout <<   p100.sucre << endl ; 
  }
