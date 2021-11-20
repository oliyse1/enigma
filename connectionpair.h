#ifndef CONNECTIONPAIR_H
#define CONNECTIONPAIR_H

using namespace std;


class ConnectionPair {
   
public:
    int connection_point_1 = 0;
    int connection_point_2 = 0;
    ConnectionPair(){}
    ConnectionPair(int connectionPoint1, int connectionPoint2) : connection_point_1(connectionPoint1), connection_point_2(connectionPoint2){}
};

#endif