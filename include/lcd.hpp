#ifndef LCD_H_
#define LCD_H_

#include <M5Stack.h>

class Lcd {
private:
	static const int LCD_HEIGHT;
	static const int LCD_WIDTH;
	static const int ROW_LENGTH;
	static const int CHAR_LENGTH;

public:
  Lcd(void);
  ~Lcd(void);

  void reset();
	char *strtoks(char*, const char*);
	int getXPosition(const char*);
	void draw(const char*);
};

#endif
