#ifndef G20PRG42324_MAIN_FASE2_CLIENTE_BUS_H_
#define G20PRG42324_MAIN_FASE2_CLIENTE_BUS_H_

class Bus {
	private:
    int id;
    char license[10];
    int seats;

public:
	Bus();
	Bus(int id, const char* license, int seats);
    int getId() const;
    const char* getLicense() const;
    int getSeats() const;
    void setId(int id);
    void setLicense(const char* license);
    void setSeats(int seats);
	virtual ~Bus();
	void imprimirBus();
};

#endif
