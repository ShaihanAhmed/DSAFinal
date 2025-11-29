#include <iostream>
#include <string>
#include <fstream>
#include "Player.h"
using namespace std;

class QueueNode
{
public:
    Player *player;
    QueueNode *next;
    QueueNode(Player *p) : player(p), next(nullptr) {};
};

class Queue
{
public:
    QueueNode *head;
    QueueNode *rear;

    Queue(void) : head(nullptr), rear(nullptr) {};

    bool isEmpty(void)
    {
        return (head == nullptr);
    }

    void Enqueue(Player *p)
    {
        QueueNode *temp = new QueueNode(p);

        if (isEmpty())
        {
            head = rear = temp;
            return;
        }

        rear->next = temp;
    }

    //for enq into priority based on scores from normal
    void enqueueP(Player* p) {
        QueueNode* temp = new QueueNode(p);

        // empty or highest score
        if (!head || p->getTotal() > head->player->getTotal()) {
            temp->next = head;
            head = temp;
            return;
        }

        QueueNode* ptr = head;
        while (ptr->next && ptr->next->player->getTotal() >= p->getTotal()) {
            ptr = ptr->next;
        }

        temp->next = ptr->next;
        ptr->next = temp;
    }

    Player *Dequeue(void)
    {
        if (isEmpty())
        {
            cout << "\nNo players in queue yet!\n";
            return;
        }
        QueueNode *temp = head;
        head = head->next;

        Player *tempPlayer = temp->player;

        delete temp;
        return tempPlayer;
    }

    //for debugging purposes
    void dispQueue(void)
    {
        if (isEmpty())
        {
            cout << "Nothing in queue yet!\n";
            return;
        }

        QueueNode* ptr = head;

        while (ptr != nullptr)
        {
            Player* tempP = ptr->player;
            cout << "\nPlayer name : " << tempP->getName();
            cout << "\nPlayer score : " << tempP->getTotal();

            ptr = ptr->next;
        }
    }

    int size(Queue* p){
        QueueNode* ptr = head;

        int count = 0;

        while (ptr != nullptr)
        {
            count++;
            ptr = ptr->next;
        }

        return count;
    }

    void matchMaking(Queue* pr){
        while (pr->size(pr) >= 2){

            Player* p1 = pr->Dequeue();
            Player* p2 = pr->Dequeue();

            //call multiplayer for p1 , p2
        }

        //call strt gme for 1 lpalyer only

        
    }
};
