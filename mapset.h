#ifndef MAP_SET
#define MAP_SET

   
/*
There are individual explanations of the funcitons above each one.
*/
#include<iostream>
using std::ostream;
#include<string>
using std::string;
#include<utility>
using std::pair;
#include<initializer_list>
using std::initializer_list;
#include<sstream>
using std::ostringstream;
#include <iostream>
using std::cout; using std::endl;
#include<algorithm>
using std::swap;using std::transform;
#include <locale>  
using std::locale;


//
// Node
//
template<typename K, typename V>
struct Node {
  K first;
  V second;
  Node *next = nullptr;
  
  Node() = default;
  Node(K,V);
  bool operator<(const Node&) const;
  bool operator==(const Node&) const;
  friend ostream& operator<<(ostream &out, const Node &n){
    // YOUR CODE HERE
    out << n.first << ":" << n.second;
    return out;
  }
};
// Makes a Node
template<typename K, typename V>
Node<K,V>::Node(K key, V value){
    first = key;
    second =  value;
}
// compare's the two nodes, even if they are upper and lower case.
template<typename K, typename V>
bool Node<K,V>::operator<(const Node &n) const{
    string str1 = first;
    string str2 = n.first;
    transform(str1.begin(), str1.end(), str1.begin(), ::tolower);
    transform(str2.begin(), str2.end(), str2.begin(), ::tolower);
    //cout << str1 << ":" << str2 << endl;
    if(str1 < str2){
        return true;
    }else{
        return false;
    }

}
//See's if the two nodes keys are equivilent.
template<typename K, typename V>
bool Node<K,V>::operator==(const Node &n) const{
    if(first == n.first){
        return true;
    }else{
        return false;
    }
}


//
// MapSet
// 
template<typename K, typename V>
class MapSet{
 private:
  Node<K,V>* head_ = nullptr;
  Node<K,V>* tail_ = nullptr;  
  size_t sz_ = 0;
  Node<K,V>* find_key(K);

 public:
  MapSet()=default;
  MapSet(initializer_list< Node<K,V> >);
  MapSet (const MapSet&);
  MapSet operator=(MapSet);
  ~MapSet();
  size_t size();
  bool remove (K);  
  bool add(Node<K,V>);
  Node<K,V> get(K);
  bool update(K,V);  
  int compare(MapSet&);
  MapSet mapset_union (MapSet&);
  MapSet mapset_intersection(MapSet&);

  friend ostream& operator<<(ostream &out, const MapSet& ms){
    // YOUR CODE HERE
    for(auto it = ms.head_; it != nullptr; it = it->next){
        out << *it;
        if(it != ms.tail_){
            out << ", ";
        }
    }
    return out;
  }  
};
//Makes the initial MapSet
template<typename K, typename V>
MapSet<K,V>::MapSet(initializer_list< Node<K,V> > il){
    for(auto it = il.begin(); it != il.end(); it++){
        add(*it);
    }
}
//This was pretty much taken straight from the example notes.
template<typename K, typename V>
MapSet<K,V>::MapSet(const MapSet &ms){
    if (ms.head_ == nullptr){
    	head_ = nullptr;
    	tail_ = nullptr;
    }
    else{
    	head_ = new Node<K,V>(*ms.head_);
    	tail_ = head_;
    	Node<K,V>* ms_ptr = ms.head_->next;
    	Node<K,V>* new_node;
    	while (ms_ptr != nullptr){
    	    new_node = new Node<K,V>(*ms_ptr);
    	    tail_->next = new_node;
    	    ms_ptr = ms_ptr->next;
    	    tail_ = new_node;
	    }
    }
}
//Swaps the componnets of ms
template<typename K, typename V>
MapSet<K,V> MapSet<K,V>::operator=(MapSet ms){
    swap(sz_, ms.sz_);
    swap(head_, ms.head_);
    swap(tail_, ms.tail_);
    return *this;
}	

//Walks down the list and deletes all of the iterators.
template<typename K, typename V>
MapSet<K,V>::~MapSet(){
    
    Node<K,V>* it = head_;
    while(it != nullptr){
        head_ = head_->next;
	    delete it;
	    it = head_;
    }
    head_ = nullptr;
    tail_ = nullptr;
    sz_ = 0;
}
// returns the size
template<typename K, typename V>
size_t MapSet<K,V>::size(){
    return sz_;
}
//Finds a key in the MapSet
template<typename K, typename V>
Node<K,V>* MapSet<K,V>::find_key(K key){
    for(auto it = head_; it != nullptr; it = it->next){
        string str = it->first;
        transform(str.begin(), str.end(), str.begin(), ::tolower);
        if(str == key){
            return it;
        }
    }
    return nullptr;
}
// Add's a node to the linked list if that said node doesn't already exist.
template<typename K, typename V>
bool MapSet<K,V>::add(Node<K,V> n){
    Node<K,V>* temp_n = new Node<K,V>(n);
    if(find_key(n.first) == nullptr){
          if(tail_ == nullptr && head_ == nullptr){
            head_ = temp_n;
            tail_ = temp_n;
            head_->next = nullptr;
            tail_->next = nullptr;
            sz_++;
            return true;
            
        }else if(head_ == tail_){
            if(*temp_n < *head_){
                head_ = temp_n;
                head_->next = tail_;
                tail_->next = nullptr;
                sz_++;
                return true;
                
            }else{
                tail_ = temp_n;
                head_->next = tail_;
                tail_->next = nullptr;
                sz_++;
                return true;
            }
        }else{
            for(auto it = head_; it != nullptr; it = it->next){
                if( *it < *temp_n and it == tail_){
                    it->next = temp_n;
                    tail_ = temp_n;
                    tail_->next = nullptr;
                    sz_++;
                    return true;
                }
                if(*temp_n < *it and it == head_){
                    head_ = temp_n;
                    head_->next = it;
                    sz_++;
                    return true;
                }
                if(*it < *temp_n and *temp_n < *it->next){
                    temp_n->next = it->next;
                    it->next = temp_n;
                    sz_++;
                    return true;
                }
            }
            return false;
        } 
    }
    return false;
    
}
//Removes a node from the MapSet.
template<typename K, typename V>
bool MapSet<K,V>::remove(K key){
    if(find_key(key) != nullptr){
        for(auto it = head_; it != nullptr; it = it->next){
            if(it == head_ && it->first == key){
                head_ = it->next;
                return true;
            }
            if(it->next == tail_ && it->next->first == key){
                tail_ = it;
                it->next = nullptr;
                return true;
            }
            if(it->next->first == key){
                it->next = it->next->next;
                return true;
            }
        }
        return false; 
    }else{
        return false;
    }
    
}
//Gets a Node
template<typename K, typename V>
Node<K,V> MapSet<K,V>::get(K key){
    if(find_key(key) != nullptr){
        return *find_key(key);
    }else{
        return Node<K,V>("",0);
    }
}
//Updates a Node
template<typename K, typename V>
bool MapSet<K,V>::update(K key, V value){
    if(find_key(key) != nullptr){
        find_key(key)->second = value;
        return true;
    }
    return false;
}
//Compares two MapSet's
template<typename K, typename V>
int MapSet<K,V>::compare(MapSet &ms){
    if(sz_ >= ms.sz_){
        auto j = ms.head_;
        for(auto i = head_; i != nullptr; i = i->next){
            if(j == nullptr){
                break;
            }
            if(i->first > j->first){
                return 1;
            }else if(i->first < j->first){
                return -1;
            }else{
                j = j->next;
            }
        }
    }else{
        auto j = head_;
        //cout << "I2";
        for(auto i = ms.head_; i != nullptr; i = i->next){
            if(j == nullptr){
                break;
            }
            if(i != nullptr && i->first > j->first){
                return -1;
            }else if(i != nullptr && i->first < j->first){
                return 1;
            }else{
                j = j->next;
            }
        }
    }
    if(sz_ > ms.sz_){
        return 1;
    }
    else if(sz_ < ms.sz_){
        return -1;
    }
    return 0;
}
//Makes a MapSet out of two different MapSet's
template<typename K, typename V>
MapSet<K,V> MapSet<K,V>::mapset_union(MapSet<K,V> &ms){
    MapSet<K,V>* result = new MapSet<K,V>();
    //cout << result << endl;
    for(auto i = head_; i != nullptr; i = i->next){
        result->add(*i);
        //cout << *result << endl;
    }
    for(auto i = ms.head_; i != nullptr; i = i->next){
        result->add(*i);
        //cout << *result << endl;
    }
    //cout << *result << endl;
    return *result;
}
//Makes a MapSet out of the different nodes in the different MapSet's
template<typename K, typename V>
MapSet<K,V> MapSet<K,V>::mapset_intersection(MapSet<K,V> &ms){
    MapSet<K,V>* result = new MapSet<K,V>();
    for(auto i = head_; i != nullptr; i = i->next){
        if(ms.find_key(i->first) != nullptr){
            result->add(*i);
            //result->next = nullptr;
        }
        
    }
    for(auto i = ms.head_; i != nullptr; i = i->next){
         if(find_key(i->first) != nullptr){
            result->add(*i);
        }
    }
    return *result;
}
#endif
  