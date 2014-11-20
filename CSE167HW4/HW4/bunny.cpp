//
//  bunny.cpp
//  CSE167HW1
//
//  Created by Mingshan Wang on 10/22/14.
//  Copyright (c) 2014 Mingshan Wang. All rights reserved.
//

#include "bunny.h"
#include <fstream>
using namespace std;

bunny::bunny(){
    model2world.identity();
    FILE* fp;     // file pointer
    float x,y,z;  // vertex coordinates
    float r,g,b;  // vertex color
    int c1,c2;    // characters read from file
    string s1,s2,s3; // string for face
    
    fp = fopen("/Users/Margaret/Desktop/CSE167_HWs/CSE167HW4/HW4/bunny.obj","rb");
    if (fp==NULL) {
        cerr << "error loading file" << endl; exit(-1);
    }
    
    // parse other cases and loop over lines of file
    while(!feof(fp)){
        c1 = fgetc(fp);
        c2 = fgetc(fp);
        if (c1=='v' && c2==' '){
            fscanf(fp, "%f %f %f %f %f %f", &x, &y, &z, &r, &g, &b);
            Vector3 p = Vector3(x, y, z);
            Vector3 c = Vector3(r, g, b);
            position.push_back(p);
            color.push_back(c);
        }
        else if(c1 == 'v' && c2 =='n'){
            fscanf(fp, " %f %f %f",&x,&y,&z);
            Vector3 n = Vector3(x, y, z);
            normal.push_back(n);
        }
        else if(c1 == 'f' &&  c2== ' '){
            fscanf(fp, "%f//%f %f//%f %f//%f", &x, &y, &z, &r, &g, &b);
            Vector3 fv = Vector3(x, g, z);
            Vector3 fn = Vector3(y, r, b);
            face_vertice.push_back(fv);
            face_normal.push_back(fn);
        }
        else{
            fscanf(fp, "\n");
        }
    }
    fclose(fp);   // make sure you don't forget to close the file when done
    for(int i  = 0;i< normal.size();i++){
        normal[i].normalize();
    }
    for(int i = 0; i< position.size();i++){
        if(position[i].x < x_smallest){
            x_smallest = position[i].x;
        }
        if(position[i].x>x_biggest){
            x_biggest = position[i].x;
        }
    }
    for(int i = 0; i< position.size();i++){
        if(position[i].y < y_smallest){
            y_smallest = position[i].y;
        }
        if(position[i].y>y_biggest){
            y_biggest = position[i].y;
        }
    }
    
    for(int i = 0; i< position.size();i++){
        if(position[i].z < z_smallest){
            z_smallest = position[i].z;
        }
        if(position[i].z>z_biggest){
            z_biggest = position[i].z;
        }
    }
    
    cout << "x_biggest is " << x_biggest << " "<< x_smallest << endl;
    cout <<"y_biggest is " <<y_biggest <<" "<< y_smallest << endl;
    cout <<"z_biggest is " <<z_biggest <<" "<< z_smallest << endl;
    
    center_x = 0.5*(x_smallest + x_biggest);
    center_y = 0.5*(y_smallest + y_biggest);
    center_z = 0.5*(z_smallest + z_biggest);
    
    light = Light();
    Matrix4 t = Matrix4();
    t.identity();
    t.makeTranslate(light.light_position[0],
                    light.light_position[1],
                    light.light_position[2]);
    m2w_light = t;
    mat = Material();
    t.identity();
    t.makeTranslate(light.light_position_s[0],
                    light.light_position_s[1],
                    light.light_position_s[2]);
    m2w_spotLight = t;
}

Matrix4& bunny::getMatrix()
{
    return model2world;
}

// rotate along y axis
void bunny::spin(double angle){
    Matrix4 tmp = Matrix4();
    tmp.makeRotateY(angle);
    model2world = model2world*tmp;
}

void bunny::scale(double scale){
    Matrix4 tmp = Matrix4();
    //tmp.identity();
    tmp.makeScale(scale, scale, scale);
    // the order is important to keep in the local space
    model2world = model2world * tmp;
}

void bunny::moveLeft(){
    //create a translation matrix
    Matrix4 *tmp = new Matrix4();
    tmp->makeTranslate(-1.0,0,0);
    model2world = *tmp * model2world;
}

void bunny::moveRight(){
    //create a translation matrix
    Matrix4 *tmp = new Matrix4();
    tmp->makeTranslate(1.0,0.0,0.0);
    model2world = *tmp * model2world;
}

void bunny::moveDown(){
    //Create a translation Matrix
    Matrix4 tmp = Matrix4();
    tmp.makeTranslate(0.0,-1.0,0.0);
    model2world = tmp * model2world;
}

void bunny::moveUp(){
    //Create a translation Matrix
    Matrix4 tmp = Matrix4();
    tmp.makeTranslate(0.0,1.0,0.0);
    model2world = tmp * model2world;
}

void bunny::moveInto(){
    //Create a translation Matrix
    Matrix4 tmp = Matrix4();
    tmp.makeTranslate(0.0,0.0,1.0);
    model2world = tmp * model2world;
}

void bunny::moveOutOf(){
    //Create a translation Matrix
    Matrix4 tmp = Matrix4();
    tmp.makeTranslate(0.0,0.0,-1.0);
    //The multiplication order is important
    model2world = tmp * model2world;
}

void bunny::update(){
    Matrix4 t = Matrix4();
    t.identity();
    t.makeTranslate(light.light_position[0], light.light_position[1], light.light_position[2]);
    m2w_light = t;
    t.identity();
    t.makeTranslate(light.light_position_s[0], light.light_position_s[1], light.light_position_s[2]);
    m2w_spotLight= t;
}
