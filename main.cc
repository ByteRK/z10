#include <cdroid.h>
#include <string>
#include <cdlog.h>
#include <iostream>
#include <homewindow.h>
class MYWindow:public Window{
public:
   MYWindow():Window(0,0,-1,-1){}
   void onDraw(Canvas&canvas){
      canvas.set_font_size(128);
      canvas.move_to(100,100);
      canvas.set_source_rgb(1,0,0);
      canvas.show_text("28");
      canvas.fill();
   }
};

///////////////////////////////////////////////////////////////////////////
class CTickHanlder : public EventHandler{
public:
   CTickHanlder() {
   }

   //10 ms 执行一次
   virtual int checkEvents() {
      static int64_t s_last_tick = SystemClock::uptimeMillis();        
      int64_t now_tick = SystemClock::uptimeMillis();

      if (now_tick - s_last_tick >= 1000) {
         s_last_tick = now_tick;
         // WindowTime::ins()->updTime();
         //LOGD("checkEvents()" );
         return 1;
      }

      return 0;
   }

   // 1s 执行一次
   virtual int handleEvents() {
      static int64_t s_last_tick = SystemClock::uptimeMillis();
      int64_t now_tick = SystemClock::uptimeMillis();

      static bool flag = false;

      if( now_tick - s_last_tick >= 10000) {
         LOGD("handleEvents() ");

         Activity_header::ins()->checkState(flag);

         s_last_tick = now_tick;
         return 1;
      }
      
      return 0;
   }
private:
};

int main(int argc,const char*argv[]){
    App app(argc,argv);
    int64_t now_tick = SystemClock::uptimeMillis();

    Window*w=new HomeWindow();
    std::string str=app.getString("@string/weathertips");
    LOGD("str=%s",str.c_str());

    CTickHanlder th;
    app.addEventHandler(&th);
    
    return app.exec();
}

