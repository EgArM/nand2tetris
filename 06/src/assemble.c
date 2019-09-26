#include <ctype.h>
#include <hash_map.h>
#include <linked_list.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct LinkedList LinkedList;

typedef struct LinkedListNode LinkedListNode;

typedef struct HashMap HashMap;

HashMap *DEST_MAP;
HashMap *COMP_MAP;
HashMap *JUMP_MAP;

const char *DEST_NULL_KEY = "";     const uint8_t DEST_NULL_VALUE = 0;
const char *DEST_M_KEY = "M";       const uint8_t DEST_M_VALUE = 1;
const char *DEST_D_KEY = "D";       const uint8_t DEST_D_VALUE = 2;
const char *DEST_MD_KEY = "MD";     const uint8_t DEST_MD_VALUE = 3;
const char *DEST_A_KEY = "A";       const uint8_t DEST_A_VALUE = 4;
const char *DEST_AM_KEY = "AM";     const uint8_t DEST_AM_VALUE = 5;
const char *DEST_AD_KEY = "AD";     const uint8_t DEST_AD_VALUE = 6;
const char *DEST_AMD_KEY = "AMD";   const uint8_t DEST_AMD_VALUE = 7;

const char *COMP_Z_KEY = "0";     const uint8_t COMP_Z_VALUE = 42;
const char *COMP_O_KEY = "1";     const uint8_t COMP_O_VALUE = 63;
const char *COMP_MO_KEY = "-1";   const uint8_t COMP_MO_VALUE = 58;
const char *COMP_D_KEY = "D";     const uint8_t COMP_D_VALUE = 12;
const char *COMP_A_KEY = "A";     const uint8_t COMP_A_VALUE = 48;    const char *COMP_M_KEY = "M";     const uint8_t COMP_M_VALUE = 112;
const char *COMP_ND_KEY = "!D";   const uint8_t COMP_ND_VALUE = 13;
const char *COMP_NA_KEY = "!A";   const uint8_t COMP_NA_VALUE = 49;   const char *COMP_NM_KEY = "!M";   const uint8_t COMP_NM_VALUE = 113;
const char *COMP_MD_KEY = "-D";   const uint8_t COMP_MD_VALUE = 15;
const char *COMP_MA_KEY = "-A";   const uint8_t COMP_MA_VALUE = 51;   const char *COMP_MM_KEY = "-M";   const uint8_t COMP_MM_VALUE = 115;
const char *COMP_DPO_KEY = "D+1"; const uint8_t COMP_DPO_VALUE = 31;
const char *COMP_APO_KEY = "A+1"; const uint8_t COMP_APO_VALUE = 55;  const char *COMP_MPO_KEY = "M+1"; const uint8_t COMP_MPO_VALUE = 119;
const char *COMP_DMO_KEY = "D-1"; const uint8_t COMP_DMO_VALUE = 14;
const char *COMP_AMO_KEY = "A-1"; const uint8_t COMP_AMO_VALUE = 50;  const char *COMP_MMO_KEY = "M-1"; const uint8_t COMP_MMO_VALUE = 114;
const char *COMP_DPA_KEY = "D+A"; const uint8_t COMP_DPA_VALUE = 2;   const char *COMP_DPM_KEY = "D+M"; const uint8_t COMP_DPM_VALUE = 66;
const char *COMP_DMA_KEY = "D-A"; const uint8_t COMP_DMA_VALUE = 19;  const char *COMP_DMM_KEY = "D-M"; const uint8_t COMP_DMM_VALUE = 83;
const char *COMP_AMD_KEY = "A-D"; const uint8_t COMP_AMD_VALUE = 7;   const char *COMP_MMD_KEY = "M-D"; const uint8_t COMP_MMD_VALUE = 71;
const char *COMP_DAA_KEY = "D&A"; const uint8_t COMP_DAA_VALUE = 0;   const char *COMP_DAM_KEY = "D&M"; const uint8_t COMP_DAM_VALUE = 64;
const char *COMP_DOA_KEY = "D|A"; const uint8_t COMP_DOA_VALUE = 21;  const char *COMP_DOM_KEY = "D|M"; const uint8_t COMP_DOM_VALUE = 85;

const char *JUMP_NULL_KEY = "";   const uint8_t JUMP_NULL_VALUE = 0;
const char *JUMP_JGT_KEY = "JGT"; const uint8_t JUMP_JGT_VALUE = 1;
const char *JUMP_JEQ_KEY = "JEQ"; const uint8_t JUMP_JEQ_VALUE = 2;
const char *JUMP_JGE_KEY = "JGE"; const uint8_t JUMP_JGE_VALUE = 3;
const char *JUMP_JLT_KEY = "JLT"; const uint8_t JUMP_JLT_VALUE = 4;
const char *JUMP_JNE_KEY = "JNE"; const uint8_t JUMP_JNE_VALUE = 5;
const char *JUMP_JLE_KEY = "JLE"; const uint8_t JUMP_JLE_VALUE = 6;
const char *JUMP_JMP_KEY = "JMP"; const uint8_t JUMP_JMP_VALUE = 7;

const char *R0_KEY = "R0";    const uint16_t R0_VALUE = 0;
const char *R1_KEY = "R1";    const uint16_t R1_VALUE = 1;
const char *R2_KEY = "R2";    const uint16_t R2_VALUE = 2;
const char *R3_KEY = "R3";    const uint16_t R3_VALUE = 3;
const char *R4_KEY = "R4";    const uint16_t R4_VALUE = 4;
const char *R5_KEY = "R5";    const uint16_t R5_VALUE = 5;
const char *R6_KEY = "R6";    const uint16_t R6_VALUE = 6;
const char *R7_KEY = "R7";    const uint16_t R7_VALUE = 7;
const char *R8_KEY = "R8";    const uint16_t R8_VALUE = 8;
const char *R9_KEY = "R9";    const uint16_t R9_VALUE = 9;
const char *R10_KEY = "R10";  const uint16_t R10_VALUE = 10;
const char *R11_KEY = "R11";  const uint16_t R11_VALUE = 11;
const char *R12_KEY = "R12";  const uint16_t R12_VALUE = 12;
const char *R13_KEY = "R13";  const uint16_t R13_VALUE = 13;
const char *R14_KEY = "R14";  const uint16_t R14_VALUE = 14;
const char *R15_KEY = "R15";  const uint16_t R15_VALUE = 15;

const char *SCREEN_KEY = "SCREEN";  const uint16_t SCREEN_VALUE = 16384;
const char *KBD_KEY = "KBD";        const uint16_t KBD_VALUE = 24576;

const char *SP_KEY = "SP";      const uint16_t SP_VALUE = 0;
const char *LCL_KEY = "LCL";    const uint16_t LCL_VALUE = 1;
const char *ARG_KEY = "ARG";    const uint16_t ARG_VALUE = 2;
const char *THIS_KEY = "THIS";  const uint16_t THIS_VALUE = 3;
const char *THAT_KEY = "THAT";  const uint16_t THAT_VALUE = 4;

map_size_t hash_string(const char *string) {
  int hash = 0;
  while(*string != '\0') {
    hash = hash * 31 + *string++;
  }

  return hash;
}

bool equals_string(const char *s1, const char *s2) {
  while (*s1 != '\0' && *s2 != '\0') {
    if (*s1++ != *s2++) {
      return false;
    }
  }
  return (*s1 == '\0' && *s2 == '\0');
}

bool read(FILE *fp, LinkedList *input) {
  char *line = NULL;
  size_t len = 0;
  ssize_t read;

  while ((read = getline(&line, &len, fp)) != -1) {
    if(linked_list_add_tail(input, line) == NULL) {
      return false;
    }
    line = NULL;
  }
  return true;
}

bool is_a_instruction(const char *line) {
  return *line == '@';
}

bool is_c_instruction(const char *line) {
  return *line == 'D' || *line == 'M' || *line == 'A' || *line == '0';
}

bool is_instruction(const char *line) {
  return is_a_instruction(line) || is_c_instruction(line);
}

bool is_symbol_line(const char *line) {
  return *line == '(';
}

bool prepare_sym_table(const LinkedList *input, HashMap *sym_table) {
  int32_t row = 0;
  LinkedListNode *line_node = input->head;

  while (line_node != NULL) {
    const char *line = line_node->value;
    while (isspace(*line)) {
      line++;
    }
    if (is_instruction(line)) {
      row++;
    } else if (is_symbol_line(line)) {
      int32_t length = 0;
      for (; *(line + length + 1) != ')'; length++) {
      }

      char* key = malloc(length + 1);
      if (key == NULL) {
        return false;
      }
      memcpy(key, line + 1, length);
      *(key + length) = '\0';

      int32_t* value = malloc(sizeof(int32_t));
      if (value == NULL) {
        return false;
      }
      *value = row;

      const void *prev = NULL;
      if (!hash_map_put(sym_table, key, value, &prev)) {
        return false;
      }
    }

    line_node = line_node->next;
  }
  return true;
}

bool assemble_a_instraction(const char *line, uint16_t *code, HashMap *sym_table, int32_t *var_counter) {
  line++;
  bool is_digit = true;
  size_t offset = 0;
  while (*(line + offset) != '\0' && !isspace(*(line + offset))) {
    if (!isdigit(*(line + offset))) {
      is_digit = false;
      break;
    }
    offset++;
  }
  *code = 0;
  if (is_digit) {
    for (size_t i = 0; i < offset; i++) {
      *code = *code * 10 + (*(line + i) - '0');
    }
  } else {
    offset = 0;
    for (; *(line + offset) != '\0' && !isspace(*(line + offset)); offset++) {
    }

    char *symbol = malloc(offset + 1);
    if (symbol == NULL) {
      return false;
    }
    memcpy(symbol, line, offset);
    *(symbol + offset) = '\0';

    const uint16_t *value = hash_map_get(sym_table, symbol);
    if (value != NULL) {
      *code = *value;
      free(symbol);
    } else {
      *code = *var_counter;
      const void *prev = NULL;
      if(!hash_map_put(sym_table, symbol, code, &prev)) {
        return false;
      }
      *var_counter += 1;
    }
  }

  *code = *code & 32767;

  return true;
}

bool assemble_c_instraction(const char *line, uint16_t *code) {
  *code = 0;
  uint8_t prefix = 7;
  uint8_t comp = 0;
  uint8_t dest = 0;
  uint8_t jump = 0;

  bool contains_destination = false;
  uint8_t curr = 1;
  while (*(line + curr) != ';') {
    if (*(line + curr) == '=') {
      contains_destination = true;
      break;
    }
    curr++;
  }

  if (contains_destination) {
    char *dest_str = malloc(curr + 1);
    if (dest_str == NULL) {
      return false;
    }
    memcpy(dest_str, line, curr);
    *(dest_str + curr) = '\0';
    dest = *(uint8_t *) hash_map_get(DEST_MAP, dest_str);
    free(dest_str);
    line = line + curr + 1;
  }

  curr = 1;
  while (*(line + curr) != ';' && !isspace(*(line + curr))) {
    curr++;
  }

  char *comp_str = malloc(curr + 1);
  if (comp_str == NULL) {
    return false;
  }
  memcpy(comp_str, line, curr);
  *(comp_str + curr) = '\0';
  comp = *(uint8_t *) hash_map_get(COMP_MAP, comp_str);
  free(comp_str);
  line = line + curr;

  if (*line == ';') {
    line++;
    char jump_str[4];
    memcpy(jump_str, line, 3);
    jump_str[3] = '\0';
    jump = *(uint8_t *) hash_map_get(JUMP_MAP, jump_str);
  }

  *code += prefix;
  *code = *code << 7;
  *code += comp;
  *code = *code << 3;
  *code += dest;
  *code = *code << 3;
  *code += jump;

  return true;
}

bool assemble_instraction(const char *line, uint16_t *code, HashMap *sym_table, int32_t *var_counter) {
  if (is_a_instruction(line)) {
    return assemble_a_instraction(line, code, sym_table, var_counter);
  } else {
    return assemble_c_instraction(line, code);
  }
}

bool assemble(const LinkedList *input, LinkedList *output, HashMap *sym_table) {
  int32_t var_counter = 16;
  LinkedListNode *line_node = input->head;
  while (line_node != NULL) {
    const char *line = line_node->value;
    while (isspace(*line)) {
      line++;
    }
    if (is_instruction(line)) {
      uint16_t *code = malloc(sizeof(uint16_t));
      if (code == NULL) {
        return false;
      }
      if (!assemble_instraction(line, code, sym_table, &var_counter)) {
        return false;
      }
      if (linked_list_add_tail(output, code) == NULL) {
        return false;
      }
    }
    line_node = line_node->next;
  }
  return true;
}

bool write(FILE *fp, const LinkedList *output) {
  char buffer[17];
  buffer[16] = '\0';
  LinkedListNode *current = output->head;
  while (current != NULL) {
    uint16_t code = *(uint16_t *) current->value;
    int8_t position = 15;
    while (position >= 0) {
      buffer[position--] = '0' + code % 2;
      code /= 2;
    }
    // printf("%s\n", buffer);
    fprintf(fp, "%s\n", buffer);
    current = current->next;
  }
  return true;
}

int main(int argc, char const *argv[]) {

  const void *prev = NULL;

  DEST_MAP = create_hash_map((map_size_t (*) (const void *)) hash_string,
                              (bool (*) (const void *, const void *)) equals_string,
                              0);

  hash_map_put(DEST_MAP, DEST_NULL_KEY, &DEST_NULL_VALUE, &prev);
  hash_map_put(DEST_MAP, DEST_M_KEY, &DEST_M_VALUE, &prev);
  hash_map_put(DEST_MAP, DEST_D_KEY, &DEST_D_VALUE, &prev);
  hash_map_put(DEST_MAP, DEST_MD_KEY, &DEST_MD_VALUE, &prev);
  hash_map_put(DEST_MAP, DEST_A_KEY, &DEST_A_VALUE, &prev);
  hash_map_put(DEST_MAP, DEST_AM_KEY, &DEST_AM_VALUE, &prev);
  hash_map_put(DEST_MAP, DEST_AD_KEY, &DEST_AD_VALUE, &prev);
  hash_map_put(DEST_MAP, DEST_AMD_KEY, &DEST_AMD_VALUE, &prev);

  COMP_MAP = create_hash_map((map_size_t (*) (const void *)) hash_string,
                              (bool (*) (const void *, const void *)) equals_string,
                              0);

  hash_map_put(COMP_MAP, COMP_Z_KEY, &COMP_Z_VALUE, &prev);
  hash_map_put(COMP_MAP, COMP_O_KEY, &COMP_O_VALUE, &prev);
  hash_map_put(COMP_MAP, COMP_MO_KEY, &COMP_MO_VALUE, &prev);
  hash_map_put(COMP_MAP, COMP_D_KEY, &COMP_D_VALUE, &prev);
  hash_map_put(COMP_MAP, COMP_A_KEY, &COMP_A_VALUE, &prev);     hash_map_put(COMP_MAP, COMP_M_KEY, &COMP_M_VALUE, &prev);
  hash_map_put(COMP_MAP, COMP_ND_KEY, &COMP_ND_VALUE, &prev);
  hash_map_put(COMP_MAP, COMP_NA_KEY, &COMP_NA_VALUE, &prev);   hash_map_put(COMP_MAP, COMP_NM_KEY, &COMP_NM_VALUE, &prev);
  hash_map_put(COMP_MAP, COMP_MD_KEY, &COMP_MD_VALUE, &prev);
  hash_map_put(COMP_MAP, COMP_MA_KEY, &COMP_MA_VALUE, &prev);   hash_map_put(COMP_MAP, COMP_MM_KEY, &COMP_MM_VALUE, &prev);
  hash_map_put(COMP_MAP, COMP_DPO_KEY, &COMP_DPO_VALUE, &prev);
  hash_map_put(COMP_MAP, COMP_APO_KEY, &COMP_APO_VALUE, &prev); hash_map_put(COMP_MAP, COMP_MPO_KEY, &COMP_MPO_VALUE, &prev);
  hash_map_put(COMP_MAP, COMP_DMO_KEY, &COMP_DMO_VALUE, &prev);
  hash_map_put(COMP_MAP, COMP_AMO_KEY, &COMP_AMO_VALUE, &prev); hash_map_put(COMP_MAP, COMP_MMO_KEY, &COMP_MMO_VALUE, &prev);
  hash_map_put(COMP_MAP, COMP_DPA_KEY, &COMP_DPA_VALUE, &prev); hash_map_put(COMP_MAP, COMP_DPM_KEY, &COMP_DPM_VALUE, &prev);
  hash_map_put(COMP_MAP, COMP_DMA_KEY, &COMP_DMA_VALUE, &prev); hash_map_put(COMP_MAP, COMP_DMM_KEY, &COMP_DMM_VALUE, &prev);
  hash_map_put(COMP_MAP, COMP_AMD_KEY, &COMP_AMD_VALUE, &prev); hash_map_put(COMP_MAP, COMP_MMD_KEY, &COMP_MMD_VALUE, &prev);
  hash_map_put(COMP_MAP, COMP_DAA_KEY, &COMP_DAA_VALUE, &prev); hash_map_put(COMP_MAP, COMP_DAM_KEY, &COMP_DAM_VALUE, &prev);
  hash_map_put(COMP_MAP, COMP_DOA_KEY, &COMP_DOA_VALUE, &prev); hash_map_put(COMP_MAP, COMP_DOM_KEY, &COMP_DOM_VALUE, &prev);

  JUMP_MAP = create_hash_map((map_size_t (*) (const void *)) hash_string,
                              (bool (*) (const void *, const void *)) equals_string,
                              0);

  hash_map_put(JUMP_MAP, JUMP_NULL_KEY, &JUMP_NULL_VALUE, &prev);
  hash_map_put(JUMP_MAP, JUMP_JGT_KEY, &JUMP_JGT_VALUE, &prev);
  hash_map_put(JUMP_MAP, JUMP_JEQ_KEY, &JUMP_JEQ_VALUE, &prev);
  hash_map_put(JUMP_MAP, JUMP_JGE_KEY, &JUMP_JGE_VALUE, &prev);
  hash_map_put(JUMP_MAP, JUMP_JLT_KEY, &JUMP_JLT_VALUE, &prev);
  hash_map_put(JUMP_MAP, JUMP_JNE_KEY, &JUMP_JNE_VALUE, &prev);
  hash_map_put(JUMP_MAP, JUMP_JLE_KEY, &JUMP_JLE_VALUE, &prev);
  hash_map_put(JUMP_MAP, JUMP_JMP_KEY, &JUMP_JMP_VALUE, &prev);

  HashMap *sym_table = create_hash_map((map_size_t (*) (const void *)) hash_string,
                                        (bool (*) (const void *, const void *)) equals_string,
                                        0);

  hash_map_put(sym_table, R0_KEY, &R0_VALUE, &prev);
  hash_map_put(sym_table, R1_KEY, &R1_VALUE, &prev);
  hash_map_put(sym_table, R2_KEY, &R2_VALUE, &prev);
  hash_map_put(sym_table, R3_KEY, &R3_VALUE, &prev);
  hash_map_put(sym_table, R4_KEY, &R4_VALUE, &prev);
  hash_map_put(sym_table, R5_KEY, &R5_VALUE, &prev);
  hash_map_put(sym_table, R6_KEY, &R6_VALUE, &prev);
  hash_map_put(sym_table, R7_KEY, &R7_VALUE, &prev);
  hash_map_put(sym_table, R8_KEY, &R8_VALUE, &prev);
  hash_map_put(sym_table, R9_KEY, &R9_VALUE, &prev);
  hash_map_put(sym_table, R10_KEY, &R10_VALUE, &prev);
  hash_map_put(sym_table, R11_KEY, &R11_VALUE, &prev);
  hash_map_put(sym_table, R12_KEY, &R12_VALUE, &prev);
  hash_map_put(sym_table, R13_KEY, &R13_VALUE, &prev);
  hash_map_put(sym_table, R14_KEY, &R14_VALUE, &prev);
  hash_map_put(sym_table, R15_KEY, &R15_VALUE, &prev);

  hash_map_put(sym_table, SCREEN_KEY, &SCREEN_VALUE, &prev);
  hash_map_put(sym_table, KBD_KEY, &KBD_VALUE, &prev);

  hash_map_put(sym_table, SP_KEY, &SP_VALUE, &prev);
  hash_map_put(sym_table, LCL_KEY, &LCL_VALUE, &prev);
  hash_map_put(sym_table, ARG_KEY, &ARG_VALUE, &prev);
  hash_map_put(sym_table, THIS_KEY, &THIS_VALUE, &prev);
  hash_map_put(sym_table, THAT_KEY, &THAT_VALUE, &prev);

  if (argc != 3) {
    printf("%s\n", "Usage: assemble <PATH_TO_ASM> <PATH_TO_HACK>");
    return 0;
  }

  char const *in_path = *(argv + 1);
  char const *out_path = *(argv + 2);

  FILE *inputf = fopen(in_path, "r");
  if (inputf == NULL) {
    fprintf(stderr, "%s%s\n", "Failed to open file: ", in_path);
    exit(-1);
  }

  LinkedList *input = create_linked_list();

  if (!read(inputf, input)) {
    fprintf(stderr, "%s%s\n", "Failed to read file: ", in_path);
    exit(-1);
  }
  fclose(inputf);

  if (!prepare_sym_table(input, sym_table)) {
    fprintf(stderr, "%s\n", "Failed to prepare symbol table.");
    exit(-1);
  }

  LinkedList *output = create_linked_list();

  if (!assemble(input, output, sym_table)) {
    fprintf(stderr, "%s\n", "Failed to assemble.");
    exit(-1);
  }

  FILE *outputf = fopen(out_path, "w");
  if (outputf == NULL) {
    fprintf(stderr, "%s%s\n", "Failed to open file: ", out_path);
    exit(-1);
  }

  if (!write(outputf, output)) {
    fprintf(stderr, "%s%s\n", "Failed to write file: ", out_path);
    exit(-1);
  }
  fclose(outputf);

  return 0;
}
