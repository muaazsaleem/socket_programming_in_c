Lab 1: Non-blocking Socket Programming
 

This lab basically aims to refresh your socket programming skills and introduce you to a slightly different socket programming technique.
I assume you are already quite familiar with socket programming in C/C++ and Java. But the typical way of socket programming using 
synchronous/blocking system calls such as read() and accept() does not work so well in distributed systems. In particular, it reduces the
performance of the system because the system is often blocked waiting for data to arrive on a socket, not doing any useful work.

In this lab, you are required to convert some C/C++ code that uses blocking system calls into non-blocking code. You are provided simple 
client-server code that uses read() and accept(). You are required to use a system call called select() to make read() and accept() non-blocking.
Basically, select() allows you to quickly check if some data is available to be read on a socket. Instead of blocking until data arrives on a socket,
you can run select() in a tight loop repeatedly checking if there is some data to be read. If yes, the program should read in the data using read().
If not, the program can go ahead and do something else, and call select() again later.

The starter code that you need to change is available at: http://www.linuxhowtos.org/data/6/server.c and http://www.linuxhowtos.org/data/6/client.c.
You should download this code into a directory and compile it using gcc or g++ as follows:

g++ –o server server.c

g++ –o client client.c

Your job is to modify this code so that it uses select() to check if data is available to read on a socket or a connection is available to accept.
It should then call read() or accept() only if the answer is yes. The man page of select is really useful and even has some useful sample code; you
can find it by just typing ‘man select’ on the command line or by going to: http://linux.die.net/man/2/select. The solution doesn’t require more than
30-40 lines of code. Most of this code is just a variation of the sample code on the man page. After you have made your changes, your program should 
have exactly the same output as it did before.

You can do this lab in pairs or individually. However, every student must submit his/her code on LMS.

Notes:- 
	struct sockaddr_in
	{
	  short   sin_family; /* must be AF_INET */
	  u_short sin_port;
	  struct  in_addr sin_addr;
	  char    sin_zero[8]; /* Not used, must be zero */
	};

	struct in_addr
	{
		unsigned long s_addr
	}

	struct  hostent
	{
	  char    *h_name;        /* official name of host */
	  char    **h_aliases;    /* alias list */
	  int     h_addrtype;     /* host address type */
	  int     h_length;       /* length of address */
	  char    **h_addr_list;  /* list of addresses from name server */
	  #define h_addr  h_addr_list[0]  /* address, for backward compatiblity */
	};