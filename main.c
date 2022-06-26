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
parse_index()
{
  FILE* index_file = fopen(".index", "r");
  if (index_file == NULL) {
    perror("Could not open index file");
    exit(1);
  }
  int i;
  size_t zero = 0;
  ssize_t nread;
  char* line;
  for (i = 0; i < MAX_INDEX_ROWS; i++) {
    line = NULL;
    if (fscanf(index_file, "%ld\n", &index_entries[i].created_at) == EOF) {
      break;
    }
    if ((nread = getline(&line, &zero, index_file)) != -1) {
      index_entries[i].title = line;
    } else {
      perror("Error parsing index file");
      exit(1);
    }
    line = NULL;
    if ((nread = getline(&line, &zero, index_file)) != -1) {
      index_entries[i].description = line;
    } else {
      break;
    }
  }
  index_len = i;
}
void
show_list()
{
  parse_index();
  print_index();
}

void
write_note(int argc, char** argv)
{
  FILE* index_file = fopen(".index", "a");
  struct PageEntry new_entry;
  new_entry.title = argv[2];
  new_entry.description = argv[3];
  new_entry.created_at = time(NULL);
  fprintf(index_file,
          "%ld\n%s\n%s\n",
          new_entry.created_at,
          new_entry.title,
          new_entry.description);
  fclose(index_file);
  printf("Write_note!\n");
}
void
show_note(int argc, char** argv)
{
  parse_index();
  size_t title_len = strlen(argv[2]);
  for (int i = 0; i < index_len; i++) {
    if (strncmp(index_entries[i].title, argv[2], title_len) == 0) {
      printf("%s\n%s", index_entries[i].title, index_entries[i].description);
    }
  }
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
