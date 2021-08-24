// QNode.h
// Queue node class for ints

// #include <cstddef>

#ifndef QNODE_H
#define QNODE_H

class QNode
   {
      public:
               QNode();
               QNode(int);
               ~QNode();
               QNode(const QNode&);
               
               int getData();
               void setData(int);
               
               QNode* getNext();
               void setNext(QNode*);
               
               static int getQNodeCount();
               
      private:
               int data;
               QNode* next;
               
               static int qnct;
   };
   
int QNode::qnct = 0;

QNode::QNode()
   {
      next = NULL;
      qnct++;
   }
   
QNode::QNode(int x)
   {
      next = NULL;
      data = x;
      qnct++;
   }

   
QNode::~QNode()
   {
      qnct--;
   }
   
QNode::QNode(const QNode &other)
   {
      data = other.data;
      next = other.next;
      qnct++;
   }
   
int QNode::getData()
   {
      return data;
   }
   
void QNode::setData(int x)
   {
      data = x;
   }
   
QNode* QNode::getNext()
   {
      return next;
   }
   
void QNode::setNext(QNode* n)
   {
      next = n;
   }
   
int QNode::getQNodeCount()
   {
      return qnct;
   }
#endif
