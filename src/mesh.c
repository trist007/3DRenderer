#include "triangle.h"
#include "mesh.h"

extern mesh_t mesh;

void
load_file_mesh_data(const char *filepath)
{
  // NOTE(trist007): so that fileSize is accurate as opposed to \r\n getting translated
  // and changing the byte offsets
  FILE *fp = fopen(filepath, "rb");

  if (!fp)
  {
    fprintf(stderr, "Unable to open file %s", filepath);
    abort();
  }

  size_t fileSize = 0;

  fseek(fp, 0, SEEK_END);
  fileSize = ftell(fp);
  fseek(fp, 0, SEEK_SET);

  char *buf = NULL;
  buf = (char *)malloc(fileSize + 1);
  if (!buf)
  {
    fprintf(stderr, "unable to allocate space for file: %s", filepath);
    abort();
  }

  fread(buf, 1, fileSize, fp);
  buf[fileSize] = '\0';
  fclose(fp);

  parse_obj(buf);
}

void
vectorLine(char *ptr)
{
  vec3_t value = { 0 };

  int matched = sscanf(ptr, "v %f %f %f", &value.x, &value.y, &value.z);

  if (matched == 3) array_push(mesh.vertices, value);
  fprintf(stderr, "added %f %f %f\n", value.x, value.y, value.z);
}

void
faceLine(char *ptr)
{
  face_t value = { 0 };

  int matched = sscanf(ptr, "f %d/%*d/%*d %d/%*d/%*d %d/%*d/%*d", &value.a, &value.b, &value.c);

  if (matched == 3) array_push(mesh.faces, value);
  fprintf(stderr, "added %d %d %d\n", value.a, value.b, value.c);
}

void
parse_obj(char *data)
{
  char      previous_char = 0;
  char     *p             = data;
  bool      isVectorLine  = false;
  bool      isFaceLine    = false;

  while (*(p++) != '\0')
  {
    if (isVectorLine)
    {
      p -= 2;
      vectorLine(p);
      p += 2;
      isVectorLine = false;
    }

    else if (isFaceLine)
    {
      p -= 2;
      faceLine(p);
      p += 2;
      isFaceLine = false;
    }

    else if (*p == '\n')
    {
      previous_char = '\n';
    }
    else if (*p == '\r')
    {
      previous_char = '\r';
    }
    else if (*p == 'v')
    {
      previous_char = 'v';
    }
    else if (*p == 'f')
    {
      previous_char = 'f';
    }
    else if (*p == 'n')
    {
      previous_char = 'n';
    }
    else if (*p == 't')
    {
      previous_char = 't';
    }
    else if (*p == ' ')
    {
      if (previous_char == 'v')
      {
        isVectorLine = true;
      }
      if (previous_char == 'f')
      {
        isFaceLine = true;
      }
      previous_char = ' ';
    }
  }
}
