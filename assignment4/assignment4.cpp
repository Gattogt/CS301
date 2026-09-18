void SortedType::PutItem(ItemType newItem){

  NodePtr* newNode;                 // pointer to node being inserted

  NodePtr* predLoc;                    // trailing pointer

  NodePtr* location;                    // traveling pointer

  boolean moreToSearch;

  location = listData;

  predLoc = NULL;

  moreToSearch = (location != NULL);

  length++;

// Find insertion point
  while(moreToSearch && newItem.ComparedTo(location->info)==GREATER){
    predLoc = location;
    location = location->next;
  }
  
// Prepare node for insertion
  newNode = new NodePtr;
  newNode->info = newItem->info;
  // ADD YOUR CODE HERE ....
  if (predLoc == NULL)
  { // meaning the list was empty or the element to insert was to small so that needed to be inserted at the beginin
    newNode->next = location;
    location = newNode;
    return;
  }

// Insert node into list
  newNode->next = location;
  predLoc->next newNode;
}