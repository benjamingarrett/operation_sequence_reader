/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "operation_sequence_reader.h"
#define FALSE 0
#define TRUE 1

operation_sequence * read_operation_sequence(char fname[200]){
    
    operation_sequence * os;
    int g, n, m;
    char buf[200];
    FILE * fp;
    
    if((fp = fopen(fname,"r"))==NULL){
        printf("Could not open %s\n", fname);
        exit(EXIT_FAILURE);
    }
    os = calloc(1, sizeof(operation_sequence));
    if(os == NULL){
        printf("Could not allocate memory for operation sequence\n");
        exit(EXIT_FAILURE);
    }
    os->has_feedback = FALSE;
    os->has_indexes = FALSE;
    while((n = fscanf(fp, "%s", buf)) != EOF){
//        printf("Processing >%s<\n", buf);
        if(strcmp("HAS_FEEDBACK",buf)==0){
            n = fscanf(fp, "%d", (int *)&os->has_feedback);
            buf[0] = 0;
        } else if(strcmp("HAS_INDEXES",buf)==0){
            n = fscanf(fp, "%d", (int *)&os->has_indexes);
            buf[0] = 0;
        } else if(strcmp("IS_ARTIFICIAL_FEEDBACK",buf)==0){
            n = fscanf(fp, "%d", (int *)&os->is_artificial_feedback);
            buf[0] = 0;
        } else if(strcmp("MAX_KEY",buf)==0){
            n = fscanf(fp, "%ld", (long int *)&os->max_key);
            buf[0] = 0;
        } else if(strcmp("CAPACITY",buf)==0){
            n = fscanf(fp, "%ld", (long int *)&os->capacity);
            buf[0] = 0;
        } else if(strcmp("MAX_LOAD",buf)==0){
            n = fscanf(fp, "%ld", (long int *)&os->max_load);
            buf[0] = 0;
        } else if(strcmp("DELETIONS_ENABLED",buf)==0){
            n = fscanf(fp, "%d", (int *)&os->deletions_enabled);
            buf[0] = 0;
        } else if(strcmp("NUM_COMMENTS",buf)==0){
            n = fscanf(fp, "%d", (int *)&m);
            for(g=0; g<m; g++){
                n = fscanf(fp, "%s", buf);
            }
            buf[0] = 0;
        } else if(strcmp("NUM_OPERATIONS",buf)==0){
            n = fscanf(fp, "%ld", (long int *)&os->num_operations);
            if((os->operation = (int64_t *)calloc(os->num_operations, sizeof(int64_t)))==NULL){
                printf("Could not allocate memory for operation\n");
                exit(EXIT_FAILURE);
            }
            if((os->key = (int64_t *)calloc(os->num_operations, sizeof(int64_t)))==NULL){
                printf("Could not allocate memory for key\n");
                exit(EXIT_FAILURE);                
            }
            if(os->has_feedback){
                if((os->expected_result = (int *)calloc(os->num_operations, sizeof(int)))==NULL){
                    printf("Could not allocate memory for result\n");
                    exit(EXIT_FAILURE);                
                }
            }
            if(os->has_indexes){
                if((os->index = (int64_t *)calloc(os->num_operations, sizeof(int64_t)))==NULL){
                    printf("Could not allocate memory for key\n");
                    exit(EXIT_FAILURE);                
                }
            }
            if(os->has_feedback){
                if(os->has_indexes){
                    for(g=0; g<os->num_operations; g++){
                        n = fscanf(fp, "%ld %ld %d %ld", &os->operation[g], &os->key[g], &os->expected_result[g], &os->index[g]);
                    }
                } else {
                    for(g=0; g<os->num_operations; g++){
                        n = fscanf(fp, "%ld %ld %d", &os->operation[g], &os->key[g], &os->expected_result[g]);
                    }                    
                }
            } else {
                if(os->has_indexes){
                    printf("Format error: sequence cannot have indexes without feedback\n");
                    exit(EXIT_FAILURE);
                } else {
                    for(g=0; g<os->num_operations; g++){
                        n = fscanf(fp, "%ld %ld", &os->operation[g], &os->key[g]);                        
                    }                    
                }
            }
            buf[0] = 0;
        }
    }
    return os;
}
