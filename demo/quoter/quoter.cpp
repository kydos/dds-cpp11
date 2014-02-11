#include "gen/quoter_DCPS.hpp"
#include <unistd.h>
#include <stdlib.h>
#include <iostream>

#include "util.hpp"

int main(int, char**) {
  dds::domain::DomainParticipant dp(0);
  dds::topic::Topic<demo::StockQuote> topic(dp, "StockQuote");
  dds::pub::Publisher pub(dp);
  dds::pub::DataWriter<demo::StockQuote> dw(pub, topic);
  srand(clock());
  while (true) {
    demo::StockQuote quote("NUVO", "NYSE", 1000.0F / ((rand() * 1.0F) / RAND_MAX), rand());
    std::cout << quote << std::endl;
    dw << quote;
    sleep(1);
  }
  return 0;
}
