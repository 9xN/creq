#include "helpers.h"

char *send_data_error(void) {
    return "Error: Failed to send data to host!\n";
}

char *read_data_error(void) {
    return "Error: Failed to read data from host!\n";
}

char *hostname_error(void) {
    return "Error: Failed to resolve host!\n";
}

char *connection_error(void) {
    return "Error: Could not connect to host!\n";
}