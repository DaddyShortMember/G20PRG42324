#ifndef G20PRG42324_MAIN_FASE2_CLIENTE_ROUTE_H_
#define G20PRG42324_MAIN_FASE2_CLIENTE_ROUTE_H_

class Route {
private:
    int id;
    int pathid;
    int currentstopid;
    int nextstopid;
    int ordernumber;

public:
    Route();
    Route(int id, int pathid, int currentstopid, int nextstopid, int ordernumber);
    int getId() const;
    int getPathId() const;
    int getCurrentStopId() const;
    int getNextStopId() const;
    int getOrderNumber() const;
    void setId(int id);
    void setPathId(int pathid);
    void setCurrentStopId(int currentstopid);
    void setNextStopId(int nextstopid);
    void setOrderNumber(int ordernumber);
    virtual ~Route();
    void imprimirRoute() const;
};

#endif
