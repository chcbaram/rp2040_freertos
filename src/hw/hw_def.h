#ifndef SRC_HW_HW_DEF_H_
#define SRC_HW_HW_DEF_H_


#include "bsp.h"


#define _DEF_FIRMWATRE_VERSION    "V220702R1"
#define _DEF_BOARD_NAME           "RP2040_BOOT"



#define _HW_DEF_RTOS_MEM_SIZE(x)              ((x)/1)


#define _HW_DEF_RTOS_THREAD_PRI_MAIN          ( tskIDLE_PRIORITY + 1UL )
#define _HW_DEF_RTOS_THREAD_PRI_CLI           ( tskIDLE_PRIORITY + 1UL )

#define _HW_DEF_RTOS_THREAD_MEM_MAIN          _HW_DEF_RTOS_MEM_SIZE( 4*1024)
#define _HW_DEF_RTOS_THREAD_MEM_CLI           _HW_DEF_RTOS_MEM_SIZE( 6*1024)



#define _USE_HW_FLASH
#define _USE_HW_RESET
#define _USE_HW_RTOS


#define _USE_HW_LED
#define      HW_LED_MAX_CH          1

#define _USE_HW_UART
#define      HW_UART_MAX_CH         1


#define _USE_HW_CLI
#define      HW_CLI_CMD_LIST_MAX    16
#define      HW_CLI_CMD_NAME_MAX    16
#define      HW_CLI_LINE_HIS_MAX    4
#define      HW_CLI_LINE_BUF_MAX    64

#define _USE_HW_LOG
#define      HW_LOG_CH              _DEF_UART1
#define      HW_LOG_BOOT_BUF_MAX    1024
#define      HW_LOG_LIST_BUF_MAX    1024

#define _USE_HW_CMD
#define      HW_CMD_MAX_DATA_LENGTH (1024+8)


#define FLASH_BOOT_ADDR             0x10000000
#define FLASH_BOOT_SIZE             (128*1024)           



#define FLASH_IMAGE_FW              0x10020000
#define FLASH_IMAGE_UPDATE          0x10200000
#define FLASH_IMAGE_SIZE            (2*1024*1024)

#define FLASH_ADDR_START            0x10020000
#define FLASH_ADDR_END              (FLASH_ADDR_START + (2048-128)*1024)


#define FLASH_OFFSET_FW_TAG         0x00000000
#define FLASH_OFFSET_FW_START       0x00000400
#define FLASH_OFFSET_FW_VECTOR      0x00000500
#define FLASH_OFFSET_FW_VER         0x00000800

#define FLASH_ADDR_FW_TAG           (FLASH_IMAGE_FW + FLASH_OFFSET_FW_TAG   )
#define FLASH_ADDR_FW_START         (FLASH_IMAGE_FW + FLASH_OFFSET_FW_START )
#define FLASH_ADDR_FW_VECTOR        (FLASH_IMAGE_FW + FLASH_OFFSET_FW_VECTOR)
#define FLASH_ADDR_FW_VER           (FLASH_IMAGE_FW + FLASH_OFFSET_FW_VER   )

#define FLASH_ADDR_UPDATE_TAG       (FLASH_IMAGE_UPDATE + FLASH_OFFSET_FW_TAG   )
#define FLASH_ADDR_UPDATE_START     (FLASH_IMAGE_UPDATE + FLASH_OFFSET_FW_START )
#define FLASH_ADDR_UPDATE_VECTOR    (FLASH_IMAGE_UPDATE + FLASH_OFFSET_FW_VECTOR)
#define FLASH_ADDR_UPDATE_VER       (FLASH_IMAGE_UPDATE + FLASH_OFFSET_FW_VER   )



#endif /* SRC_HW_HW_DEF_H_ */