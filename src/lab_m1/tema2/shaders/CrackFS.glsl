#version 330

in vec3 frag_color;
in vec3 frag_pos;

out vec4 out_color;

uniform float crack_amount;  // 0 = no crack, 1 = full crack

// Simple pseudo-random function
float hash(vec2 p) {
    return fract(sin(dot(p, vec2(127.1, 311.7))) * 43758.5453);
}

void main()
{
    vec3 base = frag_color;

    // Add dark lines/cracks based on position
    float noise = hash(frag_pos.xz * 20.0);
    float crackLine = step(0.85, noise);  // creates random dark spots

    // Darken where cracks appear
    vec3 finalColor = base * (1.0 - crackLine * crack_amount * 0.6);

    out_color = vec4(finalColor, 1.0);
}
