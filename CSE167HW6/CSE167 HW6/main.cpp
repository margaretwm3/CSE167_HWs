#include <stdlib.h>
#include <GLUT/glut.h>
#include <iostream>
#include <random>
#include <vector>
#include "SOIL.h"
#include "Matrix4.h"
#include "Camera.h"
#include "shader.h"
#include <iostream>

#define PI 3.14159265f


using namespace std;

/// a structure to hold a control point of the surface
struct Point {
    float x;
    float y;
    float z;
};

Matrix4 model2world = Matrix4();
Camera cameraMatrix = Camera();
bool envOn = false;
Shader* shader;
float timeForCurve;

/// 4x4 grid of points that will define the surface

/*
Point Points[4][4] = {
    {
        { 38,-38,50 },
        {  18,-38,50},
        { -18,-38,50 },
        {-38,-39,50 }
    },
    {
        { 38, -38,25 },
        {  18,-38,25 },
        { -18,-38,25 },
        {-38, -38,25 }
    },
    {
        { 38, -38,-25 },
        {  18,-38,-25 },
        { -18,-38,-25 },
        {-38, -38,-25 }
    },
    {
        { 38, -38,-50 },
        {  18,-38,-50},
        { -18,-38,-50},
        {-38, -38,-50}
    }
};
 */

Point Points[4][4] = {
    {
        { 15,-10,-15 },
        {  5,-10,-15},
        { -5,-10,-15 },
        {-15,-10,-15 }
    },
    {
        { 15, -10,-5 },
        {  5,-10,-5 },
        { -5,-10,-5 },
        {-15,-10,-5 }
    },
    {
        { 15,-10,5 },
        {  5,-10,5 },
        { -5,-10,5 },
        {-15,-10,5 }
    },
    {
        { 15, -10,15 },
        {  5,-10,15},
        { -5,-10,15},
        {-15, -10,15}
    }
};

// the level of detail of the surface
unsigned int LOD=100;
//calculate the normal
float delta_t = 0.00001;

int windowId = 0;
GLuint texture[5];
vector<const GLchar*> faces;
     int LoadGLTextures()
    {
        /* load an image file directly as a new OpenGL texture */
        texture[0] = SOIL_load_OGL_texture
        (
         "/Users/margaretwm3/Desktop/CSE167_HWs/CSE167HW6/PalldioPalace_extern_front.jpg",
         SOIL_LOAD_AUTO,
         SOIL_CREATE_NEW_ID,
         SOIL_FLAG_INVERT_Y
         );
        
        /* load an image file directly as a new OpenGL texture */
        texture[1] = SOIL_load_OGL_texture
        (
         "/Users/margaretwm3/Desktop/CSE167_HWs/CSE167HW6/PalldioPalace_extern_left.jpg",
         SOIL_LOAD_AUTO,
         SOIL_CREATE_NEW_ID,
         SOIL_FLAG_INVERT_Y
         );
        
        /* load an image file directly as a new OpenGL texture */
        texture[2] = SOIL_load_OGL_texture
        (
         "/Users/margaretwm3/Desktop/CSE167_HWs/CSE167HW6/PalldioPalace_extern_back.jpg",
         SOIL_LOAD_AUTO,
         SOIL_CREATE_NEW_ID,
         SOIL_FLAG_INVERT_Y
         );
        /* load an image file directly as a new OpenGL texture */
        texture[3] = SOIL_load_OGL_texture
        (
         "/Users/margaretwm3/Desktop/CSE167_HWs/CSE167HW6/PalldioPalace_extern_right.jpg",
         SOIL_LOAD_AUTO,
         SOIL_CREATE_NEW_ID,
         SOIL_FLAG_INVERT_Y
         );
        /* load an image file directly as a new OpenGL texture */
        texture[4] = SOIL_load_OGL_texture
        (
         "/Users/margaretwm3/Desktop/CSE167_HWs/CSE167HW6/PalldioPalace_extern_top.jpg",
         SOIL_LOAD_AUTO,
         SOIL_CREATE_NEW_ID,
         SOIL_FLAG_INVERT_Y
         );
        
        if(texture[0] == 0)
        {
            printf( "SOIL loading error 0: '%s'\n", SOIL_last_result() );
            return false;
        }
        if(texture[1] == 0)
        {
            printf( "SOIL loading error 1: '%s'\n", SOIL_last_result() );
            return false;
        }
        if(texture[2] == 0)
        {
            printf( "SOIL loading error 2: '%s'\n", SOIL_last_result() );
            return false;
        }
        if(texture[3] == 0)
        {
            printf( "SOIL loading error 3: '%s'\n", SOIL_last_result() );
            return false;
        }
        if(texture[4] == 0)
        {
            printf( "SOIL loading error 4: '%s'\n", SOIL_last_result() );
            return false;
        }
        return true;
    }


//------------------------------------------------------------	CalculateU()
// Given our 16 control points, we can imagine 4 curves travelling
// in a given surface direction. For example, if the parametric u
// value was 0.5, we could imagine evaluating 4 seperate curves
// at u=0.5.
//
// This function is basically here to perform that very task. each
// row of 4 points in the u-direction is evaluated to provide us
// with 4 new points. These new points then form a curve we can
// evaluate in the v direction to calculate our final output point.
//
Point CalculateU(float t,int row) {
    
    // the final point
    Point p;
    
    // the t value inverted
    float it = 1.0f-t;
    
    // calculate blending functions
    float b0 = t*t*t;
    float b1 = 3*t*t*it;
    float b2 = 3*t*it*it;
    float b3 =  it*it*it;
    
    
    // sum the effects of the Points and their respective blending functions
    p.x = b0*Points[row][0].x +
		  b1*Points[row][1].x +
		  b2*Points[row][2].x +
		  b3*Points[row][3].x ;
    
    p.y = b0*Points[row][0].y +
		  b1*Points[row][1].y +
		  b2*Points[row][2].y +
		  b3*Points[row][3].y ;
    
    p.z = b0*Points[row][0].z +
		  b1*Points[row][1].z +
		  b2*Points[row][2].z +
		  b3*Points[row][3].z ;
    
    return p;
}

//laod a cubemap
GLuint loadCubemap(vector<const GLchar*> faces)
{
    cout << "enter in loadCubemap " << endl;
    GLuint textureID;
    glGenTextures(1, &textureID);
    glActiveTexture(GL_TEXTURE0);
    
    int width,height;
    unsigned char* image;
    
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
    for(GLuint i = 0; i < faces.size(); i++)
    {
        image = SOIL_load_image(faces[i], &width, &height, 0, SOIL_LOAD_RGB);
        glTexImage2D(
                     GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0,
                     GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image
                     );
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
    
    return textureID;
}

//------------------------------------------------------------	CalculateV()
// Having generated 4 points in the u direction, we need to
// use those points to generate the final point on the surface
// by calculating a final bezier curve in the v direction.
//     This function takes the temporary points and generates
// the final point for the rendered surface
//
Point CalculateV(float t,Point* pnts) {
    Point p;
    
    // the t value inverted
    float it = 1.0f-t;
    
    // calculate blending functions
    float b0 = t*t*t;
    float b1 = 3*t*t*it;
    float b2 = 3*t*it*it;
    float b3 =  it*it*it;
    
    // sum the effects of the Points and their respective blending functions
    p.x = b0*pnts[0].x +
		  b1*pnts[1].x +
		  b2*pnts[2].x +
		  b3*pnts[3].x ;
    
    p.y = b0*pnts[0].y +
		  b1*pnts[1].y +
		  b2*pnts[2].y +
		  b3*pnts[3].y ;
    
    p.z = b0*pnts[0].z +
		  b1*pnts[1].z +
		  b2*pnts[2].z +
		  b3*pnts[3].z ;
    
    return p;
}

//------------------------------------------------------------	Calculate()
// On our bezier patch, we need to calculate a set of points
// from the u and v parametric range of 0,0 to 1,1. This calculate
// function performs that evaluation by using the specified u
// and v parametric coordinates.
//
Point Calculate(float u,float v) {
    
    // first of all we will need to evaluate 4 curves in the u
    // direction. The points from those will be stored in this
    // temporary array
    Point temp[4];
    
    // calculate each point on our final v curve
    temp[0] = CalculateU(u,0);
    temp[1] = CalculateU(u,1);
    temp[2] = CalculateU(u,2);
    temp[3] = CalculateU(u,3);
    
    // having got 4 points, we can use it as a bezier curve
    // to calculate the v direction. This should give us our
    // final point
    return CalculateV(v,temp);
}

Point controlPoint_t[4];
Point controlPoint_t_delta[4];
//for calculating the normal


Vector3 calculateNormal(float u,float v){
    Point temp[4];
    
    // calculate each point on our final v curve
    temp[0] = CalculateU(u,0);
    temp[1] = CalculateU(u,1);
    temp[2] = CalculateU(u,2);
    temp[3] = CalculateU(u,3);
    
    float u_delta = u + 0.00001;
    Point temp1[4];
    temp1[0] = CalculateU(u_delta, 0);
    temp1[1] = CalculateU(u_delta, 1);
    temp1[2] = CalculateU(u_delta, 2);
    temp1[3] = CalculateU(u_delta, 3);
    
    
    Point p = CalculateV(v, temp);
    Point p1 = CalculateV(v+0.00001, temp);
    
    Vector3 u0 = Vector3(p.x, p.y, p.z);
    Vector3 u1 = Vector3(p1.x, p1.y, p1.z);
    Vector3 tanu = u1 - u0;
    
    Point p2 = CalculateV(v, temp1);
    Vector3 v0 = Vector3(p2.x, p2.y, p2.z);
    Vector3 tanv = v0 - u0;
    tanu.normalize();
    tanv.normalize();
    
    
    Vector3 normal = tanu.cross(tanu, tanv);
    normal.normalize();
    //normal.print("normal is ");
    return normal;
}

//------------------------------------------------------------	OnReshape()
//
void OnReshape(int w, int h)
{
    // prevent a division by zero when setting aspect ratio
    if (h==0)
        h=1;
    
    // set the drawable region of the window
    glViewport(0,0,w,h);
    
    // set up the projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    // just use a perspective projection
    gluPerspective(45,(float)w/h,0.1,100);
    
    // go back to modelview matrix so we can move the objects about
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

//------------------------------------------------------------	OnDraw()
//
void OnDraw() {
    if(envOn){
        shader->bind();
        shader->printLog("sky shader ");
    }
    else{
        shader->unbind();
    }
    // clear the screen & depth buffer
    glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    Matrix4 glmatrix = cameraMatrix.getCameraMatrix();
    Matrix4 tmp = glmatrix * model2world;
    
  
    //skybox
    glPushMatrix();// Store the current matrix
    //glLoadIdentity();// Reset and transform the matrix.
    glmatrix = cameraMatrix.getCameraMatrix();//get the camera matrix
    tmp = glmatrix * model2world;
    //tmp.identity();
    tmp.transpose();
    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixd(tmp.getPointer());

    // Enable/Disable features
    glEnable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);
    glColor3f(1, 1, 1);
    
    // Render the front quad
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    // Make sure no bytes are padded:
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    // Select GL_MODULATE to mix texture with polygon color for shading:
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    // Use bilinear interpolation:
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    shader->unbind();
    glBegin(GL_QUADS);
        glNormal3f(0, 0,1);
        glTexCoord2f(0, 0); glVertex3f(  15, -15, -15);
        glTexCoord2f(1, 0); glVertex3f(  -15, -15, -15);
        glTexCoord2f(1, 1); glVertex3f(  -15, 15,-15);
        glTexCoord2f(0, 1); glVertex3f(  15,  15, -15 );
        glEnd();
    
    
    // Render the left quad
    glBindTexture(GL_TEXTURE_2D, texture[1]);
    // Make sure no bytes are padded:
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    // Select GL_MODULATE to mix texture with polygon color for shading:
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    // Use bilinear interpolation:
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glBegin(GL_QUADS);
        glNormal3f(-1,0,0);
        glTexCoord2f(0, 0); glVertex3f(  -15, -15, 15);
        glTexCoord2f(1, 0); glVertex3f(  -15, -15, -15 );
        glTexCoord2f(1, 1); glVertex3f(  -15,  15, -15);
        glTexCoord2f(0, 1); glVertex3f(  -15,  15, 15);
    glEnd();
    
    
    // Render the back quad
    glBindTexture(GL_TEXTURE_2D,texture[2]);
    // Make sure no bytes are padded:
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    // Select GL_MODULATE to mix texture with polygon color for shading:
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    // Use bilinear interpolation:
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glBegin(GL_QUADS);
        glNormal3f(0,0,-1);
        glTexCoord2f(0, 0); glVertex3f( 15, -15,  15);
        glTexCoord2f(1, 0); glVertex3f(  -15, -15,  15 );
        glTexCoord2f(1, 1); glVertex3f(  -15,  15,  15 );
        glTexCoord2f(0, 1); glVertex3f( 15,  15,  15 );
    glEnd();
    
    
    // Render the right quad
    glBindTexture(GL_TEXTURE_2D, texture[3]);
    // Make sure no bytes are padded:
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    // Select GL_MODULATE to mix texture with polygon color for shading:
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    // Use bilinear interpolation:
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glBegin(GL_QUADS);
        glNormal3f(1,0,0);
        glTexCoord2f(0, 0); glVertex3f( 15, -15, -15);
        glTexCoord2f(1, 0); glVertex3f( 15, -15, 15 );
        glTexCoord2f(1, 1); glVertex3f( 15,  15, 15 );
        glTexCoord2f(0, 1); glVertex3f( 15,  15, -15);
    glEnd();
    
    // Render the top quad
    glBindTexture(GL_TEXTURE_2D, texture[4]);
    // Make sure no bytes are padded:
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    // Select GL_MODULATE to mix texture with polygon color for shading:
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    // Use bilinear interpolation:
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glBegin(GL_QUADS);
        glNormal3f(0, -1,0);
        glTexCoord2f(0, 1); glVertex3f( -15,  15, 15 );
        glTexCoord2f(0, 0); glVertex3f( -15,  15,  -15 );
        glTexCoord2f(1, 0); glVertex3f(  15,  15,  -15 );
        glTexCoord2f(1, 1); glVertex3f(  15,  15, 15);
    glEnd();
    
    // Restore enable bits and matrix
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    // currently we've been drawing to the back buffer, we need
    // to swap the back buffer with the front one to make the image visible

    tmp.transpose();
    glLoadMatrixd(tmp.getPointer());
    
    //    timeForCurve+=0.005;
    //    if (timeForCurve == 1) {
    //      timeForCurve=0;
    //    }
    //
    //    for (int i = 0; i< 4;i++) {
    //        for (int j = 0 ; j<3; j++) {
    //            float angle = (Points[i][j].x/38+1.0);
    //            if(angle + 2*timeForCurve > 2){
    //                angle = 2*timeForCurve - (2-angle);
    //            }else{
    //                angle  = angle+2*timeForCurve;
    //            }
    //            Points[i][j].y = -38+30 * sinf(angle*PI);
    //        }
    //    }
    glDisable(GL_TEXTURE_2D);

    if(envOn){
        shader->bind();
    }
    else{
        shader->unbind();
    }
    glPushMatrix();
    Matrix4 tmp1 = cameraMatrix.getCameraMatrix();
    Matrix4 translation = Matrix4();
    translation.makeTranslate(0, 5, 1);
    translation = tmp1 * model2world * translation;
    translation.transpose();
    glLoadMatrixd(translation.getPointer());
    glDisable(GL_LIGHTING);
    glutSolidSphere(0.25, 20, 20);
    // Enable lightinge
    //GLfloat whiteMaterial[]={1.0f, 1.0f, 1.0f, 1.0f};
    //GLfloat DiffuseLight[] = {0.2, 2, 1}; //set DiffuseLight
    //glLightfv (GL_LIGHT0, GL_DIFFUSE, DiffuseLight); //change the light accordingly
    GLfloat LightPosition[] = {0, 5, 1, 0}; //set the LightPosition to the specified values
    glLightfv (GL_LIGHT0, GL_POSITION, LightPosition); //change the light accordingly
    //glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, whiteMaterial);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glPopMatrix();
    
    
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glmatrix = cameraMatrix.getCameraMatrix();
    //tmp = glmatrix * model2world;
    tmp.transpose();
    glLoadMatrixd(tmp.getPointer());
    glBegin(GL_QUADS);
    glColor3f(1, 0, 0);
    // use the parametric time value 0 to 1
    for(int j=0;j!=LOD-1;++j) {// calculate the parametric u value
        // calculate the parametric v value
        float v = (float)j/(LOD-1);
        float v1 = (float)(j+1)/(LOD-1);
        
        for (int i=0;i!=LOD-1;++i){
            float u = (float)i/(LOD-1);
            float u1 = (float)(i+1)/(LOD-1);
            
            // calculate the point on the surface
            Point p =  Calculate(u1,v);
            Point p1 = Calculate(u1,v1);
            Point p2 = Calculate(u,v1);
            Point p3 = Calculate(u,v);
            
            //glColor3f(0.8,0.5,1);
            Vector3 n = calculateNormal(u1, v);
            glNormal3f(n.x, n.y, n.z);
            glVertex3f(p.x,p.y,p.z);
            
            n = calculateNormal(u1,v1);
            glNormal3f(n.x, n.y, n.z);
            glVertex3f(p1.x,p1.y,p1.z);
            
            n = calculateNormal(u,v1);
            glNormal3f(n.x, n.y, n.z);
            glVertex3f(p2.x,p2.y,p2.z);
            
            n = calculateNormal(u,v);
            glNormal3f(n.x, n.y, n.z);
            glVertex3f(p3.x,p3.y,p3.z);
        }
    }
    glEnd();
    glPopMatrix();


    
    
    glutSwapBuffers();
    
    //solve for the first tangent approximation
}

//------------------------------------------------------------	OnInit()
//
void OnInit() {
    timeForCurve = 0;
    model2world.identity();
    cameraMatrix.set();//will set the camera matrix on default setting
}

//------------------------------------------------------------	OnExit()
//
void OnExit() {
}

//------------------------------------------------------------	OnKeyPress()
//

void idleCallback()
{
    for (int i = 0; i< 4;i++) {
        for (int j = 0 ; j<4; j++) {
            cout << Points[i][j].x << " " << Points[i][j].y << " " << Points[i][j].z << endl;
        }
    }
  OnDraw(); //called when window redraw is needed
}

void OnKeyPress(unsigned char key,int,int) {
    switch(key) {
        // increase the LOD
        case '+':{
            ++LOD;
            break;
        }
        // decrease the LOD
        case '-':{
            --LOD;
            
        // have a minimum LOD value
        if (LOD<3)
            LOD=3;
            break;
        }
        //move the camera eye x down
        case 'x':{
            cameraMatrix.xDown();
            break;
        }
        //move the camera eye x up
        case 'X':{
            cameraMatrix.xUp();
            break;
        }
        //move the camera eye y down
        case 'y':{
            cameraMatrix.yDown();
            break;
        }
        //move the camera eye y up
        case 'Y':{
            cameraMatrix.yUp();
            break;
        }
        //move the camera eye z down
        case 'z':{
            cameraMatrix.zDown();
            break;
        }
        //move the camera eye z up
        case 'Z':{
            cameraMatrix.zUp();
            break;
        }
        //rotate the camera
        case 'r':{
            Matrix4 rotation = Matrix4();
            rotation.identity();
            rotation.makeRotateY(10);
            Vector4 r = Vector4(cameraMatrix.center_e->x, cameraMatrix.center_e->y, cameraMatrix.center_e->z,0);
            r = rotation * r;
            cameraMatrix.center_e->x = r.x;
            cameraMatrix.center_e->y = r.y;
            cameraMatrix.center_e->z = r.z;
            cameraMatrix.set();
        
            break;
        }
        //rotate the camera
        case 'R':{
            Matrix4 rotation = Matrix4();
            rotation.identity();
            rotation.makeRotateY(-10);
            Vector4 r = Vector4(cameraMatrix.center_e->x, cameraMatrix.center_e->y, cameraMatrix.center_e->z,0);
            r = rotation * r;
            cameraMatrix.center_e->x = r.x;
            cameraMatrix.center_e->y = r.y;
            cameraMatrix.center_e->z = r.z;
            cameraMatrix.set();
            break;
        }
        //turn enviornment on/off
        case 'e':{
            envOn = !envOn;
            break;
        }
        case 27:{
            exit(0);
        }
        default:
            break;
    }
    
    // ask glut to redraw the screen for us...
    glutPostRedisplay();
}

//------------------------------------------------------------	main()
//
int main(int argc,char** argv) {
    
    // initialise glut
    glutInit(&argc,argv);
    
    // request a depth buffer, RGBA display mode, and we want double buffering
    glutInitDisplayMode(GLUT_DEPTH|GLUT_RGBA|GLUT_DOUBLE);
    
    // set the initial window size
    glutInitWindowSize(640,480);
    
    // create the window
    glutCreateWindow("CSE 167 HW6 ");
    
    LoadGLTextures();
    
    // set the function to use to draw our scene
    glutDisplayFunc(OnDraw);
    
    // set the function to handle changes in screen size
    glutReshapeFunc(OnReshape);
    
    // set the function for the key presses
    glutKeyboardFunc(OnKeyPress);
    glutIdleFunc(idleCallback);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    
    glEnable(GL_COLOR_MATERIAL);
    
    glEnable(GL_NORMALIZE);
    
    
    faces.push_back("/Users/margaretwm3/Desktop/CSE167_HWs/CSE167HW6/PalldioPalace_extern_right.jpg");
    faces.push_back("/Users/margaretwm3/Desktop/CSE167_HWs/CSE167HW6/PalldioPalace_extern_left.jpg");
    faces.push_back("/Users/margaretwm3/Desktop/CSE167_HWs/CSE167HW6/PalldioPalace_extern_top.jpg");
    faces.push_back("/Users/margaretwm3/Desktop/CSE167_HWs/CSE167HW6/PalldioPalace_extern_back.jpg");
    faces.push_back("/Users/margaretwm3/Desktop/CSE167_HWs/CSE167HW6/PalldioPalace_extern_front.jpg");
    shader = new Shader("/Users/margaretwm3/Desktop/CSE167_HWs/CSE167HW6/sky.vs",
                        
                        "/Users/margaretwm3/Desktop/CSE167_HWs/CSE167HW6/sky.fs",true);
    GLuint textureCube = loadCubemap(faces);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureCube);
    // run our custom initialisation
    OnInit();
    // set the function to be called when we exit
    atexit(OnExit);
    // this function runs a while loop to keep the program running.
    glutMainLoop();
    return 0;
}
