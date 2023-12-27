#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>
#define PORT 8080

typedef struct Header {
    char *name;
    char *value;
    struct Header *next;
} Header; 
// a struct to store headers as a linked list



int send_to_client(int code, int socket_id, FILE * fp, char * extension);
int create_socket();
char * get_mime_type(char * extension);

char * get_mime_type(char * extension) {
    if (strcmp(extension, ".html") == 0) {
        return "text/html";
    }
    if (strcmp(extension, ".css") == 0) {
        return "text/css";
    }
    if (strcmp(extension, ".js") == 0) {
        return "application/javascript";
    }
    if (strcmp(extension, ".png") == 0) {
        return "image/png";
    }
    if (strcmp(extension, ".jpg") == 0) {
        return "image/jpeg";
    }
    if (strcmp(extension, ".jpeg") == 0) {
        return "image/jpeg";
    }
    if (strcmp(extension, ".gif") == 0) {
        return "image/gif";
    }
    if (strcmp(extension, ".ico") == 0) {
        return "image/x-icon";
    }
    if (strcmp(extension, ".svg") == 0) {
        return "image/svg+xml";
    }
    if (strcmp(extension, ".json") == 0) {
        return "application/json";
    }
    if (strcmp(extension, ".pdf") == 0) {
        return "application/pdf";
    }
    if (strcmp(extension, ".zip") == 0) {
        return "application/zip";
    }
    if (strcmp(extension, ".rar") == 0) {
        return "application/x-rar-compressed";
    }
    if (strcmp(extension, ".7z") == 0) {
        return "application/x-7z-compressed";
    }
    if (strcmp(extension, ".tar") == 0) {
        return "application/x-tar";
    }
    if (strcmp(extension, ".gz") == 0) {
        return "application/x-gzip";
    }
    if (strcmp(extension, ".bz2") == 0) {
        return "application/x-bzip2";
    }
    if (strcmp(extension, ".mp3") == 0) {
        return "audio/mpeg";
    }
    if (strcmp(extension, ".ogg") == 0) {
        return "audio/ogg";
    }
    if (strcmp(extension, ".wav") == 0) {
        return "audio/x-wav";
    }
    if (strcmp(extension, ".mp4") == 0) {
        return "video/mp4";
    }
    if (strcmp(extension, ".webm") == 0) {
        return "video/webm";
    }
    if (strcmp(extension, ".ogv") == 0) {
        return "video/ogg";
    }
    if (strcmp(extension, ".avi") == 0) {
        return "video/x-msvideo";
    }
    if (strcmp(extension, ".mkv") == 0) {
        return "video/x-matroska";
    }
    if (strcmp(extension, ".mov") == 0) {
        return "video/quicktime";
    }
    if (strcmp(extension, ".mpg") == 0) {
        return "video/mpeg";
    }
    if (strcmp(extension, ".mpeg") == 0) {
        return "video/mpeg";
    }
    if (strcmp(extension, ".wmv") == 0) {
        return "video/x-ms-wmv";
    }
    if (strcmp(extension, ".flv") == 0) {
        return "video/x-flv";
    }
    if (strcmp(extension, ".swf") == 0) {
        return "application/x-shockwave-flash";
    }
    if (strcmp(extension, ".txt") == 0) {
        return "text/plain";
    }
    if (strcmp(extension, ".doc") == 0) {
        return "application/msword";
    }
    if (strcmp(extension, ".docx") == 0) {
        return "application/vnd.openxmlformats-officedocument.wordprocessingml.document";
    }
    if (strcmp(extension, ".xls") == 0) {
        return "application/vnd.ms-excel";
    }
    if (strcmp(extension, ".xlsx") == 0) {
        return "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet";
    }
    if (strcmp(extension, ".ppt") == 0) {
        return "application/vnd.ms-powerpoint";
    }
    if (strcmp(extension, ".pptx") == 0) {
        return "application/vnd.openxmlformats-officedocument.presentationml.presentation";
    }
    if (strcmp(extension, ".odt") == 0) {
        return "application/vnd.oasis.opendocument.text";
    }
    if (strcmp(extension, ".ods") == 0) {
        return "application/vnd.oasis.opendocument.spreadsheet";
    }
    if (strcmp(extension, ".odp") == 0) {
        return "application/vnd.oasis.opendocument.presentation";
    }
    if (strcmp(extension, ".sxw") == 0) {
        return "application/vnd.sun.xml.writer";
    }
    if (strcmp(extension, ".sxc") == 0) {
        return "application/vnd.sun.xml.calc";
    }
    if (strcmp(extension, ".sxi") == 0) {
        return "application/vnd.sun.xml.impress";
    }
    if (strcmp(extension, ".sxd") == 0) {
        return "application/vnd.sun.xml.draw";
    }
    if (strcmp(extension, ".sxg") == 0) {
        return "application/vnd.sun.xml.writer.global";
    }
    if (strcmp(extension, ".sxm") == 0) {
        return "application/vnd.sun.xml.math";
    }
    return "text/plain";
}

int send_to_client(int code, int socket_id, FILE * fp, char * extension) {
    char * file_buffer;
    char * last_modified;
    if (fp == NULL) {
        file_buffer = NULL;
    } else {
        fseek(fp, 0, SEEK_END);
        int file_size = ftell(fp);
        fseek(fp, 0, SEEK_SET);
        file_buffer = malloc(file_size);
        fread(file_buffer, file_size, 1, fp);

    }
    char *message = NULL;
    char *default_HTML = NULL;
    switch (code) {
    case 200:
        message = "OK";
        default_HTML = "<!DOCTYPE html><html><body><h1>200 OK</h1></body></html>";
        break;
    case 400:
        message = "Bad Request";
        default_HTML = "<!DOCTYPE html><html><body><h1>400 Bad Request</h1></body></html>";
        break;
    case 404:
        message = "Not Found";
        default_HTML = "<!DOCTYPE html><html><body><h1>404 Not Found</h1></body></html>";
        break;
    case 500:
        message = "Internal Server Error";
        default_HTML = "<!DOCTYPE html><html><body><h1>500 Internal Server Error</h1></body></html>";
        break;
    case 501:
        message = "Not Implemented";
        default_HTML = "<!DOCTYPE html><html><body><h1>501 Not Implemented</h1></body></html>";
        break;
    default:
        message = "Unknown Response Code";
        default_HTML = "<!DOCTYPE html><html><body><h1>Unknown Response Code</h1></body></html>";
        break;
    }
    char * body = file_buffer;
    if (body == NULL) {
        body = default_HTML;
    }
    int body_length = strlen(body);
    char * mime_type = get_mime_type(extension);
    int buffer_size = body_length+1024;
    char header[buffer_size];
    int status = snprintf(header, buffer_size,
        "HTTP/1.0 %d %s\r\n"
        "Content-Type: %s\r\n"
        "Content-Length: %d\r\n"
        "Server: Cerver/1.0\r\n"
        "\r\n", code, message, mime_type, body_length);
    if (status < 0) {
        printf("Error with snprintf\n");
        return -1;
    }
    int header_size = strlen(header);
    status = send(socket_id, header, header_size, 0);
    status = send(socket_id, body, body_length, 0);
    if (status == -1) {
        printf("Error sending response\n");
        return -1;
    }
    printf("Server sent response: %s%s\n", header, body);
    free(file_buffer);
    file_buffer = NULL;
    return 0;
}

int Head(int code, int socket_id, FILE * fp, char * extension) {
    char * file_buffer;
    char * last_modified;
    if (fp == NULL) {
        file_buffer = NULL;
    } else {
        fseek(fp, 0, SEEK_END);
        int file_size = ftell(fp);
        fseek(fp, 0, SEEK_SET);
        file_buffer = malloc(file_size);
        fread(file_buffer, file_size, 1, fp);

    }
    char *message = NULL;
    char *default_HTML = NULL;
    switch (code) {
    case 200:
        message = "OK";
        default_HTML = "<!DOCTYPE html><html><body><h1>200 OK</h1></body></html>";
        break;
    case 400:
        message = "Bad Request";
        default_HTML = "<!DOCTYPE html><html><body><h1>400 Bad Request</h1></body></html>";
        break;
    case 404:
        message = "Not Found";
        default_HTML = "<!DOCTYPE html><html><body><h1>404 Not Found</h1></body></html>";
        break;
    case 500:
        message = "Internal Server Error";
        default_HTML = "<!DOCTYPE html><html><body><h1>500 Internal Server Error</h1></body></html>";
        break;
    case 501:
        message = "Not Implemented";
        default_HTML = "<!DOCTYPE html><html><body><h1>501 Not Implemented</h1></body></html>";
        break;
    default:
        message = "Unknown Response Code";
        default_HTML = "<!DOCTYPE html><html><body><h1>Unknown Response Code</h1></body></html>";
        break;
    }
    char * body = file_buffer;
    if (body == NULL) {
        body = default_HTML;
    }
    int body_length = strlen(body);
    char * mime_type = get_mime_type(extension);
    int buffer_size = body_length+1024;
    char header[buffer_size];
    int status = snprintf(header, buffer_size,
        "HTTP/1.0 %d %s\r\n"
        "Content-Type: %s\r\n"
        "Content-Length: %d\r\n"
        "Server: Cerver/1.0"
        "\r\n", code, message, mime_type, body_length);
    if (status < 0) {
        printf("Error with snprintf\n");
        return -1;
    }
    int header_size = strlen(header);
    status = send(socket_id, header, header_size, 0);
    if (status == -1) {
        printf("Error sending response\n");
        return -1;
    }
    printf("Server sent response: %s\n", header);
    free(file_buffer);
    file_buffer = NULL;
    return 0;
}


int create_socket() {
    // Creates the socket file descriptor
    int socket_id = socket(PF_INET, SOCK_STREAM, 0);
    // Check if the socket was created
    if (socket_id == -1) {
        printf("Error creating socket\n");
        return -1;
    }
    int status;
    // Creates the socket address and assign a port
    struct sockaddr_in socket_address;
    socket_address.sin_family = AF_INET;
    socket_address.sin_port = htons(PORT);
    socket_address.sin_addr.s_addr = INADDR_ANY;
    if (bind(socket_id, (struct sockaddr *) &socket_address, sizeof(socket_address)) == -1) {
        printf("Error binding socket\n");
        close(socket_id);
        return -1;
    }
    // Socket was bound successfully
    printf("Socket was bound successfully\n");
    // Listens for connections
    if (listen(socket_id, 5) == -1) {
        printf("Error listening\n");
        close(socket_id);
        return -1;
    }
    return socket_id;
}


int main() {
  int socket_id = create_socket();
  if (socket_id == -1) {
      printf("Error creating socket, exiting\n");
      return -1;
  }
  int status;
  printf("Socket created successfully, server is listening on port %d\n", PORT);
 
  while (1) {
    // Accept connection, create a new socket for the connection
    int client_socket_id = accept(socket_id, NULL, NULL);
    if (client_socket_id == -1) {
        printf("Error accepting connection\n");
        close(socket_id);
        return -1;
    }

    // Read the request from the client into a buffer
    char * request = malloc(2048);
    status = read(client_socket_id, request, 2048);
    if (status == -1) {
        printf("Error reading from socket\n");
        close(client_socket_id);
        close(socket_id);
        return -1;
    }

    // Parse the request
    char * request_method;
    char * request_url;
    char * request_protocol;

    request_method = strtok(request, " "); // strtok will split the string at the first space
    request_url = strtok(NULL, " "); // using strtok with NULL will use the same string
    request_protocol = strtok(NULL, "\n"); // lastly get the protocol which ends with a newline
    if (request_protocol[strlen(request_protocol) - 1] == '\r') {
        // if the protocol ended with a carriage return, remove it
        request_protocol[strlen(request_protocol) - 1] = '\0';
    }
    // remove the first line of the request
    request = strtok(NULL, "\0");
    // Print the request
    printf("\n\nRequest Method: %s\nRequest URL: %s\nRequest Protocol: %s\n\n", request_method, request_url, request_protocol);
    printf("Full Request:\n%s\n", request);
        bool headers_finished = false;
        Header * head = NULL;
        Header * current_header = NULL;
        int content_length;
    printf("\nBegin reading headers\n");
        while (!headers_finished) {
            printf("Reading header line\n");
            char * header_name = NULL;
            char * header_value = NULL;
            char * header_line = NULL;
            header_line = strtok(request, "\n");
            // remove \r from the end of the header line if it exists
            if (header_line[strlen(header_line) - 1] == '\r') {
                header_line[strlen(header_line) - 1] = '\0';
            }
            printf("Header line: %s\n", header_line);
            if (header_line==NULL || header_line[0] == '\0' || header_line[0] == '\r' || header_line[0] == '\n') {
                // if the header line is empty, we've reached the end of the headers and have consumed the newline after it
                headers_finished = true;
                // consume everything up to and including the newline after the headers
                printf("\nLeft in Request: %s\n", request);
                break;
            }
            // find the colon in the header line, and set the header name to the string before the colon
            int colon_index = strchr(header_line, ':') - header_line;
            header_name = strndup(header_line, colon_index);
            // remove everything up to and including the colon from the header line
            header_line = header_line + colon_index + 1;
            if (header_name == NULL) {
                printf("Error reading header name");
                close(client_socket_id);
                close(socket_id);
                return -1;
            }
            // consume any whitespace after the colon
            while (header_line[0] == ' ') {
                header_line = header_line + 1;
            }
            // set the header value to the rest of the header line
            header_value = header_line;
            // remove any \r or \n from the end of the header value
            if (header_value[strlen(header_value) - 1] == '\n') {
                header_value[strlen(header_value) - 1] = '\0';
            }
            if (header_value[strlen(header_value) - 1] == '\r') {
                header_value[strlen(header_value) - 1] = '\0';
            }

            if (header_value == NULL) {
                printf("Error reading header value");
                close(client_socket_id);
                close(socket_id);
                return -1;
            }
            // if the header name is Content-Length, set the content length to the header value
            if (strcmp(header_name, "Content-Length") == 0) {
                content_length = atoi(header_value);
            }
            // create a new header struct and add it to the linked list of headers
            Header * new_header = (Header *)malloc(sizeof(Header));
            new_header->name = header_name;
            new_header->value = header_value;
            new_header->next = NULL;
            if (head == NULL) {
                head = new_header;
                current_header = new_header;
            }
            else {
                current_header->next = new_header;
                current_header = new_header;
            }
            // remove the header line from the request
            request = strtok(NULL, "\0");
        }
        request = strtok(NULL, "\0");
        printf("Finished reading headers\n");
        printf("\nFull Request:\n%s\n", request);
    // Check if the request is valid
    if (request_method == NULL || request_url == NULL || request_protocol == NULL) {
        // If the request is invalid, send a 400 error
        status = send_to_client(400, client_socket_id, NULL, ".html");
        if (status == -1) {
            printf("Error sending response\n");
            close(client_socket_id);
            close(socket_id);
            return -1;
        }
    }
    // Check if the request is a GET request
    if (strcmp(request_method, "GET") == 0) {
        // If the request is GET, send a 200 OK response, with the body containing the requested resource
        char * requested_resource = NULL;
        // Check if the request_url is root and if so, send the default HTML
        if (strcmp(request_url, "/") == 0) {
            requested_resource = "index.html";
        } else {
            requested_resource = request_url + 1;
            printf("Requested resource: %s\n", requested_resource);
        }
        FILE * fp = fopen(requested_resource, "r");
        printf("file pointer: %p\n", fp);
        if (fp == NULL) {
            printf("null file pointer\n");
            // If requested resource can not be accessed for some reason, send a 404 error
            status = send_to_client(404, client_socket_id, NULL, ".html");
            if (status == -1) {
                printf("Error sending response\n");
                close(client_socket_id);
                close(socket_id);
                return -1;
            }
        }
        else {
            printf("file pointer not null\n");
            // If we can access the resource, open it and read it into a buffer
            char * fp_extension = strrchr(requested_resource, '.');
            // Send a 200 OK response, with the body containing the requested resource
            status = send_to_client(200, client_socket_id, fp, fp_extension);
            fclose(fp);
            fp = NULL;

            if (status == -1) {
                printf("Error sending response\n");
                close(client_socket_id);
                close(socket_id);
                return -1;
            }
        }
    }
    else if (strcmp(request_method, "HEAD") == 0) {
        // If the request is HEAD, send a 200 OK response, with the headers for the requested resource
        char * requested_resource = NULL;
        // Check if the request_url is root and if so, send the default HTML
        if (strcmp(request_url, "/") == 0) {
            requested_resource = "index.html";
        } else {
            requested_resource = request_url + 1;
            printf("Requested resource: %send\n", requested_resource);
        }
        FILE * fp = fopen(requested_resource, "r");
        printf("file pointer: %p\n", fp);
        if (fp == NULL) {
            printf("null file pointer\n");
            // If requested resource can not be accessed for some reason, send a 404 error
            status = Head(404, client_socket_id, NULL, ".html");
            if (status == -1) {
                printf("Error sending response\n");
                close(client_socket_id);
                close(socket_id);
                return -1;
            }
        }
        else {
            printf("file pointer not null\n");
            // If we can access the resource, open it and read it into a buffer
            char * fp_extension = strrchr(requested_resource, '.');
            // Send a 200 OK response, with the headers appropriate for the requested resource
            status = Head(200, client_socket_id, fp, fp_extension);
            fclose(fp);
            fp = NULL;

            if (status == -1) {
                printf("Error sending response\n");
                close(client_socket_id);
                close(socket_id);
                return -1;
            }
        }
    }
    else if (strcmp(request_method, "POST") == 0) {
        printf("POST request\n");
        // If we have a POST request, the URL is the URL we are supposed to send the request to.
        // For this server I've decided to just save the body of POST requests to a text file to
        // represent sending data to a database.
        // Read the headers in, find content length, create string of that length, store the body of request, save string to text file, return OK
        // In file include at the top the URL it was intended for, and info from headers if relevant
        
        // first read the headers
        // read until we get a : to find the header name
        // read until we get a \r to find the header value
        
        printf("Reading body\n");
        // all the headers have been read in, now read the body of the request
        // we know the length of the body from the content length header, so we can read that many bytes and allocate a string of that length
        char * body = (char *)malloc(content_length + 1);
        printf("Body length: %d", content_length);
        strncpy(body, request, content_length);
        body[content_length] = '\0';
        printf("Body: %s", body);
        if (body == NULL) {
            printf("Error reading body, potentially no body in request\n");
            close(client_socket_id);
            close(socket_id);
            return -1;
        }
        // now we have the body of the request, we can save it to a file
        // create a file name from the current time
        printf("Creating file name\n");
        time_t t = time(NULL);
        struct tm * tm = localtime(&t);
        char s[64];
        strftime(s, sizeof(s), "%c", tm);
        char * file_name = (char *)malloc(strlen(s) + 10);
        strcpy(file_name, "POST/");
        strcat(file_name, s);
        strcat(file_name, ".txt");
        printf("Opening file %s\n", file_name);
        FILE *fp = fopen(file_name, "ab+");
        if (fp == NULL) {
            printf("Error opening file");
            close(client_socket_id);
            close(socket_id);
            return -1;
        }
        printf("Writing to file\n");
        // write the request_url to the file
        fprintf(fp, "URL: %s\n", request_url);
        // write the headers to the file
        Header * current = head;
        Header * temp = NULL;
        while (current != NULL) {
            fprintf(fp, "%s: %s\n", current->name, current->value);
            // store current in temp so we can free it
            temp = current;
            current = current->next;
            // free the memory we allocated
            temp->name = NULL;
            temp->value = NULL;
            free(temp);
        }
        // write the body to the file
        printf("Body: %s\n", body);
        fprintf(fp, "Body: %s\n", body);
        fclose(fp);
        // send a 200 response
        status = send_to_client(200, client_socket_id, NULL, ".html");
        if (status == -1) {
            printf("Error sending response\n");
            close(client_socket_id);
            close(socket_id);
            return -1;
        }
        // free the memory we allocated
        body = NULL;
        file_name = NULL;
    }
    else if (strcmp(request_method, "PUT") == 0 || strcmp(request_method, "DELETE") == 0) {
        // If the request was a valid HTTP request that we can't handle, send a 500 error
        status = send_to_client(501, client_socket_id, NULL, ".html");
        if (status == -1) {
            printf("Error sending response\n");
            close(client_socket_id);
            close(socket_id);
            return -1;
        }
    }
    else {
        // Request was invalid, send a 400 response (client error)
        status = send_to_client(400, client_socket_id, NULL, ".html");
        if (status == -1) {
            printf("Error sending response\n");
            close(client_socket_id);
            close(socket_id);
            return -1;
        }
    }

    // Response was sent successfully
    printf("Response was sent successfully\n");
    // Close the socket
    close(client_socket_id);
}
    // This code should never run, but if for some reason the
    // while loop doesn't start, this will close the socket

    // Close the socket at the end of the program
    status = close(socket_id);
    if (status == -1) {
        printf("Error closing socket\n");
        return -1;
    }

    return 0;
}
