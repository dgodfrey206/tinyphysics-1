/* This is a vertex shader 
   It is called before the fragment shader is invoked.
   It is a texture level shader and called for each vertex of the texture.
 */

//Attributes are given by OpenGL and cannot be modified
//attribute vec4 a_color;             //pixel color (RGB + alpha)
//attribute vec3 a_position;          //pixel position x, y, z
//attribute vec2 a_texCoord0;         //pixel coordinate in texture x, y

//Uniform are variables shared between calling program and vertex shader
//They are not shared with fragment shader.
//uniform

//Varying are internal variables to the shader. They are shared between vertex
//and fragment shader.
//varying vec4 v_color;               //pixel color (RBG + alpha) (can be modified)
//varying vec2 v_texCoord0;           //pixel coordinate in texture x, y

void main()
{
    ////We simply pass variables to the fragment shader
    //v_color = a_color;
    //v_texCoord0 = a_texCoord0;
    ////GL_position is a built-in variable (vec3)
    ////As it's a vec4 (homogeneous coordinates, we need to convert a_position to
    ////a 4D vector
    //gl_Position = gl_ModelViewProjectionMatrix * vec4(a_position, 1.0);
    // transform the vertex position
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;

    // transform the texture coordinates
    gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;

    // forward the vertex color
    gl_FrontColor = gl_Color;
}
