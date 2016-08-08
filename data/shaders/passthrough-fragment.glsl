/* This is a fragment shader. 
 * This is a pixel-level shader invoked after the vertex shader.
 * http://www.geeks3d.com/shader-library/
 */

//Built-in uniform to sample pixel in from texture
uniform sampler2D texture;

//Varying are internal variables to the shader. They are shared between vertex
//and fragment shader.
//varying vec4 v_color;               //pixel color (RBG + alpha) (can be modified)
//varying vec2 v_texCoord0;           //pixel coordinate in texture x, y

void main()
{
    //gl_FragColor is a built-in variable for output color for pixel    
    //gl_FragColor = texture2D(u_sampler2D, v_texCoord0) * v_color;
    //gl_FragColor = vec4(1.0, 0., 0., 1.);
    // lookup the pixel in the texture
    vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);

    // multiply it by the color
    gl_FragColor = gl_Color * pixel;
    //gl_FragColor = vec4(1., 0., 0., 1.);
}