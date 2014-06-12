varying vec3 vertex_color;
void main()
{
  gl_Position = ftransform();

  float z = gl_Vertex.z * 4 / 3;

  float r, g, b;

  if (z < 1)
  {
    b = 1;
    g = z;
    r = 0;
  }
  else if (z < 2)
  {
    b = 2 - z;
    g = 1;
    r = 0;
  }
  else if (z < 3)
  {
    b = 0;
    g = 1;
    r = z - 2;
  }
  else
  {
    b = 0;
    g = 4 - z;
    r = 1;
  }
  
  vertex_color = vec3(r, g, b);
}

