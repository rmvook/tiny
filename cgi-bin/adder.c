/*
 * adder.c - a minimal CGI program that adds two numbers together
 */
/* $begin adder */
#include <limits.h>
#include "csapp.h"

int main(void) {
	char *buf, *p;
	char arg1[MAXLINE], arg2[MAXLINE], content[MAXLINE];
	int n1 = 0, n2 = 0, sum = 0;

	/* Extract the two arguments */
	if ((buf = getenv("QUERY_STRING")) != NULL) {
		p = strchr(buf, '&');
		*p = '\0';
		//convert these into strncpy... Max out the lengh so it does not bring in things that are not numbers.
		//strncpy(arg1, buf, sizeof(buf));
		strcpy(arg1, buf);
		strcpy(arg2, p + 1);
		n1 = atoi(arg1);
		n2 = atoi(arg2);
	}

	if ((n1 > 0 && n2 > INT_MAX - n1) ||
	        (n1 < 0 && n2 < INT_MIN - n1)) {
		n1 = 0;
		n2 = 0;
	} else {
		sum = n1 + n2;
	}


	/* Make the response body */
	sprintf(content, "Welcome to add.com: THE Internet addition portal.\r\n<p>The answer is: %d + %d = %d\r\n<p>Thanks for visiting!\r\n", n1, n2, sum);

	// sprintf(content, "%sTHE Internet addition portal.\r\n<p>", content);
	// sprintf(content, "%sThe answer is: %d + %d = %d\r\n<p>", content, n1, n2, sum);
	// sprintf(content, "%sThanks for visiting!\r\n", content);

	/* Generate the HTTP response */
	printf("Content-length: %d\r\n", (int) strlen(content));
	printf("Content-type: text/html\r\n\r\n");
	printf("%s", content);
	fflush(stdout);
	exit(0);
}
/* $end adder */
