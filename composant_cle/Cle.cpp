#include <pybind11/pybind11.h>
#include "micro-ecc/uECC.h"

class Cle
{   
    private:
        char * private_key;
        char * public_key;
    public:
        Cle() { this->private_key = (char*) malloc(64*sizeof(char));
                this->public_key = (char*) malloc(2*64*sizeof(char));
                }
        ~Cle() { 
            free(this->private_key); 
            free(this->public_key);}

        void initialize(char* num) {
            for(int i=0;i<64;i++){
                this->private_key[i] = num[i];
            }
        }
        char* getPrivateKey() { 
            return this->private_key;
        }
        char* getPublicKey() {
            uECC_make_key((uint8_t *)this->public_key, (uint8_t *) this->private_key, uECC_secp256k1());
            return this->public_key;
         }

};

namespace py = pybind11;

PYBIND11_MODULE(Cle,greetings)
{
  
   // bindings to cle composant class
    py::class_<Cle>(greetings, "Cle")
        .def(py::init<>())
        .def("initialize", &Cle::initialize)
        .def("getPrivateKey", &Cle::getPrivateKey)
        .def("getPublicKey", &Cle::getPublicKey);
}