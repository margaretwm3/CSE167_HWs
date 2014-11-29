//
//  Robot.cpp
//  CSE167HW1
//
//  Created by Mingshan Wang on 11/12/14.
//  Copyright (c) 2014 Mingshan Wang. All rights reserved.
//

#include "Robot.h"

Robot::Robot(){
    this->root = new MatrixTransform();
}

MatrixTransform* Robot::buildRobot(double forwardAngle,double backwardAngle){
    root = new MatrixTransform();
    //head
    Matrix4 tmp = Matrix4();
    tmp.identity();
    tmp.makeScale(1,1,1);
    Matrix4 translate_head = Matrix4();
    translate_head.identity();
    translate_head.makeTranslate(0,6.5,1);
    tmp =  tmp * translate_head;
    MatrixTransform *head = new MatrixTransform(tmp);
    Sphere *head_sphere = new Sphere();
    head_sphere->setName("head_sphere");
    head->addChild(head_sphere);
    
    //torso
    Matrix4 bodyScale = Matrix4();
    bodyScale.identity();
    bodyScale.makeScale(1.5, 2, 2);
    Matrix4 bodyTranslate = Matrix4();
    bodyTranslate.identity();
    bodyTranslate.makeTranslate(0,0,0);
    //combine the translate and scale together to Matrix4 t
    Matrix4 t =  bodyTranslate * bodyScale;
    MatrixTransform *torso = new MatrixTransform(t);
    Cube_Geode *c = new Cube_Geode();
    c->setName("torse cube");
    torso->addChild(c);
   
    //left arm
    Matrix4 leftArm_translate = Matrix4();
    leftArm_translate.identity();
    leftArm_translate.makeTranslate(-3.8,-0.5,0);
    Matrix4 leftArm_scale = Matrix4();
    leftArm_scale.identity();
    leftArm_scale.makeScale(0.5,2,1);
    Matrix4 la =leftArm_translate * leftArm_scale;
    Matrix4 leftArm_rotate = Matrix4();
    leftArm_rotate.makeRotateX(forwardAngle);
    la = leftArm_rotate * la ;
    MatrixTransform *leftArm = new MatrixTransform(la);
    Cube_Geode *c_la = new Cube_Geode();
    c_la->setName("left arm ");
    leftArm->addChild(c_la);
   
    // right arm
    Matrix4 rightArm_translate = Matrix4();
    rightArm_translate.identity();
    rightArm_translate.makeTranslate(3.8,-0.5,0);
    Matrix4 rightArm_scale = Matrix4();
    rightArm_scale.identity();
    rightArm_scale.makeScale(0.5,2,1);
    Matrix4 ra = rightArm_translate * rightArm_scale;
    Matrix4 rightArm_rotate = Matrix4();
    rightArm_rotate.makeRotateX(backwardAngle);
    ra = rightArm_rotate * ra ;
    MatrixTransform *rightArm = new MatrixTransform(ra);
    Cube_Geode *c_ra = new Cube_Geode();
    c_ra->setName("right arm ");
    rightArm->addChild(c_ra);
    
    // left leg
    Matrix4 leftLeg_translate = Matrix4();
    leftLeg_translate.identity();
    leftLeg_translate.makeTranslate(-3,-6,0);
    Matrix4 leftLeg_scale = Matrix4();
    leftLeg_scale.identity();
    leftLeg_scale.makeScale(0.5,1.5,0.5);
    Matrix4 ll = leftLeg_translate * leftLeg_scale;
    Matrix4 leftLeg_rotate = Matrix4();
    leftLeg_rotate.makeRotateX(backwardAngle);
    ll = leftLeg_rotate * ll ;
    MatrixTransform *leftLeg = new MatrixTransform(ll);
    Cube_Geode *c_ll = new Cube_Geode();
    c_ll->setName("left leg ");
    leftLeg->addChild(c_ll);

    // right leg
    Matrix4 rightLeg_translate = Matrix4();
    rightLeg_translate.identity();
    rightLeg_translate.makeTranslate(3,-6,0);
    Matrix4 rightLeg_scale = Matrix4();
    rightLeg_scale.identity();
    rightLeg_scale.makeScale(0.5,1.5,0.5);
    Matrix4 rl = rightLeg_translate * rightLeg_scale;
    Matrix4 rightLeg_rotate = Matrix4();
    rightLeg_rotate.makeRotateX(forwardAngle);
    rl = rightLeg_rotate * rl ;
    MatrixTransform *rightLeg = new MatrixTransform(rl);
    Cube_Geode *c_rl = new Cube_Geode();
    c_rl->setName("right leg ");
    rightLeg->addChild(c_rl);
    
    //build the hierachy
    root->addChild(head);
    root->addChild(torso);
    root->addChild(leftArm);
    root->addChild(rightArm);
    root->addChild(leftLeg);
    root->addChild(rightLeg);
    return root;
}

void Robot::scaling(double scale){
    Matrix4 tmp = Matrix4();
    tmp.identity();
    tmp.makeScale(scale, scale, scale);
    root->M = (root->M) * tmp;
}

//for the army
void Robot::setLocation(float x,float y,float z){
    Matrix4 tmp = Matrix4();
    tmp.makeTranslate(x, y, z);
    this->root->M = (this->root->M) * tmp;
}



 
