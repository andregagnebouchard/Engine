// Version du GLSL
#version 150 core

// Entrée
in vec3 color;

// Sortie 
out vec4 out_Color;

void main()
{
    // Couleur finale du pixel

    out_Color = vec4(color, 1.0);
}
