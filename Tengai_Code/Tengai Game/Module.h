#include "Application.h"

class Module : public Application {
public:
	Module() {};
	bool virtual Init();
	int virtual PreUpdate();
	int virtual Update();
	int virtual PostUpdate();
	bool virtual CleanUp();
	~Module();
};