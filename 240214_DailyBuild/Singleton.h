#ifndef __SINGLETON_H__
#define __SINGLETON_H__

#define DELETE_PTR(p) { if(!p) delete p; }

template<class T>
class ippSingleton
{
	// -- How to use this class -- //
	//
	// class mySingleton : public Singleton<mySingleton>
	//	{
	//		// declare stuff
	//	};
private:
	static T *instance;
public:
	~ippSingleton()
	{
		DELETE_PTR(instance);
	}

	static T* GetInstance(void)
	{
		if(!instance) instance = new T;
		return instance;
	}
};

template<class T>
T* ippSingleton<T>::instance = 0;

#endif