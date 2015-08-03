/// Blur Fragment Shader
/// Needs higher precision than `lowp` for this blur post-processing effects
/// or we'll get bad quality blurring (pixelization)
precision highp float;
precision highp int;

varying vec4 v_fragmentColor;
varying highp vec2 v_texCoord;
uniform sampler2D CC_Texture0;

/// Two-pass gaussian blur from http://polycode.org/tutorial/screen_shaders
/// Good blur quality but slower than "Fast Blur" above.
uniform float xStep;
uniform float yStep; /// desired blur / texture width

void main(void)
{
    vec2 vTexCoord = v_texCoord.st;

    /// http://polycode.org/tutorial/screen_shaders
    vec4 sum = texture2D(CC_Texture0, vec2(vTexCoord.x - 4.0 * xStep, vTexCoord.y - 4.0 * yStep)) * 0.05;
    sum += texture2D(CC_Texture0, vec2(vTexCoord.x - 3.0 * xStep, vTexCoord.y - 3.0 * yStep)) * 0.09;
    sum += texture2D(CC_Texture0, vec2(vTexCoord.x - 2.0 * xStep, vTexCoord.y - 2.0 * yStep)) * 0.12;
    sum += texture2D(CC_Texture0, vec2(vTexCoord.x - xStep, vTexCoord.y - yStep)) * 0.15;
    sum += texture2D(CC_Texture0, vec2(vTexCoord.x, vTexCoord.y)) * 0.18;
    sum += texture2D(CC_Texture0, vec2(vTexCoord.x + xStep, vTexCoord.y + yStep)) * 0.15;
    sum += texture2D(CC_Texture0, vec2(vTexCoord.x + 2.0 * xStep, vTexCoord.y + 2.0 * yStep)) * 0.12;
    sum += texture2D(CC_Texture0, vec2(vTexCoord.x + 3.0 * xStep, vTexCoord.y + 3.0 * yStep)) * 0.09;
    sum += texture2D(CC_Texture0, vec2(vTexCoord.x + 4.0 * xStep, vTexCoord.y + 4.0 * yStep)) * 0.05;
    gl_FragColor = v_fragmentColor * sum;
}
