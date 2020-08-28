#version 150
#define PI                          3.14159265358979323846
#define BLUR                        1.0
#define erase(scene, mask) 			scene * (1. - mask)
#define add(scene, object, color)	erase(scene,object) + object*color

// Available modes: 1-2
#define MODE                        1

in vec4 vposition;
out vec4 fcolor;

uniform sampler2DRect tex0;
uniform float time;
uniform float width;
uniform float height;

struct LayerParameters
{
    vec2 center;
    float radius;
    int numCircles;
};

struct CircleParameters
{
    float t0;
    float speed;
    vec2 center;
    float radius;
    vec3 color;
};

// Functions to define the scene: the scene shows circles moving around circular layers
LayerParameters addLayer(int i);
CircleParameters addCircle(int k, int i, LayerParameters layerParams, vec2 p);

// Primitive distance functions
float dCircle(vec2 p, vec2 c, float r);

// Physical 2D movements
vec2 mcu(       // (movimiento circular uniforme)
    vec2 x0,    // initial movement position
    float r,    // movement radius
    float theta,// movement angle speed (radians)
    float t0    // initial movement time
);

void main()
{
    // Get the current pixel position
    vec2 p = vposition.xy;

    // Define the scene
    vec3 scene;     // color representing the scene
    vec3 bgColor;   // background color of the scene
    int numLayers;  // number of layers

    if(MODE == 1)
    {
        bgColor = vec3(0.05);
        numLayers = 20;
    }

    else if(MODE == 2)
    {
        bgColor = vec3(0.9);
        numLayers = 20;
    }

    else
    {
        bgColor = vec3(1.);
        numLayers = 1;
    }

    // Init the scene
    scene = add(scene, bgColor - scene, 0);

     // Define circles for each layer
    for(int i = 0; i < numLayers; i++)
    {
        LayerParameters layerParams = addLayer(i);

        for(int k = 0; k < layerParams.numCircles; k++)
        {
            CircleParameters circleParams = addCircle(k, i, layerParams, p);
            float circle = dCircle(p, circleParams.center, circleParams.radius);
            scene = add(scene, circle, circleParams.color);
        }
    }

    // Set the pixel color
    fcolor = vec4(scene, 1.0);
}

// Functions to define the scene
LayerParameters addLayer(int i)
{
    LayerParameters params;

    if(MODE == 1)
    {
        params.center = vec2(width/2, height/2);
        params.radius = 12*i;
        params.numCircles = 5*i + 1;
    }

    else if(MODE == 2)
    {
        params.center = vec2(width/2, height/2);
        params.radius = 15*i;
        params.numCircles = 10*i + 1;
    }

    else
    {
        params.center = vec2(width/2, height/2);
        params.radius = 100;
        params.numCircles = 1;
    }

    return params;
}

CircleParameters addCircle(int k, int i, LayerParameters layerParams, vec2 p)
{
    CircleParameters params;

    if(MODE == 1)
    {
        float theta = 2.;
        float speedFactor = 0.1;
        params.speed = speedFactor * theta;
        if(i % 2 == 0)
            params.speed *= -1.;
        params.t0 = (PI * k) / (speedFactor * layerParams.numCircles);
        params.center = mcu(layerParams.center, layerParams.radius, params.speed, params.t0);
        params.radius = 5;
        vec4 col0 = texture(tex0, params.center);
        vec4 col1 = texture(tex0, p.yx*1.5);
        params.color = mix(col0.bgr, col1.gbr - vec3(.2), 0.5);
    }

    else if(MODE == 2)
    {
        params.speed = -radians(10.);
        params.t0 = radians(10.0 * layerParams.numCircles / (k + 1));
        params.center = mcu(layerParams.center, layerParams.radius, params.speed, params.t0);
        params.radius = 5;
        params.color = texture(tex0, params.center).rgb;
    }

    else
    {
        params.speed = 0.;
        params.t0 = 0.;
        params.center = layerParams.center;
        params.radius = 5;
        params.color = vec3(0.);
    }

    return params;
}

// Primitive distance functions
float dCircle(vec2 p, vec2 c, float r)
{
    float d = length(c - p);
    return smoothstep(r+BLUR, r, d);
}

// Physical 2D movements
vec2 mcu(vec2 x0, float r, float theta, float t0)
{
    vec2 x;
    float t = time;

    x = vec2(r*cos(theta*(t+t0)), r*sin(theta*(t+t0))) + x0;
    return x;
}
