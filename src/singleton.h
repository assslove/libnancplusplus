#ifndef _SINGLETON_H
#define _SINGLETON_H

/**
 *	@brief	 单例模式基类
 *	@details 只允许存在一个实例的类必须从该类继承实现
 */
template<typename T>
class Singleton
{
 	protected:
		/**
		 *	@brief	构造函数
		 */
		Singleton() {}
		/**
		 *	@brief	析构函数
		 */
		~Singleton() {}

	private:
		/**
		 *	@brief	 拷贝构造函数
		 *	@details 私有成员只声明不定义,杜绝任何访问,不允许拷贝
		 */
		Singleton(const Singleton &);
		/**
		 *	@brief	 赋值拷贝操作符
		 *	@details 私有成员只声明不定义,杜绝任何访问,不允许赋值
		 */
		Singleton& operator= (const Singleton &);

	public:
		/**
		 *	@brief	获取唯一实例
		 *	@return 返回实例的引用
		 */
		static T& getInstance()
		{
			if(!s_instance)
			{
				s_instance = new T();
			}

			return *s_instance;
		}
		/**
		 *	@brief	删除唯一实例
		 */
		static void delInstance()
		{
			if(s_instance)
			{
				delete s_instance;
				s_instance = 0;
			}
		}

 	private:
		/**
		 *	@brief	单例唯一实例
		 */
		static T *s_instance;
};

template<typename T>
T* Singleton<T>::s_instance = 0;

#endif /* end _SINGLETON_H */
