#ifndef WIND_H
#define WIND_H

class Windows :public Module {
public:
	Windows() {};
	bool Init();
	int PreUpdate();
	int Update();
	int PostUpdate();
	bool CleanUp();
	~Windows() {};
};

#endif