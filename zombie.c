#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

/*number of zombies in the game: 
you should synchronize threads editing this variable*/
int zombieCounter;

/* Keeps track of number of zombies entered.*/
void zombieEntered(){

}
/* Keeps track of number of zombies killed.*/
void zombieKilled(){

}
/* Returns true if number of zombies in the room are 
greater than or equal to 100.*/
int tooManyZombiesInTheRoom(){

}

/*Returns true if more than 100 zombies have been killed.*/
int killed100Zombies(){}

/* Returns true if there is at least one zombies in the room.*/
int zombiesExist(){

}
/*Returns the count of number of zombies killed.*/
int getKilledCount(){

}

/* Returns the count of number of zombies in the room.*/
int getInTheRoomCount(){

}
/*doorman thread*/
void *doorMan(void *){

}

/*slayer thread*/
void *slayer(void *){

}
/*simulator main thread*/
int main(int argc, char **argv){
 // n tane doorman thread - joinlet
 // 1 tane slayer threah
int noorMan = atoi(argv[1]);
pthread_t t_main , t_other;
pthread_create()

 for(int i = 0 ; i < noorMan)
}