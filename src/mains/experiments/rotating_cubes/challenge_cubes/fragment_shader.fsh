#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

// texture samplers
uniform sampler2D Texture;

void main()
{
    // linearly interpolate between both textures (80% container, 20% awesomeface)
    FragColor = texture(Texture, TexCoord);
}
