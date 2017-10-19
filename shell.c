#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define interino char *

char origin[256];
char * table;
int history_len = 0;

char ** parse_string(char * s, char * parser) {
  char ** parsed = NULL;
  char * item = strtok(s,parser);
  int numitems = 0;
  while (item) {
    parsed = realloc(parsed,sizeof(char*)*++numitems);
    parsed[numitems-1] = item;
    item = strtok(NULL,parser);
  }
  strtok(parsed[numitems-1], "\n");
  parsed = realloc(parsed,sizeof(char*)*(numitems+1));
  parsed[numitems] = 0;
  return parsed;
}

char * get_nth_donger(int n) {
  FILE * dongerinos = fopen(table, "rb");
  fseek(dongerinos, 0, SEEK_END);
  long dongersize = ftell(dongerinos);
  rewind(dongerinos);
  char * filerino = malloc(dongersize+1);
  fread(filerino, dongersize, 1, dongerinos);
  fclose(dongerinos);
  filerino[dongersize] = 0;
  char ** parsed_dongerinos = parse_string(filerino, "\n");
  return parsed_dongerinos[n];
}
    
char hash() {
  char cwd[256];
  getcwd(cwd, sizeof(cwd));
  char c = 0;
  int i = 0;
  for (;cwd[i];++i) 
    c = c^cwd[i];
  return c;
}


interino main() {
  //char ** history = (char **)malloc(sizeof(char *));
  getcwd(origin, sizeof(origin));
  table = strcat(origin,"/dongers.txt");
  while ("( ‾ʖ̫‾)") {
    char done;
    printf("%s: ",get_nth_donger(hash()));
    char input[256];
    fgets(input,sizeof(input),stdin);
    char ** semicolon_parsed = parse_string(input,";");
    int i = 0;
    
    for (;semicolon_parsed[i];++i) {
      char ** command = parse_string(semicolon_parsed[i]," ");
      //hist = (char **)realloc(hist,256*++history_len);
      //printf("%s",hist[history_len-1]);
      //printf("%d\n",sizeof(input));
      //strncpy(hist[history_len-1], input, 256);
      //int j = 0;
      //for (;j<history_len;++j)
      //printf("j is %d, command |%s|\n",j,history[j]);
      if (command[0][0] == 'c' && command[0][1] == 'd' && ((command[0][2] == ' ' || command[0][2] == '\n') || !command[0][2])) {//check for cd
	if (command[1])
	  chdir(command[1]);
	else {
	  char * home = getenv("HOME");
	  chdir(home);
	}
      }
      done = 0;
      int j = 0;
      char **subcommand = NULL; 
      for (; command[j];j++) {
	if (strchr(command[j],'>') || strchr(command[j],'<')) {
	  subcommand = realloc(subcommand,sizeof(char*)*(j+1));
	  subcommand[j] = NULL;
	  if (command[j+1]) {
	    char * out = command[j+1];
	    done = 1;
	    int f = fork();
	    if (f) {
	      wait();
	    }
	    else {
	      int file;
	      /*printf("%i",strcmp(command[j],">"));
	      if (!strcmp(command[j],">")) {
		printf("%i",strcmp(command[j],">>"));
		if (!strcmp(command[j],">>")) {
		  file = open(out, O_CREAT | O_WRONLY | O_APPEND, 0644);
		  printf("appendout\n");
		}
		else {
		  file = open(out, O_CREAT | O_WRONLY| O_TRUNC, 0644);
		  printf("ovwrtout\n");
		}
		dup2(file, STDOUT_FILENO);
	      }
	      else if (!strcmp(command[j],"<")) {
		if (!strcmp(command[j],"<<")) {
		  file = open(out, O_CREAT | O_WRONLY | O_APPEND, 0644);
		  printf("appendin\n");
		}
		else {
		  file = open(out, O_CREAT | O_WRONLY| O_TRUNC, 0644);
		  printf("ovrwtin\n");
		}
		dup2(file, STDIN_FILENO);
		}*/
	      if (!strcmp(command[j],">>"))
		file = open(out, O_CREAT | O_WRONLY | O_APPEND, 0644);
	      else if (!strcmp(command[j],">"))
		file = open(out, O_CREAT | O_WRONLY| O_TRUNC, 0644);
	      else if (!strcmp(command[j],"<"))
		file = open(out, O_RDWR, 0777);
	      if (strchr(command[j],'>'))
		dup2(file, STDOUT_FILENO);
	      else {
		printf("HIMOM\n");
		dup2(file,STDIN_FILENO);
		close(file);
	      }
	      execvp(subcommand[0],subcommand);
	      return "( ͝° ͜ʖ͡°)つ";
	    } 
	    
	  }
	  else {
	    printf("No filename given");
	  }
	}

	else {
	  subcommand = realloc(subcommand,sizeof(char*)*(j+1));
	  subcommand[j] = command[j];
	}
      }
      if (command[0][0] == 'e' && command[0][1] == 'x' && command[0][2] == 'i' && command[0][3] == 't' && ((command[0][4] == ' ' || command[0][4] == '\n') || !command[0][4])) {//check for exit
	return "[̲̅$̲̅(̲̅ヽ̲̅༼̲̅ຈ̲̅ل͜ຈ̲̅༽̲̅ﾉ̲̅)̲̅$̲̅]"; 
      }
      else if (!done) {
	int f = fork();
	if (f) {
	  wait();
	}
	else {
	  execvp(command[0],command);
	  return "( ͝° ͜ʖ͡°)つ";
	} 
      }
      free(command);
    }
    free(semicolon_parsed);
  }
}
