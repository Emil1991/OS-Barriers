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
            removeList(head);
        }



        class Node {
         public:
          T data;
          Node *next;
          pthread_mutex_t lock;

          Node(){
              next=NULL;
              pthread_mutex_init(&lock,NULL);
          }

          Node(T newData){
              data=newData;
              next=NULL;
              pthread_mutex_init(&lock,NULL);
          }

          Node(T newData,Node* nextNode){
              data=newData;
              next=nextNode;
              pthread_mutex_init(&lock,NULL);
          }

          ~Node(){
              pthread_mutex_destroy(&lock);
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
                pthread_mutex_lock(&pred->lock);
                curr=pred->next;

                if(curr==NULL){//add first node
                    Node* newNode= new Node(data);
                    pthread_mutex_lock(&newNode->lock);
                    head->next=newNode;
                    size++;
                    pthread_mutex_unlock(&newNode->lock);
                    pthread_mutex_unlock(&pred->lock);
                    return true;
                }else{
                    pthread_mutex_lock(&curr->lock);
                    while (curr && curr->data<=data) {
                        pthread_mutex_unlock(&pred->lock);
                        pred=curr;
                        curr=curr->next;
                        pthread_mutex_lock(&curr->lock);
                    }

                    if(pred->data==data){//already exists node with same data
                        cout<<"already exist" <<endl;
                        pthread_mutex_unlock(&curr->lock);
                        pthread_mutex_unlock(&pred->lock);
                        return false;
                    }else{
                        Node* newNode =new Node(data,curr);
                        pred->next=newNode;
                        size++;
                        pthread_mutex_unlock(&curr->lock);
                        pthread_mutex_unlock(&pred->lock);
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
                pthread_mutex_lock(&pred->lock);
                curr=pred->next;
                pthread_mutex_lock(&curr->lock);

                while(curr && curr->data<=value){
                    if(curr->data==value){//found the item
                        pred->next=curr->next;
                        size--;
                        pthread_mutex_unlock(&curr->lock);
                        pthread_mutex_unlock(&pred->lock);
                        return true;
                    }
                    pthread_mutex_unlock(&pred->lock);
                    pred=curr;
                    curr=curr->next;
                    pthread_mutex_lock(&curr->lock);
                }
                pthread_mutex_unlock(&curr->lock);
                pthread_mutex_unlock(&pred->lock);
                return false;
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

        void removeList(Node* head){
            if(!head)
                return;
            removeList(head->next);
            free(head);
        }
};

#endif //THREAD_SAFE_LIST_H_