#ifndef G20PRG42324_MAIN_FASE2_CLIENTE_PATH_H_
#define G20PRG42324_MAIN_FASE2_CLIENTE_PATH_H_

class Path {
private:
	int id;
	int initialstop;
	int finalstop;
public:
	Path();
	Path(int id, int initialstop, int finalstop);
	int getId() const;
	int getInitialStop() const;
	int getFinalStop() const;
	void setId(int id);
	void setInitialStop(int initialstop);
	void setFinalStop(int finalstop);
	virtual ~Path();
	void imprimirPath();
};

#endif
