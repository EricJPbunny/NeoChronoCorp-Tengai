#ifndef _APP_H
#define _APP_H
class Application {
public:
	Application() {};
	bool Init();
	int Update();
	bool CleanUp();
	~Application() {};
};
#endif
