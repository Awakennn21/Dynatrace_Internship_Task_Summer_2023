g++ -std=c++17 -Wall -Wextra -I/home/stary/.vcpkg/installed/x64-linux/include \
    -L/home/stary/.vcpkg/installed/x64-linux/lib -lgtest -lnlohmann_json \
    -lboost_date_time -lboost_filesystem UnitTest.cpp -o UnitTest
./UnitTest