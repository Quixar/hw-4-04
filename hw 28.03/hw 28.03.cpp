#include <iostream>
#include <vector>
using namespace std;

__interface ISpeakable {
	virtual void speak() = 0;
};

__interface ISwimable {
	virtual void swim() = 0;
};

__interface IJumpable {
	virtual void jump() = 0;
};

class Herbivore {
protected:
	int weight;
	bool live;
public:
	Herbivore(int weight) {
		setWeight(80);
		setLive(true);
	}
	virtual void setWeight(int weight) {
		this->weight = weight;
	}
	virtual void setLive(bool live) {
		this->live = live;
	}
	virtual bool getLive() const {
		return live;
	}
	virtual int getWeight() const {
		return weight;
	}
	virtual void eatGrass() {
		weight += 10;
	}
};

class Carnivore {
protected:
	int power;
public:
	Carnivore(int power) {
		setWeight(100);
	}
	virtual void setWeight(int power) {
		this->power = power;
	}
	virtual void eat(Herbivore& herbivore) {
		if (power > herbivore.getWeight()) {
			power += 10;
			herbivore.setLive(false);
		}
		else {
			power -= 10;
		}
	}
};

class Wildebeest : public Herbivore, public ISpeakable, public IJumpable {
public:
	Wildebeest() : Herbivore(weight) {}
	void speak() {
		cout << "wildebeest make sound\n";
	}
	void jump() {
		cout << "wildebeest is jumping\n";
	}

};

class Bison : public Herbivore, public ISpeakable {
public:
	Bison() : Herbivore(weight) {}
	void speak() {
		cout << "Bison make sound\n";
	}
};

class Lion : public Carnivore, public ISpeakable, public IJumpable, public ISwimable {
public:
	Lion() : Carnivore(power) {}
	void eat(Wildebeest& wildebeest) {
		if (power > wildebeest.getWeight()) {
			power += 10;
			wildebeest.setLive(false);
		}
		else {
			power -= 10;
		}
	}
	void speak() {
		cout << "lion make sound\n";
	}
	void jump() {
		cout << "lion is jumping\n";
	}
	void swim() {
		cout << "lion is swiming\n";
	}
};

class Wolf : public Carnivore, public ISpeakable, public IJumpable, public ISwimable {
public:
	Wolf() : Carnivore(power) {}
	void eat(Bison& bison) {
		if (power > bison.getWeight()) {
			power += 10;
			bison.setLive(false);
		}
		else {
			power -= 10;
		}
	}
	void speak() {
		cout << "wolf make sound\n";
	}
	void jump() {
		cout << "wolf is jumping\n";
	}
	void swim() {
		cout << "wolf is swiming\n";
	}
};

class Continent {
protected:
	string name;
	vector<Herbivore> herbivores;
	vector<Carnivore> carnivores;
public:
	Continent(string name) {
		setName("Continent");
	}
	void setName(string name) {
		this->name = name;
	}
	virtual void addHerbivore(Herbivore& herbivore) {
		herbivores.push_back(herbivore);
	}
	virtual void addCarnivore(Carnivore& carnivore) {
		carnivores.push_back(carnivore);
	}
	vector<Herbivore> getHerbivores() const {
		return herbivores;
	}
	vector<Carnivore> getCarnivores() const {
		return carnivores;
	}
};

class Africa : public Continent {
public:
	Africa() : Continent("Africa") {}

};

class NorthAmerica : public Continent {
public:
	NorthAmerica() : Continent("North America") {}
};

class AnimalWorld {
private:
	vector<Continent> continents;
public:
	void addContinent(Continent& continent) {
		continents.push_back(continent);
	}
	void mealsHerbivores() {
		for (auto continent : continents) {
			for (auto& herbivore : continent.getHerbivores()) {
				herbivore.eatGrass();
			}
		}
	}
	void nutritionCarnivores() {
		for (auto& continent : continents) {
			for (auto& carnivore : continent.getCarnivores()) {
				for (auto& herbivore : continent.getHerbivores()) {
					if (herbivore.getLive()) {
						carnivore.eat(herbivore);
						break;
					}
				}
			}
		}
	}
};

int main() {
	Africa africa;
	NorthAmerica northAmerica;

	Wildebeest wildebeest;
	Bison bison;
	Lion lion;
	Wolf wolf;

	wildebeest.jump();
	wildebeest.speak();
	bison.speak();
	lion.jump();
	lion.speak();
	lion.swim();
	wolf.jump();
	wolf.speak();
	wolf.swim();

	africa.addHerbivore(wildebeest);
	africa.addCarnivore(lion);
	northAmerica.addHerbivore(bison);
	northAmerica.addCarnivore(wolf);

	AnimalWorld world;

	world.addContinent(africa);
	world.addContinent(northAmerica);

	world.mealsHerbivores();

	world.nutritionCarnivores();
}