#ifdef GL_ES
precision lowp float;
#endif

uniform vec4 u_color;
varying vec2 v_texCoord;
uniform sampler2D CC_Texture0;

void main()
{
    gl_FragColor = texture2D(CC_Texture0, v_texCoord) * u_color;
    //gl_FragColor = texture2D(CC_Texture0, vec2(v_texCoord.s + u_time.x, v_texCoord.t + u_time.y)); /// does not work on iOS
}
