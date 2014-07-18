#include "packet.h"
#include "proxy.h"
#include "util.h"
#include "net.h"


extern proxy_server_t proxy_server;

int send_handshake_packet(proxy_thread_t *thd)
{
   char buff[SERVER_VERSION_LENGTH+1+SCRAMBLE_LENGTH+25];
   char *end = buff;
   long server_capabilites = CLIENT_BASIC_FLAGS;

   buff[0] = (char)PROTOCOL_VERSION;
   end++;

   end = strnmov(end, MYSQL_SERVER_VERSION,SERVER_VERSION_LENGTH) + 1;
   int4store(end, thd->thread_id);
   end += 4;

   end = strmake(end, thd->scramble, SCRAMBLE_LENGTH_323) + 1;
   
   int2store(end, server_capabilites);
   end[2] = (char) proxy_server.default_charset_num;

   int2store(end+3, thd->server_status);
   bzero(end+5, 13);
   end += 18;

   end = strmake(end, thd->scramble+SCRAMBLE_LENGTH_323, SCRAMBLE_LENGTH-SCRAMBLE_LENGTH_323) + 1;
   
   int ret =  net_write_packet(thd->net, buff, (size_t)(end-buff));
   return ret;
}
