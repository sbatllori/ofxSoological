#version 150
#define PI                          3.14159265358979323846
#define BLUR                        1.0
#define erase(scene, mask) 			scene * (1. - mask)
#define add(scene, object, color)	erase(scene,object) + object*color

in vec4 vposition;
out vec4 fcolor;

uniform sampler2DRect tex0;
uniform float time;
uniform float width;
uniform float height;

// Primitive distance functions
float dCircle(vec2 p, vec2 c, float r);

// Physical 2D movements
vec2 mcu(       // (movimiento circular uniforme)
    vec2 x0,    // initial movement position
    float r,    // movement radius
    float theta,// movement angle speed (radians)
    float t0    // initial movement time
);

// Colors
vec4 getColorFromTexture(vec2 p);


void main()
{
    // Get the current pixel position
    vec2 p = vposition.xy;

//    vec4 col0 = getColorFromTexture(p);
//    vec4 col1 = getColorFromTexture(p.yx*1.5);
//    vec3 mixedCol = mix(col0.bgr, col1.gbr - vec3(.2), 0.5);

    vec3 scene;

    // Set background color
    vec3 bgColor = vec3(0.9);
    scene = add(scene, bgColor - scene, 0.0);


    // ------------------------------
    // Add circles on circular layers

    // Static parameters
    vec2 cLayers = vec2(width/2, height/2); // centroid

//    scene = add(scene, dCircle(p, mcu(cLayers, 12*20, radians(30.), 0.0), 70), vec3(0.05));
//    scene = add(scene, dCircle(p, mcu(cLayers, 12*20, radians(-30.), 0.0), 40), bgColor);


    int nLayers = 20;
    float rCircles = 5;

    for(int i = 0; i < nLayers; i++)
    {
        float rLayer = 12*i;
        int nCircles = 5*i + 1;

        for(int k=0; k < nCircles; k++)
        {
//            vec2 cCircle;
//            cCircle.x = cLayers.x + rLayer * cos(2*PI*k / nCircles);
//            cCircle.y = cLayers.y + rLayer * sin(2*PI*k / nCircles);

            float speed = 1./16.*radians(30.);
            if(i % 2 == 0)
            {
                speed *= -1;
            }

            float t0_1 = radians(1.0*nCircles/(k+1));
            float t0_2 = 16*3.82*PI*k/nCircles;
            vec2 c = mcu(cLayers, rLayer, speed, t0_2);

            vec4 col0 = getColorFromTexture(c);
            vec4 col1 = getColorFromTexture(p.yx*1.5);
            vec3 mixedCol = mix(col0.bgr, col1.gbr - vec3(.2), 0.5);

            scene = add(scene, dCircle(p, c, rCircles), mixedCol);
        }
    }
    // ------------------------------
    fcolor = vec4(scene, 1.0);
}

// Primitive distance functions
float dCircle(vec2 p, vec2 c, float r)
{
    float d = length(c - p);
    return smoothstep(r+BLUR, r, d);
}

// Physical 2D movements
vec2 mcu(vec2 x0, float r, float theta, float t0=0)
{
    vec2 x;
    float t = time;

    x = vec2(r*cos(theta*(t+t0)), r*sin(theta*(t+t0))) + x0;

    return x;
}

// Colors
vec4 getColorFromTexture(vec2 p)
{
    return texture(tex0, p);
}
