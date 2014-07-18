#ifndef __PACKET_H
#define __PACKET_H

#define PROTOCOL_VERSION 10
#define MYSQL_SERVER_VERSION "5.1.45"
#define SERVER_VERSION_LENGTH 20
#define SCRAMBLE_LENGTH 20
#define SCRAMBLE_LENGTH_323 8

#define PACKET_HEADER_LEN 4

#define CLIENT_LONG_PASSWORD	1	/* new more secure passwords */
#define CLIENT_FOUND_ROWS	2	/* Found instead of affected rows */
#define CLIENT_LONG_FLAG	4	/* Get all column flags */
#define CLIENT_CONNECT_WITH_DB	8	/* One can specify db on connect */
#define CLIENT_NO_SCHEMA	16	/* Don't allow database.table.column */
#define CLIENT_COMPRESS		32	/* Can use compression protocol */
#define CLIENT_ODBC		64	/* Odbc client */
#define CLIENT_LOCAL_FILES	128	/* Can use LOAD DATA LOCAL */
#define CLIENT_IGNORE_SPACE	256	/* Ignore spaces before '(' */
#define CLIENT_PROTOCOL_41	512	/* New 4.1 protocol */
#define CLIENT_INTERACTIVE	1024	/* This is an interactive client */
#define CLIENT_SSL              2048	/* Switch to SSL after handshake */
#define CLIENT_IGNORE_SIGPIPE   4096    /* IGNORE sigpipes */
#define CLIENT_TRANSACTIONS	8192	/* Client knows about transactions */
#define CLIENT_RESERVED         16384   /* Old flag for 4.1 protocol  */
#define CLIENT_SECURE_CONNECTION 32768  /* New 4.1 authentication */
#define CLIENT_MULTI_STATEMENTS (1UL << 16) /* Enable/disable multi-stmt support */
#define CLIENT_MULTI_RESULTS    (1UL << 17) /* Enable/disable multi-results */

/* Gather all possible capabilites (flags) supported by the server */
#define CLIENT_ALL_FLAGS  (CLIENT_LONG_PASSWORD | \
                           CLIENT_FOUND_ROWS | \
                           CLIENT_LONG_FLAG | \
                           CLIENT_CONNECT_WITH_DB | \
                           CLIENT_NO_SCHEMA | \
                           CLIENT_COMPRESS | \
                           CLIENT_ODBC | \
                           CLIENT_LOCAL_FILES | \
                           CLIENT_IGNORE_SPACE | \
                           CLIENT_PROTOCOL_41 | \
                           CLIENT_INTERACTIVE | \
                           CLIENT_SSL | \
                           CLIENT_IGNORE_SIGPIPE | \
                           CLIENT_TRANSACTIONS | \
                           CLIENT_RESERVED | \
                           CLIENT_SECURE_CONNECTION | \
                           CLIENT_MULTI_STATEMENTS | \
                           CLIENT_MULTI_RESULTS)

/*
  Switch off the flags that are optional and depending on build flags
  If any of the optional flags is supported by the build it will be switched
  on before sending to the client during the connection handshake.
*/
#define CLIENT_BASIC_FLAGS (((CLIENT_ALL_FLAGS & ~CLIENT_SSL) \
                                               & ~CLIENT_COMPRESS)) 
                                               
#define int2store(T,A)  *((char *)(T)) = (char)((A));\
                        *((char *)((T)+1)) = (char)(((A) >> 8));

#define int3store(T,A) *((char *)(T)) = (char)((A));\
                        *((char *)((T)+1)) = (char)(((A) >> 8));\
                        *((char *)((T)+2)) = (char)(((A) >> 16));\

#define int4store(T,A) *((char *)(T)) = (char)((A));\
                        *((char *)((T)+1)) = (char)(((A) >> 8));\
                        *((char *)((T)+2)) = (char)(((A) >> 16));\
                        *((char *)((T)+3)) = (char)(((A) >> 24));

#endif
