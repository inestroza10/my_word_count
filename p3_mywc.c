/*  Project 3: mywc.c , my own word count code
*/

#include <stdio.h>
#include <ctype.h>

   int  wc();
   int print();
   
   enum {OPT_C = 4, OPT_W = 2, OPT_L = 1};

   int main(int argc,char * argv[])
   {
      int chars = 0;
      int words = 0;
      int lines = 0;
      int nfiles = 0;
      int opt = 0;
      int n;
      int i;
      
      while((++argv)[0] && argv[0][0] == '-'){
	//while there is a char in the second index
         n = 1; //of the first word on command line and the
         while(argv[0][n]){					
	//first char is a '-'
            switch(argv[0][n++]){
               case 'c': opt |= OPT_C;
                  break;
               case 'w': opt |= OPT_W;
                  break;
               case 'l': opt |= OPT_L;
                  break;
               default:
                  fprintf(stderr, "mywc: illegal option -- %c\n", argv[0][n-1]);
                  fprintf(stderr, "usage: mywc [-wlc] [name ...]\n");
                  return -1;
            }
         }
      }
   
      if(!opt)
//if no option selected, select options according to input of command line
         opt = OPT_L | OPT_W | OPT_C;
   
      while(argv[0]){ //while there are file in command line
         ++nfiles; //increase file count
         if(wc(*argv, opt, &chars, &words, &lines) == -1){ //call method wc()
            perror(*argv);
            return 1;
         }
         ++argv;
      }
   
      if(nfiles == 0)
         wc("-", opt, &chars, &words, &lines);
      
      else  if(nfiles > 1)
//if more than one file on com line, calculate total cwl
         print("total", opt, words, chars, lines);
   
      return 0;
   }

   int wc(const char *fname, int opt, int *tot_chars, 
	  int *tot_words, int *tot_lines) {
   
      int char_count = 0;
      int line_count = 0;
      int word_count = 0;
      int inword = 0;
      int c;
      FILE *fp;
   
      if(fname[0] != '-')
         fp = fopen(fname, "r");
      else
         fp = stdin;
   
      if(!fp)//if file not found
         return -1;
   
      while((c = getc(fp)) != EOF) {
	//get next character until EOF character is reached
         ++char_count; 
         if(c == '\n')
            ++line_count;
         if(inword == 0 && !isspace(c)){
	   //if current char is a space and next char is not a space
            ++word_count;				
	    //increase word count and set inword flag to 1
            ++inword;
         }
         else if(inword == 1 && isspace(c))
	   //if current char is not a space and next char is
            --inword;						
	//set inword flag to 0
      }
   
      print(fname, opt, word_count, char_count, line_count);
   
      if(fname[0] != '-')
         fclose(fp);
   
      *tot_chars += char_count;
      *tot_words += word_count;
      *tot_lines += line_count;
   }

   int print(const char *fname, int opt, int words, int chars, int lines) {
      if(opt & OPT_L)//if option -l
         printf("Lines: %d  ", lines);
      if(opt & OPT_W)//if option -w
         printf("Words: %d  ", words);
      if(opt & OPT_C)//if option -c
         printf("Chars: %d  ", chars);
      if(fname[0] != '-')
         printf("File Name: %s", fname);
   
      putchar('\n');
   
      return 0;
   }

