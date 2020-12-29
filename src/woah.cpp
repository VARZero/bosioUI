#include "./include/tinyxml2/tinyxml2.h"
#include <stdio.h>
//tinyxml2::XMLDocument etml;

//etml.LoadByText();

void inElement(tinyxml2::XMLNode* Elem){
    tinyxml2::XMLElement* inElem;

    for(tinyxml2::XMLNode* inside = Elem->FirstChild(); inside != 0; inside = (tinyxml2::XMLNode*)inside->NextSibling()){
        if (inside->ToDeclaration()){continue;}
        printf("%s ", inside->Value());
        if (inElem = inside->ToElement()){
            printf("aa ");
            inElement(inside);
        }
    }
}

void vboxProcess(){

}

void hboxProcess(){

}

int main(){
    tinyxml2::XMLDocument ezml;
    //ezml.Parse();
    ezml.LoadFile("../bosioTML test/example1.xml");
    tinyxml2::XMLError err = ezml.ErrorID();
    printf("%d\n", err);

    inElement(&ezml);
}
