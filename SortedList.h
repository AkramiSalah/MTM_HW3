#pragma once

#include <iostream>
#include <stdexcept>

namespace mtm {

    template <typename T>
    class SortedList {
    public:
        class ConstIterator;
        /**
         *
         * the class should support the following public interface:
         * if needed, use =defualt / =delete
         *
         * constructors and destructor:
         * 1. SortedList() - creates an empty list.
         * 2. copy constructor
         * 3. operator= - assignment operator
         * 4. ~SortedList() - destructor
         *
         * iterator:
         * 5. class ConstIterator;
         * 6. begin method
         * 7. end method
         *
         * functions:
         * 8. insert - inserts a new element to the list
         * 9. remove - removes an element from the list
         * 10. length - returns the number of elements in the list
         * 11. filter - returns a new list with elements that satisfy a given condition
         * 12. apply - returns a new list with elements that were modified by an operation
         */

        SortedList() : head(nullptr), tail(nullptr), size(0){};

        ~SortedList(){
            Node* currNode = head;
            while(currNode != nullptr){
                Node* temp = currNode;
                currNode = currNode->next;
                delete temp;
            }
        }

        SortedList(const SortedList& otherList){
            for(const T& value : otherList){
                insert(value);
            }
        }

        ConstIterator begin() {
            return ConstIterator(head);
        }


        ConstIterator end() const{
            return ConstIterator(nullptr);
        }

        void insert( const T& value ){
            Node* nodeToInsert = new Node(value);
            for(ConstIterator iterator = begin(); iterator != end(); ++iterator){
                if( !(nodeToInsert->data > *iterator) ){
                    // according to logic (mathematical logic) the negation of the > operator is <=.
                    insert(iterator.current->prev, nodeToInsert, iterator.current->next);
                    break;
                }
            }
        }

        void remove(const ConstIterator& iterator){
            if(iterator.current == nullptr){
                throw std::out_of_range("can't remove an element that is not in the List");
            }


            Node* prevNode = iterator.current->prev;
            Node* nextNode = iterator.current->next;

            delete iterator.current;
            this->size -= 1;

            if(prevNode == nullptr && nextNode == nullptr){
                head = nullptr;
                tail = nullptr;
            }else if(prevNode == nullptr){
                head = nextNode;
                head->prev = nullptr;
            }
            else if(nextNode == nullptr){
                tail = prevNode;
                tail->next = nullptr;
            }else{
                prevNode->next = nextNode;
                nextNode->prev = prevNode;
            }
        }

        int length(){
            return this->size;
        }
        
    private:
        struct Node{
            T data;
            Node* prev;
            Node* next;
            
            explicit Node(const T& inData) : data(inData), prev(nullptr), next(nullptr){}
        };

        Node* head;
        Node* tail;
        int size;

        void insert(Node* prevNode, Node* nodeToInsert, Node* nextNode){
            if(prevNode != nullptr){
                prevNode->next = nodeToInsert;
            }
            
            if(nextNode != nullptr){
                nextNode->prev = nodeToInsert;
            }

            nodeToInsert->next = nextNode;
            nodeToInsert->prev = prevNode;
            

            this->size += 1;
            
            if(prevNode == nullptr){
                head = nodeToInsert;
            }

            if(nextNode == nullptr){
                tail = nodeToInsert;
            }
        }
    };

    template <class T>
    class SortedList<T>::ConstIterator {
    /**
     * the class should support the following public interface:
     * if needed, use =defualt / =delete
     *
     * constructors and destructor:
     * 1. a ctor(or ctors) your implementation needs
     * 2. copy constructor
     * 3. operator= - assignment operator
     * 4. ~ConstIterator() - destructor
     *
     * operators:
     * 5. operator* - returns the element the iterator points to
     * 6. operator++ - advances the iterator to the next element
     * 7. operator!= - returns true if the iterator points to a different element
     *4321
     */
    public:
        friend SortedList<T>;
        const T& operator*() const{
            if(current == nullptr){
                throw std::out_of_range("you have reached the lists end !!");
            }

            return current->data;
        }

        const ConstIterator& operator++(){
            if(current == nullptr){
                throw std::out_of_range("you have reached the lists end !!");
            }
            current = current->next;
            return *this;
        }

        bool operator!=(const ConstIterator& other) const{
            return this->current != other.current;
        }

    private:
        const Node* current;
        
        ConstIterator( const Node* node) : current(node){}
        
        ConstIterator( const ConstIterator& iterator) : current(iterator->current){}
        
        const ConstIterator& operator=(const ConstIterator& iterator){
            current = iterator->current;
        }

        ~ConstIterator() = default; // this is probably bad
    };

};
