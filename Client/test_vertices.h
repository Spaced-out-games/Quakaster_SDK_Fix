#pragma once

// 8 vertices of a cube
std::vector<Vertex> vertices = {
    {{-0.5f, -0.5f, -0.5f}}, // 0: left-bottom-back
    {{ 0.5f, -0.5f, -0.5f}}, // 1: right-bottom-back
    {{ 0.5f,  0.5f, -0.5f}}, // 2: right-top-back
    {{-0.5f,  0.5f, -0.5f}}, // 3: left-top-back
    {{-0.5f, -0.5f,  0.5f}}, // 4: left-bottom-front
    {{ 0.5f, -0.5f,  0.5f}}, // 5: right-bottom-front
    {{ 0.5f,  0.5f,  0.5f}}, // 6: right-top-front
    {{-0.5f,  0.5f,  0.5f}}  // 7: left-top-front
};

// Indices for 12 triangles (2 triangles per cube face)
std::vector <GLuint> indices = {
    // back face
    0, 1, 2,
    2, 3, 0,
    // front face
    4, 5, 6,
    6, 7, 4,
    // left face
    4, 7, 3,
    3, 0, 4,
    // right face
    1, 5, 6,
    6, 2, 1,
    // bottom face
    0, 1, 5,
    5, 4, 0,
    // top face
    3, 2, 6,
    6, 7, 3
};

const char* default_frag =
"#version 330 core\n"
"out vec4 FragColor;\n"
"void main() {\n"
"    FragColor = vec4(1.0, 0.0, 1.0, 1.0);\n"
"}";


const char* default_frag_ideal =
// defines that we'll need to tell the UberShader to add "out vec4 FragColor;" to the header
"#require out vec4 FragColor"
"void main() {\n"
"    FragColor = vec4(1.0, 0.0, 1.0, 1.0);\n"
"}";


const char* default_vert =
"#version 330 core\n"
"uniform mat4 u_Proj;\n"
"uniform mat4 u_View;\n"
"layout(location = 0) in vec3 aPos;\n"
"void main() {\n"
"    gl_Position = u_Proj * u_View * vec4(aPos, 1.0);\n"
"}";

