/*
 * Copyright (c) 2017 [n/a] info@embeddora.com All rights reserved
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *        * Redistributions of source code must retain the above copyright
 *          notice, this list of conditions and the following disclaimer.
 *        * Redistributions in binary form must reproduce the above copyright
 *          notice, this list of conditions and the following disclaimer in the
 *          documentation and/or other materials provided with the distribution.
 *        * Neither the name of The Linux Foundation nor
 *          the names of its contributors may be used to endorse or promote
 *          products derived from this software without specific prior written
 *          permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NON-INFRINGEMENT ARE DISCLAIMED.    IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Abstract: colour output check
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//https://stackoverflow.com/questions/5947742/how-to-change-the-output-color-of-echo-in-linux?rq=1
//#include "ansi_color_code.h"

int main( const int argc, const char** const argv )
{

time_t rt;

const char* reset_color = "\033[m";
const char** argv_iter  = argv;
const char*  user_color = argv[ 1 ];
int index_match = -1;

	srand( ( unsigned ) time( &rt ) );

	if( argc < 2 )
	{
		printf( "Usage: [color-name] [some-text] [endl|]\n" );
		return 0;
	}


	for( int index = 0; index < 7 * 8; ++index )
	{
		if( !strcmp( user_color, color_name[ index ] ) )
		{
			index_match = index;
		}
		++argv_iter;
	}

	argv_iter = argv;
	argv_iter += 2;

	if( index_match != -1 )
	{

		if( !strcmp( argv[ argc - 1 ], "endl" ) )
		{

			for( int index = 2; index < argc - 1; ++index )
			{
				printf( "%s%s%s\n",ANCI_color[ ( !strcmp( user_color, "random" ) ? rand() % 56 : index_match ) ], *argv_iter, reset_color );

				++argv_iter;
			}

		}
		else
		{

			for( int index = 1; index < argc - 1; ++index )
			{
				printf( "%s%s %s",ANCI_color[ ( !strcmp( user_color, "random" ) ? rand() % 56 : index_match ) ], *argv_iter, reset_color );
				++argv_iter;
			}

			printf( "\n" );
		}
	}
	else
	{
		printf( "Usage: [color-name] [some-text] [endl|]\n" );
	}

	return 0;
}
