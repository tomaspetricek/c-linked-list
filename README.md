# CLinkedList
- it shows an implementation of a linked list data structure in **C**
- linked list is created by channing nodes represented as struct **Node**
- struct can be manipulated using dedicated functions that start with name _Node__...
- since there are no exceptions in C, functions return error codes, which need to be checked
- there are no templates in C, so the only type of data it can store is integer
  
## Usage
- user first creates a head node, which is allocated on the heap like all other nodes
- then functions such as _Node_get_, _Node_delete_, _Node_insert_ can be used to work with the data structure
- finally, the _Node_free_ function has to be used to release allocated memory on the heap 