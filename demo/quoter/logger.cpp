#include <iostream>

#include "gen/quoter_DCPS.hpp"
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include "util.hpp"

int main() {
  dds::domain::DomainParticipant dp(0);
  dds::topic::Topic<demo::StockQuote> topic(dp, "StockQuote");
  dds::sub::Subscriber sub(dp);
  dds::sub::DataReader<demo::StockQuote> dr(sub, topic);
  
  dds::core::cond::WaitSet ws;
  dds::sub::cond::ReadCondition rc(dr, dds::sub::status::DataState::new_data());
  ws += rc;
  /*
    The read_next_sample operation is semantically equivalent to the read
    operation where the input Data sequence has max_len=1, the
    sample_states=NOT_READ, the view_states=ANY_VIEW_STATE, and the
    instance_states=ANY_INSTANCE_STATE.
  */

  while (true) {
    ws.wait();
    auto samples = dr.read();
    std::for_each(samples.begin(), samples.end(),
		  [](const dds::sub::Sample<demo::StockQuote>& s) { 
		    std::cout << s.data() << std::endl;
		  });
  }
  return 0;
}
