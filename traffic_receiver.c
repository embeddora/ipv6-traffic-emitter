/*
 * Copyright (c) 2018 [n/a] info@embeddora.com All rights reserved
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
 * Abstract: IPv6 client to access IPv6 the server on dedicated port, get data
 * from it, analyse the data upon receival, and evaluate connection consistency. 
 */

#include <stdio.h>

#include <unistd.h>

#include <sys/types.h>

#include <sys/socket.h>

#include <netinet/in.h>

#include "traffic_er.h"

int main(int argc, char **argv)
{
int iSocket;

char chSymbol;

struct sockaddr_in6 addr;

	if( 3 != argc )
	{
		/* Self-explanatory. First line - for all, second - for highly experienced professionals only ;-) */
		printf("Usage: %s <IPv6_ADDR> <CHAR>, \tfor instance:\n\t %s %s %s\n", argv[0], argv[0], "::1", "Y");

		return V6_ERROR;
	}

	/* Beware: it returns '0' once failed */
	if( ! inet_pton(AF_INET6, argv[1], &(addr.sin6_addr)))
	{
		/* Self-explanatory */
		printf("Invalid Address\n");

		return V6_ERROR;
	}

	/* Assign value passed via commanline to 'chSymbol' */
	chSymbol=argv[2][0];

	iSocket=socket(AF_INET6, SOCK_STREAM, 0);

	addr.sin6_family=AF_INET6;

	addr.sin6_port=htons(V6_PORT);

	if( 0 > connect(iSocket, (struct sockaddr *)&addr,   sizeof(addr) ) )
	{
		fprintf(stderr, "Connect error\n");

		return V6_ERROR;
	}

	if( 0 > write(iSocket, &chSymbol, 1) )
	{
		fprintf(stderr, "Write error\n");

		return V6_ERROR;
	}

	if( 0 > read(iSocket, &chSymbol, 1) )
	{
		fprintf(stderr, "Read error");

		return V6_ERROR;
	}

	/* Self-explanatory */
	printf("Server sent: %c\n", chSymbol);

	/* If we leave opened socket, next run won't be allright, unless somebedy else closes it for us */
	close(iSocket);

	return V6_SUCCESS;

} /* main() of traffic_receiver.c */