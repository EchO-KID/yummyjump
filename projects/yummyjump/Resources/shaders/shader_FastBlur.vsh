#ifdef GL_ES
precision highp float;
#endif

/// Fast Blur Vertex Shader
attribute vec4 a_position;
attribute vec2 a_texCoord;
attribute vec4 a_color;

varying vec4 v_fragmentColor;
varying vec2 v_texCoord;


/// Optmized Fast Blur. http://www.sunsetlakesoftware.com/2013/10/21/optimizing-gaussian-blurs-mobile-gpu
uniform float xStep; /// blur height / texture height
uniform float yStep; /// blur width / texture width

varying vec2 blurCoordinates[5];

void main()
{
    gl_Position = CC_MVPMatrix * a_position;
    v_fragmentColor = a_color;
    v_texCoord = a_texCoord;

    vec2 singleStepOffset = vec2(xStep, yStep);
    blurCoordinates[0] = v_texCoord.xy;
    blurCoordinates[1] = v_texCoord.xy + singleStepOffset * 1.407333;
    blurCoordinates[2] = v_texCoord.xy - singleStepOffset * 1.407333;
    blurCoordinates[3] = v_texCoord.xy + singleStepOffset * 3.294215;
    blurCoordinates[4] = v_texCoord.xy - singleStepOffset * 3.294215;
}

/// Qt QML Fast Blur
/*
uniform highp float yStep;
uniform highp float xStep;

varying highp vec2 qt_TexCoord0;
varying highp vec2 qt_TexCoord1;
varying highp vec2 qt_TexCoord2;
varying highp vec2 qt_TexCoord3;

void main()
{
    gl_Position = CC_MVPMatrix * a_position;
    v_fragmentColor = a_color;
    v_texCoord = a_texCoord;

    qt_TexCoord0 = vec2(v_texCoord.x + xStep, v_texCoord.y + yStep * 0.36);
    qt_TexCoord1 = vec2(v_texCoord.x + xStep * 0.36, v_texCoord.y - yStep);
    qt_TexCoord2 = vec2(v_texCoord.x - xStep * 0.36, v_texCoord.y + yStep);
    qt_TexCoord3 = vec2(v_texCoord.x - xStep, v_texCoord.y - yStep * 0.36);
}
*/

/*
void main()
{
    gl_Position = CC_MVPMatrix * a_position;
    v_fragmentColor = a_color;
    v_texCoord = a_texCoord;
}
*/