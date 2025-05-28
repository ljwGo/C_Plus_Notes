class Point{
	friend class Line;
	public:
		Point();
		Point(int x, int y);
		int getX() const;
		int getY() const;
		void setAxis(int x, int y);
		void showPosition();
		void move(int xOffset, int yOffset);
	private:
		int x;
		int y;
};
