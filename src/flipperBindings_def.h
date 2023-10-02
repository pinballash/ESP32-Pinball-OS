typedef struct {
  byte swNumber; // col * 8 + row
  byte coilNumber;
} FlipperBinding;
typedef FlipperBinding FlipperBindingList[];
// List of Swithches and their object

FlipperBindingList flipperCoilBindings = {
  //switch, coil
  {0,0},
  {1,0},
  {2,0},
  {3,0},
  {4,0},
  {5,0},
  {6,0},
  {7,0},
  {8,0},
  {9,0},
  {10,0},
  {11,0},
  {12,0},
  {13,0},
  {14,1}, //sw_flipper_left, c_flipper_left 
  {15,2}, //sw_flipper_right, c_flipper_right
};
