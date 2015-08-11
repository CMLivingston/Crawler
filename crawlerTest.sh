#!/bin/bash
#
# file: crawlerTest.sh
# author: Chris Livingston
#
# This script compiles and runs a test the crawler and logs the processes in a logfile. 


logFile=crawlerTestingLog.`date +"%a_%b_%d_%T_%Y"`

make 



# case 1: invalid seed page
crawler badName data/ 2 &>> $logFile
echo "" >> $logFile
 
# case 2: bad directory
crawler http://old-www.cs.dartmouth.edu/~cs50/tse/ badDir 2 &>> $logFile  
echo "" >> $logFile

# case 3: exceeds max depth of 4
crawler http://old-www.cs.dartmouth.edu/~cs50/tse/ ./data 5 &>> $logFile 
echo "" >> $logFile

# case 4: no arguments or too few arguments
crawler http://old-www.cs.dartmouth.edu/~cs50/tse/ &>> $logFile 
echo "" >> $logFile

# case 5: Too many arguments
crawler http://old-www.cs.dartmouth.edu/~cs50/tse/ 4 anArg fsd &>> $logFile 
echo "" >> $logFile

# case 6: directory not writable
a=unWritable
mkdir dir
chmod -w dir

crawler http://old-www.cs.dartmouth.edu/~cs50/tse/ $d 2 &>> $logFile 
echo "" >> $logFile

rmdir dir

#case 7: Working program for MaxDepth of 1
crawler http://old-www.cs.dartmouth.edu/~cs50/tse/ ./data 1 &>> $logFile
echo "" >> $logFile



exit 1











