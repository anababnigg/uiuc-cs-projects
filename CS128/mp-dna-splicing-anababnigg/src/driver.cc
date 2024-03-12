#include <iostream>

#include "dna_strand.hpp"

int main() {DNAstrand* starter = new DNAstrand();
  DNAstrand* srd = new DNAstrand();
  //'AAA' example
  //EXAMPLE 01
  /*
  char pattern[] = "gaattc";
  Node* a = new Node('c');
  Node* b = new Node('t');
  a->next = b;
  Node* c = new Node('g');
  b->next = c;
  Node* d = new Node('a');
  c->next = d;
  Node* e = new Node('a');
  d->next = e;
  Node* f = new Node('t');
  e->next = f;
  Node* g = new Node('t');
  f->next = g;
  Node* h = new Node('c');
  g->next = h;
  Node* i = new Node('g');
  h->next = i;
  // add extra
  Node* s1 = new Node('t');
  Node* s2 = new Node('g');
  Node* s3 = new Node('a');
  Node* s4 = new Node('t');
  Node* s5 = new Node('c');
  s1->next = s2;
  s2->next = s3;
  s3->next = s4;
  s4->next = s5;
  starter->NodeSetter(a, i);
  srd->NodeSetter(s1, s5);
  starter->SpliceIn(pattern, *srd);
  // printing out
  std::cout << starter->Travel(0)->data << std::endl;
  std::cout << starter->Travel(1)->data << std::endl;
  std::cout << starter->Travel(2)->data << std::endl;
  std::cout << starter->Travel(3)->data << std::endl;
  std::cout << starter->Travel(4)->data << std::endl;
  std::cout << starter->Travel(5)->data << std::endl;
  std::cout << starter->Travel(6)->data << std::endl;
  std::cout << starter->Travel(7)->data << std::endl;
  //std::cout << starter->Travel(8)->data << std::endl;
  //std::cout << starter->Travel(9)->data << std::endl;
  //std::cout << starter->Travel(10)->data << std::endl;
  */

  // AAAAA EXAMPLE (AAA)
  /*
  char pattern[] = "AAA";
  Node* a = new Node('A');
  Node* b = new Node('A');
  a->next = b;
  Node* c = new Node('A');
  b->next = c;
  Node* d = new Node('A');
  c->next = d;
  Node* e = new Node('A');
  d->next = e;
  // to splice in
   Node* s1 = new Node('g');
  Node* s2 = new Node('t');
  Node* s3 = new Node('c');
  Node* s4 = new Node('t');
  s1->next = s2;
  s2->next = s3;
  s3->next = s4;
  // manipulation
  starter->NodeSetter(a, e);
  srd->NodeSetter(s1, s4);
  starter->SpliceIn(pattern, *srd);
  // pwinting
  std::cout << starter->Travel(0)->data << std::endl;
  std::cout << starter->Travel(1)->data << std::endl;
  std::cout << starter->Travel(2)->data << std::endl;
  std::cout << starter->Travel(3)->data << std::endl;
  std::cout << starter->Travel(4)->data << std::endl;
  std::cout << starter->Travel(5)->data << std::endl;
  std::cout << starter->Travel(6)->data << std::endl;
  // std::cout << starter->Travel(7)->data << std::endl;
  //std::cout << starter->Travel(8)->data << std::endl;
  //std::cout << starter->Travel(9)->data << std::endl;
  //std::cout << starter->Travel(10)->data << std::endl;
  */
  // EXAMPLE 02
  char pattern[] = "ta";
  Node* a = new Node('c');
  Node* b = new Node('t');
  a->next = b;
  Node* c = new Node('a');
  b->next = c;
  Node* d = new Node('t');
  c->next = d;
  Node* e = new Node('a');
  d->next = e;
  Node* s1 = new Node('t');
  Node* s2 = new Node('g');
  Node* s3 = new Node('a');
  s1->next = s2;
  s2->next = s3;
  // manipulation
  starter->NodeSetter(a, e);
  srd->NodeSetter(s1, s3);
  starter->SpliceIn(pattern, *srd);
  // pwinting
    std::cout << starter->Travel(0)->data << std::endl;
  std::cout << starter->Travel(1)->data << std::endl;
  std::cout << starter->Travel(2)->data << std::endl;
  std::cout << starter->Travel(3)->data << std::endl;
  std::cout << starter->Travel(4)->data << std::endl;
  std::cout << starter->Travel(5)->data << std::endl;
  std::cout << starter->Travel(6)->data << std::endl;
}