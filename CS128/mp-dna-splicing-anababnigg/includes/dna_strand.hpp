#ifndef DNA_STRAND_HPP
#define DNA_STRAND_HPP

#include "node.hpp"

class DNAstrand {
public:
  DNAstrand() = default;
  DNAstrand(const DNAstrand& rhs) = delete;
  DNAstrand& operator=(const DNAstrand& rhs) = delete;
  ~DNAstrand();

  void SpliceIn(const char* pattern, DNAstrand& to_splice_in);

  // helpers
  bool Match(const char* pattern, Node* current);
  void Editor(const char* pattern, DNAstrand& to_splice_in, unsigned int index);

  // driver
  Node* Travel(int dist);
  void NodeSetter(Node* head, Node* tail);

private:
  Node* head_ = nullptr;
  Node* tail_ = nullptr;
};

#endif