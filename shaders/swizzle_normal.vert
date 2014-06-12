varying vec3 vertex_color;
void main()
{
  gl_Position = ftransform();
  vertex_color = gl_Normal.xyz * gl_Normal.xyz; // Example of how to use swizzling.
}

