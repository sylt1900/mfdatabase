#include "Element.h"

void Element::set_element(int type, int datasize, std::string data)
{
    this->type=type;
    this->datasize=datasize;
    this->data=data;
}

void Element::show_element()
{
    PrintScreen(this->data+"\n");
    PrintScreen(std::to_string(this->type)+"\n");
    PrintScreen(std::to_string(this->datasize)+"\n");
}
