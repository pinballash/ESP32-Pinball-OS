//create PinballLED class instances 
#include <Arduino.h>
#include <ArduinoJson.h> 
#include <Effortless_SPIFFS.h>
#include "PinballLED.h"

//set up global switchObjects so they can be accessed later
PinballLED led_0(0);
PinballLED led_1(1);
PinballLED led_2(2);
PinballLED led_3(3);
PinballLED led_4(4);
PinballLED led_5(5);
PinballLED led_6(6);
PinballLED led_7(7);
PinballLED led_8(8);
PinballLED led_9(9);
PinballLED led_10(10);
PinballLED led_11(11);
PinballLED led_12(12);
PinballLED led_13(13);
PinballLED led_14(14);
PinballLED led_15(15);
PinballLED led_16(16);
PinballLED led_17(17);
PinballLED led_18(18);
PinballLED led_19(19);
PinballLED led_20(20);
PinballLED led_21(21);
PinballLED led_22(22);
PinballLED led_23(23);
PinballLED led_24(24);
PinballLED led_25(25);
PinballLED led_26(26);
PinballLED led_27(27);
PinballLED led_28(28);
PinballLED led_29(29);
PinballLED led_30(30);
PinballLED led_31(31);
PinballLED led_32(32);
PinballLED led_33(33);
PinballLED led_34(34);
PinballLED led_35(35);
PinballLED led_36(36);
PinballLED led_37(37);
PinballLED led_38(38);
PinballLED led_39(39);
PinballLED led_40(40);
PinballLED led_41(41);
PinballLED led_42(42);
PinballLED led_43(43);
PinballLED led_44(44);
PinballLED led_45(45);
PinballLED led_46(46);
PinballLED led_47(47);
PinballLED led_48(48);
PinballLED led_49(49);
PinballLED led_50(50);
PinballLED led_51(51);
PinballLED led_52(52);
PinballLED led_53(53);
PinballLED led_54(54);
PinballLED led_55(55);
PinballLED led_56(56);
PinballLED led_57(57);
PinballLED led_58(58);
PinballLED led_59(59);
PinballLED led_60(60);
PinballLED led_61(61);
PinballLED led_62(62);
PinballLED led_63(63);
PinballLED led_64(64);
PinballLED led_65(65);
PinballLED led_66(66);
PinballLED led_67(67);
PinballLED led_68(68);
PinballLED led_69(69);
PinballLED led_70(70);
PinballLED led_71(71);
PinballLED led_72(72);
PinballLED led_73(73);
PinballLED led_74(74);
PinballLED led_75(75);
PinballLED led_76(76);
PinballLED led_77(77);
PinballLED led_78(78);
PinballLED led_79(79);
PinballLED led_80(80);
PinballLED led_81(81);
PinballLED led_82(82);
PinballLED led_83(83);
PinballLED led_84(84);
PinballLED led_85(85);
PinballLED led_86(86);
PinballLED led_87(87);
PinballLED led_88(88);
PinballLED led_89(89);
PinballLED led_90(90);
PinballLED led_91(91);
PinballLED led_92(92);
PinballLED led_93(93);
/*no need to waste space with unused objects*/
/*PinballLED led_94(94);
PinballLED led_95(95);
PinballLED led_96(96);
PinballLED led_97(97);
PinballLED led_98(98);
PinballLED led_99(99);
PinballLED led_100(100);
PinballLED led_101(101);
PinballLED led_102(102);
PinballLED led_103(103);
PinballLED led_104(104);
PinballLED led_105(105);
PinballLED led_106(106);
PinballLED led_107(107);
PinballLED led_108(108);
PinballLED led_109(109);
PinballLED led_110(110);
PinballLED led_111(111);
PinballLED led_112(112);
PinballLED led_113(113);
PinballLED led_114(114);
PinballLED led_115(115);
PinballLED led_116(116);
PinballLED led_117(117);
PinballLED led_118(118);
PinballLED led_119(119);
PinballLED led_120(120);
PinballLED led_121(121);
PinballLED led_122(122);
PinballLED led_123(123);
PinballLED led_124(124);
PinballLED led_125(125);
PinballLED led_126(126);
PinballLED led_127(127);
PinballLED led_128(128);
PinballLED led_129(129);
PinballLED led_130(130);
PinballLED led_131(131);
PinballLED led_132(132);
PinballLED led_133(133);
PinballLED led_134(134);
PinballLED led_135(135);
PinballLED led_136(136);
PinballLED led_137(137);
PinballLED led_138(138);
PinballLED led_139(139);
PinballLED led_140(140);
PinballLED led_141(141);
PinballLED led_142(142);
PinballLED led_143(143);
PinballLED led_144(144);
PinballLED led_145(145);
PinballLED led_146(146);
PinballLED led_147(147);
PinballLED led_148(148);
PinballLED led_149(149);
PinballLED led_150(150);
PinballLED led_151(151);
PinballLED led_152(152);
PinballLED led_153(153);
PinballLED led_154(154);
PinballLED led_155(155);
PinballLED led_156(156);
PinballLED led_157(157);
PinballLED led_158(158);
PinballLED led_159(159);
PinballLED led_160(160);
PinballLED led_161(161);
PinballLED led_162(162);
PinballLED led_163(163);
PinballLED led_164(164);
PinballLED led_165(165);
PinballLED led_166(166);
PinballLED led_167(167);
PinballLED led_168(168);
PinballLED led_169(169);
PinballLED led_170(170);
PinballLED led_171(171);
PinballLED led_172(172);
PinballLED led_173(173);
PinballLED led_174(174);
PinballLED led_175(175);
PinballLED led_176(176);
PinballLED led_177(177);
PinballLED led_178(178);
PinballLED led_179(179);
PinballLED led_180(180);
PinballLED led_181(181);
PinballLED led_182(182);
PinballLED led_183(183);
PinballLED led_184(184);
PinballLED led_185(185);
PinballLED led_186(186);
PinballLED led_187(187);
PinballLED led_188(188);
PinballLED led_189(189);
PinballLED led_190(190);
PinballLED led_191(191);
PinballLED led_192(192);
PinballLED led_193(193);
PinballLED led_194(194);
PinballLED led_195(195);
PinballLED led_196(196);
PinballLED led_197(197);
PinballLED led_198(198);
PinballLED led_199(199);
PinballLED led_200(200);
PinballLED led_201(201);
PinballLED led_202(202);
PinballLED led_203(203);
PinballLED led_204(204);
PinballLED led_205(205);
PinballLED led_206(206);
PinballLED led_207(207);
PinballLED led_208(208);
PinballLED led_209(209);
PinballLED led_210(210);
PinballLED led_211(211);
PinballLED led_212(212);
PinballLED led_213(213);
PinballLED led_214(214);
PinballLED led_215(215);
PinballLED led_216(216);
PinballLED led_217(217);
PinballLED led_218(218);
PinballLED led_219(219);
PinballLED led_220(220);
PinballLED led_221(221);
PinballLED led_222(222);
PinballLED led_223(223);
PinballLED led_224(224);
PinballLED led_225(225);
PinballLED led_226(226);
PinballLED led_227(227);
PinballLED led_228(228);
PinballLED led_229(229);
PinballLED led_230(230);
PinballLED led_231(231);
PinballLED led_232(232);
PinballLED led_233(233);
PinballLED led_234(234);
PinballLED led_235(235);
PinballLED led_236(236);
PinballLED led_237(237);
PinballLED led_238(238);
PinballLED led_239(239);
PinballLED led_240(240);
PinballLED led_241(241);
PinballLED led_242(242);
PinballLED led_243(243);
PinballLED led_244(244);
PinballLED led_245(245);
PinballLED led_246(246);
PinballLED led_247(247);
PinballLED led_248(248);
PinballLED led_249(249);
PinballLED led_250(250);
PinballLED led_251(251);
PinballLED led_252(252);
PinballLED led_253(253);
PinballLED led_254(254);*/

typedef struct {
  byte ledNum; 
  PinballLED *ledObject;
} LEDAttributes;
typedef LEDAttributes LEDList[];

// List of Swithches and their object
LEDList LEDs = {
  //no, PinballLED
  {0,&led_0},
  {1,&led_1},
  {2,&led_2},
  {3,&led_3},
  {4,&led_4},
  {5,&led_5},
  {6,&led_6},
  {7,&led_7},
  {8,&led_8},
  {9,&led_9},
  {10,&led_10},
  {11,&led_11},
  {12,&led_12},
  {13,&led_13},
  {14,&led_14},
  {15,&led_15},
  {16,&led_16},
  {17,&led_17},
  {18,&led_18},
  {19,&led_19},
  {20,&led_20},
  {21,&led_21},
  {22,&led_22},
  {23,&led_23},
  {24,&led_24},
  {25,&led_25},
  {26,&led_26},
  {27,&led_27},
  {28,&led_28},
  {29,&led_29},
  {30,&led_30},
  {31,&led_31},
  {32,&led_32},
  {33,&led_33},
  {34,&led_34},
  {35,&led_35},
  {36,&led_36},
  {37,&led_37},
  {38,&led_38},
  {39,&led_39},
  {40,&led_40},
  {41,&led_41},
  {42,&led_42},
  {43,&led_43},
  {44,&led_44},
  {45,&led_45},
  {46,&led_46},
  {47,&led_47},
  {48,&led_48},
  {49,&led_49},
  {50,&led_50},
  {51,&led_51},
  {52,&led_52},
  {53,&led_53},
  {54,&led_54},
  {55,&led_55},
  {56,&led_56},
  {57,&led_57},
  {58,&led_58},
  {59,&led_59},
  {60,&led_60},
  {61,&led_61},
  {62,&led_62},
  {63,&led_63},
  {64,&led_64},
  {65,&led_65},
  {66,&led_66},
  {67,&led_67},
  {68,&led_68},
  {69,&led_69},
  {70,&led_70},
  {71,&led_71},
  {72,&led_72},
  {73,&led_73},
  {74,&led_74},
  {75,&led_75},
  {76,&led_76},
  {77,&led_77},
  {78,&led_78},
  {79,&led_79},
  {80,&led_80},
  {81,&led_81},
  {82,&led_82},
  {83,&led_83},
  {84,&led_84},
  {85,&led_85},
  {86,&led_86},
  {87,&led_87},
  {88,&led_88},
  {89,&led_89},
  {90,&led_90},
  {91,&led_91},
  {92,&led_92}/*,
{93,&led_93},
{94,&led_94},
{95,&led_95},
{96,&led_96},
{97,&led_97},
{98,&led_98},
{99,&led_99},
{100,&led_100},
{101,&led_101},
{102,&led_102},
{103,&led_103},
{104,&led_104},
{105,&led_105},
{106,&led_106},
{107,&led_107},
{108,&led_108},
{109,&led_109},
{110,&led_110},
{111,&led_111},
{112,&led_112},
{113,&led_113},
{114,&led_114},
{115,&led_115},
{116,&led_116},
{117,&led_117},
{118,&led_118},
{119,&led_119},
{120,&led_120},
{121,&led_121},
{122,&led_122},
{123,&led_123},
{124,&led_124},
{125,&led_125},
{126,&led_126},
{127,&led_127},
{128,&led_128},
{129,&led_129},
{130,&led_130},
{131,&led_131},
{132,&led_132},
{133,&led_133},
{134,&led_134},
{135,&led_135},
{136,&led_136},
{137,&led_137},
{138,&led_138},
{139,&led_139},
{140,&led_140},
{141,&led_141},
{142,&led_142},
{143,&led_143},
{144,&led_144},
{145,&led_145},
{146,&led_146},
{147,&led_147},
{148,&led_148},
{149,&led_149},
{150,&led_150},
{151,&led_151},
{152,&led_152},
{153,&led_153},
{154,&led_154},
{155,&led_155},
{156,&led_156},
{157,&led_157},
{158,&led_158},
{159,&led_159},
{160,&led_160},
{161,&led_161},
{162,&led_162},
{163,&led_163},
{164,&led_164},
{165,&led_165},
{166,&led_166},
{167,&led_167},
{168,&led_168},
{169,&led_169},
{170,&led_170},
{171,&led_171},
{172,&led_172},
{173,&led_173},
{174,&led_174},
{175,&led_175},
{176,&led_176},
{177,&led_177},
{178,&led_178},
{179,&led_179},
{180,&led_180},
{181,&led_181},
{182,&led_182},
{183,&led_183},
{184,&led_184},
{185,&led_185},
{186,&led_186},
{187,&led_187},
{188,&led_188},
{189,&led_189},
{190,&led_190},
{191,&led_191},
{192,&led_192},
{193,&led_193},
{194,&led_194},
{195,&led_195},
{196,&led_196},
{197,&led_197},
{198,&led_198},
{199,&led_199},
{200,&led_200},
{201,&led_201},
{202,&led_202},
{203,&led_203},
{204,&led_204},
{205,&led_205},
{206,&led_206},
{207,&led_207},
{208,&led_208},
{209,&led_209},
{210,&led_210},
{211,&led_211},
{212,&led_212},
{213,&led_213},
{214,&led_214},
{215,&led_215},
{216,&led_216},
{217,&led_217},
{218,&led_218},
{219,&led_219},
{220,&led_220},
{221,&led_221},
{222,&led_222},
{223,&led_223},
{224,&led_224},
{225,&led_225},
{226,&led_226},
{227,&led_227},
{228,&led_228},
{229,&led_229},
{230,&led_230},
{231,&led_231},
{232,&led_232},
{233,&led_233},
{234,&led_234},
{235,&led_235},
{236,&led_236},
{237,&led_237},
{238,&led_238},
{239,&led_239},
{240,&led_240},
{241,&led_241},
{242,&led_242},
{243,&led_243},
{244,&led_244},
{245,&led_245},
{246,&led_246},
{247,&led_247},
{248,&led_248},
{249,&led_249},
{250,&led_250},
{251,&led_251},
{252,&led_252},
{253,&led_253},
{254,&led_254}*/
};




void createLedObjects()
{
  for ( byte led = 0; led < setting_leds ; led++) 
  {
        
    String LEDID = (String)led;
    byte LEDByte = led;

    //get the json file for this switchID
    String jsonConfig;
    String dataFile = "/ledConfig." + LEDID + ".json";
    //Serial.println("Opening " + dataFile);
    File file = SPIFFS.open(dataFile);
    while (file.available()) {
        // Extract each characters by one by one
        jsonConfig = file.readString();
    }
    //Serial.print("JSON Document is: ");
    //Serial.println(jsonConfig);
    if(jsonConfig == "")
    {
      //we need to send a dummy set of values
      jsonConfig = "{\"ledId\" : " + LEDID + ",\"ledName\":\"Unconfigured\",\"ledColour\":\"#000000\",\"ledIsOn\":\"false\",\"ledFlashSpeed\":\"0\"}";
    }
    //use the values in the json
    DynamicJsonDocument LEDJSON(2048);
    deserializeJson(LEDJSON,jsonConfig);
    PinballLED* thisLED = LEDs[LEDByte].ledObject;
    //sanitiseJSON
    bool ledIsOn = false;
    if(LEDJSON["ledIsOn"] == "true")
    {
      ledIsOn = true;
    }

    thisLED->setValues(LEDJSON["ledName"],LEDJSON["ledColour"],ledIsOn,LEDJSON["ledFlashSpeed"]);
    LEDJSON.clear();
  }//end 

}

//define LED Groups 
char ledArray_lowerrRing[] = {
  80,90,89,88,87,86
};
char ledArrayLowerRingCount = 6;
char ledArrayLowerRingCounter = 0;
bool cycleledLowerRing = true;

char ledArray_special[] = {
  9,23,49,77,80,83
};
char ledSecialCount = 6;

char ledArray_CHAMP[] = {
  82,19,20,21,78
};
char ledArrayCHAMPCount = 5;
bool cycleLedCHAMP = true;

char ledArray_EIGHTBALL[] = {
  36,44,45,46,47,48,56,57,58
};
char ledArrayEIGHTBALLCount = 9;
char ledArrayEIGHTBALLCounter = 0;
bool cycleLedEIGHTBALL = true;

char ledArray_LeftSide[] = {
  13,12,11,10,9,8
};
char ledArrayLeftSideCount = 6;
char ledArrayLeftSideCounter = 0;
bool cycleLedLeftSide = true;

char ledArray_RightSide[] = {
  27,26,25,24,23,22
};
char ledArrayRightSideCount = 6;
char ledArrayRightSideCounter = 0;
bool cycleLedRightSide = true;

char ledArray_PottedBalls[] = {
  62,64,67,70,72,73,75,68,63,65,66,69,71,74,76
};
char ledArrayPottedBallsCount = 15;
char ledArrayPottedBallsCounter = 0;
bool cycleLedPottedBalls = true;
bool ledArrayPottedBallsEven = true;


int row0[] = {93};
int row1[] = {88};
int row3[] = {89,87};
int row4[] = {90,86};
int row5[] = {80};
int row6[] = {81,79};
int row7[] = {83,82,78,77};
int row8[] = {68};
int row9[] = {63,65,66,69,71,74,76};
int row10[] = {63,64,67,70,72,73,75};

int* playfieldRows[10] = {row0, row1, row3, row4, row5, row6, row7, row8, row9, row10};
// Array to hold the size of each row 
int pfArraySize[10] = {1,1,2,2,1,2,4,1,7,7}, k = 0; 
int pfRowCounter = 0;
int pfRowCount = 11;

void LED_display_chase_pf()
{
  int* ptr = playfieldRows[pfRowCounter];
  for(int i = 0; i < pfArraySize[pfRowCounter]; i++)
  {
    
    PinballLED* thisCLed = LEDs[*ptr].ledObject;
     if(thisCLed->isOn() == false)
      {
        thisCLed->flashOnce(1); //cycle once a second second
      }
    ptr++;
  }
  pfRowCounter++;
  if(pfRowCounter == pfRowCount)
  {
    pfRowCounter = 0;
  }
}


bool LED_display_oddsAndEvens(char LED_ID_array[], char LED_array_length, bool isEven, int flashesPerSecond)
{
  bool isActioned = false;
  for(char ledId = 0; ledId < LED_array_length; ledId++)
    {
      if ((isEven == true) && (ledId % 2) == 0) //if number is even and we are workinh with even
      {
        PinballLED* thisCLed = LEDs[LED_ID_array[ledId]].ledObject;
        if(thisCLed->isOn() == false)
        {
          thisCLed->flashOnce(flashesPerSecond); 
          isActioned = true;
        }
      }else if ((isEven == false) && ((ledId % 2) != 0))//its an odd number and we are working with odd
      {
        
        PinballLED* thisCLed = LEDs[LED_ID_array[ledId]].ledObject;
        if(thisCLed->isOn() == false)
        {
          thisCLed->flashOnce(flashesPerSecond); 
          isActioned = true;
        }
      }
    }
    if(isActioned == true)
    {
      isEven = !isEven;
    }
    return isEven;
}

char LED_display_chase(char LED_ID_array[], char LED_array_length, int flashesPerSecond, char counter)
{
  PinballLED* thisCLed = LEDs[LED_ID_array[counter]].ledObject;
  //if(thisCLed->isOn() == false)
  //{
    thisCLed->flashOnce(flashesPerSecond); //cycle once a second second
  //}
  counter++;
  if(counter == LED_array_length)
  {
    counter = 0;
  }
  return counter;
}

void LED_display_flashBlock(char LED_ID_array[], char LED_array_length, int flashesPerSecond)
{
  for(char ledId = 0; ledId < LED_array_length; ledId++)
    {
      PinballLED* thisCLed = LEDs[LED_ID_array[ledId]].ledObject;
      if(thisCLed->isOn() == false)
      {
        thisCLed->flashOnce(flashesPerSecond); 
      }
    }
}