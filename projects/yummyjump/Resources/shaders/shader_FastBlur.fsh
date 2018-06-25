/// Blur Fragment Shader
/// Needs higher precision than `lowp` for this blur post-processing effects
/// or we'll get bad quality blurring (pixelization)

#ifdef GL_ES
precision highp float;
#endif

varying vec4 v_fragmentColor;
varying vec2 v_texCoord;
uniform sampler2D CC_Texture0;

/// two-pass optmimized Fast Blur. Blur is faster than gaussian blur and quality is acceptable.
/// http://www.sunsetlakesoftware.com/2013/10/21/optimizing-gaussian-blurs-mobile-gpu

varying vec2 blurCoordinates[5];

void main()
{
    // lowp vec4 sum = texture2D(CC_Texture0, blurCoordinates[0]) * 0.204164;
    vec4 sum = texture2D(CC_Texture0, blurCoordinates[0]) * 0.204164;
    sum += texture2D(CC_Texture0, blurCoordinates[1]) * 0.304005;
    sum += texture2D(CC_Texture0, blurCoordinates[2]) * 0.304005;
    sum += texture2D(CC_Texture0, blurCoordinates[3]) * 0.093913;
    sum += texture2D(CC_Texture0, blurCoordinates[4]) * 0.093913;
    gl_FragColor = v_fragmentColor.a * sum;
}

/// Two-pass gaussian blur from http://polycode.org/tutorial/screen_shaders
/// Good blur quality but slower than "Fast Blur" above.
/*
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
*/

/* One passe blur - Very slow
 /// http://open.gl/framebuffers
 const float blurSizeH = 1.0 / 768.0;
 const float blurSizeV = 1.0 / 1024.0;

 void main()
 {
 vec4 sum = vec4(0.0);
 for (float x = -4.0; x <= 4.0; x++)
 for (float y = -4.0; y <= 4.0; y++)
 sum += texture2D(CC_Texture0, vec2(v_texCoord.x + x * blurSizeH, v_texCoord.y + y * blurSizeV)) / 81.0;
 gl_FragColor = v_fragmentColor.a * sum;
 }
 */

/// https://www.shadertoy.com/view/XdfGDH
/// Really SLOW!
/*
float normpdf(in float x, in float sigma)
{
	return 0.39894*exp(-0.5*x*x/(sigma*sigma))/sigma;
}

const vec2 iMouse = vec2(0.0,0.0);
const vec2 iResolution = vec2(1024.0,768.0);


void main(void)
{
	vec3 c = texture2D(CC_Texture0, gl_FragCoord.xy / iResolution.xy).rgb;
	if (gl_FragCoord.x < iMouse.x)
	{
		gl_FragColor = vec4(c, 1.0);
	} else {

		//declare stuff
		const int mSize = 11;
		const int kSize = (mSize-1)/2;
		float kernel[mSize];
		vec3 final_colour = vec3(0.0);

		//create the 1-D kernel
		float sigma = 7.0;
		float Z = 0.0;
		for (int j = 0; j <= kSize; ++j)
		{
			kernel[kSize+j] = kernel[kSize-j] = normpdf(float(j), sigma);
		}

		//get the normalization factor (as the gaussian has been clamped)
		for (int j = 0; j < mSize; ++j)
		{
			Z += kernel[j];
		}

		//read out the texels
		for (int i=-kSize; i <= kSize; ++i)
		{
			for (int j=-kSize; j <= kSize; ++j)
			{
				final_colour += kernel[kSize+j]*kernel[kSize+i]*texture2D(CC_Texture0, (gl_FragCoord.xy+vec2(float(i),float(j))) / iResolution.xy).rgb;

			}
		}


		gl_FragColor = vec4(final_colour/(Z*Z), 1.0);
	}
}
*/

/*
/// Cocos2dx tutorial http://www.cocos2d-x.org/forums/6/topics/53167?r=53805
/// Good blur quality but slow
uniform vec2 pixelSize;
uniform int radius;
uniform float weights[64];
uniform vec2 direction;

void main() {
    gl_FragColor = texture2D(CC_Texture0, v_texCoord)*weights[0];
    for (int i = 1; i < radius; i++) {
        vec2 offset = vec2(float(i)*pixelSize.x*direction.x, float(i)*pixelSize.y*direction.y);
        gl_FragColor += texture2D(CC_Texture0, v_texCoord + offset)*weights[i];
        gl_FragColor += texture2D(CC_Texture0, v_texCoord - offset)*weights[i];
    }
}
*/

/// One-pass gaussian blur
/// Good blur quality but poor performance.
/*
uniform highp float yStep;
uniform highp float xStep;

void main(void) {

    // Grouping texcoord variables in order to make it work in the GMA 950. See post #13
    // in this thread:
    // http://www.idevgames.com/forums/thread-3467.html
    vec2 tc0 = v_texCoord.st + vec2(-xStep, -yStep);
    vec2 tc1 = v_texCoord.st + vec2(         0.0, -yStep);
    vec2 tc2 = v_texCoord.st + vec2(+xStep, -yStep);
    vec2 tc3 = v_texCoord.st + vec2(-xStep,          0.0);
    vec2 tc4 = v_texCoord.st + vec2(         0.0,          0.0);
    vec2 tc5 = v_texCoord.st + vec2(+xStep,          0.0);
    vec2 tc6 = v_texCoord.st + vec2(-xStep, +yStep);
    vec2 tc7 = v_texCoord.st + vec2(         0.0, +yStep);
    vec2 tc8 = v_texCoord.st + vec2(+xStep, +yStep);

    vec4 col0 = texture2D(CC_Texture0, tc0);
    vec4 col1 = texture2D(CC_Texture0, tc1);
    vec4 col2 = texture2D(CC_Texture0, tc2);
    vec4 col3 = texture2D(CC_Texture0, tc3);
    vec4 col4 = texture2D(CC_Texture0, tc4);
    vec4 col5 = texture2D(CC_Texture0, tc5);
    vec4 col6 = texture2D(CC_Texture0, tc6);
    vec4 col7 = texture2D(CC_Texture0, tc7);
    vec4 col8 = texture2D(CC_Texture0, tc8);

    vec4 sum = (1.0 * col0 + 2.0 * col1 + 1.0 * col2 +
                2.0 * col3 + 4.0 * col4 + 2.0 * col5 +
                1.0 * col6 + 2.0 * col7 + 1.0 * col8) / 16.0;
    gl_FragColor = vec4(sum.rgb, v_fragmentColor.a) * v_fragmentColor;
}
*/

// Qt QML Fast Blur. Blur not working.
/*
 varying highp vec2 qt_TexCoord0;
 varying highp vec2 qt_TexCoord1;
 varying highp vec2 qt_TexCoord2;
 varying highp vec2 qt_TexCoord3;

 void main()
 {
 highp vec4 sourceColor = (texture2D(CC_Texture0, qt_TexCoord0) +
 texture2D(CC_Texture0, qt_TexCoord1) +
 texture2D(CC_Texture0, qt_TexCoord2) +
 texture2D(CC_Texture0, qt_TexCoord3)) * 0.25;
 gl_FragColor = sourceColor;
 }
 */

/// http://www.geeks3d.com/20100909/shader-library-gaussian-blur-post-processing-filter-in-glsl/
/* Blur is working correctly (white screen)
const float rt_w = 1024.0; // render target width
const float rt_h = 768.0; // render target height

uniform float offset[3]; //= float[3] ( 0.0, 1.3846153846, 3.2307692308 );
uniform float weight[3]; //= float[3] ( 0.2270270270, 0.3162162162, 0.0702702703 );

void main()
{
    vec2 uv = v_texCoord.xy;
    vec3 tc = texture2D(CC_Texture0, uv).rgb * weight[0];
    for (int i=1; i<3; ++i)
    {
        tc += texture2D(CC_Texture0, uv + vec2(0.0, offset[i])/rt_w).rgb * weight[i];
        tc += texture2D(CC_Texture0, uv - vec2(0.0, offset[i])/rt_h).rgb  * weight[i];
    }
    gl_FragColor = vec4(tc, v_fragmentColor.a);
}
*/

/*
/// Two-passe gaussian blur
/// http://callumhay.blogspot.com.es/2010/09/gaussian-blur-shader-glsl.html
/// Very poor performance. Sigma doesn't seems to work
const float sigma = 6.0;     // The sigma value for the gaussian function: higher value means more blur
// A good value for 9x9 is around 3 to 5
// A good value for 7x7 is around 2.5 to 4
// A good value for 5x5 is around 2 to 3.5
// ... play around with this based on what you need :)

const float blurSize = 5.0 / (1024.0 * 1.05);  // This should usually be equal to
// 1.0 / texture_pixel_width for a horizontal blur, and
// 1.0 / texture_pixel_height for a vertical blur.

const float pi = 3.14159265;

#define VERTICAL_BLUR_5

// The following are all mutually exclusive macros for various
// seperable blurs of varying kernel size
#if defined(VERTICAL_BLUR_9)
const float numBlurPixelsPerSide = 4.0;
const vec2  blurMultiplyVec      = vec2(0.0, 1.0);
#elif defined(HORIZONTAL_BLUR_9)
const float numBlurPixelsPerSide = 4.0;
const vec2  blurMultiplyVec      = vec2(1.0, 0.0);
#elif defined(VERTICAL_BLUR_7)
const float numBlurPixelsPerSide = 3.0;
const vec2  blurMultiplyVec      = vec2(0.0, 1.0);
#elif defined(HORIZONTAL_BLUR_7)
const float numBlurPixelsPerSide = 3.0;
const vec2  blurMultiplyVec      = vec2(1.0, 0.0);
#elif defined(VERTICAL_BLUR_5)
const float numBlurPixelsPerSide = 2.0;
const vec2  blurMultiplyVec      = vec2(0.0, 1.0);
#elif defined(HORIZONTAL_BLUR_5)
const float numBlurPixelsPerSide = 2.0;
const vec2  blurMultiplyVec      = vec2(1.0, 0.0);
#else
// This only exists to get this shader to compile when no macros are defined
const float numBlurPixelsPerSide = 0.0;
const vec2  blurMultiplyVec      = vec2(0.0, 0.0);
#endif

void main()
{
    // Incremental Gaussian Coefficent Calculation (See GPU Gems 3 pp. 877 - 889)
    vec3 incrementalGaussian;
    incrementalGaussian.x = 1.0 / (sqrt(2.0 * pi) * sigma);
    incrementalGaussian.y = exp(-0.5 / (sigma * sigma));
    incrementalGaussian.z = incrementalGaussian.y * incrementalGaussian.y;

    vec4 avgValue = vec4(0.0, 0.0, 0.0, 0.0);
    float coefficientSum = 0.0;

    // Take the central sample first...
    avgValue += texture2D(CC_Texture0, v_texCoord.xy) * incrementalGaussian.x;
    coefficientSum += incrementalGaussian.x;
    incrementalGaussian.xy *= incrementalGaussian.yz;

    // Go through the remaining 8 vertical samples (4 on each side of the center)
    for (float i = 1.0; i <= numBlurPixelsPerSide; i++) {
        avgValue += texture2D(CC_Texture0, v_texCoord.xy - i * blurSize * blurMultiplyVec) * incrementalGaussian.x;
        avgValue += texture2D(CC_Texture0, v_texCoord.xy + i * blurSize * blurMultiplyVec) * incrementalGaussian.x;
        coefficientSum += 2.0 * incrementalGaussian.x;
        incrementalGaussian.xy *= incrementalGaussian.yz;
    }

    gl_FragColor = v_fragmentColor * (avgValue / coefficientSum);
}
*/
