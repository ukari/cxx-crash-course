#include <iostream>

struct Element {
  Element* next{};
  Element* previous{};

  Element(short operating_number) : operating_number {operating_number} {
  }

  void insert_after(Element* new_element) {
    new_element->next = next;
    new_element->previous = this;
    if (next) {
      next->previous = new_element;
    }
    next = new_element;
  }

  void insert_before(Element* new_element) {
    new_element->previous = previous;
    new_element->next = this;
    if (previous) {
      previous->next = new_element;
    }
    
    previous = new_element;
  }

  char prefix[2];
  short operating_number;
};

int main(){
  Element t0{0}, t1{1}, t2{2};
  t0.prefix[0] = 'T';
  t0.prefix[1] = 'K';
  t1.prefix[0] = 'F';
  t1.prefix[1] = 'N';
  t2.prefix[0] = 'L';
  t2.prefix[1] = 'S';
  Element t3{3}, t4{4}, t5{5};
  t3.prefix[0] = 'T';
  t3.prefix[1] = 'K';
  t4.prefix[0] = 'F';
  t4.prefix[1] = 'N';
  t5.prefix[0] = 'L';
  t5.prefix[1] = 'S';
  t0.insert_after(&t1);
  t1.insert_after(&t2);
  t5.insert_before(&t4);
  t4.insert_before(&t3);

  for(Element* i = &t0; i; i = i->next) {
    std::cout << i->operating_number << std::endl;
  }

  for(Element* i = &t5; i; i = i->previous) {
    std::cout << i->operating_number << std::endl;
  }
}
