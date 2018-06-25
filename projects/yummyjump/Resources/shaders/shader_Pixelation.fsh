/// Pixelation Post Processing Effect
/// TODO pass as parameters the resolution (rt_w/rt_h), offset and pixel size
/// Float and integer must have a `mediump` precision or the shader will not work
/// http://www.geeks3d.com/20101029/shader-library-pixelation-post-processing-effect-glsl/
/// http://coding-experiments.blogspot.com.es/2010/06/pixelation.html

#ifdef GL_ES
precision mediump float;
precision mediump int;
#endif

varying vec4 v_fragmentColor;
varying vec2 v_texCoord;
uniform sampler2D CC_Texture0;

uniform float rt_w; // texture width in pixel
uniform float rt_h; // texture height in pixel
uniform float pixel_w; /// pixelation width in pixel
uniform float pixel_h; /// pixelation height in pixel

void main()
{
    float dx = pixel_w*(1./rt_w);
    float dy = pixel_h*(1./rt_h);

    vec2 coord = vec2(dx*floor(v_texCoord.x/dx), dy*floor(v_texCoord.y/dy));

	gl_FragColor = v_fragmentColor * texture2D(CC_Texture0, coord);
}
