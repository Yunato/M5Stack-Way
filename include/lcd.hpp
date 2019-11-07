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

  void Reset();
	char *Strtoks(char*, const char*);
	int GetXPosition(const char*);
	void Draw(const char*);
};

#endif
