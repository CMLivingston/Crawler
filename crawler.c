/* ========================================================================== */
/* File: crawler.c - Tiny Search Engine web crawler
 *
 * Author: Chris Livingston
 * Date: 2/9/15
 *
 * Input: ./crawler [SEED URL] [TARGET DIRECTORY WHERE TO PUT THE DATA] [MAX CRAWLING DEPTH]
 *
 * Command line options: n/a
 *
 * Output: A file in the target dir for each web page crawled
 *
 * Error Conditions: n/a
 *
 * Special Considerations: n/a
 *
 */
/* ========================================================================== */
// ---------------- Open Issues

// ---------------- System includes e.g., <stdio.h>
#include <stdio.h>                           // printf
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>  
#include <curl/curl.h>

// ---------------- Local includes  e.g., "file.h"
#include "common.h"                          // common functionality
#include "web.h"                             // curl and html functionality
#include "list.h"                            // webpage list functionality
#include "hashtable.h"                       // hashtable functionality


// ---------------- Constant definitions

#define MAX_URL_LEN = 200; // max is 200 chars for a url

// ---------------- Macro definitions
   
static List * URLList;
static HashTable *URLsVisited; 
 int fileNo = 0; // for file count
 int currentDepth = 0;
 int depthLimit; 


// ---------------- Structures/Types

// ---------------- Private variables

// ---------------- Private prototypes
void crawlPage(WebPage * page);
int writeFile(WebPage * page);
int is_dir_writable(char* str);
int strcmp(const char *str1, const char *str2);
int strncmp(const char *str1, const char *str2, size_t n);
size_t strlen(const char *str);
char *strcpy(char *dest, const char *src);
void *malloc(size_t size);
char *strdup (const char *s);
/* ========================================================================== */

int main(int argc, char* argv[])
{

    // check command line arguments
    
    if( argc != 4 )
    {
      fprintf(stderr, "Error: Incorrect number of input arguments.\n Usage: crawler [SEED URL] [TARGET DIRECTORY] [MAX DEPTH]");
      return 1;
    }

  
    if ( is_dir_writable(argv[2]) == 1 )
    {
        fprintf(stderr, "Error: The target directory either doesn't exist or cannot be written to.");
        return 1;
    }
    else{

        int dirstat = chdir(argv[2]);
        if (dirstat == 1){
            fprintf(stderr, "Failed to change into target directory\n");
            return 1;
        }

    }
   
    int i = atoi(argv[3]);
    if( i < 0 || i > 4 )
    {
      fprintf(stderr, "Error: Incorrect crawler depth. Depth must be within range (1 - 4), inclusive.\n");
      return 1;
    }
    else{
        depthLimit = i;
    }

    // init curl
    curl_global_init(CURL_GLOBAL_ALL);

    // allocate resources
    URLsVisited = initTable();
    URLList = (List*) calloc(1,sizeof(List));
    URLList->head = (ListNode*) calloc(1,sizeof(ListNode));
    URLList->tail = (ListNode*) calloc(1,sizeof(ListNode));
    URLList->head = NULL;
    URLList->tail = NULL;


    // setup seed page
    WebPage* seedPage = (WebPage*) calloc(1, sizeof(WebPage));
    seedPage->url = argv[1]; // save url into url member of WebPage

    // get seed webpage
    int status = GetWebPage(seedPage);
    if (status == 0){
        fprintf(stderr, "This is an invalid URL.\n");
        return 1; 
    }

    printf("Please wait...\n");

    // write seed file
     writeFile(seedPage);

    // add seed page to hashtable
    HashTableInsert(URLsVisited, seedPage->url);

    // extract urls from seed page and fill the URL to be visited 
    crawlPage(seedPage);
   
    // while there are urls to crawl (URL to visit list is not empty)
    
    ListNode * node = delete(URLList); 
     
    while( node != NULL ){

        // get webpage for url
        int status = GetWebPage(node->page);
        if (status == 0){
            fprintf(stderr, "This is an invalid URL.\n");
            return 1; 
        }   

        // write page file
        writeFile(node->page);
        
        // extract urls from webpage
        if (node->page->depth < depthLimit){
            
            crawlPage(node->page);

        }
        else if (node->page->depth  > depthLimit) {
             // exceeded limit, we are done. 
        }

        node = delete(URLList); 

    }

    printf("DONE\n");
    
    // cleanup curl
    curl_global_cleanup();

    // free resources
    free(URLsVisited->table);
    free(URLList);
    return 0; 
}

// extracts all urls from a webpage and adds them to URLList and URLS_Visited
void crawlPage(WebPage * page){

   currentDepth++;

   char * new_url = NULL;  
   ListNode *listNode;
   int pos= 0;

   pos = GetNextURL(page->html, pos, page->url, &new_url);

   while (pos != -1){
    
        if(!strncmp(new_url, URL_PREFIX, strlen(URL_PREFIX))){
            if(NormalizeURL(new_url) == 1){
                
                if (HashTableLookup(URLsVisited, new_url) == 1){ // url not in table

                    listNode = newNode();
                   
                    WebPage * thePage = calloc(1,sizeof(WebPage));
                    listNode->page = thePage;
                    listNode->page->url = new_url; // url is null?
                    listNode->next = NULL;
                    listNode->page->depth = currentDepth;


                    add(URLList, listNode->page); // dropped & in front.

                    HashTableInsert(URLsVisited, listNode->page->url); // from orig insert
                    

                }
        
            }
        }
        new_url = NULL; 
        pos = GetNextURL(page->html, pos, page->url, &new_url);
	// sleep(60);
    }

    free(new_url); // cleanup
    free(page); // free current page
    
    
}

// writes the html file to the target directory
int writeFile(WebPage * page){
    
    fileNo++;

    FILE *fp;
    char fname[4];
    char strFileNo[10];
    

    sprintf(strFileNo, "%d", fileNo);
    
    strcpy(fname, strFileNo);

    fp=fopen(fname, "w");
    
    if (fp == NULL)
    {
    printf("Failed to open file %s\n", fname);
    }
  

    // write to the file 
    // url , newline, depth, newline, html on the rest    
    fprintf(fp, "%s\n", page->url);
    fprintf(fp, "%d\n", page->depth);
    fprintf(fp, "%s\n", page->html);

    fclose(fp);

    return 0;

}

// check to see if the directory is writable
int is_dir_writable(char* str) {
    if(access(str, W_OK) == 0) {
        return 0;
    } else {
        return 1;   
    }
}





