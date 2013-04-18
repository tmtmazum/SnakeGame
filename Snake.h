#include <vector>
#include <cassert>

template<class t1, class t2>
void DEBUG(t1 s, t2 t);

class pos
{public:
	float x, y;
	pos(float a, float b): x(a), y(b) {}

	int operator-(pos p)
	{
		float sx = x - p.x;
		float sy = y - p.y;
		
		if(sx==0)
		{
			if(sy > 0)
			// UP
				return 2;
			else /* DOWN */ return 3;
		}
		else if(sy == 0)
		{
			if(sx > 0)
			// LEFT
				return 0;
			else /* RIGHT */ return 1;
		
		}
		else
		{
			DEBUG("Dont know what to do with points:", 0);
			DEBUG("x",x);
			DEBUG("y",y);
			DEBUG("p.x",p.x);
			DEBUG("p.y",p.y);

			assert(false);
		}
	} 
	bool operator==(pos p)
	{
		if(p.x==x)
		{
			float diff = (p.y > y)? p.y -y : y - p.y;
			return diff <= 0.001f;
		}
		else if(p.y==y)
		{
			float diff = (p.x > x)? p.x -x : x - p.x;
			return diff <= 0.001f;
		}
		else
		{/*
			float diff1 = (p.y > y)? p.y -y : y - p.y;
			float diff2 = (p.x > x)? p.x -x : x - p.x;
			return diff1 <= 0.001f && diff2 <= 0.001f;*/
			assert(false);
		}
	}
};

class snake
{public:
	std::vector<pos> body;
	float speed;
	enum dir { left, right, up, down };
	dir motion;
	
	snake(float spd)
	{
		speed = spd;
		body.push_back(pos(-0.1f, 0.0f));
		body.push_back(pos(0.1f, 0.0f));		
		motion = left; 
	}	

	void move()
	{
		if(body.front().x >= 1.0f)
		{
			body.insert(body.begin(), pos(-1.0f, body.front().y));	
			body.insert(body.begin(), pos(-1.0f, body.front().y));
		}/*
		if(body.front().x <= -1.0f)
		{
			body.insert(body.begin(), pos(1.0f, body.front().y));
		}
		else if(body.front().y >= 1.0f)
		{
			body.insert(body.begin(), pos(body.front().x, -1.0f));
		}
		else if(body.front().y <= -1.0f)
		{
			body.insert(body.begin(), pos(body.front().x, 1.0f));
		}*/

		body.front().x += (motion==right)? speed : (motion==left)? -speed : 0;
		body.front().y += (motion==up)? speed : (motion==down)? -speed : 0;

		dir d = (dir) (body.at(body.size()-2) - body.back());

		
		if(body.back() == body.at(body.size()-2) )
		{	
			body.pop_back();
		}
		else
		{
			body.back().x += (d==left)? speed : (d==right)? -speed : 0;
			body.back().y += (d==up)? speed : (d==down)? -speed : 0;		
		}	
	}

	void change_direction(dir d) 
	{ 
		body.insert(body.begin(), body.front());		
		motion = d; 
	}
};
