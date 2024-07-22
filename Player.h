#pragma once
class Player
{
	std::string name;
	int score;

	public:
	Player() {
	}

	Player(std::string name) {
		this->name = name;
	}

	Player(std::string name, int score) {
		this->name = name;
		this->score = score;
	}

	std::string getName() {
		return name;
	}

	int getScore() {
		return score;
	}

	void setScore(int score) {
		this->score = score;
	}

	bool operator < (Player &player) {
		return this->score > player.score;
	}

	std::string toString() {
		std::string str = name;
		int iter = 0;
		str.append("#");

		char _0 = '0';

		int i100 = score/ 100 % 10;
		str += (_0 + i100);

		int i10 = score / 10 % 10;
		str += (_0 + i10);

		int i1 = score % 10;
		str += (_0 + i1);

		return str;
	}
};

