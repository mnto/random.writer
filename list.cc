/************************************************************
 *                                                          *
 * File name: list.cc                                       *
 * Name: Minh To                                            *
 * Assignment: Random Writer                                *
 * Date: 11/05/15                                           *
 *                                                          *
 * This data structure is a doubly-linked list of nodes     * 
 * with two sentinels: _front and _back. Any node in        *
 * between contains data and are indexed as in a list.      *
 * This class provides fundamental methods to manipulate    *
 * this data structure.                                     *
 *                                                          *
 ***********************************************************/

#include "list.h"
#include <cmath>

// List node constructors provided by Prof. Campbell

list_node::list_node() : prev(NULL), next(NULL) {}

list_node::list_node(list_node *p, list_node *n) : prev(p), next(n) {}

list_node::list_node(list_node *p, const list_element & d, list_node * n):
  prev(p), data(d), next(n) {}

// List constructors/destructor/assignment also provided.  
// No need to change these.

list::list() 
{
  _init();
}

list::~list()
{
  _destroy();
}

list::list(const list & orig)
{
  _init();
  _copy(orig);
}

list & list::operator=(const list & rhs)
{
  if (this != &rhs) {
    _destroy();
    _copy(rhs);
  }
  return *this;
}

void list::_init() 
{
  _size = 0;
  _current_index = 0;
  _front = new list_node(); // front sentinel
  _rear = new list_node(); // back sentinel
  _rear->prev = _front;
  _front->next = _rear;
  _current = _rear;
}

// void list::_destroy()
// destroy all node pointers
void list::_destroy()
{
  // remove anything in between the sentinels
  if (size() != 0) { 
    for (size_t i = 0; i < size(); i++) {
      remove_at(i);
    }
  }
  delete _front;
  delete _rear;
}

// void add((const list_element & item, int index)
// Insert a new element at a position (k) given by index.
// If index is non-negative, k is index; otherwise
// k is size() + index.
void list::add(const list_element & item, int index) 
{
  list_node * p = new list_node(NULL, item, NULL);
  _set_current_index(index >= 0? index: size() + index);
  // insert new node in between _current and its previous node
  p->prev = _current->prev;
  _current->prev->next = p;
  p->next = _current;
  _current->prev = p;
  _current = p;
  _size++;
}

// void _copy(const list & orig) 
// make a deep copy of the list passed through reference in the parameter
void list::_copy(const list & orig) 
{ 
  for (size_t i = 0; i < orig.size(); i++) {
    add(orig.get(i), i); 
  }
}

// void remove_at(int index) 
// Remove an element from this list.  
// index indicates a position k in the manner described in (add)
void list::remove_at(int index) 
{
  list_node * p;
  _set_current_index(index >= 0? index: size() + index);
  p = _current;
  // remove the current node
  // make next node point to the previous node and vice versa
  _current->prev->next = _current->next;
  _current->next->prev = _current->prev;
  _current = _current->next;
  delete p;
  _size--;
}

// void remove(const list_element & item)
// Let i be the smallest non-negative integer where get(i)==item. 
// Post: same as for removeAt(i)
// If no such i exists, no change to the list.
void list::remove(const list_element & item)
{
  for (size_t i = 0; i < size(); i++)
    if (get(i) == item)
      remove_at(i);
}

// size_t find(const list_element & item) const 
// return smallest non-negative integer where get(i)==item,
// or size() if no such integer
size_t list::find(const list_element & item) const 
{
  for (size_t i = 0; i < size(); i++) { 
    if (get(i) == item)
      return i;
  }
  return size();
}

// list_element get(int index) const
// return the element at position k.
list_element list::get(int index) const
{
  _set_current_index(index);
  return _current->data;
}

// size_t size() const
// return the number of elements of the list
size_t list::size() const
{
  return _size;
}

// void output(std::ostream & ostr) const 
// output the list
void list::output(std::ostream & ostr) const 
{
  ostr << "<";  
  for (size_t i = 0; i < size(); i++) {
    ostr << get(i);
    if (i != _size-1)
      ostr << ", ";
  }
  ostr << ">";  ;
}

// void set_current_index(size_t index) const
// current points to the node holding the element at position index,
// or to the rear sentinel.
// _current_index is index.
void list::_set_current_index(size_t index) const
{
  if (index == size()) {
    //_current_index = index;
    _current = _rear;
  }
  else if (index == 0) 
    //_current_index = index;
    _current = _front->next;
  else if (index == _current_index)
    return;
  else {
    size_t distance; // distance from _current_index to index
    size_t distfromrear = size() - index - 1; // distance from _rear
    list_node * p;
    size_t smallest; // smallest distance
    int direction;
    size_t closest; //index of the closest node pointer 
    // make distance positive
    _current_index > index? 
      distance = _current_index - index : distance = index - _current_index;
    // find smallest distance
    smallest = std::min(std::min(distance, index), distfromrear); 
    // determine direction
    if (smallest == distance) {
      p = _current;
      closest = _current_index;
      if (_current_index > index)  // go backward from _current
	direction = -1;
      else  // go forward from _current
	direction = 1;
    }
    else if (smallest == index) { // closest to _front
      p = _front->next;
      closest = 0;
      direction = 1;
    }
    else { // closest to _rear
      p = _rear;
      closest = size();
      direction = -1;
    }
    // move pointer
    for (size_t i = closest; i != index; i+= direction) {
      if (direction == 1)
	p = p->next;
      else
	p = p->prev;
    }
    _current = p;
  }
  _current_index = index;
}
    
