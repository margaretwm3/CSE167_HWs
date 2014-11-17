//
//  Node.cpp
//  CSE167HW1
//
//  Created by Mingshan Wang on 11/10/14.
//  Copyright (c) 2014 Mingshan Wang. All rights reserved.
//

#include "Node.h"

Node::Node(){
    parent = nullptr;
    name = "";
}

Node::Node(string name){
    this->name = name;
    parent = nullptr;
}

string Node::getName(){
    return this->name;
}

void Node::setName(string name){
    this->name = name;
}

Node* Node::getParent(){
    return this->parent;
}

void Node::setParent(Node* n){
    this->parent = n;
}