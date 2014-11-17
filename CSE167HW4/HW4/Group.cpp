//
//  Group.cpp
//  CSE167HW1
//
//  Created by Mingshan Wang on 11/10/14.
//  Copyright (c) 2014 Mingshan Wang. All rights reserved.
//

#include "Group.h"
using namespace std;

Group::Group(){
}

void Group::addChild(Node* n){
    n->setParent(this);
    numOfChild++;
    nodeList.push_back(n);
}

void Group::removeChild(string name){
    list<Node*>::iterator iter = nodeList.begin();
    list<Node*>::iterator end = nodeList.end();
    for(;iter!=end;++iter){
        if((*iter)->getName() == name){
            nodeList.remove(*iter);
        }
   }
}

void Group::draw(Matrix4 C){
    cout << "in group" << endl;
    list<Node*>::iterator iter = nodeList.begin();
    list<Node*>::iterator end = nodeList.end();
    for(;iter!=end;++iter){
        (*iter)->draw(C);
    }
}

void Group::update(){

}

void Group::drawBoundingBox(Matrix4 C){

}
