/*
 * hw.c
 *
 *  Created on: Jun 13, 2021
 *      Author: baram
 */

#include "hw.h"



static const firm_ver_t boot_ver __attribute__((section(".version"))) = 
{
  .magic_number = VERSION_MAGIC_NUMBER,
  .version_str  = _DEF_FIRMWATRE_VERSION,
  .name_str     = _DEF_BOARD_NAME,
};


static void tagInfo(void);


static const firm_tag_t *p_firm_tag = (firm_tag_t *)FLASH_ADDR_FW_TAG;
static const firm_ver_t *p_firm_ver = (firm_ver_t *)FLASH_ADDR_FW_VER;

static const firm_tag_t *p_update_tag = (firm_tag_t *)FLASH_ADDR_UPDATE_TAG;
static const firm_ver_t *p_update_ver = (firm_ver_t *)FLASH_ADDR_UPDATE_VER;




bool hwInit(void)
{  

  cliInit();
  resetInit();
  logInit();
  ledInit();
  uartInit();
  uartOpen(_DEF_UART1, 115200);
  logOpen(_DEF_UART1, 115200);
  
  flashInit();

  logPrintf("[ Bootloader Begin... ]\r\n");
  logPrintf("Booting..Name \t\t: %s\r\n", _DEF_BOARD_NAME);
  logPrintf("Booting..Ver  \t\t: %s\r\n", _DEF_FIRMWATRE_VERSION);
  logPrintf("Clk sys  \t\t: %d\r\n", clock_get_hz(clk_sys));
  logPrintf("Clk peri \t\t: %d\r\n", clock_get_hz(clk_peri));
  logPrintf("Clk usb  \t\t: %d\r\n", clock_get_hz(clk_usb));
  logPrintf("Clk adc  \t\t: %d\r\n", clock_get_hz(clk_adc));
  logPrintf("Clk rtc  \t\t: %d\r\n", clock_get_hz(clk_rtc));
  logPrintf("Clk timer\t\t: %d\r\n", clock_get_hz(clk_ref));
  logPrintf("\n");
  logPrintf("Reset Mode\t\t: %s\r\n", resetGetBootModeMsg());
  logPrintf("Reset Count\t\t: %d\r\n", resetGetCount());
  logPrintf("Boot Ver Addr\t\t: 0x%X\r\n", (int)&boot_ver);
  logPrintf("Firm Ver Addr\t\t: 0x%X\r\n", (int)p_firm_ver);
  logPrintf("\n");

  tagInfo();

  return true;
}

void tagInfo(void)
{
  if (p_firm_tag->magic_number == TAG_MAGIC_NUMBER)
  {
    logPrintf("Tag fw addr \t\t: 0x%X\r\n", p_firm_tag->fw_addr);
    logPrintf("Tag fw size \t\t: 0x%X\r\n", p_firm_tag->fw_size);
    logPrintf("Tag fw crc  \t\t: 0x%X\r\n", p_firm_tag->fw_crc);
  }
  else
  {
    logPrintf("Tag fw   \t\t: Empty\r\n");
  }  
  
  logPrintf("\n");

  if (p_update_tag->magic_number == TAG_MAGIC_NUMBER)
  {
    logPrintf("Tag update addr \t: 0x%X\r\n", p_update_tag->fw_addr);
    logPrintf("Tag update size \t: 0x%X\r\n", p_update_tag->fw_size);
    logPrintf("Tag update crc  \t: 0x%X\r\n", p_update_tag->fw_crc);
  }
  else
  {
    logPrintf("Tag update \t\t: Empty\r\n");
  }  

  logPrintf("\n");

  if (p_firm_ver->magic_number == VERSION_MAGIC_NUMBER)
  {
    logPrintf("Firm Name \t\t: %s\r\n", p_firm_ver->name_str);
    logPrintf("Firm Ver  \t\t: %s\r\n", p_firm_ver->version_str);
  }
  else
  {
    logPrintf("Firm Name \t\t: Empty\r\n");
    logPrintf("Firm Ver  \t\t: Empty\r\n");
  }  


  if (p_update_ver->magic_number == VERSION_MAGIC_NUMBER)
  {
    logPrintf("Update Name \t\t: %s\r\n", p_update_ver->name_str);
    logPrintf("Update Ver  \t\t: %s\r\n", p_update_ver->version_str);
  }
  else
  {
    logPrintf("Update Name \t\t: Empty\r\n");
    logPrintf("Update Ver  \t\t: Empty\r\n");
  }   
}

void jumpToFw(void)
{
  void (**jump_func)(void) = (void (**)(void))(FLASH_ADDR_FW_VECTOR + 4); 


  bspDeInit();
  __set_MSP(*(uint32_t *)(FLASH_ADDR_FW_VECTOR));
  scb_hw->vtor = FLASH_ADDR_FW_VECTOR;


  resetSetBootMode(RESET_MODE_FW);

  (*jump_func)();
}