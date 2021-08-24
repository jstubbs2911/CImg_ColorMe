// Queue.h
// queue class for integers

#include <cstddef>
#include <sstream>  

#include "QNode.h"

#ifndef QUEUE_H
#define QUEUE_H

class Queue
   {
      public:
               Queue();
               Queue(int);
               ~Queue();
               Queue(const Queue&);
               
               void enQ(int);
               int deQ();
               
               bool isEmpty();
               int getSize();

               std::string toString();
               
               static int getQueueCount();
               
      private:
               QNode* front;
               QNode* back;
               int size;                  // number of items in this queue
               static int qct;            // now many queues exist
   };
   
int Queue::qct = 0;

Queue::Queue()
   {
      front = back = NULL;
      qct++;
      size = 0;
   }  // default constructor
   
Queue::Queue(int x)
   {
      front = new QNode(x);
      back = front;
      qct++;
      size = 1;
   } // 1-param constructor
   
Queue::~Queue()
   {
      while (!isEmpty())
         deQ();
      qct--;
   }  // destructor
   
Queue::Queue(const Queue &other)
   {
      front = back = NULL;
      qct++;
      
      if (other.front == NULL)
         return;
      QNode* t;
      t = other.front;
      while (t!=NULL)
         {
            enQ(t->getData());
            t = t->getNext();
         }
      size = other.size;
   } // copy constructor

std::string Queue::toString()
   {
      if (isEmpty())
         return "";
      else
         {
            std::stringstream ss;
            QNode* t;
            t = front;
            while (t!=NULL)
               {
                  ss << t->getData()<<' ';
                  t = t->getNext();
               }
            return ss.str();
         }
   } // toString()


bool Queue::isEmpty()
   {
	   return front == NULL && back == NULL;
      
   } // isEmpty()
   
int Queue::deQ()
   {
	   int x;
	   QNode* t;
	   t = front;
	   x = front -> getData();
	   front = front -> getNext();
	   size--;
	   delete t;
	   if (front == NULL)
			back = NULL;

	return x;
      
   } // deQ()
   
void Queue::enQ(int x)
   {
      QNode* t = new QNode;
      t -> setData(x);
      if (back == NULL)
		{
			back = t;
			front = t;
			size++;
		}
	 else 
	 {
		back -> setNext(t);
		back = t;
		size++;
	 }
   }  //enQ()
   
int Queue::getQueueCount()
   {
      return qct;
   }  // getQueueCount()


int Queue::getSize()
   {
      return size;
   }  // getSize()

#endif
