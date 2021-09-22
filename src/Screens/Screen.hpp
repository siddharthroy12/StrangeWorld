#ifndef SCREEN_HPP
#define SCREEN_HPP

class Screen {
	public:
		virtual void update() {}
		virtual void render() {}
		virtual ~Screen() {}
};


#endif