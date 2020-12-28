#include "./include/tinyxml2/tinyxml2.h"
#include <stdio.h>
//tinyxml2::XMLDocument etml;

//etml.LoadByText();

int main(){
    tinyxml2::XMLDocument ezml;
    //ezml.Parse();
    ezml.LoadFile("a.xml");
    tinyxml2::XMLError err = ezml.ErrorID();
    printf("%d\n", err);

    tinyxml2::XMLNode* xml = ezml.FirstChildElement("bosioBoard");
    for(tinyxml2::XMLNode* i = xml; i != 0; i = (tinyxml2::XMLNode*)i->NextSibling()){
        printf("%s ", i->Value());
    }
}
