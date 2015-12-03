#include "my17.h"

using namespace my17;

static R* s_r_instance = NULL;
static D* s_d_instance = NULL;

R* R::getInstance()
{

    if( s_r_instance == NULL )
        s_r_instance = new R();
    return s_r_instance;

}



D* D::getInstance()
{

    if( s_d_instance == NULL )
        s_d_instance = new D();
    return s_d_instance;

}

