#include "Animal.h"
#include "AnimalFactory.h"

class Farm 
{
public:

	Farm();

	Farm(const Farm& other);
	Farm& operator = (const Farm& other);

	Farm(Farm&& other) noexcept;
	Farm& operator = (Farm&& other) noexcept;

	~Farm();

	void addAnimal(AnimalType animalType);
	void addAnimal(const Animal& animal);

	void roarAll() const;

	AnimalType getTypeByIndex(unsigned index) const;

private:
	Animal** animals;
	size_t count;
	size_t capacity;

	void copyFrom(const Farm& other);
	void moveFrom(Farm&& other);
	void free();

	void resize();
};
