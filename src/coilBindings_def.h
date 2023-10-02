typedef struct {
  byte swNumber; // col * 8 + row
  byte coilNumber;
} CoilBinding;
typedef CoilBinding CoilBindingList[];
// List of Swithches and their object

CoilBindingList switchCoilBindings = {
  //switch, coil
  {0,0},
  {1,0},
  {2,0},
  {3,0},
  {4,5},  //sw_sling_left, c_sling_left
  {5,6},  //sw_sling_right, c_sling_right
  {6,3},  //sw_pop_left, c_pop_left
  {7,4},  //sw_pop_right, c_pop_right
  {8,0},
  {9,0},
  {10,0},
  {11,0},
  {12,0},
  {13,0},
  {14,0},
  {15,0},
  {16,0},
  {17,0},
  {18,0},
  {19,0},
  {20,0},
  {21,0},
  {22,0},
  {23,0},
  {24,0},
  {25,0},
  {26,0},
  {27,0},
  {28,0},
  {29,0},
  {30,0},
  {31,0},
  {32,0},
  {33,0},
  {34,0},
  {35,0},
  {36,0},
  {37,0},
  {38,0},
  {39,0},  
};
