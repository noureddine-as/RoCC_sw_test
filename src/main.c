// int main(int argc, char** argv)
// {
// 	printf("Hello, WOrld!\n");

// 	return 99;
// }

#include "xcustom.h"




#define k_DO_WRITE 0
#define k_DO_READ 1
#define k_DO_LOAD 2
#define k_DO_ACCUM 3

#define XCUSTOM_ACC 0

#define doWrite(y, rocc_rd, data)                                       \
  ROCC_INSTRUCTION(XCUSTOM_ACC, y, data, rocc_rd, k_DO_WRITE);
#define doWrite1(y, rocc_rd, data)                                       \
  ROCC_INSTRUCTION(XCUSTOM_ACC, y, data, rocc_rd, k_DO_WRITE);
#define doRead(y, rocc_rd)                                              \
  ROCC_INSTRUCTION(XCUSTOM_ACC, y, 0, rocc_rd, k_DO_READ);
#define doLoad(y, rocc_rd, mem_addr)                                    \
  ROCC_INSTRUCTION(XCUSTOM_ACC, y, mem_addr, rocc_rd, k_DO_LOAD);
#define doAccum(y, rocc_rd, data) \
  ROCC_INSTRUCTION(XCUSTOM_ACC, y, data, rocc_rd, k_DO_ACCUM);

#define XCUSTOM_CHAR 2


#define XCUSTOM_TRANS 1

#define doTranslate(y, vaddr)                                \
ROCC_INSTRUCTION(XCUSTOM_TRANS, y, vaddr, 0, 0);


void assert(int cond)
{
  if(!cond){
  printf("[INFO] Condition failed\n");
	exit(99);}
}

int main() {

  unsigned long int data [] = {0xdead, 0xbeef, 0x0bad, 0xf00d}, y;

  unsigned short addr = 1;
  printf("[INFO] Write R[%d] = 0x%lx\n", addr, data[0]);
  doWrite(y, addr, data[0]);

  printf("[INFO] Read R[%d]\n", addr);
  doRead(y, addr);
  printf("[INFO]   Received 0x%lx (expected 0x%lx)\n", y, data[0]);
  assert(y == data[0]);

  unsigned long int data_accum = -data[0] + data[1];
  printf("[INFO] Accum R[%d] with 0x%lx\n", addr, data_accum);
  doAccum(y, addr, data_accum);
  assert(y == data[0]);

  printf("[INFO] Read R[%d]\n", addr);
  doRead(y, addr);
  printf("[INFO]   Received 0x%lx (expected 0x%lx)\n", y, data[1]);
  assert(y == data[1]);

  unsigned long int data_addr;
  doTranslate(data_addr, &data[2]);
  printf("[INFO] Load 0x%lx (virt: 0x%p, phys: 0x%p) via L1 virtual address\n",
         data[2], &data[2], (void *) data_addr);
  doLoad(y, addr, &data[2]);
  assert(y == data[1]);

  printf("[INFO] Read R[%d]\n", addr);
  doRead(y, addr);
  printf("[INFO]   Received 0x%lx (expected 0x%lx)\n", y, data[2]);
  assert(y == data[2]);



  return 0;
}