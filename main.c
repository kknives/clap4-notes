#include <stdio.h>
#include <string.h>
#include <time.h>

void
show_help()
{
  printf("Notes Management\n");
  printf("-h\t Show this message\n");
  printf("list\t List stored notes\n");
  printf("show [title]\t Show note with given title\n");
}

struct PageEntry
{
  time_t created_at;
  char *title, *description;
};

void
show_list()
{
  FILE* index_file = fopen(".index", "r");
  for (int i = 0; i < MAX_INDEX_ROWS; i++) {
    int off = fscanf(index_file,
                     "%ld %ms %ms",
                     &index_entries[i].created_at,
                     &index_entries[i].title,
                     &index_entries[i].description);
  }

  printf("Show_list!\n");
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
