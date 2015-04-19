#version 120
attribute vec2 inPosition;
attribute vec2 inTexCoords;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projMatrix;
void
main ()
{
  gl_Position = vec4 (inPosition, 0.0, 1.0);
  gl_position = modelMatrix * gl_position;
  gl_position = viewMatrix * gl_position;
  gl_position = projMatrix * gl_position;
  gl_TexCoord[0] = vec4 (inTexCoords, 0, 0);
}
