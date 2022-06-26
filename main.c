#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_INDEX_ROWS 100

struct PageEntry
{
  time_t created_at;
  char *title, *description;
};

struct PageEntry index_entries[MAX_INDEX_ROWS];
int index_len = -1;

void
err_die(const char* msg)
{
  fprintf(stderr, "%s\n", msg);
  exit(1);
}

void
show_help()
{
  printf("Notes Management\n");
  printf("-h\t Show this message\n");
  printf("list\t List stored notes\n");
  printf("show [title]\t Show note with given title\n");
  printf("write [title] [text]\t Write a note with given title\n");
}

void
show_note(int argc, char** argv)
{
  printf("Show_note!\n");
}

void
print_index()
{
  for (int i = 0; i < index_len; i++) {
    printf("%10s %20s %50s\n",
           ctime(&index_entries[i].created_at),
           index_entries[i].title,
           index_entries[i].description);
  }
}
void
show_list()
{
  FILE* index_file = fopen(".index", "r");
  if (index_file == NULL) {
    perror("Could not open index file");
    exit(1);
  }
  int i;
  for (i = 0; i < MAX_INDEX_ROWS; i++) {
    int off = fscanf(index_file,
                     "%ld %ms %ms",
                     &index_entries[i].created_at,
                     &index_entries[i].title,
                     &index_entries[i].description);
    if (off == EOF) {
      perror("Malformed index file");
      fclose(index_file);
      exit(1);
    }
  }
  index_len = i + 1;

  print_index();
  printf("Show_list!\n");
}

void
write_note(int argc, char** argv)
{
  printf("Write_note!\n");
}
int
main(int argc, char** argv)
{
  if (argc < 2) {
    show_help();
    return 0;
  } else if (strcmp(argv[1], "list") == 0) {
    show_list();
  } else if (strcmp(argv[1], "show") == 0) {
    show_note(argc, argv);
  } else if (strcmp(argv[1], "write") == 0) {
    write_note(argc, argv);
  } else {
    show_help();
  }
  return 0;
}
