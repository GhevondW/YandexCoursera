#include <iostream>
#include "stream.h"

int main() {

	std::cout << "DP" << std::endl;

	Stream* s = new Encode
	{
		new Decode
		{
			new Decode
			{
				new Encode
				{
					new FinalizeStream()
				}
			}
		}
	};

	std::string my_value = "code_";

	std::cout << my_value << std::endl;

	s->Pass(my_value);

	std::cout << my_value << std::endl;

	return 0;
}