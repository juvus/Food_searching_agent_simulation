#ifndef DBG_H_
#define DBG_H_

#include <stdio.h>
#include <string.h>

/* Set of useful debug macros from the book "Learn C Hard Way" */

#define debug(M, ...) { printf("[DEBUG] | %s | %s | %d | ", __FILE__, __func__, __LINE__); printf(M "\n", ##__VA_ARGS__); }
#define error(M, ...) { printf("[ERROR] | %s | %s | %d | ", __FILE__, __func__, __LINE__); printf(M "\n", ##__VA_ARGS__); }
#define warn(M, ...) { printf("[WARN] | %s | %s | %d | ", __FILE__, __func__, __LINE__); printf(M "\n", ##__VA_ARGS__); }
#define info(M, ...) { printf("[INFO] | %s | %s | %d | ", __FILE__, __func__, __LINE__); printf(M "\n", ##__VA_ARGS__); }

#define check(A, M, ...) if(!(A)) { error(M, ##__VA_ARGS__); }

#endif // DBG_H_
