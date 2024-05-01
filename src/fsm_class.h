#ifndef _FSM_CLASS_H_
#define _FSM_CLASS_H_

class FSM_Class{//Definición de la clase
  private:
  int STATE_PRINCIPAL;

  public:
  enum STATE{
    INIT,
    READ_SP,
    READ_SENSORS,
    ACT_VALV,
    SHOW_SCREEN,
    UPL_DATA  
  };
  void OPERATION();
  void SET_STATE(int N);

};
#endif