#version 330 core

in vec2 TexCoord;

out vec4 FragColor;

uniform float alpha;
uniform sampler2D tex;
uniform vec3 colorChange;

void main()
{
    vec4 finalColor = texture(tex, TexCoord);

    FragColor = vec4(
        finalColor.rgb + colorChange,
        finalColor.a * alpha
    );
}
