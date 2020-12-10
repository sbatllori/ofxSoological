#version 150

in vec4 vposition;
out vec4 fcolor;

uniform sampler2DRect tex0;


void main()
{
    vec2 p = vposition.xy;
    vec2 uv = vec2(960 - p.x, p.y); // Flip on the X-axis
    vec4 px_color = texture(tex0, uv);

    if(px_color.r >= px_color.g && px_color.r >= px_color.b)
        px_color = vec4(px_color.r, 0, 0, 1);

    else if(px_color.g >= px_color.b)
        px_color = vec4(0, px_color.g, 0, 1);

    else
        px_color = vec4(0, 0, px_color.b, 1);

    fcolor = px_color;
}
