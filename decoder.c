#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    printf("Usage: %s <filename>\n", argv[0]);
    return 1;
  }

  FILE *file = fopen(argv[1], "rb");
  if (!file)
  {
    printf("Error: Could not open file %s\n", argv[1]);
    return 1;
  }

  fseek(file, 0, SEEK_END);
  long file_size = ftell(file);
  fseek(file, 0, SEEK_SET);

  struct
  {
    const unsigned char opcode;
    const char *mnemonic;
  } table[] = {
      {0b100010, "mov"},
  };

  struct
  {
    const unsigned char opcode;
    const char *reg_name;
  } registers_w0[] = {
      {0b000, "al"},
      {0b001, "cl"},
      {0b010, "dl"},
      {0b011, "bl"},
      {0b100, "ah"},
      {0b101, "ch"},
      {0b110, "dh"},
      {0b111, "bh"},
  };

  struct
  {
    const unsigned char opcode;
    const char *reg_name;
  } registers_w1[] = {
      {0b000, "ax"},
      {0b001, "cx"},
      {0b010, "dx"},
      {0b011, "bx"},
      {0b100, "sp"},
      {0b101, "bp"},
      {0b110, "si"},
      {0b111, "di"},
  };

  unsigned char *buffer = (unsigned char *)malloc(file_size);
  if (!buffer)
  {
    printf("Error: Could not allocate memory for file %s\n", argv[1]);
    fclose(file);
    return 1;
  }

  fread(buffer, 1, file_size, file);

  for (int i = 0; i < file_size; i += 2)
  {
    if (i % 2 == 0)
    {
      printf("\n");
    }

    unsigned char opcode = buffer[i] >> 2 & 0b111111;
    unsigned char d = buffer[i] >> 1 & 0b1;
    unsigned char w = buffer[i] & 0b1;

    unsigned char mod = buffer[i + 1] >> 6 & 0b11;
    unsigned char reg = buffer[i + 1] >> 3 & 0b111;
    unsigned char rm = buffer[i + 1] & 0b111;
    if (opcode == table[0].opcode)
    {
      if (w == 0)
      {
        printf("%s %s, %s", table[0].mnemonic, registers_w0[rm].reg_name, registers_w0[reg].reg_name);
      }
      else
      {
        printf("%s %s, %s", table[0].mnemonic, registers_w1[rm].reg_name, registers_w1[reg].reg_name);
      }
    }
  }

  free(buffer);
  fclose(file);
  return 0;
}
