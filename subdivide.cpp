#include <iostream>

using namespace std;

int main()
{
	// given a static value
	int n = 2;
	int i;
	float s, t = 1.0f;
	s = 0.0f;
	for (i = 0; i < n; i++)
	{
		t = (s + t)/2;
		cout << "value is: " << t << std::endl;
		s = t/2;
	}

}
