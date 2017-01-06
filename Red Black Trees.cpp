//**************************************************************
//  rbtree.cpp
//  Red Black Tree
//
//  Created by Aniketh Sukhtankar on October 26, 2016.
//  C++ Program to Implement Red Black Tree
//  Implements a Red Black Tree class.
//**************************************************************
#include <iostream>
#include <iomanip> //to format output
#include <sstream>
#include <string>
#include <deque>
#include <stdlib.h>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <cassert>

using namespace std;

struct node
{
       string myKey;
       node *myParent;
       string color;
       string discipline;
       string gender;
       string isTeam;
       string event;
       string venue;
       string medal;
       string athlete;
       string country;
       node *myLeft;
       node *myRight;
};
class redBlackTree
{
      node *q;
   public :
      node *root;

      redBlackTree()
      {
              q=NULL;
              root=NULL;
      }
      void insert(string discipline,string gender,string ind_team,string event,string venue,string medal,string athlete,string country,string myKey);
      void insertfix(node *);
      void myLeftRotate(node *);
      void myRightRotate(node *);
      bool del(string myKey);
      node* successor(node *);
      node* predecessor(node *);
      node* minimum(node *);
      node* maximum(node *);
      void inorderTreeWalk(node *);
      void preorderTreeWalk(node *);
      void postorderTreeWalk(node *);
      void delfix(node *);
      //void disp();
      //void display( node *);
      node*  search(string myKey);
};
void redBlackTree::insert(string discipline,string gender,string ind_team,string event,string venue,string medal,string athlete,string country,string myKey)
{
     int i=0;
     node *p,*q;
     node *t=new node;
     t->discipline=discipline;
     t->gender=gender;
     t->isTeam=ind_team;
     t->event=event;
     t->venue=venue;
     t->medal=medal;
     t->athlete=athlete;
     t->country=country;
     t->myKey=myKey;
     t->myLeft=NULL;
     t->myRight=NULL;
     t->color="RED";
     p=root;
     q=NULL;
     if(root==NULL)
     {
           root=t;
           t->myParent=NULL;
     }
     else
     {
         while(p!=NULL)
         {
              q=p;
              if(p->myKey<t->myKey)
                  p=p->myRight;
              else
                  p=p->myLeft;
         }
         t->myParent=q;
         if(q->myKey<t->myKey)
              q->myRight=t;
         else
              q->myLeft=t;
     }
     insertfix(t);
}
void redBlackTree::insertfix(node *t)
{
     node *u;
     if(root==t)
     {
         t->color="BLACK";
         return;
     }
     while(t->myParent!=NULL&&t->myParent->color=="RED")
     {
           node *g=t->myParent->myParent;
           if(g->myLeft==t->myParent)
           {
                        if(g->myRight!=NULL)
                        {
                              u=g->myRight;
                              if(u->color=="RED")
                              {
                                   t->myParent->color="BLACK";
                                   u->color="BLACK";
                                   g->color="RED";
                                   t=g;
                              }
                        }
                        else
                        {
                            if(t->myParent->myRight==t)
                            {
                                 t=t->myParent;
                                 myLeftRotate(t);
                            }
                            t->myParent->color="BLACK";
                            g->color="RED";
                            myRightRotate(g);
                        }
           }
           else
           {
                        if(g->myLeft!=NULL)
                        {
                             u=g->myLeft;
                             if(u->color=="RED")
                             {
                                  t->myParent->color="BLACK";
                                  u->color="BLACK";
                                  g->color="RED";
                                  t=g;
                             }
                        }
                        else
                        {
                            if(t->myParent->myLeft==t)
                            {
                                   t=t->myParent;
                                   myRightRotate(t);
                            }
                            t->myParent->color="BLACK";
                            g->color="RED";
                            myLeftRotate(g);
                        }
           }
           root->color="BLACK";
     }
}

bool redBlackTree::del(string myKey)
{
     if(root==NULL)
     {
           cout<<"\ntree is empty." ;
           return false;
     }
     string x = myKey;
     node *p;
     p=root;
     node *y=NULL;
     node *q=NULL;
     int found=0;
     while(p!=NULL&&found==0)
     {
           if(p->myKey==x)
               found=1;
           if(found==0)
           {
                 if(p->myKey<x)
                    p=p->myRight;
                 else
                    p=p->myLeft;
           }
     }
     if(found==0)
     {
            //cout<<"\nElement Not Found.";
            return false;
     }
     else
     {
         if(p->myLeft==NULL||p->myRight==NULL)
              y=p;
         else
              y=successor(p);
         if(y->myLeft!=NULL)
              q=y->myLeft;
         else
         {
              if(y->myRight!=NULL)
                   q=y->myRight;
              else
                   q=NULL;
         }
         if(q!=NULL)
              q->myParent=y->myParent;
         if(y->myParent==NULL)
              root=q;
         else
         {
             if(y==y->myParent->myLeft)
                y->myParent->myLeft=q;
             else
                y->myParent->myRight=q;
         }
         if(y!=p)
         {
             p->color=y->color;
             p->myKey=y->myKey;
         }
         if(y->color=="BLACK")
             delfix(q);
             return true;
     }
}

void redBlackTree::delfix(node *p)
{
    node *s;
    while(p!=root&&p->color=="BLACK")
    {
          if(p->myParent->myLeft==p)
          {
                  s=p->myParent->myRight;
                  if(s->color=="RED")
                  {
                         s->color="BLACK";
                         p->myParent->color="RED";
                         myLeftRotate(p->myParent);
                         s=p->myParent->myRight;
                  }
                  if(s->myRight->color=="BLACK"&&s->myLeft->color=="BLACK")
                  {
                         s->color="RED";
                         p=p->myParent;
                  }
                  else
                  {
                      if(s->myRight->color=="BLACK")
                      {
                             s->myLeft->color=="BLACK";
                             s->color="RED";
                             myRightRotate(s);
                             s=p->myParent->myRight;
                      }
                      s->color=p->myParent->color;
                      p->myParent->color="BLACK";
                      s->myRight->color="BLACK";
                      myLeftRotate(p->myParent);
                      p=root;
                  }
          }
          else
          {
                  s=p->myParent->myLeft;
                  if(s->color=="RED")
                  {
                        s->color="BLACK";
                        p->myParent->color="RED";
                        myRightRotate(p->myParent);
                        s=p->myParent->myLeft;
                  }
                  if(s->myLeft->color=="BLACK"&&s->myRight->color=="BLACK")
                  {
                        s->color="RED";
                        p=p->myParent;
                  }
                  else
                  {
                        if(s->myLeft->color=="BLACK")
                        {
                              s->myRight->color="BLACK";
                              s->color="RED";
                              myLeftRotate(s);
                              s=p->myParent->myLeft;
                        }
                        s->color=p->myParent->color;
                        p->myParent->color="BLACK";
                        s->myLeft->color="BLACK";
                        myRightRotate(p->myParent);
                        p=root;
                  }
          }
       p->color="BLACK";
       root->color="BLACK";
    }
}

void redBlackTree::myLeftRotate(node *p)
{
     if(p->myRight==NULL)
           return ;
     else
     {
           node *y=p->myRight;
           if(y->myLeft!=NULL)
           {
                  p->myRight=y->myLeft;
                  y->myLeft->myParent=p;
           }
           else
                  p->myRight=NULL;
           if(p->myParent!=NULL)
                y->myParent=p->myParent;
           if(p->myParent==NULL)
                root=y;
           else
           {
               if(p==p->myParent->myLeft)
                       p->myParent->myLeft=y;
               else
                       p->myParent->myRight=y;
           }
           y->myLeft=p;
           p->myParent=y;
     }
}
void redBlackTree::myRightRotate(node *p)
{
     if(p->myLeft==NULL)
          return ;
     else
     {
         node *y=p->myLeft;
         if(y->myRight!=NULL)
         {
                  p->myLeft=y->myRight;
                  y->myRight->myParent=p;
         }
         else
                 p->myLeft=NULL;
         if(p->myParent!=NULL)
                 y->myParent=p->myParent;
         if(p->myParent==NULL)
               root=y;
         else
         {
             if(p==p->myParent->myLeft)
                   p->myParent->myLeft=y;
             else
                   p->myParent->myRight=y;
         }
         y->myRight=p;
         p->myParent=y;
     }
}

node* redBlackTree::successor(node *p)
{
    if(p->myRight!=NULL)
        return minimum(p->myRight);
    node *y=p->myParent;
    while(y!=NULL&& p==y->myRight)
    {
        p=y;
        y=y->myParent;
    }
    return y;
}

node* redBlackTree::predecessor(node *p)
{
    if(p->myLeft!=NULL)
        return maximum(p->myLeft);
    node *y=p->myParent;
    while(y!=NULL&& p==y->myLeft)
    {
        p=y;
        y=y->myParent;
    }
    return y;

}

node* redBlackTree::search(string myKey)
{
     /*if(root==NULL)
     {
           cout<<"\ntree is empty\n" ;
           return  NULL;
     }*/
     string x=myKey;
     node *p=root;
     int found=0;
     while(p!=NULL&& found==0)
     {
            if(p->myKey==x)
                found=1;
            if(found==0)
            {
                 if(p->myKey<x)
                      p=p->myRight;
                 else
                      p=p->myLeft;
            }
     }
     if(found==0)
          return NULL;
     else
                return p;
}

node* redBlackTree::minimum(node* p)
{
     if(root==NULL)
     {
           cout<<"\ntree is empty\n" ;
           return  NULL;
     }
     //node *p=root;
     while(p->myLeft!=NULL)
     {
                      p=p->myLeft;
     }
     return p;
}

node* redBlackTree::maximum(node* p)
{
     if(root==NULL)
     {
           cout<<"\ntree is empty\n" ;
           return  NULL;
     }
     //node *p=root;
     while(p->myRight!=NULL)
     {
                      p=p->myRight;
     }
     return p;
}

 // Print the tree in-order
// Traverse the myLeft sub-tree, root, myRight sub-tree
void redBlackTree::inorderTreeWalk (node* n) {
    if(root==NULL)
     {
          cout<<"\ntree is empty";
          return ;
     }
    if ( n ) {
       inorderTreeWalk(n->myLeft);
        cout <<"\n\n\ndiscipline :   "<< n -> discipline;
        cout <<"\ngender :       "<< n -> gender;
        cout <<"\nteam or ind :  "<< n -> isTeam;
        cout <<"\nevent :        "<< n -> event;
        cout <<"\nvenue :        "<< n -> venue;
        cout <<"\nmedal :        "<< n -> medal;
        cout <<"\nathlete :      "<< n -> athlete;
        cout <<"\ncountry :      "<< n -> country;
        cout <<"\ncolor:         "<< n -> color;
       inorderTreeWalk(n->myRight);
    }
}

// Print the tree pre-order
// Traverse the root, myLeft sub-tree, myRight sub-tree
void redBlackTree::preorderTreeWalk (node* n) {
    if(root==NULL)
     {
          cout<<"\ntree is empty";
          return ;
     }
    if ( n ) {
       cout <<"\n\n\ndiscipline :   "<< n -> discipline;
        cout <<"\ngender :       "<< n -> gender;
        cout <<"\nteam or ind :  "<< n -> isTeam;
        cout <<"\nevent :        "<< n -> event;
        cout <<"\nvenue :        "<< n -> venue;
        cout <<"\nmedal :        "<< n -> medal;
        cout <<"\nathlete :      "<< n -> athlete;
        cout <<"\ncountry :      "<< n -> country;
        cout <<"\ncolor:         "<< n -> color;
       preorderTreeWalk(n->myLeft);
       preorderTreeWalk(n->myRight);
    }
}

// Print the tree post-order
// Traverse myLeft sub-tree, myRight sub-tree, root
void redBlackTree::postorderTreeWalk (node* n) {
    if(root==NULL)
     {
          cout<<"\ntree is empty";
          return ;
     }
    if ( n ) {
       postorderTreeWalk(n->myLeft);
       postorderTreeWalk(n->myRight);
       cout <<"\n\n\ndiscipline :   "<< n -> discipline;
        cout <<"\ngender :       "<< n -> gender;
        cout <<"\nteam or ind :  "<< n -> isTeam;
        cout <<"\nevent :        "<< n -> event;
        cout <<"\nvenue :        "<< n -> venue;
        cout <<"\nmedal :        "<< n -> medal;
        cout <<"\nathlete :      "<< n -> athlete;
        cout <<"\ncountry :      "<< n -> country;
        cout <<"\ncolor:         "<< n -> color;
    }
}

/* The method printMenu displays the menu to a user */

  void printMenu()
   {
     cout << "\n\nCommands\n";
     cout << "------\t\t------\n";
     cout << "tree_inorder\n";
     cout << "tree_preorder\n";
     cout << "tree_postorder\n";
     cout << "tree_maximum\n";
     cout << "tree_minimum\n";
     cout << "tree_successor\n";
     cout << "tree_predecessor\n";
     cout << "tree_search\n";
     cout << "tree_insert\n";
     cout << "quit\n\n";
  }

int main()
{
    // local variables, can be accessed anywhere from the main method
       string inputInfo;

       string discipline, gender, isTeam, event, venue, medal, athlete, country, itemKey;
       node * found;
       string line="";
       bool success = false;

       int ch,y=0;
       redBlackTree obj;

       while(line!="quit"){
            printMenu();
            cout << "Please Enter A Command:\n";
            getline(cin, line);
            istringstream ss(line);
            string token;
            string commandLine[10];
            int i =0;
            while(std::getline(ss, token, ',')) {
                    //std::cout << token << '\n'; Debug
                    commandLine[i] = token;
                    //std::cout << athleteData[i] << '\n'; Debug
                    i=i+1;
                }

            itemKey = commandLine[1]+commandLine[2]+commandLine[3]+commandLine[4];
            cout<<"\n";
            if(commandLine[0]=="tree_inorder"){

                obj.inorderTreeWalk(obj.root);

            }
            if(commandLine[0]=="tree_preorder"){

                obj.preorderTreeWalk(obj.root);

            }
            if(commandLine[0]=="tree_postorder"){

                obj.postorderTreeWalk(obj.root);

            }
            if(commandLine[0]=="tree_maximum"){
                node*x=obj.maximum(obj.root);

                    cout<< "The last athlete is";
                    cout <<"\n\ndiscipline :   "<< x -> discipline;
                    cout <<"\ngender :       "<< x -> gender;
                    cout <<"\nteam or ind :  "<< x -> isTeam;
                    cout <<"\nevent :        "<< x -> event;
                    cout <<"\nvenue :        "<< x -> venue;
                    cout <<"\nmedal :        "<< x -> medal;
                    cout <<"\nathlete :      "<< x -> athlete;
                    cout <<"\ncountry :      "<< x -> country;
                    cout <<"\ncolor:         "<< x -> color;

            }
            if(commandLine[0]=="tree_minimum"){
                node*x=obj.minimum(obj.root);

                    cout<< "The first athlete is";
                   cout <<"\n\ndiscipline :   "<< x -> discipline;
                   cout <<"\ngender :       "<< x -> gender;
                   cout <<"\nteam or ind :  "<< x -> isTeam;
                   cout <<"\nevent :        "<< x -> event;
                   cout <<"\nvenue :        "<< x -> venue;
                   cout <<"\nmedal :        "<< x -> medal;
                   cout <<"\nathlete :      "<< x -> athlete;
                   cout <<"\ncountry :      "<< x -> country;
                   cout <<"\ncolor:         "<< x -> color;

            }
            if(commandLine[0]=="tree_successor"){
                node*x=obj.search(commandLine[1]+commandLine[2]+commandLine[3]+commandLine[4]);
                node*y=obj.successor(x);
                if(x==NULL || y==NULL)
                    cout<<"The medal recipient "<<commandLine[4]<<" for "<<commandLine[1]<<" with event "<<commandLine[3]<<" does not have any successor.\n";
                else
                    {
                    cout<< "The successor of the medal recipient "<<commandLine[4]<<" for "<<commandLine[1]<<" with event "<<commandLine[3]<<" is ";
                   cout <<"\n\ndiscipline :   "<< y -> discipline;
                   cout <<"\ngender :       "<< y -> gender;
                   cout <<"\nteam or ind :  "<< y -> isTeam;
                   cout <<"\nevent :        "<< y -> event;
                   cout <<"\nvenue :        "<< y -> venue;
                   cout <<"\nmedal :        "<< y -> medal;
                   cout <<"\nathlete :      "<< y -> athlete;
                   cout <<"\ncountry :      "<< y -> country;
                   cout <<"\ncolor:         "<< y -> color;
                    }
            }
            if(commandLine[0]=="tree_predecessor"){
                node*x=obj.search(commandLine[1]+commandLine[2]+commandLine[3]+commandLine[4]);
                node*y=obj.predecessor(x);
                if(x==NULL || y==NULL)
                    cout<<"The medal recipient "<<commandLine[4]<<" for "<<commandLine[1]<<" with event "<<commandLine[3]<<" does not have any predecessor.\n";
                else
                    {
                    cout<< "The predecessor of the medal recipient "<<commandLine[4]<<" for "<<commandLine[1]<<" with event "<<commandLine[3]<<" is ";
                   cout <<"\n\ndiscipline :   "<< y -> discipline;
                   cout <<"\ngender :       "<< y -> gender;
                   cout <<"\nteam or ind :  "<< y -> isTeam;
                   cout <<"\nevent :        "<< y -> event;
                   cout <<"\nvenue :        "<< y -> venue;
                   cout <<"\nmedal :        "<< y -> medal;
                   cout <<"\nathlete :      "<< y -> athlete;
                   cout <<"\ncountry :      "<< y -> country;
                   cout <<"\ncolor:         "<< y -> color;
                    }
            }
            if(commandLine[0]=="tree_search"){
                node*x=obj.search(commandLine[1]+commandLine[2]+commandLine[3]+commandLine[4]);
                if(x==NULL)
                    cout<<commandLine[4]<<" for "<<commandLine[1]<<" with event "<<commandLine[3]<<" not found.\n";
                else
                    cout<< "The medal recipient "<<commandLine[4]<<" has the medal of "<<x->medal<<".\n";
            }
            if(commandLine[0]=="tree_insert"){
                if(obj.search(commandLine[1]+commandLine[2]+commandLine[4]+commandLine[7])==NULL)
                    {
                        obj.insert(commandLine[1],commandLine[2],commandLine[3],commandLine[4],commandLine[5],commandLine[6],commandLine[7],commandLine[8],commandLine[1]+commandLine[2]+commandLine[4]+commandLine[7]);
                        cout<< "The medal recipient "<<commandLine[7]<<" for "<<commandLine[1]<< " with event "<<commandLine[4] <<" inserted\n";
                    }
                else
                    cout<< "The medal recipient "<<commandLine[7]<<" for "<<commandLine[1]<< " with event "<<commandLine[4] <<" NOT inserted\n";
            }
       }

    return 0;

}
