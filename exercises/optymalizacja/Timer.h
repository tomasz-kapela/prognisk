#include <iostream>
#include <string>



#include <chrono>
class Timer{
   typedef std::chrono::steady_clock clock_type;
   typedef clock_type::time_point time_point;
   
   std::string name;
   time_point m_start;
   time_point m_stop = time_point::min();
   
public:
   Timer(const std::string & name = "") : name(name), m_start(clock_type::now()){
   }
   void start(){
	   m_start = clock_type::now();
   }
   void stop(){
       m_stop = clock_type::now();
   }
   ~Timer(){
       if(m_stop == time_point::min()) stop();
       std::chrono::duration<double, std::milli> diff= (m_stop -m_start);
       std::cout << name << " : " << diff.count() << " ms. " << std::endl;
      // std::cout << "    . ... " << std::chrono::duration<double, std::micro>(diff).count() << std::endl;
      // std::cout << std::chrono::duration_cast<std::chrono::duration<int, std::micro>>(diff).count() << std::endl;
   }
   
   double durationInMs() {
       return std::chrono::duration<double, std::milli>(clock_type::now() - m_start).count();
   }
};
