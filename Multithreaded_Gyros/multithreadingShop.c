//------------------------//
//  Mertzanis Loukas 4457 //
//  HY345 - Assignment 2  //
//------------------------//

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int flag = 0, i, customerNum, chairNum;
sem_t sitOnChair, onlyCustomerInShop, chillOnFb, waitForSouvlakia;

void cookOrder(int num)
{
    printf("Chef: -Ksekinaw na ftiaxnw ta pitogura pelati n%d!\n", num);
    sleep(1);
    printf("Chef: -Etoimi i paragelia n%d, partin kai efuges magka mou.\n", num);
}

void *customer(void *id)
{
    printf("O pelatis n%d eskase sto souvlatzidiko.\n", (*((int *)id) + 1));
    sem_wait(&sitOnChair); //an den uparxei eleutheri karekla perimenei orthios, alliws kathetai
    printf("O pelatis n%d arazei se karekla.\n", (*((int *)id) + 1));
    sem_wait(&onlyCustomerInShop); //an uparxei pelatis mesa perimenei, alliws mpainei mesa k paragelnei
    sem_post(&sitOnChair);         //eleutherwse karekla
    printf("O pelatis n%d mpainei sto souvlatzidiko kai dinei paragelia.\n", (*((int *)id) + 1));
    sem_post(&chillOnFb);        //chef ase to kinito
    sem_wait(&waitForSouvlakia); //perimene na ftiaksei ta pitogura
    printf("O pelatis n%d feugei apo to souvlatzidiko.\n", (*((int *)id) + 1));
    sem_post(&onlyCustomerInShop); //pleon mporei na mpei allos pelatis mesa sto magazi
}

void *chef()
{
    int orderCounter = 1;
    printf("Anoiksame kai sas perimenoume!\n");
    while (!flag)
    {
        printf("O chef rixnei ena check sto fb.\n");
        sleep(0.1);
        sem_wait(&chillOnFb); //aragma sto fb mexri na mpei o epomenos
        if (!flag)
        {
            cookOrder(orderCounter++);
            sem_post(&waitForSouvlakia); //etoimi i paragelia
        }
        else
        {
            printf("Chef: Teleiwsame me tin pelateia, as to kleisoume to magazaki!\n");
        }
    }
}

void idArrayInit(int *arr)
{
    for (i = 0; i < customerNum; i++)
        arr[i] = i;
}

int main()
{
    int *idArray;
    pthread_t chefThread;
    pthread_t *customerThreadArr;

    printf("Enter number of chairs and number of customers: ");
    scanf("%d %d", &chairNum, &customerNum);

    customerThreadArr = (pthread_t *)malloc(customerNum * sizeof(pthread_t));
    idArray = (int *)malloc(customerNum * sizeof(int));
    idArrayInit(idArray);

    sem_init(&chillOnFb, 0, 0);
    sem_init(&waitForSouvlakia, 0, 0);
    sem_init(&sitOnChair, 0, chairNum);
    sem_init(&onlyCustomerInShop, 0, 1);

    pthread_create(&chefThread, NULL, chef, NULL);

    for (i = 0; i < customerNum; i++)
    {
        pthread_create(&(customerThreadArr[i]), NULL, customer, (void *)&idArray[i]);
        if (!(i % 3) && (i != 0)) //arxika skane 4 pelates, kai meta se set twn 3wn
        {
            sleep(5);
        }
    }

    for (i = 0; i < customerNum; i++)
    {
        pthread_join(customerThreadArr[i], NULL);
    }

    flag = 1;
    sem_post(&chillOnFb); //Ase to kinito, mporeis na pas spiti sou
    free(idArray);
    pthread_join(chefThread, NULL);
    return 0;
}
