#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h> 
#include <time.h>

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

/*number of zombies in the game: 
you should synchronize threads editing this variable*/
int zombieCounter;
int killed_zombie_counter;// we need to handling killed zombie numbers with a variable

// 2 sec waiting function 
void *delay(int second){
    int milsec = 1000 * second;
    clock_t startTime = clock();
    while(clock() < (startTime+milsec));
}
/* Keeps track of number of zombies entered.*/
void zombieEntered(){
    zombieCounter++;
}
/* Keeps track of number of zombies killed.*/
void zombieKilled(){
    zombieCounter--;
    killed_zombie_counter++;
}
/* Returns true if number of zombies in the room are 
greater than or equal to 100.*/
int tooManyZombiesInTheRoom(){
    return (zombieCounter >= 100);
}

/*Returns true if more than 100 zombies have been killed.*/
int killed100Zombies(){
    return (killed_zombie_counter > 100);
}

/* Returns true if there is at least one zombies in the room.*/
int zombiesExist(){
    return (zombieCounter > 0);
}
/*Returns the count of number of zombies killed.*/
int getKilledCount(){
    return killed_zombie_counter;
}

/* Returns the count of number of zombies in the room.*/
int getInTheRoomCount(){
    return zombieCounter;
}
/*doorman thread*/
void *doorMan(void *n)
{
    while(killed100Zombies() || !tooManyZombiesInTheRoom()){
        // time condition
        if(delay(2)){
            int chance = rand() % 2 + 1;
            //chance condition
            if(chance > 1){
                pthread_mutex_lock(&lock);
                zombieEntered();
                pthread_mutex_unlock(&lock);
            }
        }
    }
    pthread_exit(NULL);
}

/*slayer thread*/
void *slayer(void *n)
{
    while(!tooManyZombiesInTheRoom() || killed100Zombies()){
        if(zombiesExist()){
            if(delay(2)){
                pthread_mutex_lock(&lock);
                zombieEntered();
                pthread_mutex_unlock(&lock);
            }
        }
    }
    pthread_exit(NULL);
}
/*simulator main thread*/
int main(int argc, char **argv)
{

    int nMan = atoi(argv[1]);
    pthread_t t_sl, *t_dm; //thread slayer and thread doorman's variables
    t_dm = malloc (nMan* sizeof(pthread_t));

    //doorMan threads created
    for (int i = 0; i < nMan; i++)
    {
        pthread_create(&t_dm[i], NULL, doorMan, NULL);
    }
    //slayer thread created
    pthread_create(&t_sl, NULL, slayer, NULL);
    pthread_join(t_sl, NULL); // must be waiting for doorMan's threads before executed

    for (int i = 0; i < nMan; i++)
    {
        pthread_join(t_dm[i], NULL);
    }

    if (killed100Zombies())
    {
        printf("killed 100 zombies\n");
    }
    else if (tooManyZombiesInTheRoom())
    {
        printf("to many zombies in the room\n");
    }
    return 0;
}
