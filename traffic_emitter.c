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
 * Abstract: IPv6 server to process client request on dedicated port, pass
 * client a specific data once requested.
 */

#include <stdio.h>

#include <unistd.h>

#include <sys/types.h>

#include <sys/socket.h>

#include <netinet/in.h>

#include "traffic_er.h"

/* Amount of server's read&write interations */
#define V6_ATTEMPTS	5

int main()
{
/* IDs of server sockets, and amount of interations */
int iServerSock, iSock, iCnt = V6_ATTEMPTS;

/* Placeholder for byte being first received, then - sent */
char chSymbol;

/* Placeholder for actual size of client address. */
socklen_t iLen;

struct sockaddr_in6 saddr, caddr;

	/* Let there be a communication endpoint */
	iServerSock = socket(AF_INET6, SOCK_STREAM, 0);

	/* Define IPv6 proto for server */
	saddr.sin6_family=AF_INET6;

	/* Define server to receive packets with no address assigned to interface */
	saddr.sin6_addr=in6addr_any;

	/* Define server port */
	saddr.sin6_port=htons(V6_PORT);

	/* Assign an address to comm. endpoint */
	bind(iServerSock, (struct sockaddr *)&saddr, sizeof(saddr));

	/* Let the comunication endpoint be passively listening for incoming connections */
	listen(iServerSock, 5);

	/* At least one iteraion _will be done */
	do
	{
		/* Self-explanatory */
		printf("Waiting for request on port 0x%04x\n", V6_PORT);

		/* The magic is that this may be altered (to our benefit, by the way) */
		iLen = sizeof(struct sockaddr_in6);

		/* Wait idly for connection request incoming from client */
		iSock = accept(iServerSock, (struct sockaddr *)&caddr, &iLen);


		/* Get a first character of data incoming */
		if( 0 > read(iSock, &chSymbol, 1) )
		{

			/* Can't get? 'Read' operation isn't allright, which is stopper */
			fprintf(stderr, "read() operation failed\n");

			/* Socket is in unknown state */
			return V6_ERROR;
		}

		/* Alter the symbol so the client on _that end of socket will see we've changed it */
		chSymbol++;

		/* Put a symbold into socket - pass it back to a client */
		if(0 > write(iSock, &chSymbol, 1) )
		{
			/* Can't put? 'Write' operation isn't allright, which is stopper */
			fprintf(stderr, "write() operation failed\n");

			/* Socket is in unknown state */
			return V6_ERROR;

		}

		/* No use to keep opened client's socket anymore */
		close(iSock);

	/* Stop if amount of iterations is over. Don't want 'while(1)' here for Ctrl-C exit is not good for opened sockets */
	} while (iCnt--);

	/* Job is done and socket is closed */
	return V6_SUCCESS;

} /* main() of traffic_emitter.c */
