varying vec3 Normal;
varying vec3 Position;
uniform samplerCube skybox;


void main()
{
    //gl_FragColor = vec4(Normal,1);
    vec3 camera = vec3(0.0, 10.0, 10.0);
    vec3 reflection = reflect((Position - camera), normalize(Normal));
    vec3 reflectDirection = normalize(reflect((Position-camera).xyz,normalize(Normal)));
    gl_FragColor = textureCube(skybox, reflectDirection);
}