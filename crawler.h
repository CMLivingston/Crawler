/* ========================================================================== */
/* File: crawler.h
 *
 * Project name: CS50 Tiny Search Engine
 * Component name: Crawler
 *
 *
 */
/* ========================================================================== */
#ifndef CRAWLER_H
#define CRAWLER_H

// ---------------- Prerequisites e.g., Requires "math.h"
#include "common.h"                     // common functionality
#include <stdio.h>      				// in/out functionality 
#include <stdlib.h>
// ---------------- Constants

// ---------------- Structures/Types
// ---------------- Public Variables
// ---------------- Prototypes/Macros
void crawlPage(WebPage * page);
int writeFile(WebPage * page);
int is_dir_writable(char* str);

#endif // CRAWLER_H
