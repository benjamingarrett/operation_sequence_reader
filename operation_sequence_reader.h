/* 
 * File:   operation_sequence_reader.h
 * Author: benjamin
 *
 * Created on April 27, 2017, 11:09 AM
 */

#ifndef OPERATION_SEQUENCE_READER_H
#define OPERATION_SEQUENCE_READER_H

#ifdef __cplusplus
extern "C" {
#endif

  typedef struct {
    int has_feedback;
    int has_indexes;
    int is_artificial_feedback;
    int deletions_enabled;
    int64_t num_operations;
    int64_t max_key;
    int64_t capacity;
    int64_t max_load;
    int64_t * operation;
    int64_t * key;
    int64_t * index;
    int * expected_result;
  } operation_sequence;
  operation_sequence * read_operation_sequence(char fname[200]);

#ifdef __cplusplus
}
#endif

#endif /* OPERATION_SEQUENCE_READER_H */

