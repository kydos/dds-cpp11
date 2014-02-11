#ifndef CEX_UTIL_HPP
#define CEX_UTIL_HPP

std::ostream& operator << (std::ostream& os, const demo::StockQuote& q) {
  os << "("  << q.stock() 
     << ", " << q.xchange() 
     << ", " << q.value()
     << ", " << q.trade_volume() << ")";
  return os;
}

#endif /* CEX_UTIL_HPP */
