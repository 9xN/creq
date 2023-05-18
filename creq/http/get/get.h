#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#pragma once

void directory_check_get(char *data, char *directory, char *host);
bool requests_get(int port, char *website, char *directory);