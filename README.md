# creq

creq is a small, simple, and easy-to-use HTTP library written in C. It allows you to:

- Make GET requests to fetch data from HTTP servers 
- Send POST requests to submit data to HTTP servers
- (put, patch & delete requests coming soon)

Key features:

- Minimal code footprint  
- Simple, intuitive API
- Cross-platform (works on Linux, Windows and macOS)

creq is meant for developers who want a basic HTTP library for:

- Prototyping and experimenting
- Learning how HTTP clients work under the hood   
- Small projects with low-level dependencies

Compared to larger HTTP libraries like cURL, creq has a much smaller codebase 
(only a few hundred lines of code) making it easy to read, understand and extend.

To install and use creq in your C project, follow these steps:

```bash
gcc (file including creq/creq.h) creq/helpers/helpers.c creq/http/get/get.c creq/http/post/post.c
```

## API
Currently, creq only supports GET and POST requests. More HTTP methods will be added in the future.

- GET request ```requests_get(int port, char *website, char *directory);```
- POST request ```requests_post(int port, char *website, char *directory, char *post_data, char *content_type);```
