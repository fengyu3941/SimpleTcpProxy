This is a simple tcp proxy based on boost::asio.

Use Cmake to generate a build system. 
cd tcpproxy
mkdir build
cd build
cmake -DBOOST_ROOT="your_boost_root_path" -DBOOST_INCLUDEDIR="your_boost_includedir_path" ../

Some Problem need fix:
1. cancel long running asynchronous connect after a period of time
2. support ipv6

