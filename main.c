#include "trie.h"
#include "edges_nodes.h"
#include "errors.h"
#include "frequency.h"
#include "rest_functions.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>


#include <sys/ioctl.h>
#include <ctype.h>
#include <unistd.h>
#include <termios.h>

#define LINESIZE 128
#define BACKSPACE 0x7f

/*
 * 
 */

int getchar_silent() {
    int ch;
    struct termios oldt, newt;

    /* Retrieve old terminal settings */
    tcgetattr(STDIN_FILENO, &oldt);

    /* Disable canonical input mode, and input character echoing. */
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);

    /* Set new terminal settings */
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    /* Read next character, and then switch to old terminal settings. */
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    return ch;
}

int main(int argv, const char *args[]) {

    int i,j,k,z ;
    int word_no =-1 ;
    int word_length=-1;
    int next,previous;
    int enable =0;
    int isCapital =0;
    FILE * fp;
    char * pPath;
    char * test_str ;
    char ** stringMatrix = NULL;
    char ** stringTestMatrix = NULL ;
    char digit_buffer[8];
    char buffer[64] ;
    char master_buffer[4096];               
    char str[64];
    struct winsize w;
    MotherTreeNode m;
    
    if(argv == 1)
    {
        pPath = getenv("HOME");
        strcat(pPath,"/.dict");
    }
    else
    {
        if(argv != 3)
        {
            printf("Incorrect arguments\n");
            exit(-1);
        }
        else
        {
            if(strcmp(args[1],"-d")!=0)
            {
                printf("Uknown command\n");
                exit(-1);
            }
            else
            {
                pPath = args[2];            //as it is now one needs to enter a valid path (not enviromental variable)
            }
        }
    }
      
    
    
    fp = fopen(pPath, "a+"); 
    if(fp==NULL)
    {
        perror("fopen");
        exit(-1);
    }
    
    initializeMotherTreeNode(&m);

    
    
    memset(str, '\0', 64);                      //Initializing buffers
    memset(digit_buffer, '\0', 8);
    memset(buffer, '\0', 64);
    memset(master_buffer, '\0', 4096);

    while (fscanf(fp, "%s", str) != EOF) {              //Passing dictionary to Trie
        addToMotherTreeNode(&m, str);
        memset(str, '\0', 64);
    }
    //printMotherTreeNode(&m);
    
    i = 0; 
    j=0;
    k=0;
    /* Keep reading one character at a time */
    while ((next = getchar_silent()) != EOF) {
        
        /*check if buffer is full*/
        if(j==4095)             
        {
            printf("\nbuffer is full !");
            exit(-1);
        }
        /* Print normal characters */
        if ( isalpha(next) ) {
            
            if(previous=='\t')                  //case : previous char is a TAB and next one is a letter
            {
                printf("%s",master_buffer);
                enable =0 ;
                previous = '\0' ;
                //deleteStringMatrix(stringMatrix);
                stringMatrix = NULL ;       
            }
            
            putchar(next);
            master_buffer[j] = next ;
            /*Capitals-small*/
            if(next >= 'A' && next <= 'Z')
            {
                next = next +('a'-'A') ;
                isCapital = 1;
            }
            else
            {
                isCapital = 0;
            }
            buffer[i] = next ;
            
            i++;
            j++;
            continue;
        }
        
        if(next == ' ' ||  next == '\n' )
        {
            
            putchar(next);
            
            find(&m ,&stringTestMatrix ,buffer);
            
            if(stringTestMatrix== NULL && buffer[0]!='\0')         //add the word if it doesnt exit at the END of the file
            {
                test_str = malloc((strlen(buffer)+1)*sizeof(char));
                strcpy(test_str,buffer);
                fprintf(fp,"%s\n",test_str);
                free(test_str);
            }
            else
                deleteStringMatrix(stringTestMatrix);
            stringTestMatrix = NULL ;
            
            
            addToMotherTreeNode(&m, buffer);                    //add the word to trie
            i=0 ;
            memset(buffer, '\0', 64);
            master_buffer[j] = next ;
            j++;
            continue;
        }
        
        if( ispunct(next) )
        {
            //Ignore punctuation
            i=0 ;
            memset(buffer, '\0', 64);
            putchar(next);
            master_buffer[j] = next ;
            j++;
            continue;
        }
        
        if( isdigit(next) && enable==1)
        {
            
            digit_buffer[k]=next ;
            k++;
            
            word_no = atoi(digit_buffer);
            
            
            
            if( stringMatrix[word_no-1] == NULL || word_no > N || word_no <=0 )      //fixed
            {
                k=0;
                //enable =0;                      //must press tab again... (if uncommented)
                continue ;
            }
            
            j =j-i;
            i=0;
            memset(buffer, '\0', 64);
            word_length = strlen(stringMatrix[word_no-1]);
            
            for(z=0;z<word_length;z++)
            {
                master_buffer[j]= (stringMatrix[word_no-1])[z];             
                buffer[i]=(stringMatrix[word_no-1])[z];
                i++;
                j++;
            }
            
            printf("%s",master_buffer);
            //stringMatrix = NULL;
            addToMotherTreeNode(&m, buffer);        
            enable =0;
            k=0;
            previous = '\0';
            deleteStringMatrix(stringMatrix);
            stringMatrix = NULL;
            //i=0;                          //edw den prepei na ginei auto giati o xristis mporei na thelei na prosthesei leksi !
            //memset(buffer, '\0', 64);
            continue;
        }
        /* Treat special characters differently */
        switch (next) {
            case '\t': /* Just read a tab */
                /* Get terminal window size */
                ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

                /* Fill next line with asterisks */
               
               
                find(&m ,&stringMatrix ,buffer);                    //find will create strinMatrix ,one that carries most frequent words
                if(stringMatrix == NULL)
                {
                    printf("\n%s",master_buffer);
                    break ;
                }
                
                if(stringMatrix[1]== NULL  && stringMatrix[0]!= NULL )         //stringMatrix has 1 word only
                {
                    j =j-i;
                    i=0;
                    memset(buffer, '\0', 64);
                    word_length = strlen(stringMatrix[0]);

                    for(z=0;z<word_length;z++)
                    {
                        if(isCapital == 1)
                        {
                            if(master_buffer[j] == '\0')
                                master_buffer[j]= toupper((stringMatrix[0])[z]);
                            
                            if(master_buffer[j]>= 'a' && master_buffer[j] <= 'z')       //if small letter
                                master_buffer[j]= (stringMatrix[0])[z];
                            else
                                master_buffer[j]= toupper((stringMatrix[0])[z]);
                        }
                        else
                        {
                            if(master_buffer[j]>= 'A' && master_buffer[j] <= 'Z')       //if capital letter
                                master_buffer[j]= toupper((stringMatrix[0])[z]);
                            else
                                master_buffer[j]= (stringMatrix[0])[z];
                        }
                        j++;
                        buffer[i]=(stringMatrix[0])[z];
                        i++;
                    }

                    printf("\n%s",master_buffer);
                    //free stringMatrix <---------------------------------
                    //stringMatrix = NULL;
                    addToMotherTreeNode(&m, buffer);
                    i=0;
                    memset(buffer, '\0', 64);
                    deleteStringMatrix(stringMatrix);
                    stringMatrix = NULL;
                    break;
                }
                
                printf("\n");               //stringMatrix has more words
                previous =next ;
                for(z=0 ;z<N ;z++)          
                {
                    if((stringMatrix)[z] != NULL)
                        fprintf(stderr,"%s ",(stringMatrix)[z]);            //TAB to stderr
                        //printf("%s ",(stringMatrix)[z]);                  //TAB to stdout
                }
                fprintf(stderr,"\n");
                enable =1 ;                             //allows 1,2,.....,9 to "work"
                
                break;

            case BACKSPACE: /* Just read a backspace */
                /* Move the cursor one step back, print space, and move
                 * cursor back once more to imitate backward character
                 * deletion.
                 */
                printf("\b \b");
                
                if(i>0)  
                {
                    i--;
                    buffer[i]='\0';
                }
                if(j>0) 
                {
                    j--;
                    master_buffer[j]='\0';
                } 
                break;

            case VEOF: /* Just read EOF (Ctrl-D) */
                /* The EOF character is recognized only in canonical input
                 * mode. In noncanonical input mode, all input control
                 * characters such as Ctrl-D are passed to the application
                 * program exactly as typed. Thus, Ctrl-D now produces
                 * this character instead.
                 */
                destroyMotherTree(&m);
                fclose(fp);
                printf("\n\nExiting. Bye...");
                goto THE_END;
            default:
                continue;
        }
    }
THE_END:
    putchar('\n');


   
    return (EXIT_SUCCESS);
}


