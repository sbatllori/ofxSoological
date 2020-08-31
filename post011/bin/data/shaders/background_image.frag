#version 150

in vec4 vposition;
in vec2 vtexcoord;

out vec4 fcolor;

uniform sampler2DRect tex0;
uniform float height;


void main()
{
    // Get the texture coordinates with a flip on the Y-axis
    vec2 uv = vec2(vtexcoord.x, height - vtexcoord.y);

    // Get the pixel color from the texture
    vec3 color = texture(tex0, uv).rgb;

    // Decrease the amount of light of the brightest gray colors
    if(color.r == color.b && color.r == color.g)
        if(color.r > 0.5)
            color -= 0.25;

    // Set the final pixel color
    fcolor = vec4(color, 1.0);

}
