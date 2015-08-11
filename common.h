/* ================================================================= */
/* File: common.h
 *
 * Project name: CS50 Tiny Search Engine
 * Component name: Crawler
 *
 * This file contains the common defines and data structures.
 *
 */
/* ========================================================================== */
#ifndef COMMON_H
#define COMMON_H

// ---------------- Prerequisites e.g., Requires "math.h"
#include <stddef.h>                         // size_t


// ---------------- Constants
#define INTERVAL_PER_FETCH 1                 // seconds between fetches

#define MAX_DEPTH 4                          // don't want to go too far do

// limit crawling to only this domain
#define URL_PREFIX "http://old-www.cs.dartmouth.edu/~cs50/tse"

 // // Maximum number of times to try to fetch a webpage
#define MAX_TRY  3

// ---------------- Structures/Types

typedef struct WebPage {
    char *url;                               // url of the page
    char *html;                              // html code of the page
    size_t html_len;                         // length of html code
    int depth;                               // depth of crawl
} WebPage;


/*
 *  * GetWebPage - curl page->url, store into page->html
 *   * @page: the webpage struct containing the url to curl
 *    *
 *     * Returns 1 if the curl was successful; otherwise, 0. If the curl succeeded,
 *      * then page->html will contain the content retrieved. The WebPage struct should
 *       * have been allocated by the caller, but the page->html pointer is expected to
 *        * be NULL. If this function is successful, a new, null-terminated character
 *         * buffer will be allocated. It is the caller's responsibility to free this
 *          * memory.
 *           *
 *            * Students may find it convenient to modify this function to deal with
 *             * additional libcurl options or crawler functional requirements.
 *              *
 *               * Usage example:
 *                * WebPage* page = calloc(1, sizeof(WebPage));
 *                 * page->url = "http://www.example.com";
 *                  *
 *                   * if(GetWebpage(page)) {
 *                    *     // DO SOMETHING WITH page->html
 *                     * }
 *                      */
int GetWebPage(WebPage *page);

/*
 *  * GetNextURL - returns the next url from html[pos] into result
 *   * @html: pointer to the html buffer
 *    * @pos: current position in html buffer
 *     * @base_url: the base url of the webpage, used to fixup relative links
 *      * @result: a pointer to character pointer, used to pass the url back out
 *       *
 *        * Returns the current position search so far in html; otherwise, returns  0) {
 *         *     // DO SOMETHING WITH THE RESULT
 *          * }
 *           *
 *            */

int GetNextURL(char *html, int pos, char *base_url, char **result);

/* Standard Linux system calls used
 *  *
 *   * free(char *);
 *    * unsigned int sleep(unsigned int seconds);
 *     * void free(void *ptr);
 *      * void *malloc(size_t size);
 *       *
 *        * Make sure you include the correct set of #include files for these sys calls
 *         */




//
//
#endif // COMMON_H