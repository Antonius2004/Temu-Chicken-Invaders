#version 330

layout(location = 0) in vec3 v_position;
layout(location = 3) in vec3 v_color;  // color is at location 3 in VertexFormat

out vec3 frag_color;
out vec3 frag_pos;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform float crack_amount;  // 0 = no crack, 1 = full crack

// Simple pseudo-random function
float hash(vec2 p) {
    return fract(sin(dot(p, vec2(127.1, 311.7))) * 43758.5453);
}

void main()
{
    vec3 pos = v_position;

    // Create edge deformation based on position
    float edgeFactor = abs(pos.x) + abs(pos.z);  // stronger at edges
    float noise = hash(pos.xz * 10.0) * 2.0 - 1.0;  // random offset -1 to 1

    // Displace vertices slightly (more at edges)
    float displacement = noise * crack_amount * 0.15 * edgeFactor;
    pos.y += displacement;
    pos.x += noise * crack_amount * 0.05;
    pos.z += hash(pos.zx * 10.0) * crack_amount * 0.05;

    frag_color = v_color;
    frag_pos = pos;

    vec4 worldPos = Model * vec4(pos, 1.0);
    gl_Position = Projection * View * worldPos;
}
