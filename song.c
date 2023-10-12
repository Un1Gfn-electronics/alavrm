#include "beeper.h"
#include "pitch.tmp.h"

void part_kcsiqr(){

  P("8", PITCH_B_5);
  P("8", PITCH_Cis_6);
  P("16.", PITCH_E_6);
  P("32", 0);
  P("4.", PITCH_E_6);

  P("8", PITCH_B_5);
  P("8", PITCH_Cis_6);
  P("16.", PITCH_E_6);
  P("32", 0);
  P("4", PITCH_Fis_6);
  P("8", 0);

  P("8", PITCH_Gis_6);
  P("16", PITCH_Fis_6);
  P("16", PITCH_E_6);
  P("8", PITCH_Cis_6);
  P("8", PITCH_Gis_6);
  P("4.", PITCH_Fis_6);
  P("16.", PITCH_E_6);
  P("32", 0);
  P("4", PITCH_E_6);
  P("8", 0);

}

void part_xldoqm(){

  P("8", PITCH_E_6);
  P("8", PITCH_Gis_6);
  P("8", PITCH_B_6);
  P("4", PITCH_Cis_7);
  P("16", PITCH_Cis_7);
  P("16", 0);

  P("8", PITCH_Cis_7);
  P("8", PITCH_B_6);
  P("16", PITCH_Gis_6);
  P("32", PITCH_Fis_6);
  P("32", 0);
  P("4", PITCH_Fis_6);
  P("8", 0);

  P("8", PITCH_E_6);
  P("8", PITCH_E_7);
  P("8", PITCH_Dis_7);
  P("4", PITCH_Cis_7);
  P("16", PITCH_Cis_7);
  P("16", 0);

  P("8", PITCH_Cis_7);
  P("8", PITCH_B_6);
  P("8", PITCH_Gis_6);
  P("4", PITCH_Fis_6);
  P("8", 0);

}

void song(){
  part_kcsiqr();
  part_kcsiqr();
  part_xldoqm();
  part_kcsiqr();
}
