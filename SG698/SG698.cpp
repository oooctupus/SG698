#include "HEADERS.h"

int main()
{
	st_length_domain A;
	uint16* B;
	A.u14_length=0;
	A.u2_status=LEN_RESERVE_3;
	B=(uint16*)&A;
	//std::cout<<std::hex<<A<<std::endl;
	std::cout<<std::hex<<*(B)<<std::endl;
	return 0;
}
