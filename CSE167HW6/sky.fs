varying vec3 Normal;
uniform samplerCube skybox;
varying vec3 Position;

void main()
{
    vec3 camera = vec3(0.0, 15.0, 15.0);
    vec3 reflection = reflect((Position - camera), normalize(Normal));
    vec3 reflectDirection = normalize(reflect((Position-camera).xyz,normalize(Normal)));
    gl_FragColor = textureCube(skybox, reflectDirection);
}