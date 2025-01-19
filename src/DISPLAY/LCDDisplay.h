#include <Arduino.h>
//include dependancies
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

void oneTopOneBottomDisplay(String DMDTopLine, String DMDBottomLine);
void resetDisplay();
void DisplayBootModeFunction(void * pvParameters);
void DisplayControllerFunction(void * pvParameters);
void displayClearLine(int line);
void displayClearAllLines();
void displayNewScore(String displayScore);
void displayRealScore(int score);

//setup a task handler;
TaskHandle_t DisplayController;
TaskHandle_t DisplayBootMode;
TaskHandle_t DisplayAttractMode;
TaskHandle_t DisplayGameMode;
TaskHandle_t DisplayEndOfBallMode;
TaskHandle_t DisplayEndOfGameMode;
TaskHandle_t DisplayDiagnosticsMode;

#define I2C_SDA 13
#define I2C_SCL 4

LiquidCrystal_I2C lcd(0x27, 20, 4); // set the LCD address to 0x27 for a 20 chars and 4 line display


void DisplayControllerFunction(void * pvParameters)
{
  resetDisplay();  
  for(;;){
    if(g_myPinballGame.isGameActive() == true)
	{

		lcd.setCursor(0,1);
		lcd.print(g_myPinballGame.getScoreDisplay(1));

		lcd.setCursor(0,3);
		lcd.print(g_myPinballGame.getScoreDisplay(3));

		lcd.setCursor(13,1);
		lcd.print(g_myPinballGame.getScoreDisplay(2));

		lcd.setCursor(13,3);
		lcd.print(g_myPinballGame.getScoreDisplay(4));

		lcd.setCursor(7,2);
		lcd.print(g_myPinballGame.getPlayerDisplay());

		lcd.setCursor(11,2);
		lcd.print(g_myPinballGame.getBallDisplay());
	
	}else{
		String DMDTopText = g_myPinballGame.getDMDTopLine();
		String DMDBottomText = g_myPinballGame.getDMDBottomLine();

		ScoreboardTText = DMDTopText;
		ScoreboardBText = DMDBottomText; 
		lcd.setCursor(0,0);
		if(ScoreboardTText.length() < 20)
		{
			//we need to pad
			int initialLen = ScoreboardTText.length();
			for(int n = initialLen; n <= 20; n++)
			{
				ScoreboardTText = ScoreboardTText + " ";
			}
		}
		if(ScoreboardBText.length() < 20)
		{
			//we need to pad
			int initialLen = ScoreboardBText.length();
			for(int n = initialLen; n <= 20; n++)
			{
				ScoreboardBText = ScoreboardBText + " ";
			}
		}
		lcd.print(ScoreboardTText);
		lcd.setCursor(0,2);
		lcd.print(ScoreboardBText);
	}
	
    vTaskDelay(50);       
  }

}

void resetDisplay() //to be done when changing layout on the display
{
    displayClearLine(0);
	displayClearLine(1);
	displayClearLine(2);
	displayClearLine(3);
}
void oneTopOneBottomDisplay(String DMDTopLine, String DMDBottomLine) // Simple layout with a top line and a bottom line.
{
  /*DMDDisplay.setZone(0,12,23); // Make zone 0 the whole top display
  char scoreboardTChar[40];
  DMDTopLine.toCharArray(scoreboardTChar, sizeof(scoreboardTChar));
  DMDDisplay.displayZoneText(0,scoreboardTChar,PA_CENTER,0,0,PA_NO_EFFECT,PA_NO_EFFECT);
  
  DMDDisplay.setZone(1,0,11); // Make zone 1 the whole bottom display
  char scoreboardBChar[40];
  DMDBottomLine.toCharArray(scoreboardBChar, sizeof(scoreboardBChar));
  DMDDisplay.displayZoneText(1,scoreboardBChar,PA_CENTER,0,0,PA_NO_EFFECT,PA_NO_EFFECT);

  DMDDisplay.displayAnimate();*/
}

void displayClearAllLines()
{
	displayClearLine(0);
	displayClearLine(1);
	displayClearLine(2);
	displayClearLine(3);
}

void displayClearLine(int line)
{
	lcd.setCursor(0,line);
	lcd.print("                    ");
}

void displayNewScore(String displayScore)
{
	lcd.setCursor(0,0);
	lcd.print(displayScore);
}

void displayRealScore(int score)
{
	lcd.setCursor(0,3);
	lcd.print(score);
}

String createScore(int score)
{
	String scoreString = String(score);
	if (score < 1000)
	{
		return String(score);	
	}
	if(score < 1000000)
	{
		//we need to split the string
		int scoreStringLength = String(score).length();
		int startIndex = 0;
		String thousands = String(score).substring(startIndex, scoreStringLength-3); //good
		startIndex = thousands.length();
		String hundreds = String(score).substring(startIndex, startIndex+3);
		String returnString = thousands + "," + hundreds;
		return returnString;	
	}
	if(score < 100000000)
	{
		//we need to split the string
		int scoreStringLength = String(score).length();
		int startIndex = 0;
		String millions = String(score).substring(startIndex, scoreStringLength-6); //we need to remove the 000,000
		startIndex = millions.length();
		String thousands = String(score).substring(startIndex, startIndex+3);
		startIndex = thousands.length()+millions.length();
		String hundreds = String(score).substring(startIndex, startIndex+3);
		String returnString = millions + "," + thousands + "," + hundreds;
		return returnString;	
	}
	return scoreString;

}

