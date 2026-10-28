/* I learned to input files: https://www.google.com/search?q=codigo+facilito+leer+un+archivo+con+c%2B%2B&oq=codigo+facilito+leer+un+archivo+con+c%2B%2B&gs_lcrp=EgZjaHJvbWUyBggAEEUYOTIGCAEQRRg80gEHMzA2ajBqN6gCALACAA&sourceid=chrome&source=chrome.ob&ie=UTF-8#fpstate=ive&vld=cid:dfd24cb4,vid:RBZidsPGkfs,st:0
   I learned to transform from string to int: https://stackoverflow.com/questions/7663709/how-can-i-convert-a-stdstring-to-int
   I used the following video to solve traverse in order after several hours of trying myself: https://www.google.com/search?q=how+to+print+a+binary+tree+in+ascending+order+c%2B%2B&oq=how+to+print+a+binary+tree+in+ascending+order+c%2B%2B&gs_lcrp=EgZjaHJvbWUyBggAEEUYOTIHCAEQIRigATIHCAIQIRigATIHCAMQIRigATIHCAQQIRigAdIBCTEwOTQ5ajBqN6gCALACAA&sourceid=chrome&source=chrome.ob&ie=UTF-8#fpstate=ive&vld=cid:faa21a35,vid:z0FDBGbf42Q,st:0
*/

#include <iostream>
#include <fstream>
#include <string>
using namespace std;
string line;
string text;
struct Node{
  int value;
  Node *next;
};
struct TreeNode
{
  int value;
  TreeNode *right = NULL;
  TreeNode *left = NULL;
};

class MYBTS{
  public:
   TreeNode* root;
   Node *rear;
   MYBTS(){
     root = NULL;
     rear = NULL;
   }
   bool isEmpty(){
    return rear == NULL;
  }
  void Enqueue(int value){
    Node* newNode = new Node;
    newNode->value = value;
    if (rear == NULL){
      rear = newNode;
      newNode->next = rear;
      return;
    }
    Node *temp = rear->next;
    rear->next = newNode;
    rear = newNode;
    newNode->next = temp;
  }
  int Dequeue(){
    if(rear == NULL){
      cout << "The queue is Empty" << endl;
      return -1;
    }
    if(rear == rear->next){
      Node *temp = rear->next;
      rear = NULL;
      return temp->value;
    }
    Node *temp = rear->next;
    rear->next = temp->next;
    return temp->value;
  }
  void fillMyQueue(TreeNode* tree){
    if(tree != NULL){
      if(tree->left != NULL){
        fillMyQueue(tree->left);
      }
      Enqueue(tree->value);
      if(tree->right != NULL){
        fillMyQueue(tree->right);
      }
    }
    else
    {
      cout << "Tree is empty"<<endl;
    }

    // if(tree == NULL){
    //   return;
    // }else if(tree->left == NULL){
    //   Enqueue(tree->value);
    // }else if(tree->right == NULL){
    //   Enqueue(tree->value);
    // }
    // else{
    //    Enqueue(tree->value); 
    // }
    // fillMyQueue(tree->left);
    // fillMyQueue(tree->right);
    
  }
    void print(){
      Node *temp = rear;
      int count = 0;
      while (count != 100){
        temp = temp->next;
        cout <<temp->value<<endl;
        count++;
      }
    }

   int CountNodes(TreeNode* tree){
      if(tree == NULL){
        return 0;
      }
      return CountNodes(tree->left) + CountNodes(tree->right) + 1;
    }
    int GetLength(){
      return CountNodes(root);
   }
   bool Insert(int value){
     TreeNode *newTreeNode = new TreeNode;
     newTreeNode->value = value;
     TreeNode *temp = root;
     if(root == NULL){
      root = newTreeNode;
     }
     while(temp != NULL){
      if(newTreeNode->value < temp->value){
        if(temp->left == NULL){
          temp->left = newTreeNode;
          break;
        }
        else{temp = temp->left;}
      }else if(newTreeNode-> value > temp->value){
        if(temp->right == NULL){
          temp->right = newTreeNode;
          break;
        }
        else{temp = temp->right;}
      }else{return false;}
     }
     return true;
   }
};

int main()
{
  MYBTS* bt = new MYBTS;
  ifstream numfile("numfile.txt");

  while(getline(numfile, line)){
    bt->Insert(stoi(line));
  }
  numfile.close();
  bt->fillMyQueue(bt->root);
  bt->print();
}