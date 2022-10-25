#include "ap.h"





static void cliInfo(cli_args_t *args);
static void cliThread(void *args);








void apInit(void)
{

  cliOpen(_DEF_UART1, 115200);

  cliAdd("info", cliInfo);
  logBoot(false);

  xTaskCreate(cliThread, "cliThread", _HW_DEF_RTOS_THREAD_MEM_CLI, NULL, _HW_DEF_RTOS_THREAD_PRI_CLI, NULL);
}

void apMain(void)
{
  while(1)
  {
    ledToggle(_DEF_LED1);
    delay(500);
  }
}

void cliThread(void *args)
{
  while(1)
  {
    cliMain();
    delay(1);
  }
}

void cliInfo(cli_args_t *args)
{
  bool ret = false;

  if (args->argc == 1 && args->isStr(0, "flash"))
  {
    extern const uint32_t __flash_binary_start;
    extern const uint32_t __flash_binary_end;

    cliPrintf("Flash FW Start : 0x%X\n", &__flash_binary_start);
    cliPrintf("Flash FW End   : 0x%X\n", &__flash_binary_end);
    cliPrintf("Flash FW Size  : %d KB\n", ((uint32_t)&__flash_binary_end - (uint32_t)&__flash_binary_start)/1024);

    ret = true;
  }

  if (args->argc == 1 && args->isStr(0, "jump"))
  {
    cliPrintf("JumpToFw()\n");
    delay(50);

    jumpToFw();
    ret = true;
  }

  if (args->argc == 1 && args->isStr(0, "task"))
  {
    uint8_t buffer[1024];

    vTaskList((char *)buffer);
    cliPrintf("\r\n");
    cliPrintf("Name          State  Priority  Stack   Num\r\n");
    cliPrintf("******************************************\r\n");
    cliPrintf((char *)buffer);
    cliPrintf("******************************************\r\n");
    cliPrintf("Free Heap: %d\r\n", xPortGetMinimumEverFreeHeapSize());
    ret = true;
  }

  if (ret != true)
  {
    cliPrintf("info flash\n");
    cliPrintf("info task\n");
  }
}
