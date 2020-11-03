#version 150
#define PI                          3.14159265358979323846
#define BLUR                        1.0
#define erase(scene, mask) 			scene * (1. - mask)
#define add(scene, object, color)	erase(scene, object) + object * color

// Available modes: 1(dark), 2(bright)
#define MODE                        2

in vec4 vposition;
out vec4 fcolor;

uniform sampler2DRect tex0;
uniform float time;
uniform float width;
uniform float height;

struct Layer
{
    int idx_;
    vec2 center_;
    float radius_;
    int num_particles_;
};

struct Particle
{
    vec2 center_;
    float radius_;
    vec3 color_;
};

Layer AddLayer(int idx);
Particle AddParticle(int idx, Layer layer, vec2 p);
float dCircle(vec2 p, vec2 c, float r);
vec2 UniformCircularMotion(vec2 x0, float r, float theta, float t0);

void main()
{
    // Get the current pixel position
    vec2 p = vposition.xy;

    // Define the scene parameters
    vec3 scene;
    vec3 bg_color= vec3(1.);
    int num_layers = 1;

    if(MODE == 1)
    {
        bg_color = vec3(0.05);
        num_layers = 20;
    }
    else if(MODE == 2)
    {
        bg_color = vec3(0.9);
        num_layers = 20;
    }

    // Init the scene
    scene = add(scene, bg_color - scene, 0);

     // Define the particles for each layer and add them to the scene
    for(int i = 0; i < num_layers; i++)
    {
        Layer layer = AddLayer(i);
        for(int k = 0; k < layer.num_particles_; k++)
        {
            Particle particle = AddParticle(k, layer, p);
            float circle = dCircle(p, particle.center_, particle.radius_);
            scene = add(scene, circle, particle.color_);
        }
    }

    // Set the pixel color
    fcolor = vec4(scene, 1.0);
}

// Functions to define the scene
Layer AddLayer(int idx)
{
    Layer layer;
    layer.idx_ = idx;

    if(MODE == 1)
    {
        layer.center_ = vec2(width / 2, height / 2);
        layer.radius_ = 12 * idx;
        layer.num_particles_ = 5 * idx + 1;
    }
    else if(MODE == 2)
    {
        layer.center_ = vec2(width / 2, height / 2);
        layer.radius_ = 15 * idx;
        layer.num_particles_ = 10 * idx + 1;
    }
    else
    {
        layer.center_ = vec2(width / 2, height / 2);
        layer.radius_ = 100.;
        layer.num_particles_ = 1;
    }

    return layer;
}

Particle AddParticle(int idx, Layer layer, vec2 p)
{
    Particle particle;

    if(MODE == 1)
    {
        // Define the parameters for the uniform circular motion
        // - the motion starts in a different position of the circle,
        // depending on the number of particles on the layer
        // - the moving direction alternates every layer
        float theta = 2.;
        float speed_factor = .1;
        float t0 = (PI * idx) / (speed_factor * layer.num_particles_);
        float speed = speed_factor * theta;
        speed = layer.idx_ % 2 == 0 ? speed : -speed;
        particle.center_ = UniformCircularMotion(layer.center_, layer.radius_, speed, t0);

        // Define the drawing parameters
        particle.radius_ = 5.;
        vec4 col0 = texture(tex0, particle.center_);
        vec4 col1 = texture(tex0, p.yx*1.5);
        particle.color_ = mix(col0.bgr, col1.gbr - vec3(.2), 0.5);
    }
    else if(MODE == 2)
    {
        // Define the parameters for the uniform circular motion
        // - transform the circular motion according to the particle index
        float speed = -radians(10.);
        float t0 = radians(10.0 * layer.num_particles_ / (idx + 1));
        particle.center_ = UniformCircularMotion(layer.center_, layer.radius_, speed, t0);

        // Define the drawing parameters
        particle.radius_ = 5.;
        particle.color_ = texture(tex0, particle.center_).rgb;
    }
    else
    {
        // Default values
        particle.center_ = layer.center_;
        particle.radius_ = 5.;
        particle.color_ = vec3(0.);
    }

    return particle;
}

// Primitive distance functions
float dCircle(vec2 p, vec2 c, float r)
{
    float d = length(c - p);
    return smoothstep(r + BLUR, r, d);
}

// Physical 2D movements
vec2 UniformCircularMotion(
        vec2 x0,        // initial movement position
        float r,        // movement radius
        float theta,    // movement angle speed (radians)
        float t0        // initial movement time
)
{
    vec2 x;
    float t = time;

    x = vec2(r * cos(theta * (t + t0)), r * sin(theta * (t + t0))) + x0;
    return x;
}
