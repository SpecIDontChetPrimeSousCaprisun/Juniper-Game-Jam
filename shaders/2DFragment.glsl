#version 330 core

in vec2 TexCoord;

out vec4 FragColor;

uniform float alpha;

uniform sampler2D tex;

void main()
{
  vec4 finalColor;

  finalColor = texture(tex, TexCoord);

  FragColor = vec4(finalColor.x, finalColor.y, finalColor.z, alpha);
}
