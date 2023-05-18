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

void directory_check_post(char *data, char *post_data, char *directory, char *host, char *content_type);
bool requests_post(int port, char *website, char *directory, char *post_data, char *content_type);