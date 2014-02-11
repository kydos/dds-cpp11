#include <iostream>

#include "gen/quoter_DCPS.hpp"
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include "util.hpp"
#include <dds/sub/LambdaDataReaderListener.hpp>

#include <thread>         // std::thread, std::this_thread::sleep_for
#include <chrono> 

int main() {
  dds::domain::DomainParticipant dp(0);
  dds::topic::Topic<demo::StockQuote> topic(dp, "StockQuote");
  dds::sub::Subscriber sub(dp);
  dds::sub::DataReader<demo::StockQuote> dr(sub, topic);
  
  dds::sub::LambdaDataReaderListener<demo::StockQuote> listener;

  listener.data_available = [](dds::sub::DataReader<demo::StockQuote>& dr) { 
    auto samples = dr.read();
    std::for_each(samples.begin(), samples.end(),
		  [](const dds::sub::Sample<demo::StockQuote>& s) { 
		    std::cout << s.data() << std::endl;
		  });
    
  };
  
  dr.listener(&listener, dds::core::status::StatusMask::data_available());
  std::this_thread::sleep_for(std::chrono::seconds(10));
  dr.listener(nullptr, dds::core::status::StatusMask::none());

  return 0;
}
