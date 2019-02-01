#pragma once

#define FSE_FALLBACK_BASIC_VERT const std::string vertexData = \
									std::string("#version 330 core\n") + \
									std::string("in vec2 in_position;\n") + \
									std::string("in vec2 in_texCoords;\n") + \
									std::string("out vec2 pass_texCoords;\n") + \
									std::string("uniform VertUniforms { mat4 mvp; float depth; };\n") + \
									std::string("void main() {\n") + \
									std::string("gl_Position = mvp * vec4(in_position, depth, 1.0);\n") + \
									std::string("pass_texCoords = in_texCoords; }")

#define FSE_FALLBACK_BASIC_FRAG const std::string fragmentData = \
									std::string("#version 330 core\n") + \
									std::string("in vec2 pass_texCoords;\n") + \
									std::string("out vec4 out_colour;\n") + \
									std::string("uniform sampler2D uSampler2D;\n") + \
									std::string("void main() {\n") + \
									std::string("vec4 texturedColour = texture(uSampler2D, pass_texCoords); if(texturedColour.a < 0.07f) discard;") + \
									std::string("out_colour = texturedColour; }")