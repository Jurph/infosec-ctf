/*
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int goodfunction();  
int hackedfunction(); // initialized next to each other.
  
int vuln(const char *format){
        char buffer[128];   																		// 0x0804862b
        int (*ptrf)(); 																				

        memset(buffer, 0, sizeof(buffer));													// 0x0804862f
        printf("goodfunction() = %p\n", goodfunction);								// 0x08048641
        printf("hackedfunction() = %p\n\n", hackedfunction);						// 0x08048653

        ptrf = goodfunction;																	// 0x0804865b
        printf("before : ptrf() = %p (%p)\n", ptrf, &ptrf);								// 0x08048678

        printf("I guess you want to come to the hackedfunction...\n");		// 0x08048490 - why does this get "puts()" instead of printf as expected?
        sleep(2);																					// 0x08048470 - TODO: see if sleep() responds badly to weird input.
        ptrf = goodfunction;																	// 0x08048697

        snprintf(buffer, sizeof buffer, format);											// 0x080486ad

        return ptrf();																				// 0x080486be
}

int main(int argc, char **argv){
        if (argc <= 1){
                fprintf(stderr, "Usage: %s <buffer>\n", argv[0]);
                exit(-1);
        }
        exit(vuln(argv[1]));  																		// 0x080486f1 - wait, what?! We're exiting the whole time vuln() is running? 
}																										// 	TODO: consider pointer implications.

int goodfunction(){
        printf("Welcome to the goodfunction, but i said the Hackedfunction..\n");
        fflush(stdout);																			// 0x08048715

        return 0;
}

int hackedfunction(){																			// 0x08048724
        printf("Way to go!!!!");																	// 0x0804872d
	    fflush(stdout);																			// 0x0804873b
        setreuid(geteuid(),geteuid());														// 0x08048743 
        system("/bin/sh");																		// 0x0804875e

        return 0;
}
