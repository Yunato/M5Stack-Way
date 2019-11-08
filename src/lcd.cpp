#include "lcd.hpp"

const int Lcd::LCD_HEIGHT  = 240;
const int Lcd::LCD_WIDTH   = 320;
const int Lcd::ROW_LENGTH  = 24;
const int Lcd::CHAR_LENGTH = LCD_WIDTH / 17;

/**
 * @brief Constructor
 * @details Setup
 */
Lcd::Lcd(void) {
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.setTextSize(3);
  M5.Lcd.setBrightness(100);
}

/**
 * @brief Destructor
 */
Lcd::~Lcd(void) {}

/**
 * @brief Reset screen
 */
void Lcd::reset(void) {
  M5.Lcd.fillScreen(BLACK);
}

/**
 * @breif String splitting
 * @param s1 target
 * @param s2 delimiter
 * @return string array
 */
char* Lcd::strtoks(char *s1, const char *s2) {
	static char *str = 0;
	register int i,j;

	if(s1)
		str = s1;
	else
		s1 = str;
	if(!s1)
		return 0;

	j = strlen(s2);
	while(1){
		if(!*str){
			str = 0;
			return s1;
		}

		for(i = 0; i < j; i++){
			if(*str == s2[i]){
				*str++ = 0;
				return s1;
			}
		}
		str++;
	}
}

/**
 * @breif Determine the display position of the horizontal axis
 * @param str target
 * @return the display position of the horizontal axis
 */
int Lcd::getXPosition(const char* str) {
	return LCD_WIDTH / 2 - (strlen(str) / 2) * CHAR_LENGTH;
}

/**
 * @breif Draw on lcd
 * @param str target
 */
void Lcd::draw(const char *str) {
	reset();

	int lenStr = 0, cnt = 0, lenCnt = 0, index = 0;
	while(str[index] != '\0'){
		lenStr++;
		if(str[index++] != '\n')
			cnt++;
	}
	if((lenStr - cnt + 1) > 8)
		lenCnt = 0;
	else
		lenCnt = 5 - (lenStr - cnt + 1) / 2;

	char* ptr;
	char buff[512];
	strcpy(buff, str);
	ptr = strtoks(buff, "\n");
  M5.Lcd.setCursor(getXPosition(ptr), ROW_LENGTH * (lenCnt++));
  M5.Lcd.print(ptr);
	while((ptr = strtoks(NULL, "\n")) != NULL){
    M5.Lcd.setCursor(getXPosition(ptr), ROW_LENGTH * (lenCnt++));
    M5.Lcd.print(ptr);
		str = NULL;
	}
}
