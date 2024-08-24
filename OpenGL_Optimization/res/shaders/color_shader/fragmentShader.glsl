#version 330 core
out vec4 FragColor;

in vec2 t_TexCoord;

uniform sampler2D texture1;
uniform vec4 color;

void main()
{
    vec4 texColor = texture(texture1, t_TexCoord);
    
    // If the texture is transparent, use frameColor, otherwise use texColor
    vec3 finalColor = mix(vec3(color), texColor.rgb, texColor.a);
    
    // Combine with base color
    FragColor = vec4(finalColor, 1.0f);
}
