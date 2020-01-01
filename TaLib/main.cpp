#include <iostream>
#include <time.h>
#include <assert.h>
#include "ta_libc.h"

//ta-lib示例
int main()
{
	std::cout << "ta-lib test" << std::endl;

	// init ta-lib context
	TA_RetCode retcode;
	retcode = TA_Initialize();
	assert(retcode == TA_SUCCESS);

	// comput moving average price
	TA_Real close_price_array[400] = { 0 };
	// construct random price
	srand((unsigned)time(0));
	for (int i = 0; i < 400; i++)
		close_price_array[i] = rand() % 50 + 100;

	TA_Real	out[400] = { 0 };
	TA_Integer out_begin = 0;
	TA_Integer out_nb_element = 0;

	retcode = TA_MA(0, 399,
		&close_price_array[0],
		30, TA_MAType_SMA,
		&out_begin, &out_nb_element, &out[0]);

	assert(retcode == TA_SUCCESS);

	std::cout << "---- compute output ----" << std::endl;
	std::cout << "out_benin_index: " << out_begin << std::endl;
	std::cout << "out_nb_element:" << out_nb_element << std::endl;
	std::cout << "out price array: " << std::endl;
	for (auto& price : out)
		std::cout << price << " ";

	retcode = TA_Shutdown();
	assert(retcode == TA_SUCCESS);

	std::cin.get();

	return 0;
}
