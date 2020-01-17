#ifndef THREAD_SAFE_LIST_H_
#define THREAD_SAFE_LIST_H_

#include <pthread.h>
#include <iostream>
#include <iomanip> // std::setw

using namespace std;

template <typename T>
class List 
{
    public:
        /**
         * Constructor
         */
        List() {
        head=new Node();
        size=0;
        }


        /**
         * Destructor
         */
        ~List(){

        }

        class Node {
         public:
          T data;
          Node *next;

          Node(){
              next=NULL;
          }

          Node(T newData){
              data=newData;
              next=NULL;
          }

          Node(T newData,Node* nextNode){
              data=newData;
              next=nextNode;
          }

        };

        /**
         * Insert new node to list while keeping the list ordered in an ascending order
         * If there is already a node has the same data as @param data then return false (without adding it again)
         * @param data the new data to be added to the list
         * @return true if a new node was added and false otherwise
         */
        bool insert(const T& data) {
            Node *pred, *curr;

            try {
                pred=head;
                curr=pred->next;
                if(curr==NULL){//add first node
                    Node* newNode= new Node(data);
                    head->next=newNode;
                    size++;
                    return true;
                }else{
                    while (curr && curr->data<=data) {
                        pred=curr;
                        curr=curr->next;
                    }

                    if(pred->data==data){//already exists node with same data
                        cout<<"already exist" <<endl;
                        return false;
                    }else{
                        Node* newNode =new Node(data,curr);
                        pred->next=newNode;
                        size++;
                        return true;
                    }
                }
            }catch(exception e){
                return false;
            }
        }

        /**
         * Remove the node that its data equals to @param value
         * @param value the data to lookup a node that has the same data to be removed
         * @return true if a matched node was found and removed and false otherwise
         */
        bool remove(const T& value) {
            Node *pred, *curr;

            try{
                pred=head;
                curr=pred->next;
            }catch(exception e){
                return false;
            }

        }

        /**
         * Returns the current size of the list
         * @return the list size
         */
        unsigned int getSize() {
			return size;
        }


		// Don't remove
        void print() {
//          pthread_mutex_lock(&list_mutex);
          Node* temp = head;
          if (temp == NULL)
          {
            cout << "";
          }
          else if (temp->next == NULL)
          {
            cout << temp->data;
          }
          else
          {
            while (temp != NULL)
            {
              cout << right << setw(3) << temp->data;
              temp = temp->next;
              cout << " ";
            }
          }
          cout << endl;
//          pthread_mutex_unlock(&list_mutex);
        }

		// Don't remove
        virtual void __add_hook() {}
		// Don't remove
        virtual void __remove_hook() {}

    private:
        Node* head;
        unsigned int size;
    // TODO: Add your own methods and data members
};

#endif //THREAD_SAFE_LIST_H_