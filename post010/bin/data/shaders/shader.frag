#version 150
#define PI                          3.14159265358979323846
#define BLUR                        1.0
#define erase(scene, mask) 			scene * (1. - mask)
#define add(scene, object, color)	erase(scene,object) + object*color

// Available modes: 1-2
#define MODE                        2

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

void main()
{
    // Get the current pixel position
    vec2 p = vposition.xy;

    // Init the scene
    vec3 scene;

    vec3 bgColor = vec3(0.9);
    scene = add(scene, bgColor - scene, 0);

    // Add circular layers of circles moving around
    vec2 cLayers = vec2(width/2, height/2); // center of the circular layers
    int nLayers = 20;                       // number of layers
    float rCircles = 5;                     // radius of the circles moving around
    float theta = 2.;                       // factor to define the speed of the moving circles
    float speedFactor = 0.1;                // factor to define the speed of the moving circles
    float speed = speedFactor * theta;      // speed of the moving circles

    // Define each circular layer
    for(int i = 0; i < nLayers; i++)
    {
        float rLayer = 12*i;    // radius of the current circular layer
        int nCircles = 5*i + 1; // number of circles on the current layer

        if(i % 2 == 0)
            speed = -1. * abs(speed);
        else
            speed *= -1.;

        // Define each moving circle of the current layer
        for(int k=0; k < nCircles; k++)
        {
            // Define different renderings
            float t0;
            vec2 c;
            vec3 color;

            if(MODE == 1)
            {
                t0 = 1./speedFactor*PI*k/nCircles;
                c = mcu(cLayers, rLayer, speed, t0);

                vec4 col0 = texture(tex0, c);
                vec4 col1 = texture(tex0, p.yx*1.5);
                color = mix(col0.bgr, col1.gbr - vec3(.2), 0.5);
            }

            else if(MODE == 2)
            {
                t0 = radians(20.0 * nCircles / (k + 1));
                c = mcu(cLayers, rLayer, -radians(10.), t0);

                color = texture(tex0, c).rgb;
            }

            // Add the current circle to the current layer
            scene = add(scene, dCircle(p, c, rCircles), color);
        }
    }

    // Set the pixel color
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
