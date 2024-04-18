#include <iostream>
#include <vector>

template <typename T>
struct Node { 
    T& data;
    Node<T> *next; //right
    Node<T> *prev; //left

    Node(T& d): data(d), next(nullptr), prev(nullptr){}
} ; 

template <typename T>
class linkedList { 

	int nodeCount;

	Node<T> *head; //furthest right
	Node<T> *tail; //furthest left

    Node<T> *findNode(const T& data) const { 

        Node<T> *rnode = head;
        Node<T> *lnode = tail;
        
        while(lnode || rnode){ 
            if(lnode->next->data == data){ 
                return lnode;
            }
            lnode = lnode->next;
            if(rnode->data == data){ 
                return rnode;
            }
            rnode = rnode->prev;

            if(lnode == rnode){ 
                return nullptr;
            }
        }
        return nullptr;
    }
	
	public: 
		linkedList(): nodeCount(0), head(nullptr), tail(nullptr){}; 

	void add(T& data){ 

        Node<T>* newNode = new Node<T>(data); 

        if(nodeCount == 0){ 
            head = newNode; 
            tail = newNode;
        } else { 
             newNode->prev = head;
             head->next = newNode;
             head = newNode;  
        }
        nodeCount++; 
    }
	
	bool remove(const T& data){  // true successfully removed ,false if item doesnt exist. 

        if(nodeCount < 1){ 
            return false;
        }

        if(!head||!tail) { 
            return false;
        }

        Node<T> *node = findNode(data);
         
        if(node == nullptr){
            return false;
        } 

        if(node->prev){
            node->prev->next = node->next; 
        } else { 
            node->next->prev = nullptr;
            tail = node->next; 
        }

        if(node->next){
            node->next->prev = node->prev;
        } else { 
            node->prev->next = nullptr;
            head = node->prev; 
        }

        node->next = nullptr; 
        node->prev = nullptr;

        delete(node); 
        nodeCount--; 

        return true;
    } 
	
	bool moveForward(const T& data){ 

        Node<T> *node = findNode(data);  

        if(!node){
            return false;
        } 

        if(node->next == nullptr){ 
            return false;
        }

        Node<T>* temp = node->next; 

        node->next->prev = node->prev; 
        
        node->next = node->next->next;

        if(node->next){ 
            node->next->prev = node; 
        }

        if(node->prev){
            node->prev->next = node->next;  
        } else { 
            tail = temp;
        }

        node->prev = temp;

        if(!node->next){ 
            head = node;
        }

        return true;
    }
    bool moveBackward(const T& data){ 
        Node<T> *node = findNode(data);
         
        if(!node){
            return false;
        } 

        if(node->prev == nullptr){ 
            return false;
        }

        if(node->next == nullptr){ 
            head = node->prev;
        }

        Node<T>* prevtemp = node->prev;

        if(prevtemp->prev){ // 1 2 3, 3 wants to move back
            prevtemp->prev->next = node; 
            node->prev = prevtemp->prev;
        } else { // 1 2 3, 2 wants to move back
            node->prev = prevtemp->prev;
        }

        prevtemp->next = node->next; 

        if(node->next){ 
            node->next->prev = node->prev;
        }

        node->next = prevtemp;

        if(node->prev == nullptr){ 
            tail = node;
        }

        return true;
    }

    std::vector<T> printNodes(){ 
        Node<T> *node = tail;
        std::vector<T> nodeValues; 
        
        while(node){
            std::cout << node->data << std::endl;
            nodeValues.push_back(node->data);
            node = node->next;
        }

        return nodeValues;
    }

} ;

int main(int argc, char *argv[]){ 

    linkedList<int> list;

    // Test adding nodes
    int a = 1, b = 2, c = 3;
    list.add(a);
    list.add(b);
    list.add(c);

    // Test printNodes function
    std::vector<int> expectedNodes = {1, 2, 3};
    std::vector<int> actualNodes = list.printNodes();
    if (actualNodes == expectedNodes) {
        std::cout << "add function test passed" << std::endl;
    } else {
        std::cout << "add function test failed" << std::endl;
    }

    // Test removing a node
    bool removed = list.remove(b);
    list.printNodes();
    if (removed) {
        std::cout << "Node with data 2 removed successfully" << std::endl;
    } else {
        std::cout << "Failed to remove node with data 2" << std::endl;
    }

    // Test moving a node forward
    list.moveForward(a); //crashes. 
    expectedNodes = {3, 1};
    actualNodes = list.printNodes();
    if (actualNodes == expectedNodes) {
        std::cout << "Node with data 1 moved forward successfully" << std::endl;
    } else {
        std::cout << "Failed to move node with data 1 forward" << std::endl;
    }

    // Test moving a node backward
    expectedNodes = {1, 3};
    list.moveBackward(3);
    actualNodes = list.printNodes();
    if (actualNodes == expectedNodes) {
        std::cout << "Node with data 3 moved backward successfully" << std::endl;
    } else {
        std::cout << "Failed to move node with data 3 backward" << std::endl;
    }

    return 0;
    }
