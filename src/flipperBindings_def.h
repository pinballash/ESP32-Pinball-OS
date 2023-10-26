typedef struct {
  byte swNumber; // col * 8 + row
  byte coilNumber;
} FlipperBinding;
typedef FlipperBinding FlipperBindingList[];
// List of Swithches and their object

FlipperBindingList flipperCoilBindings = {
  //switch, coil
  {0,0},
  {1,1}, //sw_flipper_left, c_flipper_left 
  {2,2}, //sw_flipper_right, c_flipper_right
};
