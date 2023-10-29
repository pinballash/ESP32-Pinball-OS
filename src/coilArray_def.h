//create PinballCoil class instances
PinballCoil c_flipper_left("c_flipper_left",0,0,0,20);
PinballCoil c_flipper_right("c_flipper_right",0,1,0,20);
PinballCoil c_pop_left("c_pop_left",0,2,50,100);
PinballCoil c_pop_right("c_pop_right",0,3,50,100);
PinballCoil c_sling_left("c_sling_left",0,4,50,100);
PinballCoil c_sling_right("c_sling_right",0,5,50,100);
PinballCoil c_saucer_kicker("c_saucer_kicker",0,6,400,2000);
PinballCoil c_drop_1_2("c_drop_1_2",0,7,500,2000);
PinballCoil c_drop_3("c_drop_3",1,0,200,2000);
PinballCoil c_drop_4_5("c_drop_4_5",1,1,200,2000);
PinballCoil c_drop_6("c_drop_6",1,2,200,2000);
PinballCoil c_drop_7("c_drop_7",1,3,200,2000);
PinballCoil c_knocker("c_knocker",1,4,100,2000);
PinballCoil c_outhole_kicker("c_outhole_kicker",1,5,400,2000);
PinballCoil c_spare_1("c_spare_1",1,6,50,100);
PinballCoil c_topper_1("c_topper_1",1,7,1000,100);

typedef struct {
  byte swNum; // col * 8 + row
  PinballCoil *coilObject;
} CoilAttributes;
typedef CoilAttributes CoilList[];
// List of Swithches and their object

CoilList coils = {
  //no, PinballSwitch
  {0,&c_spare_1},
  {1,&c_flipper_left},
  {2,&c_flipper_right},
  {3,&c_pop_left},
  {4,&c_pop_right},
  {5,&c_sling_left},
  {6,&c_sling_right},
  {7,&c_saucer_kicker},
  {8,&c_drop_1_2},
  {9,&c_drop_3},
  {10,&c_drop_4_5},
  {11,&c_drop_6},
  {12,&c_drop_7},
  {13,&c_knocker},
  {14,&c_outhole_kicker},
  {15,&c_spare_1},
  {16,&c_topper_1},
};
