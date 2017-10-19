### ᕕ( ᐛ )ᕗ SHELLERINO ᕕ( ᐛ )ᕗ
by Aaron Mortenson, Eric Kolbusz

Features:
  - Forks and executes commands
  - Ignores extra whitespace in input
  - Allows for the input of several commands at once with ;
  - Redirects with <, >, and >>
  - Changes directories
  - Hashes the current directory for a gentle donger learning curve
  - Exits regularly

Attempted:
  - History, which might have eventually led to up arrow shindigs
  - Pipes

Bugs:
  - Certain donger-hating computers may print the current directory hash after the colon, making input seem really faulty and ruining the whole appeal of a 128 donger hash table

Files & Function Headers:
  (shell.c is our only file other than makefile)

- char ** parse_string(char * s, char * parser)
  - returns an array of strings
  - the array is created by repeatedly splitting s on parser
  - all strings in the return array are null-terminated

- char * get_nth_donger(int n)
  - returns the nth donger as a string
  - reads from dongers.txt
  - return string is stripped of newline and null-terminated

- char hash()
  - returns a char which is used as an int by get_nth_donger in main
  - hashes the current working directory to generate the char

- interino main()
  - interino is defined as char * we just wanted to feel special
  1. parses input on ;
  2. for every string in semicolon_parsed:
  3. checks for and executes cd
  4. checks for and executes <, >, and >>
  5. checks for and executes exit
  6. forks and executes the command
