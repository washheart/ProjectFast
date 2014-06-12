varying vec3 vertex_color;
void main()
{
  gl_Position = ftransform();
  //vertex_color = gl_Vertex.xyz; // Example of how to use swizzling.
  vertex_color = vec3(gl_Vertex.y, gl_Vertex.y, 0);
}

