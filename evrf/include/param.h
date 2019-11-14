#ifndef PARAM
#define PARAM

class Param
{
private:
    int /*language,*/ label_nbre, label_size;
    char **text;
    char label_filename[255], base_directory[500];
    void label_read(char *filename);

public:
  Param(char *filename);
  ~Param();
  char *get_label(int idx);
  char *get_base_directory();
};

#endif // PARAM

