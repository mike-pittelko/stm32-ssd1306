#include "ssd1306.h"
#include <string.h>
#include <stdio.h>

void ssd1306_TestBorder() {
    ssd1306_Fill(Black);
   
    uint32_t start = HAL_GetTick();
    uint32_t end = start;
    do {

        ssd1306_DrawRectangle(1,1,SSD1306_WIDTH-1,SSD1306_HEIGHT-1, White);
        ssd1306_UpdateScreen();
    
        HAL_Delay(5);
        end = HAL_GetTick();
    } while((end - start) < 2000);
   
}

void ssd1306_TestFonts() {
    ssd1306_Fill(Black);
    ssd1306_DrawRectangle(1,1,SSD1306_WIDTH-1,SSD1306_HEIGHT-1, White);

    ssd1306_SetCursor(1, 1);
    ssd1306_WriteString("Font 11x18-1", Font_11x18, White);
    ssd1306_SetCursor(1, 1+ (18*1));
    ssd1306_WriteString("Font 11x18-2", Font_11x18, White);
    ssd1306_SetCursor(1, 1+ (18*2));
    ssd1306_WriteString("Font 11x18-3", Font_11x18, White);
    ssd1306_SetCursor(1, 1+ (18*3));
    ssd1306_WriteString("Font 11x18-4", Font_11x18, White);

/*    ssd1306_WriteString("Font 16x26", Font_16x26, White);
    ssd1306_SetCursor(0, 26+3);
    ssd1306_WriteString("Font 11x18", Font_11x18, White);
    ssd1306_SetCursor(0, 26+4+18);
    ssd1306_WriteString("Font 7x10", Font_7x10, White);
    ssd1306_SetCursor(0, 26+4+18+4+10);
    ssd1306_WriteString("Font 6x8", Font_6x8, White);
*/    ssd1306_UpdateScreen();
}

void ssd1306_TestFPS() {
    ssd1306_Fill(White);
   
    uint32_t start = HAL_GetTick();
    uint32_t end = start;
    int fps = 0;
    char message[] = "ABCDEFGHIJK";
   
    ssd1306_SetCursor(0,0);
    ssd1306_WriteString("Testing...", Font_11x18, Black);
   
    do {
        ssd1306_SetCursor(0, 18);
        ssd1306_WriteString(message, Font_11x18, Black);
        ssd1306_UpdateScreen();
       
        char ch = message[0];
        memmove(message, message+1, sizeof(message)-2);
        message[sizeof(message)-2] = ch;

        fps++;
        end = HAL_GetTick();
    } while((end - start) < 4000);
   

    char buff[64];
    fps = (float)fps / ((end - start) / 1000.0);
    snprintf(buff, sizeof(buff), "~%d FPS", fps);
   
    ssd1306_Fill(White);
    ssd1306_SetCursor(2, 18);
    ssd1306_WriteString(buff, Font_11x18, Black);
    ssd1306_UpdateScreen();
    HAL_Delay(1000);
}

void ssd1306_TestAll() {
    ssd1306_Init();
    ssd1306_Fill(Black);
    ssd1306_TestFPS();
    HAL_Delay(3000);
    ssd1306_TestBorder();
    ssd1306_TestFonts();
}
