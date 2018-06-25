#ifdef GL_ES
precision lowp float;
#endif

uniform vec4 u_color;
varying vec2 v_texCoord;
uniform sampler2D CC_Texture0;

/*
void main()
{
    // Convert to grayscale
    vec3 color = texture2D(CC_Texture0, v_texCoord).rgb;
    float gray = (color.r + color.g + color.b) / 3.0;
    vec3 grayscale = vec3(gray);

    gl_FragColor = vec4(grayscale, 1.0);
}
*/
/*
const highp vec3 W = vec3(0.2125, 0.7154, 0.0721);

void main()
{
    float luminance = dot(texture2D(CC_Texture0, v_texCoord).rgb, W);

    gl_FragColor = vec4(vec3(luminance), 1.0);
}
*/

/// Grayscale well implemented but might be optimized?!
void main(void)
{
    gl_FragColor = vec4(vec3(dot(texture2D(CC_Texture0, v_texCoord).rgb, vec3(0.2125, 0.7154, 0.0721))), u_color.a);
}
