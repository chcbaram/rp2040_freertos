#include "main.h"


static void mainThread(void *params);



int main() 
{
  bspInit();


  xTaskCreate(mainThread, "mainThread", _HW_DEF_RTOS_THREAD_MEM_MAIN, NULL, _HW_DEF_RTOS_THREAD_PRI_MAIN, NULL);
  
  vTaskStartScheduler();

  return 0;
}

void mainThread(void *params)
{
  (void)params;

  hwInit();
  apInit();
  apMain();
}