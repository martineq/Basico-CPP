// mon.h
#ifndef  MON_INC
#define  MON_INC
 
#include "mongoose/mongoose.h" //Header de la librería

class Mon {
   public:
   void EjemploUno();

   private:
   static int ev_handler(struct mg_connection *, enum mg_event);
}; 
 
#endif
