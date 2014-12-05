varying vec3 Normal;
uniform vec3 LightPosition;
//uniform vec3 cameraPosition;

//varying vec3 camera;
varying vec3 Position;

void main () {
    Normal  = gl_NormalMatrix * gl_Normal;
   // camera = cameraPosition;
    Position = vec3(gl_ModelViewProjectionMatrix * gl_Vertex);
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
  }