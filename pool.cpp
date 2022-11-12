#include "pool.h"

#include "Projectile.h"
#include "ExplosionBullet.h"
#include "Enemy.h"

template<class T>
pool<T>::pool()
{
}

template<class T>
pool<T>::~pool()
{
}

template<class T>
size_t pool<T>::getCount()
{
	return poolOf.getCount();
}


template<class T>
T& pool<T>::PopElement()
{

	T& elem = poolOf.get(poolOf.getCount() - 1);
	poolOf.pop_back();
	return elem;
}

template<class T>
void pool<T>::AddElement(T element)
{
	poolOf.push_back(element);
}


template class pool<Projectile*>;
template class pool<ExplosionBullet*>;
template class pool<Enemy*>;