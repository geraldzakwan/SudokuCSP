class Koordinat {
	public:
		Koordinat(float x = 0, float y = 0) {
			this->x = x;
			this->y = y;
		}

	float getX() {
		return x;
	}

	float getY() {
		return y;
	}

	void setX(float x) {
		this->x = x;
	}

	void setY(float y) {
		this->y = y;
	}

	private:
		float x,y;	
};